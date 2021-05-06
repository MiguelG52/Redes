//librerias estandar de c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//librerias para tener acceso a datos de configuracion de red
#include <sys/ioctl.h>
#include <net/if.h>

//librerias de protoclo
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <arpa/inet.h>

#include <net/ethernet.h> /* the L2 protocols */

void getDatos(int ds){
	//declaramos estructura
	struct ifreq nic;
	//Leemos el nombre de la interfaz de red
	char *nombre = malloc(100 * sizeof(char));
	printf("\nInserta el nombre de la interfaz: ");
	scanf("%[^\n]", nombre);
	nombre = realloc(nombre, strlen(nombre)+1);
	
	strcpy(nic.ifr_name, nombre);
	//veriricamos la peticion
	if(ioctl(ds, SIOCGIFINDEX, &nic) == -1)
	{
		perror("\nError al obtener el index");
		exit(0);
	}
	else
	{
		printf("\nEl index es: %d\n", nic.ifr_ifindex);

	}
}


int main()
{
	//creamos socket de tipo crudo de af_packet
	int packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	//validamos apertura
	if(packet_socket == -1)
	{
		perror("Error al abrir el socket\n");
		exit(0);
	}
	else
	{
		printf("Exito al abrir el socket\n");
		getDatos(packet_socket);
	}
	close(packet_socket);
	return 0;
}

