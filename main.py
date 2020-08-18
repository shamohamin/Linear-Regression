import pandas as pd
import matplotlib.pyplot as plt
import os
import subprocess

df = pd.read_csv('train.csv')

sale_price = df['SalePrice']
lot_area = df['LotArea']

hold = lot_area.copy()

data = zip(lot_area, sale_price)
pd.DataFrame(data=data).to_csv('pricing.csv', index=None)

lot_area = (lot_area - lot_area.min())/(lot_area.max() - lot_area.min())


def linear_regression(X, y, m_current=1, b_current=2, epochs=10000, learning_rate=.9):
    N = float(len(y))
    for i in range(epochs):
        y_current = (m_current * X) + b_current
        cost = sum([data**2 for data in (y_current-y)]) / N
        m_gradient = -(1/N) * sum(X * (y - y_current))
        b_gradient = -(1/N) * sum(y - y_current)
        m_current = m_current - (learning_rate * m_gradient)
        b_current = b_current - (learning_rate * b_gradient)
    return m_current, b_current, cost


# m_current, b_current, cost = linear_regression(lot_area, sale_price)

os.system("cd cpp_src && make ")
subproc = subprocess.Popen("./run.out", cwd='cpp_src', stdout=subprocess.PIPE)
outputs = subproc.communicate()[0]
os.system("cd cpp_src && make clean ")
print(str(outputs))
b_current, m_current, cost = outputs.decode('utf-8').split(':')


y = []
for i in lot_area:
    y.append(float(b_current) + float(i)*float(m_current))


plt.scatter(lot_area, sale_price)
plt.title('housing training sets')
plt.xlabel('Lot Area')
plt.ylabel('Sail Price')

plt.scatter(lot_area, y, color="red")
plt.show()
