# Script que genera bloques de texto de 1024kib con el siguiente formato:
# 'Bloque n:
# 1024kb
# ...
# 1024kb
# '
# El tamaño se indica antes de ejecutar
# Se compila: python3 block.py > <archivo_salida>

def repetir_bloque(cantidad,bloque):
    print("Bloque ",cantidad+1,":",sep="")
    print(bloque)
    # print()

bloque = "1024kb\n" * 141  # Cada línea es "1024kb\n", se repite 100 veces
for i in range(100):
    repetir_bloque(i,bloque)
