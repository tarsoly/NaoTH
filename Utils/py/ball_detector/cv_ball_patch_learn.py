#!/usr/bin/python

import cv2
import numpy as np

from sklearn.linear_model import Perceptron
from sklearn.linear_model import SGDClassifier
from sklearn import svm
import sklearn.neural_network as nn

import naoth.features as feat
from naoth.util import *

def unroll_responses(responses, class_n):
        sample_n = len(responses)
        new_responses = np.zeros(sample_n*class_n, np.int32)
        resp_idx = np.int32( responses + np.arange(sample_n)*class_n )
        new_responses[resp_idx] = 1
        return new_responses

def makeTrainData(X, labels, unroll=False):
  n_feat = 144;
  samples = np.zeros((0, n_feat), dtype=np.float32)
  for s in X:
    img = s.reshape((12,12))
    f = feat.bin1(img)
    samples = np.vstack([samples, f])
  
  if unroll:
    responses = np.float32(unroll_responses(labels, 2).reshape(-1, 2))
  else:
    responses = np.int32(labels)
    
  return n_feat, samples, responses
  
def learn(X, labels, nLayer1=10, nLayer2=10):
  
  n_feat, samples, responses = makeTrainData(X, labels, True)
   
  layers = [n_feat, 2]
  if nLayer1 < 2 and nLayer2 < 2:
    # no hidden layers
    layers = [n_feat, 2]
  elif nLayer2 < 2:
    # nLayer1 is single hidden layer
    layers = [n_feat, nLayer1, 2]
  elif nLayer1 < 2:
    # nLayer2 is single hidden layer
    layers = [n_feat, nLayer2, 2]
  else:
    # both are valid hidden layers
    layers = [n_feat, nLayer1, nLayer2, 2]
   
  #estimator = cv2.ml.KNearest_create()
  #estimator = cv2.ml.SVM_create()
  #estimator = cv2.ml.DTrees_create()
  #estimator = cv2.ml.RTrees_create()
  estimator = cv2.ml.ANN_MLP_create()
  estimator.setLayerSizes(np.asarray(layers))
  # must be set!!!
  estimator.setActivationFunction(cv2.ml.ANN_MLP_SIGMOID_SYM )
  estimator.setTermCriteria((cv2.TERM_CRITERIA_COUNT + cv2.TERM_CRITERIA_EPS, 20000, 0.001))
  #estimator.setTrainMethod(cv2.ml.ANN_MLP_BACKPROP)
  #estimator.setBackpropWeightScale(0.001)
  #estimator.setBackpropMomentumScale(0.0)
  
  trainData = cv2.ml.TrainData_create(samples=samples, 
    layout=cv2.ml.ROW_SAMPLE , responses=responses)
  
  estimator.train(trainData)
  
  return estimator
  
def classify(X, labels, estimator):  
  n_feat, samples, responses = makeTrainData(X, labels, True)
  
  classified = np.zeros(samples.shape[0], dtype=np.int)
  
  # classify
  for i in range(0, samples.shape[0]):
    ret, result = estimator.predict(np.asmatrix(samples[i,:]))
    
    classified[i] = ret;
    
  return classified

def show_errors_asfeat(X, goldstd_response, actual_response):  
  
  image = np.zeros(((patch_size[1]+1)*show_size[1], (patch_size[0]+1)*show_size[0]))
  
  errorIdx = list()
  # count
  for i in range(0,X.shape[0]):
    if actual_response[i] != goldstd_response[i]:
        errorIdx.append(i)	
      
  # show errors
  maxShownErrors = min(len(errorIdx), show_size[0]*show_size[1])
  shownErrorIdx = errorIdx[0:maxShownErrors]
  
  j = 0
  for i in shownErrorIdx:
    a = np.transpose(np.reshape(X[i,:], (12,12)))
    y = j // show_size[0]
    x = j % show_size[0]
    
    # apply feature
    f = feat.bin1(a)
    
    image[y*13:y*13+12,x*13:x*13+12] = np.reshape(f, (12,12))
    j += 1
    
  plt.imshow(image, cmap=plt.cm.gray, interpolation='nearest')

  plt.xticks(())
  plt.yticks(())
  plt.show()
  
if __name__ == "__main__":
  
  # load patches from the file
  f_train = "patches-approach-ball"
  f_eval = "patches-ball-sidecick"
  
  splitRatio = -1.0
  
  if len(sys.argv) == 2:
    f_train = sys.argv[1]
    f_eval = sys.argv[1]
    splitRatio = 0.8
  elif len(sys.argv) > 2:
    f_train = sys.argv[1]
    f_eval = sys.argv[2]
  
  
  if splitRatio < 0.0:
    X_train, labels_train = load_data(f_train)
    X_eval, labels_eval = load_data(f_eval)
  else:
    X_all, labels_all = load_data(f_train)
    X_train, labels_train, X_eval, labels_eval = shuffle_and_split(X_all, labels_all, splitRatio)
    
  print("Train size", X_train.shape[0])
  print("Eval size", X_eval.shape[0])
  
  #allEstimators = dict()
  
  #for h1 in reversed(range(2, 3)):
  #  for h2 in range(2, 3):
  #    print("Learning with layers "  + str((h1, h2)))
  #    estimator = learn(X_train, labels_train, h1, h2)
  #    print("Evaluating with layers " + str((h1, h2)))
  #    classified = classify(X_eval, labels_eval, estimator)
  #    precision, recall, _ = calc_precision_recall(X_eval, labels_eval, classified)
  #    allEstimators[estimator] = (precision, recall)
  #    print("precision: " + str(precision))
  #    print("recall: " + str(recall))
  #    print("---------------")
  #    # funny
  #    if precision >= 0.99 and recall >= 0.9:
  #      break
  #print(allEstimators)
      
  print("Learning several layer sizes...")
  estimator = learn(X_train, labels_train)
  print("Saving...")
  estimator.save("ball_detector_model.dat")
  print("Evaluating...")
  classfied = classify(X_eval, labels_eval, estimator)
  show_evaluation(X_eval, labels_eval, classfied)
#  show_errors_asfeat(X_eval, labels_eval, classfied)

    
