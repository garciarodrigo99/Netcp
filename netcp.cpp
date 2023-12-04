// g++-13 -o netcp -std=c++20 -g netcp.cpp menu.cpp

#include "socket_functions.hpp"

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
		return Netcp_errors::FILE_MISSING_ERROR;
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
		return Netcp_errors::SOCK_CREATION_ERROR;
	}
	// printf("%d\n",fd);
	sockaddr_in local_address{};
	// Domain TCP/IP
	local_address.sin_family = AF_INET;
	// Establecer cualquier direccion usando conversor de hexadecimal a long.
	local_address.sin_addr.s_addr = htonl(INADDR_ANY);
	// Asignar cualquier puerto.
	local_address.sin_port = htons(0); 
	
	// // Asignar dirección
	int result = bind(fd,reinterpret_cast<const sockaddr*>(&local_address), sizeof(local_address) );
	if (result < 0) {
		fprintf(stderr,"Error al asignar una dirección\n");
		return Netcp_errors::ADDRESS_ASSIGNMENT_ERROR;
	}

	// auto address = make_ip_address(std::nullopt);
	// auto address2 = make_ip_address(std::nullopt, 8080);
	// auto address3 = make_ip_address("192.168.10.2");
	// auto address4 = make_ip_address("192.168.10.2:8080");
	// auto address5 = make_ip_address("192.168.10.2", 8080);
	// //auto address6 = make_ip_address("192.168.10.2:8080", 1234); 

	// if (address5.has_value()) {
	// 	const sockaddr_in& direccion = *address5;
	// 	std::cout << ip_address_to_string(direccion) << std::endl;
	// }
	
	auto address7 = make_ip_address("127.0.0.1", 8080);
	auto result7 = make_socket(address7.value());
	if (result7) {
		int sock_fd = result7.value();
		std::cout << "Socket: " << sock_fd << std::endl;
	}
	auto result8 = make_socket();
	if (result8) {
		int sock_fd = result8.value();
		std::cout << "Socket: " << sock_fd << std::endl;
	}
	auto address9 = make_ip_address("127.0.0.1");
	auto result9 = make_socket(address9.value());
	if (result9) {
		int sock_fd = result9.value();
		std::cout << "Socket: " << sock_fd << std::endl;
	}

  return 0;
}