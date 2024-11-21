import numpy as np
import pandas as pd
import matplotlib.pyplot as plt


def txt2array(file):
    with open(file, "r") as f:
        lines = f.readlines()

    waveform = []

    for line in lines:
        line = line.split("\n")[0]
        waveform.append(float(line))

    return np.array(waveform)


def img_draw(array, label=None):
    length = array.shape[0]
    if label == None:
        plt.plot(range(length), array)
    else:
        plt.plot(range(length), array, label=label)


waveform = txt2array("./waveform.txt")
out_demodulated = txt2array("./demodulated.txt")
out_spectrum = txt2array("./spectrum.txt")

img_draw(waveform, "waveform")
img_draw(out_demodulated, "demodulated")
plt.legend()
plt.show()
img_draw(out_spectrum)
plt.show()
