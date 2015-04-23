import matplotlib.pyplot as plt
import numpy
from mpl_toolkits.mplot3d import Axes3D 
from mpl_toolkits.mplot3d import axes3d
def plot():
    #numpy.set_printoptions(threshold='nan')
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    X, Y, Z = axes3d.get_test_data(0.05)
    print X
    ax.set_xlabel('TIME (DAYS)')
    ax.set_ylabel('Optimal Minimized Risk')
    ax.set_zlabel('Price (USD$)')

    ax.plot_surface(X, Y, Z,cmap=plt.cm.jet, rstride=10, cstride=10)
    plt.show()
plot()


