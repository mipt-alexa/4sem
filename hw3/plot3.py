import matplotlib.pyplot as plt
import numpy

f = open("mydata3.txt")

X, Y = zip(*[map(int, line.strip().split()) for line in f.readlines()])

plt.scatter(X, Y)

plt.xlabel("table size")
plt.ylabel("number of collisions")
plt.title('task 3')

plt.savefig('Figure_3.png')
