#!/usr/bin/python

import os, sys, getopt, math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as ptc

from sklearn.linear_model import Perceptron
from sklearn.linear_model import SGDClassifier
from sklearn import svm
import sklearn.neural_network as nn

import patchReader

show_size = (50, 30) # width, height
patch_size = (12, 12) # width, height
def getMarker(x,y,c):
  pos = (x*(patch_size[0]+1)-1,y*(patch_size[1]+1)-1)
  return ptc.Rectangle( pos, width=patch_size[0]+1, height=patch_size[1]+1, alpha=0.3, color=c)

  
def learn(X, labels):
  #estimator = Perceptron(n_iter=10, shuffle=True)
  #estimator = SGDClassifier()
  estimator = svm.SVC(kernel='linear')
  #estimator = nn.MLPClassifier()
  
  estimator.fit(X, labels)
  #print estimator.decision_function(X[15,:])
  
  c = np.reshape(estimator.coef_, (12, 12))
  print estimator.coef_
  print estimator.intercept_
  
  plt.imshow(c, cmap=plt.cm.gray, interpolation='nearest')
  plt.show()
  
  
  image = np.zeros(((patch_size[1]+1)*show_size[1], (patch_size[0]+1)*show_size[0]))
  
  # classify
  j = 0
  marker = []
  for i in range(4400,4400+show_size[0]*show_size[1]):
    a = np.transpose(np.reshape(X[i,:], (12,12)))
    y = j // show_size[0]
    x = j % show_size[0]
    image[y*13:y*13+12,x*13:x*13+12] = a
    
    if estimator.decision_function(X[i,:]) > 0:
      if labels[i]:
        marker.append(getMarker(x,y,'green'))
      else:
        marker.append(getMarker(x,y,'red'))
    else:
      if labels[i]:
        marker.append(getMarker(x,y,'yellow'))
      
    j += 1
    
  plt.imshow(image, cmap=plt.cm.gray, interpolation='nearest')
  for m in marker:
    plt.gca().add_patch(m)
  plt.xticks(())
  plt.yticks(())
  plt.show()
  
  
def load_from_csv(file):
  f = open(file, 'r')
  patches = []
  
  for line in f:
    s = line.split(';')
    a = np.array(s).astype(float)
    patches.append(a)

