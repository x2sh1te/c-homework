import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('results.csv')

X_real = df['N'].values
Y_real = df['Time(seconds)'].values

N_last = X_real[-1]
Time_last = Y_real[-1]

k_coeff = Time_last / (N_last ** 2)

X_predict = list(range(0, 2000001, 20000))
Y_predict = [k_coeff * (n ** 2) for n in X_predict]

plt.figure(figsize=(10, 6))
plt.scatter(X_real, Y_real, color='blue', label='Реальные данные', zorder=5)
plt.plot(X_predict, Y_predict, color='red', linestyle='--', label='Прогноз $O(N^2)$')
plt.title('График времени работы и прогноз')
plt.xlabel('Количество людей (N)')
plt.ylabel('Время (в секундах)')
plt.legend()
plt.grid(True)
plt.show()
