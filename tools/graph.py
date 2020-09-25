import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np
#import matplotlib as mpl

#mpl.rcParams['figure.dpi'] = 300

df = pd.read_csv('log4.csv', sep=",")
#print(df)
df = df.set_index("number")

ax = df.plot(marker='.')
ax.set_yscale('log')
ax.set_xscale('linear')
ax.grid(color='b', linestyle='-', linewidth=0.1)
ax.set_xlabel('X digit')
ax.set_ylabel('Y time (s)')
ax.set_facecolor((1.0, 1.0, 1.0))

#start, end = ax.get_xlim()
#ax.xaxis.set_ticks(np.arange(start, end, 0.712123))
#ax.xaxis.set_major_formatter(ticker.FormatStrFormatter('%0.1f'))

#locx = ticker.MultipleLocator(base=2.0)
#locy = ticker.MultipleLocator(base=0.1)
#ax.xaxis.set_major_locator(locx)
#ax.yaxis.set_major_locator(locy)
print()

plt.title('Prime functions perf')

plt.show() 
fig = ax.get_figure()
fig.set_size_inches((21,9))
fig.savefig('graph.png', bbox_inches='tight', dpi=1200)


#THANK https://stackoverflow.com/questions/33888973/get-values-from-matplotlib-axessubplot
#https://www.analyticsvidhya.com/blog/2020/05/10-matplotlib-tricks-data-visualization-python/
#https://stackoverflow.com/questions/6282058/writing-numerical-values-on-the-plot-with-matplotlib
