import matplotlib.pyplot as plt
import pandas as pd
import sys

data1 = pd.read_csv(sys.argv[1])
data2 = pd.read_csv(sys.argv[2])
data3 = pd.read_csv(sys.argv[3])
data4 = pd.read_csv(sys.argv[4])


label1 = sys.argv[5]
label2 = sys.argv[6]
label3 = sys.argv[7]
label4 = sys.argv[8]


title = sys.argv[9]

label_x = sys.argv[10]
label_y = sys.argv[11]


x1 = data1['n'].values
y1 = data1['tiempo[ms]'].values

x2 = data2['n'].values
y2 = data2['tiempo[ms]'].values

x3 = data3['n'].values
y3 = data3['tiempo[ms]'].values

x4 = data4['n'].values
y4 = data4['tiempo[ms]'].values


plt.plot(x1, y1, label=label1)
plt.legend()
plt.plot(x2, y2, label=label2)
plt.legend()
plt.plot(x3, y3, label=label3)
plt.legend()
plt.plot(x4, y4, label=label4)
plt.legend()

plt.ticklabel_format(style='plain') #DESACTIVA NOTACIÓN CIENTÍFICA

plt.xlabel(label_x)
plt.ylabel(label_y)

plt.title(title)

plt.grid()

#plt.show()
plt.savefig('./graficos/' + title + '.png')

