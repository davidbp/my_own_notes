
import random, util
import numpy as np

from queue import *

from game import Directions
from game import Agent

######################################################################

class MLNN_RandomAgent(Agent):
  """
    An MLNN random agent (run with "python pacman.py -p MLNN_RandomAgent")
  """

  def __init__( self ):
    return

  def getAction(self, curGameState):
    """
    Compute the action to take in the current state
    """

    # Legal actions (although an action lead to a closed path, it is legal)
    legalActions = curGameState.getLegalActions()

    return random.choice(legalActions)

######################################################################

class MLNN_LearnedFromDataAgent(Agent):
  """
    An MLNN agent learned from data
      (run with "python pacman.py -p MLNN_LearnedFromDataAgent -a nf=NFeatures,fm=FNameModel,sa=True")
  """

  def __init__( self, nf=0, fm='FNameModel', sa=False ):
    ##############################################
    ### nf: Number of features (MANDATORY)
    ### fm: Filename of the Model (MANDATORY)
    ### sa: StopAllowed (OPTIONAL)
    ##############################################

    # Initial number of food dots
    self.numInitFood = None

    # Grid graph
    self.Nodes = None

    # Set parameters to object variables
    self.NFeatures = int(nf);
    self.FNameModel = fm;
    if isinstance(sa,str):  ### the value of 'sa' has been set in the arguments
      self.stopAllowed = (sa == 'True' or sa == 'true' or sa == '1')
    else:
      self.stopAllowed = sa

    # Load the model
    import pickle
    self.model = pickle.load(open(self.FNameModel, 'rb'))


  def getAction(self, curGameState):
    """
    Compute the action to take in the current state
    """

    # Legal actions (although an action lead to a closed path, it is legal)
    legalActions = curGameState.getLegalActions()
    #print(legalActions)

    # Stores the initial nomber of foods (only once)
    if self.numInitFood is None:
      self.numInitFood = curGameState.getNumFood()

    # Construct node graph for subsequent BFS (only once)
    if self.Nodes is None:
      self.Nodes = constructGridGraph(curGameState)

    # Remove 'Stop' from legalActions (if required)
    if 'Stop' in legalActions and not self.stopAllowed:
      legalActions.remove('Stop')

    # Specific variables related to the labels
    # normalizeConfidenceValues forces the confidence values to sum up to 1 (without changing the maximum)
    normalizeConfidenceValues = True      ### [CRITICAL POINT] Normalize confidence values to sum up to 1
    # sortedLabels is the list of all possible labels SORTED by RELEVANCE (we prefer the first one to the second, etc)
    sortedLabels    = [+2, +1, -1]        ### [CRITICAL POINT] SORTED by RELEVANCE (don't forget the commas!!!)

    # Move according to model output
    predictedLabelValues = [self.getDecision(curGameState, a) for a in legalActions]
    vDecisionValues = np.array(predictedLabelValues).T
    predictedLabels = vDecisionValues[0]
    predictedValues  = vDecisionValues[1]
    #
    selectedAction = None
    selectedValue  = None
    for i in range(len(sortedLabels)):                                          ### Search first for the most promising ones
      for j in range(len(predictedLabels)):
        if (sortedLabels[i] == predictedLabels[j] and \
            (selectedValue is None  or  selectedValue < predictedValues[j])):   ### Untie by predictedValues
          selectedAction = legalActions[j]
          selectedValue  = predictedValues[j]
      if selectedAction is not None:
        return selectedAction

    # We should never arrive here...
    return random.choice(legalActions)


  def getDecision(self, state, action):
    (closestGhost1Distance, closestGhost2Distance, closestIntersectionDistance, closestFoodDistance, closestCapsuleDistance, \
     actionClosestToGhost1, actionClosestToGhost2, actionClosestToFood, actionClosestToCapsule, \
     closestGhost1Scared, closestGhost2Scared, pctProgress) = \
      getCandidateFeatures(self.Nodes, self.numInitFood, state, action)

    # Create input vector as a row numpy array
    x = np.zeros((1,self.NFeatures))
    x[0][0] = 1 / closestGhost1Distance
    x[0][1] = closestGhost1Scared
    x[0][2] = actionClosestToGhost1
    x[0][3] = actionClosestToFood
    for i in range(self.NFeatures-4):
      x[0][4+i] = np.random.rand()
    features = x

    # Obtain the predictions of the model
    predictedLabel = self.model.getPredictedLabels(features)[0]
    decisionValues = self.model.getDecisionValues(features)[0]
    # Normalize the predictions so as to sum up 1
    sumPredictionVector = np.sum(decisionValues)
    if sumPredictionVector > 0: ### We do not want to change the index of the maximum (if sumPredictionVector < 0)
      decisionValues = decisionValues / sumPredictionVector
    decisionValue = np.max(decisionValues)

    return [predictedLabel, decisionValue]


