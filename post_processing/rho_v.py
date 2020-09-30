"""
created by Hossein Sadeghi

Date = 24.09.2020

"""

import pandas as pd
import matplotlib.pyplot as plt 
import numpy as np
import os.path

directory = './results/flux_2'
filename = 'PedSim.csv'
file_path = os.path.join(directory, filename)

df = pd.read_csv(file_path, index_col=1, header=0)

df = df.sort_values(by = ['ID', 'time'], ascending = [True, True]).reset_index() 
#print(df.head())

df = df.where((df['x'] >= 10) & (df['x'] <= 15) & (df['y'] >= 10) & (df['y'] <= 15)).dropna()

df['v'] = np.sqrt(df['v_x']*df['v_x']+df['v_y']*df['v_y'])

df = df[['time','v']]
df_mean = df.groupby(['time']).mean()
df_count = df.groupby(['time']).count()
df_count.rename(columns={"v": "person"}, inplace=True)
A = (15-10) * (15-10) 
df_mean['rho'] = df_count['person']/A
df_mean = df_mean.reset_index()[['v','rho']]
#df_mean = df_mean.groupby(['rho']).agg(['mean', 'std']).reset_index()
df_mean = df_mean.groupby(['rho'])['v'].describe()[['mean', 'std']].reset_index()

fig = plt.figure()
#plt.plot(df_rho, df_mean['v'], 'o', markersize=2)
plt.errorbar(df_mean['rho'], df_mean['mean'], df_mean['std'], linestyle='-', marker='_', markersize=3.5, capsize=2)
    
plt.xlim(0,1.4)
#plt.ylim(0,25)
plt.xlabel(r'$\rho_{avr} \left(\frac{p}{m^2}\right)$')
plt.ylabel(r'$V_{avr} \left(\frac{m}{s}\right)$')
plt.grid(b=None)
plt.tight_layout()

fig.patch.set_facecolor('white')
fig.patch.set_alpha(1)

directory += '/figs'
outputName = 'rho_v.png'
file_path = os.path.join(directory, outputName)
plt.savefig(file_path, format='png', dpi=900)