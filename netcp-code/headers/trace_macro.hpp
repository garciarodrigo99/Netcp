// Archivo de cabecera para seguir una traza en caso de que así se indique en 
// al compilar. Simplemente es una función a la que se llama y en caso de que 
// el flag de traza esté activado se imprime el mensaje pasado por parámetro.

#ifndef TRACE_MACRO_HPP
#define TRACE_MACRO_HPP

#include <iostream>
#include <vector>

#ifdef TRACE
// Función de utilidad para imprimir elementos de un vector
template <typename T>
void print_vector(const std::vector<T>& vec) {
    std::cout << "[";
    for (const auto& elem : vec) {
        std::cout << elem;
    }
    std::cout << "]" << std::endl;
}
#define TRACE_MSG(message) std::cout << "TRACE: " << message << std::endl
#define TRACE_VECTOR(vec) print_vector(vec)

#else

#define TRACE_MSG(message)
#define TRACE_VECTOR(vec)

#endif

#endif // TRACE_MACRO_HPP
