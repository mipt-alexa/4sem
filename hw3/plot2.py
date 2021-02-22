import matplotlib.pyplot as plt

f = open("mydata2.txt")

X, Y = zip(*[map(int, line.strip().split()) for line in f.readlines()])

plt.scatter(X, Y)

plt.xlabel("table size")
plt.ylabel("number of collisions")
plt.title('task 2')


plt.savefig('Figure_2.png')
