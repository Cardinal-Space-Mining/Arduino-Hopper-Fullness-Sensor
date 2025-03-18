import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
import random

style.use("fivethirtyeight")

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

def animateNOT(i):
    graph_data = open('example.txt','r').read()
    lines = graph_data.split('\n')
    xs = []
    ys = []
    for line in lines:
        if len(line) > 1:
            x, y = line.split(',')
            xs.append(float(x))
            ys.append(float(y))

    ax1.clear()
    ax1.plot(xs, ys)

xs = [1,2,3,4,5,6]
ys = [80,34,12,21,32,54]


def animate(i):
    ys = ys[1:]
    ys.append(random.randint(1,100))

    print(ys)

    ax1.clear()
    ax1.plot(xs, ys)


ani = animation.FuncAnimation(fig, animate, interval=1000,cache_frame_data=False )
plt.show()
