import matplotlib.pyplot as plt
import numpy

f = open("mydata.txt")

X = []
Y1 = []
Y2 = []

for line in f.readlines():
    lst = line.split()
    X.append(int(lst[0]))
    Y1.append(int(lst[1]))
    Y2.append(int(lst[2]))

for i in X:
    i = i*numpy.log(i)

print(X)

plt.scatter(X, Y1, label="set.insert()")
plt.scatter(X, Y2, label="sort(vector)")

plt.xlabel("N log(N)")
plt.ylabel("milliseconds")
plt.legend()
plt.show()
