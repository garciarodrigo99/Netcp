#include <vector>
#include <cstdint>
#include <unistd.h>
#include <cerrno>
#include <system_error>
#include <expected>
#include <fcntl.h>

[[nodiscard]]
std::expected<int, std::error_code> open_file(const std::string& path, 
                                                int flags, mode_t mode) {
    int fd = open(path.c_str(), flags, mode);
    if (fd == -1) {
        std::error_code error(errno, std::system_category());
        return std::unexpected(error);
    }
    return fd;
}

[[nodiscard]]
std::error_code read_file(int fd, std::vector<uint8_t>& buffer) {
    ssize_t bytes_read = read(fd, buffer.data(), buffer.size());
    if (bytes_read < 0) {
        return std::error_code(errno, std::system_category());
    }
    buffer.resize(bytes_read);
    return std::error_code(0, std::system_category());
}

[[nodiscard]]
std::error_code write_file(int fd, const std::vector<uint8_t>& buffer){

    ssize_t bytes_write = write(fd, buffer.data(), buffer.size());
    if (bytes_write < 0) {
        return std::error_code(errno, std::system_category());
    }
    return std::error_code(0, std::system_category());
}