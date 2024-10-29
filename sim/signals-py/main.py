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


def img_draw(array):
    length = array.shape[0]
    plt.plot(range(length), array)


waveform = txt2array("./waveform.txt")
spectrum = txt2array("./spectrum.txt")

img_draw(waveform)
plt.show()
