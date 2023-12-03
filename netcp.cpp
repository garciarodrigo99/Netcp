// g++-13 -o netcp -std=c++23 netcp.cpp
#include <stdio.h>

/*
 * ERROR 1: Falta nombre de archivo en los parametros de ejecución
*/

void help(char* program_name){
	printf("Modo de empleo: %s [-h] ORIGEN\n",program_name);
}

int main(int args, char* argv[]){

	// Comprobar argumento 1
	if (args == 1){
		printf("%s: falta un archivo como argumento\n",argv[0]);
		help(argv[0]);
		return 1;
	}

	if ((argv[1] == "-h") || argv[1] == "--help"){
		help(argv[0]);
		return 0;
	}
	
	// Comprobar que existe el archivo
  return 0;
}