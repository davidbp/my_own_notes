
Examples:

  python pacman.py -p MLNN_RandomAgent
  python pacman.py -p MLNN_RandomAgent -l smallClassic
  python pacman.py -p MLNN_RandomAgent -l originalClassic -n 10 -q
  python pacman.py -p MLNN_RandomAgent -k 1 --frameTime 0
  python pacman.py -p MLNN_RandomAgent -k 2 --frameTime 0

======================

python pacman.py --help

python pacman.py
  The default pacman agent is KeyboardAgent

python pacman.py -n numGames
  The number of GAMES to play [Default: 1]

python pacman.py -l layoutName
  The LAYOUT_FILE from which to load the map layout [Default: mediumClassic]

  Already implemented layouts (layoutName.lay in layouts/):
      capsuleClassic  mediumClassic   openClassic      smallClassic  trappedClassic
      contestClassic  minimaxClassic  originalClassic  testClassic   trickyClassic

python pacman.py -p pacmanAgent
  The agent TYPE in the pacmanAgents module to use [Default: KeyboardAgent]

  Already implemented ones:   [Default: KeyboardAgent]
    KeyboardAgent - Manual (arrows)
    KeyboardAgent2 - Manual (i/j/k/l/u)
    LeftTurnAgent - Turns left at every opportunity
    GreedyAgent - Uses the score in a greedy search

  In order to implement a new one, it needs a file myPacmanAgent.py (it must end with 'gents.py')
  The class only needs to contain:
    from game import Agent
    from game import Directions
    class myPacmanAgent( Agent ):
      def __init__( self ):
        ...
      def getAction( self, state ):
        # state contains the current information of the game
        ...
	move = any of { Directions.STOP, Directions.WEST, Directions.EAST, Directions.NORTH, Directions.SOUTH }
        return move

python pacman.py -g ghostAgent
  The ghost agent TYPE in the ghostAgents module to use [Default: RandomGhost]

  Already implemented ones:
    RandomGhost (GhostAgent) - A ghost that chooses a legal action uniformly at random
    DirectionalGhost (GhostAgent) - A ghost that prefers to rush Pacman, or flee when scared

Other options:

  -a AGENTARGS, --agentArgs=AGENTARGS
    Comma separated values sent to agent. e.g. "opt1=val1,opt2,opt3=val3"

  --timeout=TIMEOUT
    Maximum length of time an agent can spend computing in a single game [Default: 30]

  --frameTime=FRAMETIME
    Time to delay between frames; <0 means keyboard [Default: 0.1]

  -f, --fixRandomSeed
    Fixes the random seed to always play the same game

  -q, --quietTextGraphics
    Generate minimal output and no graphics

  -t, --textGraphics
    Display output as text only

  -k NUMGHOSTS, --numghosts=NUMGHOSTS
    The maximum number of ghosts to use [Default: 4]

  -z ZOOM, --zoom=ZOOM
    Zoom the size of the graphics window [Default: 1.0]

  -r, --recordActions
    Writes game histories to a file (named by the time they were played)

  --replay=GAMETOREPLAY
    A recorded game file (pickle) to replay

  -x NUMTRAINING, --numTraining=NUMTRAINING
    How many episodes are training (suppresses output) [Default: 0]

  -c, --catchExceptions
    Turns on exception handling and timeouts during games

======================
