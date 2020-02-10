import numpy as np
rand = np.random.RandomState(42)
t = 100 * rand.rand(100)
y = np.sin(2 * np.pi * t) + 0.1 * rand.randn(100)

f = open("./Data/cyclic-data.hpp","w")
f.write("std::vector<double> input_data{" + np.array2string(y,separator=',')[1:-1] + "};\n\n")
f.write("std::vector<double> times{" + np.array2string(np.linspace(0,1,100),separator=',')[1:-1] + "};\n\n")
f.write("std::vector<double> frequencies{" + np.array2string(np.linspace(0,50,100),separator=',')[1:-1] + "};")
f.close()
