#include <bits/socket.h>
#include <system_error>
#include <string>
#include <vector>
#include "netinet/in.h"
#include <iostream>
#include "netcp_errors.hpp"

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
        std::error_code(Netcp_errors::FILE_MISSING_ERROR.error_code, 
								std::system_category());
	}
    return std::error_code(0, std::system_category());
}