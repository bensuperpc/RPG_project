import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('log2.csv', sep=",")
#print(df)
df = df.set_index("number")

ax = df.plot(marker='.')
ax.set_yscale('log')
ax.set_xscale('linear')
ax.grid(color='b', linestyle='-', linewidth=0.1)
plt.show()
