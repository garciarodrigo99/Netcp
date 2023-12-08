// g++-13 -o netcp -std=c++23 -g netcp.cpp
// Generación aleatoria de solo numeros y caracteres:
// LC_CTYPE=C tr -dc 'a-zA-Z0-9' </dev/urandom | head -c 1024 >testfile

#include "headers/menu.hpp"
#include "headers/socket_functions.hpp"
#include "headers/file_functions.hpp"
#include "headers/message_functions.hpp"
#include "headers/trace_macro.hpp"
//#include <format>

void help(char* program_name){
	printf("Modo de empleo: %s [-h] ORIGEN\n",program_name);
}

/*
* Dada una cadena std::string, obtener la variable de entorno en un objeto 
* std::string. Se añadió barra baja al final ya que llamaba a la llamada del
* sistema, no a la del programa
*/
std::string getenv_(const std::string& name)
{
	char* value = getenv(name.c_str());
	if (value) {
		return std::string(value);
	}
	else {
		return std::string();
	}
}

/*
	Función que ejecuta el programa cuando se llama a la opción -l
*/
void listeningMode(int listen_port,const std::string& path){
	sockaddr_in remote_address{};
	socklen_t src_len = sizeof(remote_address);

	std::vector<uint8_t> buffer(1024);

	auto address = make_ip_address(std::nullopt, listen_port);
	auto make_socket_result = make_socket(address.value());
	if (!make_socket_result){
		std::cerr << "Listening mode: ";
		netcpErrorExit(Netcp_errors::SOCKET_CREATION_ERROR);
	}
	int sock_fd = make_socket_result.value();

	receive_from(sock_fd,buffer,remote_address);

    auto open_file_result = open_file(path, 
									O_WRONLY | O_CREAT, 
									0666);
    if (!open_file_result) {
		std::cerr << "Listening mode: ";
        std::cerr << "Error al abrir el archivo: " << open_file_result.error().message() << std::endl;
        netcpErrorExit(Netcp_errors::FILE_NOT_FOUND_ERROR);
    }

    int open_file_fd = open_file_result.value();

    auto write_file_result = write_file(open_file_fd, buffer);
	std::cout << "write_file_result: " << write_file_result << std::endl;
    if (write_file_result) {
		std::cerr << "Listening mode: ";
        std::cerr << "Error al escribir el archivo: " << open_file_result.error().message() << std::endl;
        netcpErrorExit(Netcp_errors::FILE_NOT_FOUND_ERROR);
    }

	// Cerrar el descriptor de la llamada a open_file
	close(open_file_fd);

	// Cerrar el descriptor de la llamada a write_file
	close(write_file_result.value());
}

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
	int port = options.value().port;
	if (options.value().port == 0){
		port = std::stoi(getenv_("NETCP_PORT"));
	}
	TRACE_MSG("Variable de entorno NETCP_PORT: " << getenv_("NETCP_PORT"));
	TRACE_MSG("Variable de entorno NETCP_IP: " << getenv_("NETCP_IP"));;
	if (options.value().listen){
		listeningMode(port,options.value().output_filename);
		return EXIT_SUCCESS;
	}

	// -Función enviar-
	auto make_socket_result = make_socket();
	if (!make_socket_result){
		netcpErrorExit(Netcp_errors::SOCKET_CREATION_ERROR);
	}
	int sock_fd = make_socket_result.value();

	sockaddr_in remote_address;

	if (options.value().env){
		remote_address = make_ip_address(getenv_("NETCP_IP"),port).value();
	} else{
		// Si no se elige usar las variables de entorno, make_ip_address se 
		// llama con std::nullopt para que se asigne 0.0.0.0 
		remote_address = make_ip_address(std::nullopt,port).value();
	}

	netcp_send_file(options.value().output_filename,sock_fd,remote_address);

	close(sock_fd);

  return EXIT_SUCCESS;
}