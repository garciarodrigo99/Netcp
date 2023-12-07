# Proyecto Netcp

Este proyecto implementa un sistema de transferencia de archivos llamado Netcp. A continuación, se presenta la estructura del directorio de trabajo:

## Estructura del Proyecto

- **headers**: Contiene los archivos de cabecera (`.hpp`) necesarios para el proyecto.
  - `file_functions.hpp`: Funciones relacionadas con la manipulación de archivos.
  - `menu.hpp`: Definiciones relacionadas con el menú del programa.
  - `message_functions.hpp`: Funciones relacionadas con el manejo de mensajes.
  - `netcp_errors.hpp`: Definiciones de errores específicos de Netcp.
  - `socket_functions.hpp`: Funciones relacionadas con la manipulación de sockets.

- **pruebas**: Contiene archivos de prueba y código relacionado con pruebas.
  - `prueba`: Ejecutable de prueba.
  - `prueba.cc`: Código fuente de la prueba.

- **textfiles**: Contiene archivos de texto para pruebas.
  - `testfile2.txt`: Archivo de texto de prueba 2.
  - `testfile.txt`: Archivo de texto de prueba.

- **Netcp-workspace.code-workspace**: Configuración del espacio de trabajo para Visual Studio Code.

- **netcp.cpp**: Archivo fuente principal del proyecto.

## Cómo Compilar y Ejecutar

Para **compilar** el proyecto: 
```bash 
g++-13 -o netcp -std=c++23 -g netcp.cpp
```

Para **ejecutar** el proyecto: 
```bash 
# Como máquina emisora
./netcp -o <file_location>

# Como máquina receptora
./netcp -l <port_number>
```
## Notas
```info
! README.md generado con ChatGPT a partir de la salida del comando tree
Se modificó la salida para adecuar la descripción al directorio
```