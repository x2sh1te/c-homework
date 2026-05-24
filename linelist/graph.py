import csv
import matplotlib.pyplot as plt

N = []
time_vals = []

with open('result.csv', 'r', encoding='utf-8') as f:
    reader = csv.DictReader(f, delimiter=';')
    for row in reader:
        N.append(int(row['N']))
        time_vals.append(float(row['time']))

def predict_O_N2(n, base_n, base_time):
    return base_time * (n / base_n) ** 2

plt.plot(N, time_vals, 'o', label='Реальные данные', color='green', zorder=3)

max_N_pred = max(N) * 3
N_predict = list(range(min(N), max_N_pred + 1, 10000))
time_predict = [predict_O_N2(n, N[-1], time_vals[-1]) for n in N_predict]

plt.plot(N_predict, time_predict, '--', label='Прогноз O(N²)', color='red', zorder=4)

plt.xlabel('N')
plt.ylabel('Время (сек)')
plt.title('Зависимость времени от N с прогнозом')
plt.legend()
plt.grid(True)
plt.xlim(left=0)
plt.ylim(bottom=0)

plt.show()