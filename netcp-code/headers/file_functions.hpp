#include <vector>
#include <cstdint>
#include <unistd.h>
#include <cerrno>
#include <system_error>
#include <expected>
#include <fcntl.h>

// Abre un archivo con la ruta especificada y devuelve un objeto std::expected<int, std::error_code>.
// Si la apertura tiene éxito, devuelve el descriptor de archivo (fd). En caso de error, devuelve un
// objeto std::unexpected<int> que encapsula un std::error_code representando el error.
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

// Lee el contenido de un archivo dado su descriptor de archivo (fd) y lo almacena en un vector de bytes.
// Devuelve un std::error_code que indica si la operación de lectura fue exitosa o si ocurrió un error.
[[nodiscard]]
std::error_code read_file(int fd, std::vector<uint8_t>& buffer) {
    ssize_t bytes_read = read(fd, buffer.data(), buffer.size());
    if (bytes_read < 0) {
        return std::error_code(errno, std::system_category());
    }
    buffer.resize(bytes_read);
    return std::error_code(0, std::system_category());
}

// Escribe el contenido de un vector de bytes en un archivo dado su descriptor de archivo (fd).
// Devuelve un std::error_code que indica si la operación de escritura fue exitosa o si ocurrió un error.
[[nodiscard]]
std::error_code write_file(int fd, const std::vector<uint8_t>& buffer){

    ssize_t bytes_write = write(fd, buffer.data(), buffer.size());
    if (bytes_write < 0) {
        return std::error_code(errno, std::system_category());
    }
    return std::error_code(0, std::system_category());
}

