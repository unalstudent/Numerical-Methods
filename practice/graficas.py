import pandas as pd
import matplotlib.pyplot as plt

# ==========================================
# 1. CARGAR LOS DATOS
# ==========================================
# Cambia 'datos.txt' por el nombre o ruta de tu archivo.
# El parámetro 'sep' define cómo están separados los datos:
# ',' para comas | '\t' para tabulaciones | ' ' para espacios
df = pd.read_csv('gemelos.txt', sep=',')

# Imprimir las primeras filas para verificar que los datos se leyeron correctamente
print("Datos cargados:")
print(df.head())

# ==========================================
# 2. ASIGNAR VARIABLES
# ==========================================
# Cambia 'NombreColumnaX' y 'NombreColumnaY' por los nombres reales de tus columnas
x = df['twins']
y = df['norma']

# ==========================================
# 3. CREAR Y CONFIGURAR LA GRÁFICA
# ==========================================
plt.figure(figsize=(10, 6))  # Tamaño de la gráfica (ancho, alto)

# Gráfica de línea (puedes cambiar 'plot' por 'scatter' para puntos o 'bar' para barras)
plt.plot(x, y, 
         marker='o',         # Estilo de los puntos ('o', 's', '^', etc.)
         linestyle='-',      # Estilo de la línea ('-', '--', '-.', ':')
         color='blue',       # Color de la línea
         label='Datos 1')    # Etiqueta para la leyenda

# ==========================================
# 4. PERSONALIZACIÓN
# ==========================================
plt.title('Título Principal de la Gráfica', fontsize=16)
plt.xlabel('Nombre del Eje X', fontsize=12)
plt.ylabel('Nombre del Eje Y', fontsize=12)

# Añadir una cuadrícula de fondo para facilitar la lectura
plt.grid(True, linestyle='--', alpha=0.7)

# Mostrar la leyenda
plt.legend()

# ==========================================
# 5. MOSTRAR O GUARDAR
# ==========================================
# Descomenta la siguiente línea si quieres guardar la gráfica como imagen:
plt.savefig('resultado.png', dpi=300, bbox_inches='tight')

# Mostrar la gráfica en pantalla
# plt.show()