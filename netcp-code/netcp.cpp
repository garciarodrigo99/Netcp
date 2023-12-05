// g++-13 -o netcp -std=c++20 -g netcp.cpp menu.cpp
// Generación aleatoria de solo numeros y caracteres:
// LC_CTYPE=C tr -dc 'a-zA-Z0-9' </dev/urandom | head -c 1024 >testfile

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

	std::string file_path = "testfile.txt";  // Reemplaza con la ruta a tu archivo
    int flags = O_RDONLY;
    mode_t mode = 0;  // Modo no relevante para la apertura de lectura

    auto result = open_file(file_path, flags, mode);
    if (!result) {
        std::cerr << "Error al abrir el archivo: " << result.error().message() << std::endl;
        return result.error().value();
    }

    int fd = result.value();
    std::vector<uint8_t> buffer(1024);  // Tamaño del buffer, puedes ajustarlo según tus necesidades

    auto read_result = read_file(fd, buffer);
	std::cout << "read_result: " << read_result << std::endl;
    if (!read_result) {
        std::cout.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
        std::cout << std::endl;
    } else {
        std::cerr << "Error al leer el archivo: " << read_result.message() << std::endl;
        return read_result.value();
    }
	
	// auto address = make_ip_address(std::nullopt);
	// auto socket = make_socket(address.value());
	// if (socket) {
	// 	auto sock_fd = socket.value();
	// 	std::cout << sock_fd << std::endl;
	// }

  return EXIT_SUCCESS;
}