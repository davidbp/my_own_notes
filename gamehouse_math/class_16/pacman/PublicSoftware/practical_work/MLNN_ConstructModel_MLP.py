
from __future__ import print_function, division

import sys, time, pandas, pickle
import numpy as np

import sklearn
# General sklearn modules
from sklearn.base            import BaseEstimator
from sklearn.preprocessing   import LabelEncoder

# Keras for Multilayer Perceptrons
import keras


############################
### MLP Class/Functions
############################

class MLP_Keras(BaseEstimator):
  """
  Standard MLP constructed with Keras
  To be compatible with sklearn, the following functions must be implemented:
    __init__    Allows to define all the parameters of the model
    fit         Trains the classifier
    predict     Obtains the predictions for a data set
    score       Obtains the accuracy for a data set
  Additionally, several methods are added to make it compatible with PacMan/MLNN_Agents:
    saveModel           Saves the object
    getDecisionValues   Obtains the decision values for each possible label in a data set
    getPredictedLabels  Obtains the predicted labels for a data set
  """

  ### Sklearn compatibility methods

  def __init__ (self, NFeatures=None, NClasses=None):

    ### Copy the parameters to object variables
    self.NFeatures = NFeatures
    self.NClasses  = NClasses

    ### Encoder
    self.LabelEncoder = sklearn.preprocessing.LabelEncoder()
    
    ### Architecture
    self.BaseArchitecture = defineArchitecture_MLP(self.NFeatures, self.NClasses)

    ### Training algorithm (with specific parameters)
    TrainAlgorithm = defineTrainAlgorithm_MLP()

    ### Batch size
    self.BatchSize = defineBatchsize_MLP()

    ### Number of epochs
    self.Epochs = defineEpochs_MLP()

    ### Model
    # Inputs and Outputs to the model
    input_shape = (self.NFeatures,)
    inputs      = keras.layers.Input(shape=input_shape)
    outputs     = self.BaseArchitecture(inputs)
    # Define the model
    model       = keras.models.Model(inputs=inputs, outputs=outputs)
    # Compile the model
    model.compile(loss=['categorical_crossentropy'], optimizer=TrainAlgorithm, metrics=['categorical_accuracy'])
    self.model = model


  def fit (self, DataInputs, DataLabels):
    self.model.fit(DataInputs, DataLabels, batch_size=self.BatchSize, epochs=self.Epochs)
    return self


  def predict (self, DataInputs):
    predictions = self.model.predict(DataInputs);     #print(predictions)
    return predictions


  def score (self, DataInputs, DataLabels):
    scores = self.model.evaluate(DataInputs,DataLabels)
    ### Accuracy
    accuracy = 100.0*scores[1];                       #print(accuracy)
    return accuracy


  ### Additional methods

  def saveModel (self, FileNameModel):
    print("\nSaving model... ",FileNameModel)
    pickle.dump(self, open(FileNameModel, 'wb'))


  def getDecisionValues (self, DataInputs):
    ### Obtains the decision values for each possible label in a data set
    return self.predict(DataInputs)


  def getPredictedLabels (self, DataInputs):
    ###  Obtains the predicted labels for a data set
    predictions = self.predict(DataInputs);                             #print(predictions)
    outputLabels = np.argmax(predictions,axis=1);
    # Inverse encode of integers as class values
    outputLabels = self.LabelEncoder.inverse_transform(outputLabels);   #print(outputLabels);
    return outputLabels


###=====================================================

def defineArchitecture_MLP(NFeatures, NClasses):
  network = keras.models.Sequential()

  ### TODO: Define the hidden layer(s)
  # network.add(...)

  # Output layer (do not modify!)
  network.add(keras.layers.Dense(NClasses, activation='softmax'))
  return network


def defineTrainAlgorithm_MLP():

  ### TODO: Define the training algorithm (and its parameters, if any)
  # TrainAlgorithm = ...

  return TrainAlgorithm


def defineBatchsize_MLP():

  ### TODO: Define the batch size
  # BatchSize = ...

  return BatchSize


def defineEpochs_MLP():

  ### TODO: Define the number of epochs
  # Epochs = ...

  return Epochs