######################################################################
### YOU DO NOT HAVE TO MODIFY ANYTHING FROM HERE!!!
######################################################################


######################################################################
### Auxiliar variables, classes and functions

# Search functions will return maxDistance if they do not find the objective
maxDistance = 999


###
class Node:
  def __init__(self, pos, distance=-1):
    self.position = pos
    self.x = pos[0]
    self.y = pos[1]
    self.distance = distance
    self.neighbors = []


###
def constructGridGraph(state):
  width = state.getFood().width
  height = state.getFood().height
  debug = 'Constructing a grid graph of size (%d, %d) ...\n' % (width, height)
  nodes = []

  # loop over the whole grid and create a node at each corresponding place
  for x in range(width):
    nodes.append([])
    for y in range(height):
      nodes[x].append(Node((x,y)))

  # debugging counters
  edgeCount = 0
  vertexCount = 0

  # loop over each node and add their valid neighboring nodes to their neighbors list
  for x in range(width):
    for y in range(height):
      # debugging only
      if not state.hasWall(x, y):
        vertexCount += 1
      # looping from  1 to  4 will give adjacent x coordinates
      # looping from -1 to -4 will give adjacent y coordinates
      # first element is needed but irrelevant beacuse of the differences in neg. & pos. indexing
      d = [666, 1,0, -1,0]
      for k in range(1, 4 + 1):
        cx = x + d[k]
        cy = y + d[-k]
        # check that this position is still within the map
        if cx >= 0 and cx < width:
          if cy >= 0 and cy < height:
            # make sure it is also a value cell pacman can walk on
            if not state.hasWall(cx, cy):
              edgeCount += 1
              nodes[x][y].neighbors.append(nodes[cx][cy])

  debug += 'Found %d vertices and %d edges.' % (vertexCount, edgeCount/2)
  #print(debug)
  return nodes


###
def getCandidateFeatures(nodes, numInitFood, state, action):
  # Distance to X = Number of Movements to reach X (without repeating position)

  nGhostsToFind = 2
  ghostDistance, ghostScared = getInfoClosestGhosts(nodes, state, action, nGhostsToFind=nGhostsToFind)
  if action != Directions.STOP:
    ghostDistanceSTOP, ghostScaredSTOP = getInfoClosestGhosts(nodes, state, Directions.STOP, nGhostsToFind=nGhostsToFind)

  # ghost proximity
  closestGhost1Distance = ghostDistance[0]  #float(getClosestGhostDistance(nodes, state, action))
  closestGhost2Distance = ghostDistance[1]

  # intersection proximity
  closestIntersectionDistance = float(getClosestIntersectionDistance(nodes, state, action))

  # food proximity
  closestFoodDistance = float(getClosestFoodDistance(nodes, state, action))

  # capsule proximity
  closestCapsuleDistance = float(getClosestCapsuleDistance(nodes, state, action))

  # actionClosestToGhostX: 1 if moving in this direction will get pacman closest to the closest ghostX in ths direction, 0 otherwise
  actionClosestToGhost1 = 0
  if action != Directions.STOP and (closestGhost1Distance+1 == ghostDistanceSTOP[0] or closestGhost1Distance+1 == ghostDistanceSTOP[1]):
    actionClosestToGhost1 = 1
  actionClosestToGhost2 = 0
  if action != Directions.STOP and (closestGhost2Distance+1 == ghostDistanceSTOP[1] or closestGhost2Distance+1 == ghostDistanceSTOP[1]):
    actionClosestToGhost2 = 1

  # actionClosestToFood: 1 if moving in this direction will get pacman closest to food, 0 otherwise
  actionClosestToFood = 0
  if action != Directions.STOP and closestFoodDistance + 1 == getClosestFoodDistance(nodes, state, Directions.STOP):
    actionClosestToFood = 1

  # actionClosestToCapsule: 1 if moving in this direction will get pacman closest to capsule, 0 otherwise
  actionClosestToCapsule = 0
  if action != Directions.STOP and closestCapsuleDistance + 1 == getClosestCapsuleDistance(nodes, state, Directions.STOP):
    actionClosestToCapsule = 1

  # closestGhostScared: 1 if the closest ghost in this direction is scared, 0 otherwise
  closestGhost1Scared = int(ghostScared[0])
  closestGhost2Scared = int(ghostScared[1])

  # total percentage of food collected
  pctProgress = 1.0 - (float(state.generateSuccessor(0, action).getNumFood()) / numInitFood)

  return (closestGhost1Distance, closestGhost2Distance, closestIntersectionDistance, closestFoodDistance, closestCapsuleDistance, \
          actionClosestToGhost1, actionClosestToGhost2, actionClosestToFood, actionClosestToCapsule, \
          closestGhost1Scared, closestGhost2Scared, pctProgress)


