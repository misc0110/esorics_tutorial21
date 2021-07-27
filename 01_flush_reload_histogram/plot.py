import matplotlib.pyplot as plt

data = [ [int(y) for y in x.split(",")] for x in open("histogram.csv").read().strip().split("\n")[1:] ]
time = [ x[0] for x in data ]

plt.plot(time, [ x[1] for x in data ])
plt.plot(time, [ x[2] for x in data ])

plt.title("Cache Histogram")
plt.xlabel('Access Time')
plt.ylabel('Number Of Accesses')

plt.legend(["Cache hits", "Cache misses"])
plt.show()
