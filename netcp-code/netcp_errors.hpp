/*
    Definición de una struct para manejar los errores.
    Se ha hecho de la siguiente manera pues se han encontrado problemas con 
    las clases tupla y pair a la hora de inicializar, ya que al parecer no se
    puede inicializar.
*/

#pragma once

struct ErrorStruct {
    int error_code;
    const char* error_text;
};

struct Netcp_errors {
    static constexpr ErrorStruct FILE_MISSING_ERROR{2,"No se especificó el archivo a enviar.\n"};
    static constexpr ErrorStruct SOCKET_CREATION_ERROR{3,"No se pudo crear el socket.\n"};
    static constexpr ErrorStruct ADDRESS_ASSIGMENT_ERROR{4,"No se pudo asignar una dirección al socket.\n"};
    static constexpr ErrorStruct FILE_NOT_FOUND_ERROR{5,"No se pudo abrir el archivo indicado.\n"};
    static constexpr ErrorStruct UNSENT_BYTES_ERROR{6,"No se ha podido enviar bytes.\n"};
};

void netcpErrorExit(const ErrorStruct& error_type){
    std::cerr << "Error: " << error_type.error_text;
    std::exit(error_type.error_code);
}