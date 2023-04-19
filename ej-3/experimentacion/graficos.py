import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = "serif"
plt.rcParams["font.serif"] = ["Times New Roman"]
config = {"fontsize":20, "labelpad":20}

# plot aleatorios
df = pd.read_csv("./out/runtime_aleatorio.csv")

f, ax = plt.subplots(figsize=(7, 7))
sns.regplot(x="n", y="time", data=df, ax=ax, order=2) #, ci=None)
ax.set_xscale("log", base=2)
ax.set_yscale("log", base=2)
ax.set_xlabel("tamaño de la entrada", **config)
ax.set_ylabel("tiempo (segundos)", **config)
ax.tick_params(labelsize=16, size=10)
ax.grid()
f.savefig("./out/aleatorio.png", bbox_inches='tight')

r = np.corrcoef(df['time'], df['n'])[0, 1]
print("El coeficiente de correlación de Pearson para aleatorio es: r="+str(r))

# plot comparacion
df = pd.read_csv("./out/runtime_comprimido.csv")
df2 = pd.read_csv("./out/runtime_separado.csv")

f, ax = plt.subplots(figsize=(7, 7))
ax.scatter(df["n"], df["time"], color='orange')
ax.plot(df["n"], df["time"], color='orange', label='comprimida')
ax.scatter(df2["n"], df2["time"])
ax.plot(df2["n"], df2["time"], label='separadas')
ax.set_xscale("log", base=2)
ax.set_yscale("log", base=2)
ax.set_xlabel("tamaño de la entrada", **config)
ax.set_ylabel("tiempo (segundos)", **config)
ax.tick_params(labelsize=16, size=10)
ax.grid()
ax.legend(fontsize="xx-large")
f.savefig("./out/comparacion.png", bbox_inches='tight')

c = np.average(df2['time'] - df['time'])
print("La constante entre ambos conjuntos de datos es c=" + str(c))
