// g++-13 -o netcp -std=c++20 -g netcp.cpp menu.cpp
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <cstdint>
#include <system_error>
#include <vector>
#include <cstring>  // Para la función std::strchr
#include <optional>
//#include <expected>

#define FILE_MISSING_ERROR 1
#define SOCK_CREATION_ERROR 3
#define ADDRESS_ASSIGNMENT_ERROR 4

/*
 * ERROR 1: Falta nombre de archivo en los parametros de ejecución
*/

void help(char* program_name){
	printf("Modo de empleo: %s [-h] ORIGEN\n",program_name);
}

/*
* Dada una cadena std::string, obtener la variable de entorno en un objeto 
* std::string
*/
std::string getenv(const std::string& name)
{
	char* value = getenv(name.c_str());
	if (value) {
		return std::string(value);
	}
	else {
		return std::string();
	}
}

std::string ip_address_to_string(const sockaddr_in& address){
	in_addr_t s_addr = address.sin_addr.s_addr;
	in_addr addr;
    addr.s_addr = s_addr;

	std::string ip_str(inet_ntoa(addr));

    // Concatenar la dirección IP y el número de puerto separados por ':'
    std::string result = ip_str + ":" + std::to_string(ntohs(address.sin_port));

    return result;
}

std::optional<sockaddr_in> make_ip_address(const std::optional<std::string> ip_address, uint16_t port = 0) {

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

// std::error_code read_file(int fd, const std::vector<uint8_t>& buffer);

// using make_socket_result = std::expected<int, std::error_code>;

// make_socket_result make_socket(std::optional<sockaddr_in> address = std::nullopt);
// std::error_code send_to(int fd, 
// 						const std::vector<uint8_t>& message,
// 						const sockaddr_in& address);

int main(int args, char* argv[]){

	// Comprobar argumento 1
	if (args == 1){
		fprintf(stderr,"%s: falta un archivo como argumento\n",argv[0]);
		help(argv[0]);
		return FILE_MISSING_ERROR;
	}

	if ((argv[1] == "-h") || argv[1] == "--help"){
		help(argv[0]);
		return 0;
	}

	/*
	* AF_INET: TCP/IP
	* SOCK_DGRAM: UDP
	* protocol: 0
	*/
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (fd < 0) {
		fprintf(stderr," Error al crear el socket\n");
		return SOCK_CREATION_ERROR;
	}
	printf("%d\n",fd);
	sockaddr_in local_address{};
	// Domain TCP/IP
	local_address.sin_family = AF_INET;
	// Establecer cualquier direccion usando conversor de hexadecimal a long.
	local_address.sin_addr.s_addr = htonl(INADDR_ANY);
	// Asignar cualquier puerto.
	local_address.sin_port = htons(0); 
	
	int result = bind(fd,reinterpret_cast<const sockaddr*>(&local_address), sizeof(local_address) );
	if (result < 0) {
		fprintf(stderr,"Error al asignar una dirección\n");
		return ADDRESS_ASSIGNMENT_ERROR;
	}

	auto address = make_ip_address(std::nullopt);
	auto address2 = make_ip_address(std::nullopt, 8080);
	auto address3 = make_ip_address("192.168.10.2");
	auto address4 = make_ip_address("192.168.10.2:8080");
	auto address5 = make_ip_address("192.168.10.2", 8080);
	auto address6 = make_ip_address("192.168.10.2:8080", 1234); 

	if (address5.has_value()) {
		const sockaddr_in& direccion = *address5;
		std::cout << ip_address_to_string(direccion) << std::endl;
	}
	
	

  return 0;
}