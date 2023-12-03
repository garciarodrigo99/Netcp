// g++-13 -o netcp -std=c++23 netcp.cpp
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdint>
#include <system_error>
#include <vector>
#include <optional>
//#include <expected>

#define FILE_MISSING_ERROR 1
#define SOCK_CREATION_ERROR 3

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

// std::optional<sockaddr_in> make_ip_address(
// 							const std::optional<std::string> ip_address, 
// 							uint16_t port=0);

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
	
	// Comprobar que existe el archivo
  return 0;
}