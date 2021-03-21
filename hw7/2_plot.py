import matplotlib.pyplot as plt


f = open("2_data.txt")

X, Y = zip(*[map(int, line.strip().split()) for line in f.readlines()])


plt.scatter(X, Y)

plt.xlabel("N")
plt.ylabel("milliseconds")

# plt.show()
plt.savefig('2_figure.png')
