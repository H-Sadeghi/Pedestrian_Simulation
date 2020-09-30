"""
created by Hossein Sadeghi

Date = 24.09.2020

"""

import pandas as pd
import matplotlib.pyplot as plt 
import numpy as np
import seaborn as sns
import os.path
sns.set()

directory = './results/flux_2'
filename = 'PedSim.csv'
file_path = os.path.join(directory, filename)

df = pd.read_csv(file_path, index_col=1, header=0)

df = df.sort_values(by = ['ID', 'time'], ascending = [True, True]).reset_index() 
#print(df.head())

df = df[['x', 'y', 'v_x', 'v_y']]
df['v'] = np.sqrt(df['v_x']*df['v_x']+df['v_y']*df['v_y'])
df.drop(['v_x'], axis=1, inplace=True) 
df.drop(['v_y'], axis=1, inplace=True)
df = df.round({'x': 1, 'y': 1})
df = df.groupby(['x','y']).mean().reset_index()

heatmap1_data = pd.pivot_table(df, values='v', 
                     index=['y'], 
                     columns='x') 

fig = plt.figure()
fig=sns.heatmap(heatmap1_data,xticklabels=False, yticklabels=False,cmap='rainbow', cbar_kws={'label': r'$V_{avr}\left(\frac{m}{s}\right)$'})
plt.ylim(0,25)
plt.xlim(0,25)
plt.hlines(100, 0, 100, colors='k', linestyles='solid')
plt.hlines(150, 0, 100, colors='k', linestyles='solid')
plt.hlines(100, 150, 250, colors='k', linestyles='solid')
plt.hlines(150, 150, 250, colors='k', linestyles='solid')
plt.vlines(100, 0, 100, colors='k', linestyles='solid')
plt.vlines(150, 0, 100, colors='k', linestyles='solid')
plt.vlines(100, 150, 250, colors='k', linestyles='solid')
plt.vlines(150, 150, 250, colors='k', linestyles='solid')

plt.axis('equal')

plt.ylabel('')    
plt.xlabel('')

plt.grid(b=None)
plt.tight_layout()

fig.patch.set_facecolor('white')
fig.patch.set_alpha(1)

directory += '/figs'
outputName = 'heatmap_v.png'
file_path = os.path.join(directory, outputName)
figure = fig.get_figure()    
figure.savefig(file_path, dpi=900)

