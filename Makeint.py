import numpy as np

Before = np.genfromtxt("LostEventtest.dat")
Ints = np.savetxt("LostEventtest2.dat", Before, fmt = "%i") 