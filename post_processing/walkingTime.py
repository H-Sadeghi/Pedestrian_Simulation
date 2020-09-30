"""
created by Hossein Sadeghi

Date = 24.09.2020

"""

import pandas as pd
import matplotlib.pyplot as plt 
import numpy as np
import os.path

flux = [0.2,0.5,0.7,1,1.3,1.5,1.6, 1.7, 1.8,2]

t_avr = []
t_std = []
for i in flux:
    directory = './results/flux_' + str(i)
    filename = 'PedSim.csv'
    file_path = os.path.join(directory, filename)

    df = pd.read_csv(file_path, index_col=1, header=0)

    df = df.sort_values(by = ['ID', 'time'], ascending = [True, True]).reset_index() 

    t_max = df.groupby(['ID'])['time'].max().reset_index()
    t_min = df.groupby(['ID'])['time'].min().reset_index()
    t = pd.merge(t_min, t_max, on='ID')

    t = t.where(t['time_y'] != 60).dropna()
    t['walking_time'] = t['time_y'] - t['time_x']
    t_avr.append(np.mean(t['walking_time']))
    t_std.append(np.std(t['walking_time']))

fig = plt.figure()
plt.errorbar(flux, t_avr, t_std, linestyle='-', marker='_', markersize=3, capsize=5)
    
plt.xlim(0.1,2.1)
#plt.ylim(0.2,2)
plt.xlabel(r'$flux_{in} \left(\frac{p}{s}\right)$')
plt.ylabel('walking time (s)')
plt.grid(b=None)
plt.tight_layout()

directory = './results'
outputName = 'walking_time.png'
file_path = os.path.join(directory, outputName)
plt.savefig(file_path, format='png', dpi=900)