import matplotlib.pyplot as plt
import numpy

f = open("mydata.txt")

X, Y1, Y2 = zip(*[map(int, line.strip().split()) for line in f.readlines()])

for i in X:
    i = i * numpy.log(i)

plt.scatter(X, Y1, label="set.insert()")
plt.scatter(X, Y2, label="sort(vector)")

plt.xlabel("N log(N)")
plt.ylabel("milliseconds")
plt.legend()
# plt.show()
plt.savefig('Figure_1.png')