###
def getInfoClosestGhosts(nodes, state, action, nGhostsToFind=1):
  # get the relevant positions
  curPosition = state.getPacmanState().getPosition()
  newPosition = state.generateSuccessor(0, action).getPacmanState().getPosition()

  # setup data structures for the search
  openQueue = Queue()
  closedSet = set()

  if action != Directions.STOP:
    closedSet.add(curPosition)  # ensures we 'close of our back' and start searching only in the given direction
    root = nodes[newPosition[0]][newPosition[1]]
    root.distance = 1
    openQueue.put(root)
  else:
    root = nodes[curPosition[0]][curPosition[1]]
    root.distance = 1
    openQueue.put(root)

  # control and info variables
  maxGhosts = len(state.getGhostStates())
  ghostDistance = maxDistance * np.ones(maxGhosts)
  ghostScared = np.zeros(maxGhosts)
  nGhostsFound = 0

  # start the BF search
  while openQueue.qsize() > 0:
    # pop new node and add it to the closed set
    currentNode = openQueue.get()
    closedSet.add(currentNode.position)

    # check for our objective
    for ghost in state.getGhostStates():
      # round ghost positions in case they are inbetween nodes
      # this happens when they are scared and have reduced movement speed
      if round(ghost.getPosition()[0]) == currentNode.position[0]:
        if round(ghost.getPosition()[1]) == currentNode.position[1]:
          ghostDistance[nGhostsFound] = currentNode.distance
          if ghost.scaredTimer > 0:
            ghostScared[nGhostsFound] = 1
          nGhostsFound = nGhostsFound + 1
          if nGhostsFound == nGhostsToFind:
            return ghostDistance, ghostScared

    for candidateNode in currentNode.neighbors:
      # increment distance for every edge you cross in the node-grid-graph
      candidateNode.distance = currentNode.distance + 1
      if not candidateNode.position in closedSet:
        openQueue.put(candidateNode)

  # Not enough ghosts were found in this direction
  return ghostDistance, ghostScared


###
def getClosestGhostDistance(nodes, state, action):
  # get the relevant positions
  curPosition = state.getPacmanState().getPosition()
  newPosition = state.generateSuccessor(0, action).getPacmanState().getPosition()

  # setup data structures for the search
  openQueue = Queue()
  closedSet = set()

  if action != Directions.STOP:
    closedSet.add(curPosition)  # ensures we 'close of our back' and start searching only in the given direction
    root = nodes[newPosition[0]][newPosition[1]]
    root.distance = 1
    openQueue.put(root)
  else:
    root = nodes[curPosition[0]][curPosition[1]]
    root.distance = 1
    openQueue.put(root)

  # start the BF search
  while openQueue.qsize() > 0:
    # pop new node and add it to the closed set
    currentNode = openQueue.get()
    closedSet.add(currentNode.position)

    # check for our objective
    for ghost in state.getGhostStates():
      # round ghost positions in case they are inbetween nodes
      # this happens when they are scared and have reduced movement speed
      if round(ghost.getPosition()[0]) == currentNode.position[0]:
        if round(ghost.getPosition()[1]) == currentNode.position[1]:
          return currentNode.distance

    for candidateNode in currentNode.neighbors:
      # increment distance for every edge you cross in the node-grid-graph
      candidateNode.distance = currentNode.distance + 1
      if not candidateNode.position in closedSet:
        openQueue.put(candidateNode)

  # No ghost was found in this direction
  return maxDistance


