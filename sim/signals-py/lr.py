import numpy as np
import matplotlib.pyplot as plt

y = np.array([1.202, 1.518, 2.462, 3.958, 4.049, 4.961, 5.715, 6.973, 8.397])
x = np.array([0.1, 0.5, 1, 1.5, 2, 2.5, 3, 4, 5])

coefficients = np.polyfit(x, y, 3)
polynomial = np.poly1d(coefficients)

x_ = np.linspace(x.min(), x.max(), 100)
y_ = polynomial(x_)

print(polynomial)

plt.plot(x, y, "o", label="Original", color="red", markersize=4)
plt.plot(x_, y_, "-", label="Linear fit", markersize=3)

plt.legend()
plt.show()
