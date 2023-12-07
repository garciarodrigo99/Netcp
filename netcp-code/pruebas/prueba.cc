// g++-13 -o netcp -std=c++23 -g netcp.cpp menu.cpp
// Generación aleatoria de solo numeros y caracteres:
// LC_CTYPE=C tr -dc 'a-zA-Z0-9' </dev/urandom | head -c 1024 >testfile

#include "../headers/menu.hpp"
#include "../headers/socket_functions.hpp"
#include "../headers/file_functions.hpp"

int main(int args, char* argv[]){
    // Crear el socket
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        std::cerr << "Error al crear el socket" << std::endl;
        return 1;
    }

    // Configurar la dirección
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Escuchar en cualquier dirección
    address.sin_port = htons(0);           // Puerto 0 para que el sistema elija uno dinámicamente

    // Asignar el socket a la dirección
    if (bind(sock_fd, reinterpret_cast<const sockaddr*>(&address), sizeof(address)) == -1) {
        std::cerr << "Error en bind: " << strerror(errno) << std::endl;
        close(sock_fd);
        return 1;
    }

    // Ahora, address.sin_port contiene el puerto elegido por el sistema
    std::cout << "Puerto asignado: " << ntohs(address.sin_port) << std::endl;

    // Preparar datos para sendto
    std::string message = "Adios desde sendto";
    sockaddr_in remote_address{};
    remote_address.sin_family = AF_INET;
    remote_address.sin_addr.s_addr = inet_addr("0.0.0.0");  // Dirección de destino
    remote_address.sin_port = htons(8080);                      // Puerto de destino

    // Llamada a sendto
    int bytes_sent = sendto(sock_fd, message.c_str(), message.size(), 0,
                            reinterpret_cast<const sockaddr*>(&remote_address), sizeof(remote_address));
    if (bytes_sent < 0) {
        std::cerr << "Error en sendto: " << strerror(errno) << std::endl;
    } else {
        std::cout << "Bytes enviados: " << bytes_sent << std::endl;
    }

    // Cerrar el socket cuando ya no lo necesites
    close(sock_fd);

    return 0;
}