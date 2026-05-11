import csv
import matplotlib.pyplot as plt

# Читаем данные из CSV
N = []
time = []

with open('results.csv', 'r') as f:
    reader = csv.DictReader(f)
    for row in reader:
        N.append(int(row['N']))
        time.append(float(row['Time(seconds)']))

# Функция для прогноза O(N²)
def predict_O_N2(n, base_n, base_time):
    """Прогноз времени по квадратичной зависимости"""
    return base_time * (n / base_n) ** 2

# Строим реальные данные
plt.plot(N, time, 'o-', label='Реальные данные', color='green')

# Строим прогноз: берём первую точку как базу
N_predict = list(range(min(N), max(N) + 1, 1000))
time_predict = [predict_O_N2(n, N[0], time[0]) for n in N_predict]

plt.plot(N_predict, time_predict, '--', label='Прогноз O(N²)', color='red')

# Оформление
plt.xlabel('N')
plt.ylabel('Время (сек)')
plt.title('Зависимость времени от N')
plt.legend()
plt.grid(True)
plt.show()