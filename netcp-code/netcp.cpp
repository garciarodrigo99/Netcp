// g++-13 -o netcp -std=c++23 -g netcp.cpp menu.cpp
// Generación aleatoria de solo numeros y caracteres:
// LC_CTYPE=C tr -dc 'a-zA-Z0-9' </dev/urandom | head -c 1024 >testfile

#include "menu.hpp"
#include "socket_functions.hpp"
#include "file_functions.hpp"
#include "message_functions.hpp"


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

    auto open_file_result = open_file("testfile.txt", O_RDONLY, 0);
    if (!open_file_result) {
        std::cerr << "Error al abrir el archivo: " << open_file_result.error().message() << std::endl;
        netcpErrorExit(Netcp_errors::FILE_NOT_FOUND_ERROR);
    }

    int fd = open_file_result.value();
    std::vector<uint8_t> buffer(1024);  // Tamaño del buffer, puedes ajustarlo según tus necesidades

    auto read_open_file_result = read_file(fd, buffer);
	std::cout << "read_open_file_result: " << read_open_file_result << std::endl;
    if (read_open_file_result) {
        std::cerr << "Error al leer el archivo: " << read_open_file_result.message() << std::endl;
        return read_open_file_result.value();
    }
	
	//auto address = make_ip_address("192.168.10.2", 8080);
	auto make_socket_result = make_socket();
	if (make_socket_result){
		int sock_fd = make_socket_result.value();
	}
	sockaddr_in remote_address = make_ip_address(std::nullopt,8080).value();
	std::string message_text("¡Hola, mundo!");
	
	send_to(make_socket_result.value(),message_text,remote_address);
	send_to(make_socket_result.value(),buffer,remote_address);

	close(make_socket_result.value());

  return EXIT_SUCCESS;
}