def constructModel_MLP_Keras (Inputs, Labels, ModelSelection, FileNameModel):
  """
  Model selection and construction of the final model (MLP_Keras)
  """

  ## Number of features and classes
  NFeatures = Inputs.shape[1]
  NClasses  = len(np.unique(Labels))

  ## Classifier
  classifier = MLP_Keras(NFeatures, NClasses)
  print(classifier.BaseArchitecture.summary())

  ## Encode class values as integers
  #   https://scikit-learn.org/stable/modules/generated/sklearn.preprocessing.LabelEncoder.html
  classifier.LabelEncoder.fit(Labels)
  ## We may transform the labels to a 1-of-C encoding with
  # y_train = keras.utils.to_categorical(classifier.LabelEncoder.transform(Labels))

  if not ModelSelection:

    ### TODO: Construction of the final model

    ### Save model into a file
    classifier.saveModel(FileNameModel)

  else:

    ### We may use implemented functions in sklearn.model_selection
    from sklearn import model_selection

    ### TODO: Model selection runs (note that no model is saved)


###=====================================================

def readCommand (argv):
  """
  Processes the command used to run this file from the command line.
  """
  def default(str):
    return str + ' [Default: %default]'

  from optparse import OptionParser
  usageStr = """
  USAGE:      python MLNN_ConstructModel.py <options>
  """
  parser = OptionParser(usageStr)

  parser.add_option('-i', '--inputs', dest='InputsFileName',
                    help=default('the Filename where the INPUTS are stored'), default='InputsFileName.txt')
  parser.add_option('-l', '--labels', dest='LabelsFileName',
                    help=default('the Filename where the LABELS are stored'), default='LabelsFileName.txt')
  parser.add_option('-s', '--modelSelection', action='store_true', dest='ModelSelection',
                    help=default('boolean indicating if run for model selection'), default=False)
  parser.add_option('-m', '--fileModel', dest='FileNameModel',
                    help=default('the Filename where the MODEL has to be saved'), default='FileNameModel.model')

  parsedoptions, otherjunk = parser.parse_args(argv)
  if len(otherjunk) != 0:
    raise Exception('Command line input not understood: ' + str(otherjunk))
  #print(type(parsedoptions),parsedoptions)

  options = dict()
  options['InputsFileName'] = parsedoptions.InputsFileName
  options['LabelsFileName'] = parsedoptions.LabelsFileName
  options['ModelSelection'] = parsedoptions.ModelSelection
  options['FileNameModel']  = parsedoptions.FileNameModel

  return options


def loadDatasetsFromFiles (InputsFileName, LabelsFileName, Path="./", Separator=" ", Header=None):
  """
  Loads inputs and labels from the filenames in the parameters
  """

  print("Loading datasets from files in %s:" % Path, end=""); sys.stdout.flush()
  itime = time.time()

  # Load input data and convert to numpy.array
  path_data = Path + InputsFileName
  print(" %s" % InputsFileName, end=""); sys.stdout.flush()
  #df_data = pandas.read_csv(path_data,sep=Separator,header=Header)
  df_data = pandas.read_csv(path_data,sep=Separator+"+",header=Header,engine='python')
  Inputs = df_data.values.astype(float)

  # Load labels and convert to numpy.array
  Labels = None
  if LabelsFileName is not None:
    path_labels= Path + LabelsFileName
    print(" %s" % LabelsFileName, end=""); sys.stdout.flush()
    #df_labels = pandas.read_csv(path_labels,sep=Separator,header=Header)
    df_labels = pandas.read_csv(path_labels,sep=Separator+"+",header=Header,engine='python')
    Labels = df_labels.values.astype(float)
    Labels = Labels.ravel()   ### sklearn prefers shapes (N,) than (N,1)

  print("  took %.1fs" % (time.time()-itime))
  return Inputs, Labels


def runMainConstructModel (options):
  #print(type(options),options)

  ### Copy options to variables
  InputsFileName = options['InputsFileName']
  LabelsFileName = options['LabelsFileName']
  ModelSelection = options['ModelSelection']
  FileNameModel  = options['FileNameModel']

  ### Load data
  Inputs, Labels = loadDatasetsFromFiles(InputsFileName,LabelsFileName,Path="./")
  print("Number of Examples: %d" % Inputs.shape[0])
  print("Number of Features: %d" % Inputs.shape[1])
  print("Number of Labels: %d" % len(np.unique(Labels)))
  
  constructModel_MLP_Keras(Inputs, Labels, ModelSelection, FileNameModel)


if __name__ == '__main__':

  options = readCommand(sys.argv[1:]) # Get arguments based on input
  runMainConstructModel(options)

###=====================================================
