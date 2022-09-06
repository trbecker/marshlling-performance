#!/usr/bin/python3

import sys
import os.path
import numpy as np

def get_mean_stdev(data):
    return (np.average(data), np.std(data))

print('Time')
print('\\begin{tabular}{r|c|c}')
print('array elements & encoding (ms) & decoding (ms) \\\\ \\hline')
for dname in [256, 512, 1024, 2048, 4096]:
    with open(os.path.join(str(dname), 'results.dat'), 'r') as fp:
        data = np.loadtxt(fp, delimiter=' ')
        enc_mean, enc_stdev = get_mean_stdev(data[:,0])
        dec_mean, dec_stdev = get_mean_stdev(data[:,1])
        print(f'{dname} & ${enc_mean:.4f} \\pm {enc_stdev:.4f}$ & ${dec_mean:.4f} \\pm {dec_stdev:.4f}$ \\\\')
print('\\end{tabular}')

enc_tp_all = []
dec_tp_all = []

print('\nThroughput')
print('\\begin{tabular}{r|c|c}')
print('array elements & encoding (MiB/s) & decoding (MiB/s) \\\\ \\hline')
for dname in [256, 512, 1024, 2048, 4096]:
    with open(os.path.join(str(dname), 'results.dat'), 'r') as fp:
        data = np.loadtxt(fp, delimiter=' ')
        enc_tp = dname * 4000 / data[:,0] / 1024/ 1024
        dec_tp = dname * 4000 / data[:,1] / 1024/ 1024
        enc_mean, enc_stdev = get_mean_stdev(enc_tp)
        dec_mean, dec_stdev = get_mean_stdev(dec_tp)
        print(f'{dname} & ${enc_mean:.4f} \\pm {enc_stdev:.4f}$ & ${dec_mean:.4f} \\pm {dec_stdev:.4f}$ \\\\')
        enc_tp_all.append(enc_tp)
        dec_tp_all.append(dec_tp)
print('\\end{tabular}')

enc_tp_all_arr = enc_tp_all[0]
for a in enc_tp_all[1:]:
    enc_tp_all_arr = np.concatenate((enc_tp_all_arr, a))


dec_tp_all_arr = dec_tp_all[0]
for a in dec_tp_all[1:]:
    dec_tp_all_arr = np.concatenate((dec_tp_all_arr, a))

enc_tp_mean, enc_tp_stdev = get_mean_stdev(enc_tp_all_arr)
dec_tp_mean, dec_tp_stdev = get_mean_stdev(dec_tp_all_arr)

print(f'encoding: ${enc_tp_mean:.4f} \\pm {enc_tp_stdev:.4f}$ MiB/s')
print(f'decoding: ${dec_tp_mean:.4f} \\pm {dec_tp_stdev:.4f}$ MiB/s')
