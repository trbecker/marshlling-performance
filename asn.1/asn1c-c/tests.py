#!/usr/bin/python3

import sys
import os.path
import numpy as np

def get_mean_stdev(data):
    return (np.average(data), np.std(data))

print('Time')
for dname in [256, 512, 1024, 2048, 4096]:
    with open(os.path.join(str(dname), 'results.dat'), 'r') as fp:
        data = np.loadtxt(fp, delimiter=' ')
        enc_mean, enc_stdev = get_mean_stdev(data[1,:])
        dec_mean, dec_stdev = get_mean_stdev(data[2,:])
        print(f'{dname} & ${enc_mean:.4f} \\pm {enc_stdev:.4f}$ & ${dec_mean:.4f} \\pm {dec_stdev:.4f}$')

print('\nThroughput')
for dname in [256, 512, 1024, 2048, 4096]:
    with open(os.path.join(str(dname), 'results.dat'), 'r') as fp:
        data = np.loadtxt(fp, delimiter=' ')
        enc_mean, enc_stdev = get_mean_stdev(dname * 4000 / data[1,:] /1024/1024)
        dec_mean, dec_stdev = get_mean_stdev(dname * 4000 / data[2,:] /1024/1024)

        print(f'{dname} & ${enc_mean:.4f} \\pm {enc_stdev:.4f}$ & ${dec_mean:.4f} \\pm {dec_stdev:.4f}$')
