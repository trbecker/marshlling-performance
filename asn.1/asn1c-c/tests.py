import sys
import numpy as np

def get_mean_stdev(data):
    return (np.average(data), np.std(data))

for fname in sys.argv[1:]:
    with open(fname, 'r') as fp:
        data = np.loadtxt(fp, delimiter=' ')
        enc_mean, enc_stdev = get_mean_stdev(data[1,:])
        dec_mean, dec_stdev = get_mean_stdev(data[2,:])
        print(f'${enc_mean:.4f} \\pm {enc_stdev:.4f}$ & ${dec_mean:.4f} \\pm {dec_stdev:.4f}$')
