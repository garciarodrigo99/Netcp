def repetir_bloque(cantidad,bloque):
    print("Bloque ",cantidad,":",sep="")
    print(bloque)
    # print()

bloque = "1024kb\n" * 141  # Cada línea es "1024kb\n", se repite 100 veces
for i in range(100):
    repetir_bloque(i,bloque)
