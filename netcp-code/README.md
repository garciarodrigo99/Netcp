# Proyecto Netcp

Este proyecto implementa un sistema de transferencia de archivos llamado Netcp. A continuación, se presenta la estructura del directorio de trabajo:

## Estructura del Proyecto

- **headers**: Contiene los archivos de cabecera (`.hpp`) necesarios para el proyecto.
  - `file_functions.hpp`: Funciones relacionadas con la manipulación de archivos.
  - `menu.hpp`: Definiciones relacionadas con el menú del programa.
  - `message_functions.hpp`: Funciones relacionadas con el manejo de mensajes.
  - `netcp_errors.hpp`: Definiciones de errores específicos de Netcp.
  - `socket_functions.hpp`: Funciones relacionadas con la manipulación de sockets.
  - `trace_macro.hpp`: funcionalidades para el seguimiento de trazas en el código mediante la impresión condicional de mensajes.
- **pruebas**: Contiene archivos de prueba y código relacionado con pruebas.
  - `prueba`: Ejecutable de prueba.
  - `prueba.cc`: Código fuente de la prueba.

- **textfiles**: Contiene archivos de texto para pruebas.
  - `testfile2.txt`: Archivo de texto de prueba 2.
  - `testfile.txt`: Archivo de texto de prueba.

- **Netcp-workspace.code-workspace**: Configuración del espacio de trabajo para Visual Studio Code.

- **netcp.cpp**: Archivo fuente principal del proyecto.

## Cómo Compilar y Ejecutar
El proyecto cuenta con un archivo Makefile que contempla distintas tareas para adecuar la compilación y ejecución del programa.

Para **compilar** el proyecto: 
Modo normal, sin salida estándar, solo salida de error.
```bash 
make
```
Modo traza: el código mostrará diferentes mensajes colocados estratégicamente en el código para ir viendo la ejecución del programa.
```bash 
make trace
```

Para **ejecutar** el proyecto: 
Hay dos formas de ejecutar el programa:
#### Servidor
Para ejecutar el modo servidor se llamará a la opción server, a lo que se le pueden añadir diferentes opciones adicionales
```bash 
# Opción sin traza y pasándole el puerto en la ejecución del programa en la 
# respectiva tarea. En este modo la red es 0.0.0.0 ó 127.0.0.1
make server
# Igual que el caso anterior pero con la traza activada.
make server-trace
# En este caso el ejecutable tomará los valores de las variables de entono 
# NETCP_PORT y NETCP_IP para establecer el puerto y red de envío. En caso de 
# que estas variables de entorno no estén definidas el programa dará error.
make server-env
# Igual que el caso anterior pero con la traza activada.
make server-env-trace
```
#### Cliente
Para ejecutar el modo servidor se llamará a la opción client, a lo que se le pueden añadir diferentes opciones adicionales
```bash 
# Opción sin traza y pasándole el puerto en la ejecución del programa en la 
# respectiva tarea.
make client
# Igual que el caso anterior pero con la traza activada.
make client-trace
# En este caso el ejecutable tomará los valores de las variables de entono 
# NETCP_PORT para establecer el puerto de envío. En caso de que la variable
# de entorno no esté definida el programa dará error.
make client-env
# Igual que el caso anterior pero con la traza activada.
make client-env-trace
```
## Notas
```info
! README.md generado con ChatGPT a partir de la salida del comando tree
Se modificó la salida para adecuar la descripción al directorio
```