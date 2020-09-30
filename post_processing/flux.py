"""
created by Hossein Sadeghi

Date = 24.09.2020

"""

import pandas as pd
import matplotlib.pyplot as plt 
import numpy as np
import os.path

flux = [0.2,0.5,0.7,1,1.3,1.5,1.6, 1.7, 1.8,2]
flux_out = []
for i in flux:
    directory = './results/flux_' + str(i)
    filename = 'PedSim.csv'
    file_path = os.path.join(directory, filename)

    df = pd.read_csv(file_path, index_col=1, header=0)

    df = df.sort_values(by = ['ID', 'time'], ascending = [True, True]).reset_index() 

    df = df.groupby(['ID']).max().reset_index()
    df = df[df.time < 60]
    df = df[['ID', 'time']]
    flux_out.append(df.shape[0]/(df['time'].max()-df['time'].min())/2)

fig = plt.figure()
plt.plot(flux, flux_out, '-o')
    
plt.xlim(0.2,2)
plt.ylim(0.2,2)
plt.xlabel(r'$flux_{in} \left(\frac{p}{s}\right)$')
plt.ylabel(r'$flux_{out} \left(\frac{p}{s}\right)$')
plt.grid(b=None)
plt.tight_layout()

directory = './results'
outputName = 'flux.png'
file_path = os.path.join(directory, outputName)
plt.savefig(file_path, format='png', dpi=900)
