// g++-13 -o netcp -std=c++20 -g netcp.cpp menu.cpp

#include "menu.hpp"
#include "socket_functions.hpp"
#include "file_functions.hpp"


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

// std::error_code send_to(int fd, 
// 						const std::vector<uint8_t>& message,
// 						const sockaddr_in& address);

int main(int args, char* argv[]){

	auto options = parse_args(args, argv);
	if (!options){
		return EXIT_FAILURE;
	}
	if (options.value().show_help) {
		help(argv[0]);
		return EXIT_SUCCESS;
	}
	if (options.value().output_filename.empty()){
		netcpErrorExit(Netcp_errors::FILE_MISSING_ERROR);
	}
	
	auto address = make_ip_address(std::nullopt);
	auto socket = make_socket(address.value());
	if (socket) {
		auto sock_fd = socket.value();
		std::cout << sock_fd << std::endl;
	}

  return EXIT_SUCCESS;
}