#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int leerArchivo(char *path){
    FILE *archivo = NULL;
    int n;
    archivo = fopen(path, "r");
    if(!archivo){
    	fclose(archivo);
    	return 0;
	}
    else{
    	while(!feof(archivo)){
        	fscanf(archivo, "%d\n", &n);
            printf("Numero: %d\n", n);
        }
    }
    fclose(archivo);
    return 1;
}
int guardarArchivo(char *path, int n){
	FILE *archivo = NULL;
	archivo = fopen(path, "a");
	if(!archivo){
		fclose(archivo);
		return 0;
	}
	else{
		fprintf(archivo, "%d\n", n);
		fclose(archivo);
		return 1;
	}
}

int main(){
	char *path = "prueba.txt";
	leerArchivo(path);
	guardarArchivo(path, 1000);
	return EXIT_SUCCESS;
}
