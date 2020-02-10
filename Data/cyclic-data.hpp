double input_data[] = { 0.29365239, 0.40399472, 0.95904944,-0.94533201,-0.61918723,-0.54928509,
 -0.78572822,-0.72537183, 0.56381377,-0.98615661, 0.45058907,-0.02373616,
  0.94637461, 1.04622153, 0.92110255, 0.9396707 , 0.38812245, 0.11967562,
  0.90060514, 0.55142705, 0.94808747,-0.28657783, 0.9756891 ,-0.77847003,
 -0.7643171 ,-0.15239924,-0.23780798, 0.38245287, 0.98243111,-0.74990884,
 -0.81098434, 0.34085423,-0.00665611,-0.65184398,-0.57863944,-0.84787095,
  0.24632408,-0.74783409, 0.44423077, 0.12582284, 0.95473391,-0.22779495,
  0.48910312,-0.33895234,-0.61455844, 0.90896323, 1.01991754,-0.09745915,
 -0.82071417, 0.31036645,-0.35708699,-0.13998831,-0.29968428, 0.05791873,
 -1.12365282, 0.93055179,-0.91800749,-0.53168072,-0.23426733,-0.05107254,
 -0.81698743, 0.71750247,-0.63128276,-1.01503995, 0.57675302, 1.12313442,
  0.38786742, 1.0003934 , 0.30459099,-0.84854136, 0.86347381,-0.85423417,
 -0.27000903,-0.25618098,-0.89452811,-0.54949082, 0.64808607, 0.5880849 ,
 -0.79217822,-0.59074759, 1.11555938, 0.92425636, 0.4156482 , 0.85258381,
  0.48129478,-0.03622163,-0.12906846,-1.08141633,-0.88741839, 1.02527934,
 -0.16998404, 1.08216799, 0.4489615 , 0.64371289, 0.48202692, 0.60498043,
  0.98160837,-0.96555271,-0.2326427 ,-0.88719037};

double times[] = {0.        ,0.01010101,0.02020202,0.03030303,0.04040404,0.05050505,
 0.06060606,0.07070707,0.08080808,0.09090909,0.1010101 ,0.11111111,
 0.12121212,0.13131313,0.14141414,0.15151515,0.16161616,0.17171717,
 0.18181818,0.19191919,0.2020202 ,0.21212121,0.22222222,0.23232323,
 0.24242424,0.25252525,0.26262626,0.27272727,0.28282828,0.29292929,
 0.3030303 ,0.31313131,0.32323232,0.33333333,0.34343434,0.35353535,
 0.36363636,0.37373737,0.38383838,0.39393939,0.4040404 ,0.41414141,
 0.42424242,0.43434343,0.44444444,0.45454545,0.46464646,0.47474747,
 0.48484848,0.49494949,0.50505051,0.51515152,0.52525253,0.53535354,
 0.54545455,0.55555556,0.56565657,0.57575758,0.58585859,0.5959596 ,
 0.60606061,0.61616162,0.62626263,0.63636364,0.64646465,0.65656566,
 0.66666667,0.67676768,0.68686869,0.6969697 ,0.70707071,0.71717172,
 0.72727273,0.73737374,0.74747475,0.75757576,0.76767677,0.77777778,
 0.78787879,0.7979798 ,0.80808081,0.81818182,0.82828283,0.83838384,
 0.84848485,0.85858586,0.86868687,0.87878788,0.88888889,0.8989899 ,
 0.90909091,0.91919192,0.92929293,0.93939394,0.94949495,0.95959596,
 0.96969697,0.97979798,0.98989899,1.        };

double frequencies[] = { 0.        , 0.50505051, 1.01010101, 1.51515152, 2.02020202, 2.52525253,
  3.03030303, 3.53535354, 4.04040404, 4.54545455, 5.05050505, 5.55555556,
  6.06060606, 6.56565657, 7.07070707, 7.57575758, 8.08080808, 8.58585859,
  9.09090909, 9.5959596 ,10.1010101 ,10.60606061,11.11111111,11.61616162,
 12.12121212,12.62626263,13.13131313,13.63636364,14.14141414,14.64646465,
 15.15151515,15.65656566,16.16161616,16.66666667,17.17171717,17.67676768,
 18.18181818,18.68686869,19.19191919,19.6969697 ,20.2020202 ,20.70707071,
 21.21212121,21.71717172,22.22222222,22.72727273,23.23232323,23.73737374,
 24.24242424,24.74747475,25.25252525,25.75757576,26.26262626,26.76767677,
 27.27272727,27.77777778,28.28282828,28.78787879,29.29292929,29.7979798 ,
 30.3030303 ,30.80808081,31.31313131,31.81818182,32.32323232,32.82828283,
 33.33333333,33.83838384,34.34343434,34.84848485,35.35353535,35.85858586,
 36.36363636,36.86868687,37.37373737,37.87878788,38.38383838,38.88888889,
 39.39393939,39.8989899 ,40.4040404 ,40.90909091,41.41414141,41.91919192,
 42.42424242,42.92929293,43.43434343,43.93939394,44.44444444,44.94949495,
 45.45454545,45.95959596,46.46464646,46.96969697,47.47474747,47.97979798,
 48.48484848,48.98989899,49.49494949,50.        };