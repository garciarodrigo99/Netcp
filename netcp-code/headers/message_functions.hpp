#include <bits/socket.h>
#include <system_error>
#include <string>
#include <vector>
#include "netinet/in.h"
#include <iostream>
#include "netcp_errors.hpp"
#include <format>

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