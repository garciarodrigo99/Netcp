// Archivo de cabecera para seguir una traza en caso de que así se indique en 
// al compilar. Simplemente es una función a la que se llama y en caso de que 
// el flag de traza esté activado se imprime el mensaje pasado por parámetro.

#ifndef TRACE_MACRO_HPP
#define TRACE_MACRO_HPP

#include <iostream>

#ifdef TRACE
#define TRACE_MSG(message) std::cout << "TRACE: " << message << std::endl
#else
#define TRACE_MSG(message)
#endif

#endif // TRACE_MACRO_HPP
