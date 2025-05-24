import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Загрузка данных
data = pd.read_csv('res.csv')

# Список цветов 
custom_colors = ['red', 'blue', 'green', 'orange', 'purple', 'cyan']

# Создание графика
plt.figure(figsize=(12, 8))
sns.lineplot(data=data, x='Размер матрицы', y='Время мс', 
             hue='Кол-во потоков', palette=custom_colors, marker='o')

plt.title('Matrix')
plt.xlabel('Размер матрицы')
plt.ylabel('Время мс')
plt.grid(True)
plt.legend(title='Кол-во потоков')
plt.tight_layout()

# Сохранение графика
plt.savefig('matrix.png', dpi=300)
plt.show()