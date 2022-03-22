import matplotlib.pyplot as plt

x = []
y = []
with open('base.txt','r') as f:
    for line in f:
        lines = line.replace('\n','').replace('[','').replace(']','').replace(' ','').split(',')
        if(float(lines[0]) < 48. or float(lines[0]) > 50.):
            continue
        if(float(lines[1]) < -125. or float(lines[1]) > -123.):
            continue
        x.append(float(lines[0]))
        y.append(float(lines[1]))

plt.scatter(x,y,color = "red")
with open('test.txt', 'r') as f:
    for line in f:
        lines = line.replace('\n','').replace('[','').replace(']','').replace(' ','').split(',')
        if(float(lines[0]) < 48. or float(lines[0]) > 50.):
            continue
        if(float(lines[1]) < -125. or float(lines[1]) > -123.):
            continue
        x.append(float(lines[0]))
        y.append(float(lines[1]))
plt.plot(x,y,color="blue")
plt.show()