###
def getClosestFoodDistance(nodes, state, action):
  # get the relevant positions
  curPosition = state.getPacmanState().getPosition()
  newPosition = state.generateSuccessor(0, action).getPacmanState().getPosition()

  # setup data structures for the search
  openQueue = Queue()
  closedSet = set()

  if action != Directions.STOP:
    closedSet.add(curPosition)  # ensures we 'close of our back' and start searching only in the given direction
    root = nodes[newPosition[0]][newPosition[1]]
    root.distance = 1
    openQueue.put(root)
  else:
    root = nodes[curPosition[0]][curPosition[1]]
    root.distance = 1
    openQueue.put(root)

  # start the BF search
  while openQueue.qsize() > 0:
    # pop new node and add it to the closed set
    currentNode = openQueue.get()
    closedSet.add(currentNode.position)

    # check for our objective
    if state.hasFood(currentNode.x, currentNode.y):
      return currentNode.distance

    for candidateNode in currentNode.neighbors:
      # increment distance for every edge you cross in the node-grid-graph
      candidateNode.distance = currentNode.distance + 1
      if not candidateNode.position in closedSet:
        openQueue.put(candidateNode)

  # No food was found in this direction
  return maxDistance


###
def getClosestIntersectionDistance(nodes, state, action):
  # get the relevant positions
  curPosition = state.getPacmanState().getPosition()
  newPosition = state.generateSuccessor(0, action).getPacmanState().getPosition()

  # setup data structures for the search
  openQueue = Queue()
  closedSet = set()

  if action != Directions.STOP:
    closedSet.add(curPosition)  # ensures we 'close of our back' and start searching only in the given direction
    root = nodes[newPosition[0]][newPosition[1]]
    root.distance = 1
    openQueue.put(root)
  else:
    root = nodes[curPosition[0]][curPosition[1]]
    root.distance = 1
    openQueue.put(root)

  # start the BF search
  while openQueue.qsize() > 0:
    # pop new node and add it to the closed set
    currentNode = openQueue.get()
    closedSet.add(currentNode.position)

    # check for our objective
    if len(currentNode.neighbors) >= 3:
      return currentNode.distance

    for candidateNode in currentNode.neighbors:
      # increment distance for every edge you cross in the node-grid-graph
      candidateNode.distance = currentNode.distance + 1
      if not candidateNode.position in closedSet:
        openQueue.put(candidateNode)

  # No intersection was found in this direction
  return maxDistance


###
def getClosestCapsuleDistance(nodes, state, action):
  # get the relevant positions
  curPosition = state.getPacmanState().getPosition()
  newPosition = state.generateSuccessor(0, action).getPacmanState().getPosition()

  # setup data structures for the search
  openQueue = Queue()
  closedSet = set()

  if action != Directions.STOP:
    closedSet.add(curPosition)  # ensures we 'close of our back' and start searching only in the given direction
    root = nodes[newPosition[0]][newPosition[1]]
    root.distance = 1
    openQueue.put(root)
  else:
    root = nodes[curPosition[0]][curPosition[1]]
    root.distance = 1
    openQueue.put(root)

  # start the BF search
  while openQueue.qsize() > 0:
    # pop new node and add it to the closed set
    currentNode = openQueue.get()
    closedSet.add(currentNode.position)

    # check for our objective
    for capsule in state.getCapsules():
      if capsule == currentNode.position:
        return currentNode.distance

    for candidateNode in currentNode.neighbors:
      # increment distance for every edge you cross in the node-grid-graph
      candidateNode.distance = currentNode.distance + 1
      if not candidateNode.position in closedSet:
        openQueue.put(candidateNode)

  # No capsule was found in this direction
  return maxDistance


###
def getClosestGhost(nodes, state, action):
  # get the relevant positions
  curPosition = state.getPacmanState().getPosition()
  newPosition = state.generateSuccessor(0, action).getPacmanState().getPosition()

  # setup data structures for the search
  openQueue = Queue()
  closedSet = set()

  if action != Directions.STOP:
    closedSet.add(curPosition)  # ensures we 'close of our back' and start searching only in the given direction
    root = nodes[newPosition[0]][newPosition[1]]
    root.distance = 1
    openQueue.put(root)
  else:
    root = nodes[curPosition[0]][curPosition[1]]
    root.distance = 1
    openQueue.put(root)

  # start the BF search
  while openQueue.qsize() > 0:
    # pop new node and add it to the closed set
    currentNode = openQueue.get()
    closedSet.add(currentNode.position)

    # check for our objective
    for ghost in state.getGhostStates():
      # round ghost positions in case they are inbetween nodes
      # this happens when they are scared and have reduced movement speed
      if round(ghost.getPosition()[0]) == currentNode.position[0]:
        if round(ghost.getPosition()[1]) == currentNode.position[1]:
          return ghost

    for candidateNode in currentNode.neighbors:
      # increment distance for every edge you cross in the node-grid-graph
      candidateNode.distance = currentNode.distance + 1
      if not candidateNode.position in closedSet:
        openQueue.put(candidateNode)

  # No ghost was found in this direction
  return None


######################################################################
