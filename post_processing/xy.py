"""
created by Hossein Sadeghi

Date = 24.09.2020

"""

import pandas as pd
import matplotlib.pyplot as plt 
import os.path

directory = './results/flux_0.5'
filename = 'PedSim.csv'
file_path = os.path.join(directory, filename)

df = pd.read_csv(file_path, index_col=1, header=0)

df = df.sort_values(by = ['ID', 'time'], ascending = [True, True]).reset_index() 
#print(df.head())

df1 = df.where(df['Group'] == 0)
df2 = df.where(df['Group'] == 1)

n1 = df1['ID'].max()
n2 = df2['ID'].max()

fig = plt.figure()
#for i in range (1,int(n1)):
#    ID = df.where(df1['ID'] == i)
#    X = ID['x'].dropna()
#    Y = ID['y'].dropna() 
#    plt.plot(X, Y, 'b', linewidth=0.25)

for i in range (1,int(n2)):
    ID = df.where(df2['ID'] == i)
    X = ID['x'].dropna()
    Y = ID['y'].dropna() 
    plt.plot(X, Y, 'r', linewidth=0.25)

plt.hlines(10, 0, 10, colors='k', linestyles='solid')
plt.hlines(15, 0, 10, colors='k', linestyles='solid')
plt.hlines(10, 15, 25, colors='k', linestyles='solid')
plt.hlines(15, 15, 25, colors='k', linestyles='solid')
plt.vlines(10, 0, 10, colors='k', linestyles='solid')
plt.vlines(15, 0, 10, colors='k', linestyles='solid')
plt.vlines(10, 15, 25, colors='k', linestyles='solid')
plt.vlines(15, 15, 25, colors='k', linestyles='solid')
    
plt.xlim(0,25)
plt.ylim(0,25)

plt.tick_params(top=False, bottom=False, left=False, right=False,
                labelleft=False, labelbottom=False)
plt.axis('equal')
plt.grid(b=None)
plt.tight_layout()

fig.patch.set_facecolor('white')
fig.patch.set_alpha(1)

directory += '/figs'
outputName = 'xy_CD.png'
file_path = os.path.join(directory, outputName)
#plt.savefig(file_path, format='png', dpi=900)
plt.savefig(file_path, format='png', dpi=900)

