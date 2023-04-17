import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

fig = plt.figure()

df = pd.read_csv("runtime_aleatorio.csv")
df['cota'] = df['n']

ax1 = sns.lmplot(x='time', y='cota', data=df)
plt.xlabel("tiempo (s)")
plt.ylabel("cota teorica")

df['log_time'] = np.log(df['time'])
df['log_cota'] = np.log(df['cota'])
ax1 = sns.lmplot(x='log_time', y='log_cota', data=df)
plt.xlabel("log_tiempo (s)")
plt.ylabel("log_cota")

r = np.corrcoef(df['log_time'], df['log_cota'])[0, 1];
print("El coeficiente de correlación de Pearson es: r="+str(r))


df = pd.read_csv("runtime_comprimido.csv")
df2 = pd.read_csv("runtime_separado.csv")
df['time_comprimido'] = df2['time']

fig, ax = plt.subplots()

ax.scatter(np.log(df['n']),np.log(df['time']),color='red')
ax.plot(np.log(df['n']),np.log(df['time']),color='red', label='comprimido')
ax.scatter(np.log(df['n']),np.log(df['time_comprimido']),color='blue')
ax.plot(np.log(df['n']),np.log(df['time_comprimido']),color='blue', label='separado')

plt.xlabel("log_n")
plt.ylabel("log_tiempo (s)")

ax.legend()
ax.grid(True)

plt.show()

log_c = np.average(np.log(df['time_comprimido']) - np.log(df['time']))
print("La constante entre ambos conjuntos de datos es c=" + str(np.exp(log_c)))