import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as signal
import pywt

y_data = np.loadtxt("output.txt")
y_data = y_data - y_data[0]
width = len(y_data)
y_filter = y_data[int(width / 2) - 50 : int(width / 2) + 50]
# append zeros to the beginning and end of the filter
y_conv = signal.fftconvolve(y_data, y_filter, mode="full")
plt.plot(y_conv)
plt.show()
