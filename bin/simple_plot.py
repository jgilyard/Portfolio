from pylab import *
from sys import argv

def sim_plot(Equity,intercept, x):
    t = arange(100.0,200.0, 0.1)
    s = (float(intercept) + float(x)*t)
    plot(t, s)
    xlabel('TIME (DAYS)')
    ylabel('Price (USD$)')
    title(Equity +" Plot")
    grid(True)
    savefig("test.png")
    show()
def main():
    sim_plot("IBM", 12, 45)
main()
