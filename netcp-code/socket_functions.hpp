#include <iostream>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdint>
#include <cstring>  // Para la función std::strchr
#include <optional>
#include <expected>
#include <system_error>
#include "netcp_errors.hpp"

std::string ip_address_to_string(const sockaddr_in& address){
	in_addr_t s_addr = address.sin_addr.s_addr;
	in_addr addr;
    addr.s_addr = s_addr;

	std::string ip_str(inet_ntoa(addr));

    // Concatenar la dirección IP y el número de puerto separados por ':'
    std::string result = ip_str + ":" + std::to_string(ntohs(address.sin_port));

    return result;
}

std::optional<sockaddr_in> make_ip_address(const std::optional<std::string> ip_address, 
											uint16_t port = 0) {

	// Configuración por defecto.
	sockaddr_in address{};
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr;

	// Si se indica un número negativo,se establece como cero para que el sistema se encargue.
	if (port < 0) {
		port = 0;
	}
	

	if (ip_address) {
		// Si se proporciona una dirección IP, intentamos parsearla
		if (std::strchr(ip_address->c_str(), ':') != nullptr) {
			// Si la dirección IP contiene un ':' asumimos que también se proporciona el puerto

			if(port != 0){
				std::cerr << "Valor indicado dos maneras distintas.\n";
				return std::nullopt;				
			}
			std::string ip;
			uint16_t new_port;

			// Dividimos la cadena en la dirección IP y el puerto
			std::size_t colon_pos = ip_address->find(':');
			ip = ip_address->substr(0, colon_pos);
			std::string port_str = ip_address->substr(colon_pos + 1);

			// Intentamos convertir la parte del puerto a un número
			try {
					new_port = std::stoi(port_str);
			} catch (const std::invalid_argument& e) {
					std::cerr << "Error: Puerto no válido.\n";
					return std::nullopt;
			}

			// Actualizamos la estructura sockaddr_in
			address.sin_port = htons(new_port);
			if (inet_aton(ip.c_str(), &(address.sin_addr)) <= 0) {
					std::cerr << "Error: Dirección IP no válida.\n";
					return std::nullopt;
			}

		} else {
				// Si no hay ':' asumimos que solo se proporciona la dirección IP
				if (inet_aton(ip_address->c_str(), &(address.sin_addr)) <= 0) {
						std::cerr << "Error: Dirección IP no válida.\n";
						return std::nullopt;
				}
		}
	} else {
			// Si no se proporciona una dirección IP, dejamos la dirección IP como INADDR_ANY
			address.sin_addr.s_addr = INADDR_ANY;
	}

	return address;
}

//[[nodiscard]]
using make_socket_result = std::expected<int, std::error_code>;
make_socket_result make_socket(
std::optional<sockaddr_in> address = std::nullopt){
	// Crear el socket
	/*
	* AF_INET: TCP/IP
	* SOCK_DGRAM: UDP
	* protocol: 0
	*/
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        // Error al crear el socket
        return std::unexpected(std::error_code(
								Netcp_errors::FILE_MISSING_ERROR.error_code, 
								std::system_category()));
    }																		
    // Si se proporciona una dirección, intentar asignarla al socket
    if (address.has_value()) {
        sockaddr_in addr = address.value();
		int bind_result = bind(sock_fd, reinterpret_cast<const sockaddr*>(&addr), 
								sizeof(addr));
        if (bind_result < 0) {
        	close(sock_fd);  // Cerrar el socket

            // Devolver un error específico de bind
            return std::unexpected(std::error_code(
									Netcp_errors::ADDRESS_ASSIGMENT_ERROR.error_code, 
									std::system_category()));
        }
    }

    // La función ha tenido éxito, retornar el descriptor de socket
    return sock_fd;
}