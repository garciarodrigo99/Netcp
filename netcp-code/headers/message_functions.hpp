#include <bits/socket.h>
#include <system_error>
#include <string>
#include <vector>
#include <iostream>
#include <format>
#include "netinet/in.h"
#include "netcp_errors.hpp"
#include "trace_macro.hpp"

#define UDP_SIZE 1024

std::error_code send_to(int fd, const std::string& message,const sockaddr_in& address){
    int bytes_sent = sendto(fd,
            message.data(), message.size(), 
			0,
			reinterpret_cast<const sockaddr*>(&address),sizeof(address));

	if (bytes_sent < 0) {
		std::cerr << "Error en send_to: " << Netcp_errors::UNSENT_BYTES_ERROR.error_text;
        std::error_code(Netcp_errors::FILE_MISSING_ERROR.error_code, 
								std::system_category());
	}
    return std::error_code(0, std::system_category());
}


std::error_code send_to(int fd, const std::vector<uint8_t>& message,const sockaddr_in& address){
    int bytes_sent = sendto(fd,
            message.data(), message.size(), 
			0,
			reinterpret_cast<const sockaddr*>(&address),sizeof(address));

	if (bytes_sent < 0) {
		std::cerr << "Error en send_to: " << Netcp_errors::UNSENT_BYTES_ERROR.error_text;
        std::error_code(Netcp_errors::UNSENT_BYTES_ERROR.error_code, 
								std::system_category());
	}
    return std::error_code(0, std::system_category());
}

std::error_code receive_from(int fd, std::string& message, sockaddr_in& address){
	socklen_t src_len = sizeof(address);
	int bytes_read = recvfrom(fd,
							message.data(), message.size(), 
							0,
							reinterpret_cast<sockaddr*>(&address),
							&src_len);
	if (bytes_read < 0){
		std::cerr << "Error en send_to: " << Netcp_errors::UNRECEIVED_BYTES_ERROR.error_text;
        std::error_code(Netcp_errors::UNRECEIVED_BYTES_ERROR.error_code, 
								std::system_category());
	}
	message.resize(bytes_read);
	// Imprimir el mensaje y la dirección del remitente
	std::cout << std::format("El sistema '{}'' envió el mensaje '{}'\n",
							ip_address_to_string(address),
							message.c_str());
	return std::error_code(0, std::system_category());
}

std::error_code receive_from(int fd, std::vector<uint8_t>& message, 
							sockaddr_in& address){
							
	socklen_t src_len = sizeof(address);
	int bytes_read = recvfrom(fd,
							message.data(), message.size(), 
							0,
							reinterpret_cast<sockaddr*>(&address),
							&src_len);
	if (bytes_read < 0){
		std::cerr << "Error en send_to: " << Netcp_errors::UNRECEIVED_BYTES_ERROR.error_text;
        std::error_code(Netcp_errors::UNRECEIVED_BYTES_ERROR.error_code, 
								std::system_category());
	}
	message.resize(bytes_read);

	std::string output(message.begin(),message.end());
	// Imprimir el mensaje y la dirección del remitente
	std::cout << std::format("El sistema '{}'' envió el mensaje '{}'\n",
							ip_address_to_string(address),
							output);	
	return std::error_code(0, std::system_category());
}

std::error_code netcp_send_file(const std::string& filename,
								int sock_fd,
								const sockaddr_in& remote_address){
	TRACE_MSG("Traza activada");		
	auto open_file_result = open_file(filename, O_RDONLY, 0);
    if (!open_file_result) {
        std::cerr << "Error al abrir el archivo: " << open_file_result.error().message() << std::endl;
        netcpErrorExit(Netcp_errors::FILE_NOT_FOUND_ERROR);
    }

    int open_file_fd = open_file_result.value();
    std::vector<uint8_t> buffer(UDP_SIZE);  // Tamaño del buffer

	while (true)
	{
		auto read_file_result = read_file(open_file_fd, buffer);
		//std::cout << "read_file_result: " << read_file_result << std::endl;
    	if (read_file_result) {
        	std::cerr << "Error al leer el archivo: " << read_file_result.message() << std::endl;
        	netcpErrorExit(Netcp_errors::FILE_NOT_FOUND_ERROR);
    	}

		// Verificar si llega al final del archivo
        if (buffer.empty()) {
			TRACE_MSG("Buffer vacío");
            break;
        }
		TRACE_MSG("----- Leído: -----");
		TRACE_VECTOR(buffer);
		TRACE_MSG("------------------");
        auto send_result = send_to(sock_fd, buffer, remote_address);
        if (send_result) {
            std::cerr << "Error al enviar el archivo: " << send_result.message() << std::endl;
            netcpErrorExit(Netcp_errors::UNSENT_BYTES_ERROR);
        }

        // Limpiar el búfer
        buffer.resize(UDP_SIZE);
		// // Cerrar el descriptor de la llamada a read_file
		// close(read_file_result.value());

		send_to(sock_fd,buffer,remote_address);
	}
	

	// Cerrar el descriptor de la llamada a open_file
	close(open_file_fd);

	// Cerrar el descriptor de la llamada a make_socket
	return std::error_code(0, std::system_category());
}

std::error_code netcp_receive_file(const std::string& filename);