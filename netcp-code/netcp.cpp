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

	// // printf("%d\n",fd);
	// sockaddr_in local_address{};
	// // Domain TCP/IP
	// local_address.sin_family = AF_INET;
	// // Establecer cualquier direccion usando conversor de hexadecimal a long.
	// local_address.sin_addr.s_addr = htonl(INADDR_ANY);
	// // Asignar cualquier puerto.
	// local_address.sin_port = htons(0); 
	
	auto socket = make_socket();
	if (socket) {
		auto sock_fd = socket.value();
		std::cout << sock_fd << std::endl;
	}
  return 0;
}