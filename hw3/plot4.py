import matplotlib.pyplot as plt
import numpy

f = open("mydata4.txt")

Y = [[0] * 15] * 10

X, Y[0], Y[1], Y[2], Y[3], Y[4], Y[5], Y[6], Y[7], Y[8] = zip(*[map(int, line.strip().split()) for line in f.readlines()])


for i in range(0, 9):
    plt.plot(X, Y[i], label=str(i))

plt.xlabel("table size")
plt.ylabel("number of collisions")
plt.title('task 4')
plt.legend()

plt.savefig('Figure_4.png')
