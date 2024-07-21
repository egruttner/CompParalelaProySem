import matplotlib.pyplot as plt
import pandas as pd
import sys

data1 = pd.read_csv(sys.argv[1])

label1 = sys.argv[2]
title = sys.argv[3]
label_x = sys.argv[4]
label_y = sys.argv[5]

x1 = data1['n'].values
y1 = data1['tiempo[ms]'].values

plt.plot(x1, y1, label=label1)
plt.legend()

plt.xlabel(label_x)
plt.ylabel(label_y)

plt.ticklabel_format(style='plain') #DESACTIVA NOTACIÓN CIENTÍFICA

plt.title(title)

plt.grid()

plt.show()
#plt.savefig('./graficos/' + title + '.pdf',bbox_inches='tight')

