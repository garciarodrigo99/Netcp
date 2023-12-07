// g++-13 -o prueba -std=c++23 -g prueba.cc
#include <unistd.h>  // Necesario para la llamada al sistema write
#include <iostream>
#include <vector>
#include <cstdint>
#include <fcntl.h>

int main() {

    // Datos que deseas escribir en el archivo
    std::vector<uint8_t> data = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x2C, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64};

    // Abre o crea un archivo llamado "output.txt" para escribir
    int file_descriptor = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (file_descriptor == -1) {
        perror("Error al abrir o crear el archivo");
        return 1;
    }

    // Llama a la llamada al sistema write
    ssize_t bytes_written = write(file_descriptor, data.data(), data.size());
    if (bytes_written == -1) {
        perror("Error al escribir en el archivo");
        close(file_descriptor);  // Cierra el archivo en caso de error
        return 1;
    }

    // Cierra el archivo después de escribir
    close(file_descriptor);

    std::cout << "Se han escrito " << bytes_written << " bytes en el archivo." << std::endl;

    return 0;
}