if __name__ == "__main__":
  
  ball_labels_csv = [15, 33, 51, 70, 87, 106, 125, 144, 160, 187, 205, 224, 242, 263, 281, 300, 322, 341, 358, 379, 399, 418, 438, 459, 497, 480, 513, 530, 548, 569, 587, 615, 632, 651, 671, 692, 712, 731, 751, 770, 791, 809, 828, 847, 866, 883, 904, 924, 942, 956, 972, 998, 1024, 1046, 1067, 1087, 1109, 1128, 1147, 1162, 1180, 1197, 1214, 1230, 1248, 1268, 1287, 1312, 1330, 1346, 1366, 1380, 1399, 1419, 1437, 1498, 1516, 1536, 1554, 1572, 1590, 1608, 1626, 1645, 1660, 1681, 1696, 1717, 1732, 1756, 1772, 1789, 1809, 1824, 1845, 1847, 1863, 1864, 1884, 1886, 1911, 1940, 1917, 1948, 1959, 1966, 1979, 1986, 2006, 2013, 2023, 2034, 2052, 2068, 2047, 2077,2097, 2090, 2111, 2119, 2133, 2140, 2151, 2156, 2171, 2191, 2196, 2178, 2211, 2323, 2348, 2369, 2392, 2409, 2434, 2456, 2474, 2492, 2512, 2543, 2587, 2567, 2618, 2633, 2657, 2676, 2694, 2722, 2740, 2760, 2781, 2802, 2818, 2840, 2858, 2878, 2899, 2930, 2950, 2969, 2993, 3015, 3036, 3056, 3078, 3097, 3121, 3145, 3159, 3186, 3222, 3209, 3249, 3274, 3294, 3311, 3326, 3344, 3359, 3380, 3393, 3406, 3420, 3437, 3453, 3470, 3489, 3523, 3508, 3538, 3554, 3572, 3592, 3611, 3630, 3653,3672, 3691, 3711, 3725, 3741, 3759, 3776, 3792, 3813, 3830, 3844, 3860, 3878, 3895, 3912, 3926, 3947, 3965, 3982, 4000, 4017, 4032, 4047, 4065, 4079, 4095, 4111, 4126, 4139, 4156, 4169, 4188, 4206, 4228, 4249, 4281, 4265, 4301, 4312, 4330, 4342, 4353, 4366, 4398, 4421, 4433, 4447, 4462, 4482, 4502, 4519, 4537, 4548, 4564, 4581, 4592, 4607, 4619, 4634, 4654, 4667, 4685, 4703, 4718, 4738, 4757, 4773, 4791, 4806, 4825, 4846, 4868, 4883, 4899, 4920, 4943, 4957, 4973, 5004, 5027,5046, 5064, 5080, 5104, 5123, 5139, 5153, 5172, 5190, 5219, 5235, 5252, 5270, 5292, 5312, 5324, 5334, 5352, 5371, 5387, 5408, 5422, 5451, 5468, 5490, 5509, 5527, 5555, 5574, 5602, 5624, 5647, 5667, 5690, 5707, 5728, 5750, 5768, 5791, 5812, 5833, 5849, 5867, 5885, 5905, 5922, 5945, 5961, 5976, 5995, 6017, 6035, 6059, 6070, 6395, 6406, 6448, 6467, 6484, 6430, 6503, 6519, 6536, 6555, 6576, 6594, 6609, 6626, 6645, 6661, 6676, 6695, 6714, 6731, 6752, 6770, 6786, 6803, 6819, 6836,6851, 6866, 6883, 6902, 6923, 6937, 6953, 6971, 6987, 7017, 7043, 7061, 7080, 7104, 7123, 7141, 7163, 7182, 7202, 7220, 7234, 7250, 7267, 7283, 7302, 7327, 7353, 7372, 7387, 7404, 7426, 7444, 7465, 7490, 7549, 7563, 7583]
 
 
  ball_labels_log = [2, 16, 31, 45, 59, 75, 90, 104, 126, 141, 158, 171, 188, 202, 217, 233, 251, 263, 278, 294, 310, 325, 341, 357, 373, 386, 400, 415, 431, 446, 466, 483, 499, 515, 530, 545, 562, 575, 593, 611, 626, 641, 656, 673, 687, 704, 720, 738, 751, 764, 784, 801, 818, 833, 848, 866, 879, 894, 907, 920, 937, 950, 962, 976, 989, 1006, 1028, 1043, 1057, 1072, 1086, 1100, 1114, 1130, 1163, 1179, 1194, 1210, 1225, 1241, 1256, 1271, 1285, 1299, 1313, 1329, 1342, 1360, 1377, 1396, 1409, 1423,1439, 1453, 1469, 1483, 1500, 1518, 1521, 1541, 1546, 1557, 1561, 1572, 1576, 1592, 1595, 1606, 1609, 1622, 1625, 1637, 1640, 1651, 1654, 1665, 1669, 1684, 1687, 1699, 1702, 1716, 1719, 1735, 1739, 1752, 1850, 1863, 1880, 1894, 1910, 1929, 1946, 1962, 1977, 1999, 2016, 2037, 2060, 2080, 2095, 2113, 2131, 2152, 2169, 2185, 2203, 2217, 2233, 2246, 2260, 2277, 2289, 2308, 2329, 2344, 2362, 2380, 2399, 2419, 2435, 2452, 2467, 2485, 2505, 2523, 2538, 2558, 2574, 2589, 2607, 2623,2636, 2651, 2665, 2679, 2692, 2705, 2716, 2728, 2743, 2758, 2772, 2786, 2799, 2810, 2821, 2834, 2849, 2863, 2878, 2891, 2906, 2921, 2937, 2951, 2964, 2977, 2989, 3002, 3015, 3031, 3049, 3061, 3075, 3089, 3102, 3116, 3131, 3143, 3156, 3171, 3185, 3199, 3210, 3222, 3236, 3248, 3260, 3273, 3285, 3298, 3309, 3321, 3335, 3346, 3363, 3379, 3388, 3402, 3415, 3426, 3435, 3448, 3457, 3467, 3482, 3492, 3505, 3517, 3526, 3542, 3558, 3570, 3586, 3598, 3610, 3621, 3633, 3645, 3654, 3663,3676, 3687, 3699, 3714, 3727, 3739, 3752, 3767, 3779, 3795, 3808, 3823, 3840, 3857, 3871, 3884, 3904, 3920, 3934, 3954, 3970, 3987, 4002, 4017, 4031, 4048, 4065, 4078, 4094, 4109, 4128, 4144, 4155, 4168, 4183, 4200, 4215, 4230, 4244, 4257, 4270, 4283, 4302, 4317, 4331, 4347, 4364, 4385, 4400, 4422, 4440, 4458, 4475, 4491, 4508, 4525, 4541, 4559, 4577, 4594, 4611, 4628, 4644, 4658, 4672, 4685, 4701, 4715, 4728, 4744, 4760, 4776, 4794, 4809, 4823, 4835, 4844, 5057, 5082, 5090,5108, 5122, 5136, 5149, 5160, 5171, 5185, 5199, 5215, 5230, 5242, 5255, 5268, 5281, 5293, 5308, 5327, 5342, 5361, 5375, 5400, 5414, 5426, 5438, 5451, 5464, 5480, 5494, 5511, 5524, 5539, 5550, 5564, 5584, 5599, 5613, 5630, 5644, 5660, 5675, 5691, 5706, 5723, 5737, 5750, 5762, 5776, 5789, 5804, 5822, 5838, 5852, 5865, 5878, 5890, 5904, 5924, 5941, 5957, 5971, 5986]
 
  # load patches from the file
  #patches = load_from_csv("./patches.txt")
  patches = patchReader.readAllPatchesFromLog('./ball-move-around-patches.log')
  ball_labels = ball_labels_log
  
  X = np.array(patches)
  labels = np.zeros((X.shape[0],))
  labels[ball_labels] = 1
  
  learn(X, labels)
  

    