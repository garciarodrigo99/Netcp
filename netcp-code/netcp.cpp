// g++-13 -o netcp -std=c++23 -g netcp.cpp menu.cpp
// Generación aleatoria de solo numeros y caracteres:
// LC_CTYPE=C tr -dc 'a-zA-Z0-9' </dev/urandom | head -c 1024 >testfile

#include "menu.hpp"
#include "socket_functions.hpp"
#include "file_functions.hpp"
#include "message_functions.hpp"
#include <format>

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

void listeningMode(int listen_port){
	sockaddr_in remote_address{};
	socklen_t src_len = sizeof(remote_address);

	std::string message_text;
	message_text.resize(100);

	auto make_socket_result = make_socket();
	if (!make_socket_result){
		std::cerr << "Listening mode: ";
		netcpErrorExit(Netcp_errors::SOCKET_CREATION_ERROR);
	}
	int sock_fd = make_socket_result.value();

	int bytes_read = recvfrom(sock_fd,
							message_text.data(), message_text.size(), 
							0,
							reinterpret_cast<sockaddr*>(&remote_address),
							&src_len);
	if (bytes_read < 0){
	// Error al recibir el mensaje.
	}
	message_text.resize(bytes_read);
	// Imprimir el mensaje y la dirección del remitente
	std::cout << std::format("El sistema '{}'' envió el mensaje '{}'\n",
							ip_address_to_string(remote_address),
							message_text.c_str());
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

	if (options.value().listen){
		listeningMode(options.value().listen_port);
	}

    auto open_file_result = open_file(options.value().output_filename, O_RDONLY, 0);
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
	if (!make_socket_result){
		netcpErrorExit(Netcp_errors::SOCKET_CREATION_ERROR);
	}
	int sock_fd = make_socket_result.value();
	sockaddr_in remote_address = make_ip_address(std::nullopt,8080).value();
	std::string message_text("¡Hola, mundo!");
	
	send_to(sock_fd,message_text,remote_address);
	send_to(sock_fd,buffer,remote_address);

	close(sock_fd);

  return EXIT_SUCCESS;
}