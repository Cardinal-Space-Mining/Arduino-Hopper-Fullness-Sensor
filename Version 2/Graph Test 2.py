import matplotlib.pyplot as plt
import random, time

def update(arr, num=""):
    num = random.randint(1,100)#comment out line
    arr.pop()
    arr.append(num)
    return arr


plt.xlabel('time')
plt.ylabel('Percent')

x1,y1 = [],[]
for i in range(20): #length in 
    x1.append(i+1)
    y1.append(0)

while True:
    num = random.randint(1,100)
    y1.pop()
    y1.append(num)

    plt.plot(x1, y1)
    plt.show()

    #time.sleep(1)


while True:
    y1 = update(y1)
    plt.plot(x1, y1)
    plt.show()
    #time.sleep(1)
