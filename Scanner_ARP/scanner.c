#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
 #include <sys/time.h>

unsigned char MACorigen[6],IPorigen[4],MASCARAorigen[4],IPdestino[4],MACdestino[6];
unsigned char tramaEnv[1514],tramaRec[1514];
unsigned char MACbroad[6]={0xff,0xff,0xff,0xff,0xff,0xff};
unsigned char ethertype[2]={0x08,0x06};
unsigned char hardware[2]={0x00,0x01},protocolo[2]={0x08,0x00},codeARPenv[2]={0x00,0x01},codeARPrec[2]={0x00,0x02};
char *nombreArchivo = "redes.txt"

void leerArchivo(char *path){
    FILE *archivo = NULL;
    int n;
    archivo = fopen(path, "r");
    if(!archivo){
    	fclose(archivo);
    	perror("No se pudo abrir el archivo")
        exit(0);
	}
    else{
    	while(!feof(archivo)){
        	fscanf(archivo, "%d\n", &n);
            printf("Numero: %d\n", n);
        }
        fclose(archivo);
    }
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

int obtenerDatos(int ds){
	struct ifreq nic;
	int index,i;
	printf("Inserta el nombre de la interfaz de red: \n");
	scanf("%s",nic.ifr_name);
	//OBteniendo el Indice de red
	if(ioctl(ds,SIOCGIFINDEX,&nic)==-1){
		perror("Error al obtener el indice");
		exit(1);
	}else{
		//Obteniendo la MAC
		index=nic.ifr_ifindex;
		if(ioctl(ds,SIOCGIFHWADDR,&nic)==-1){
			perror("Error al obtener la MAC");
			exit(1);
		}else{
			memcpy(MACorigen,nic.ifr_hwaddr.sa_data+0,6);
			for(i=0;i<6;i++){
				printf("%.2x", MACorigen[i]);
			}
			//Obteniendo la IP
			printf("\n");
			if(ioctl(ds,SIOCGIFADDR,&nic)==-1){
				perror("Error al obtener la IP");
				exit(1);
			}else{
				memcpy(IPorigen,nic.ifr_addr.sa_data+2,4);
				for(i=0;i<4;i++){
					printf("%d.", IPorigen[i]);
				}
				printf("\n");
				//Obteniendo la MASCARA DE SUBRED
				if(ioctl(ds,SIOCGIFNETMASK,&nic)==-1){
					perror("Error al obtener la MASCARA DE SUBRED");
					exit(1);
				}else{
					memcpy(MASCARAorigen,nic.ifr_addr.sa_data+2,4);
					for(i=0;i<4;i++){
						printf("%d.", MASCARAorigen[i]);
					}
				}
			}
		}
	}
	return index;
}
void estructuraTrama(unsigned char *trama){
	//memset(&MACdestino,0x00,sizeof(MACdestino));
	memcpy(trama+0,MACbroad,6);
	memcpy(trama+6,MACorigen,6);
	memcpy(trama+12,ethertype,2);
	memcpy(trama+14,hardware,2);
	memcpy(trama+16,protocolo,2);
	trama[18]=6;
	trama[19]=4;
	memcpy(trama+20,codeARPenv,2);
	memcpy(trama+22,MACorigen,6);
	memcpy(trama+28,IPorigen,4);
	memset(trama+32,0x00,6);
	memcpy(trama+38,IPdestino,4);
}
void enviarTrama(int ds, int index, unsigned char *trama){
	struct sockaddr_ll nic;
	int tam;
	memset(&nic,0x00,sizeof(nic));
	nic.sll_family=AF_PACKET;
	nic.sll_protocol=htons(ETH_P_ALL);
	nic.sll_ifindex=index;
	tam=sendto(ds,trama,60,0,(struct sockaddr *)&nic, sizeof(nic));
	if(tam==-1){
		perror("Error al enviar ");
	}else{
		perror("Exito al enviar ");
	}
}
void imprimeTrama(unsigned char *paq,int len){
	int i;
	for(i=0;i<len;i++){
		if(i%16==0){
			printf("\n");
		}
		printf("%.2x ", paq[i]);
	}
	printf("\n");
}

int filtroARP(unsigned char *trama, int len){
	if(!memcmp(trama,MACorigen,6)){
		if(!memcmp(trama+12,ethertype,2)){
			if(!memcmp(trama+20,codeARPrec,2)){
				if(!memcmp(trama+38,IPorigen,4)){
					return 1;
				}
			}
		}	
	}
	return 0;
}

void recibeTrama(int ds, unsigned char *trama){
	int i=0;
	int tam,bandera=0;
	struct timeval start, end;
    long mtime=0, seconds, useconds;
	gettimeofday(&start, NULL);
	while(mtime<1000){
		tam = recvfrom(ds,trama,1514,MSG_DONTWAIT,NULL,0);
		if(tam==-1){
			//perror("Error al recibir");
			//exit(1);
		}else{
			bandera = filtroARP(trama,tam);
			memcpy(MACdestino,trama+6,6);
			if (bandera == 1){
				imprimeTrama(trama,tam);
				bandera=1;	
			}
		}
		gettimeofday(&end, NULL);
        seconds  = end.tv_sec  - start.tv_sec;
        useconds = end.tv_usec - start.tv_usec;
        mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
        if(bandera==1){
        	break;
        }
	}
	printf("Elapsed time: %ld milliseconds\n", mtime);
}
void obtenerIPdestino(){
	//char *algo_addr;
	char IP[50];
	printf("Ingrese la IP destino:\n");
	scanf("%s",IP);
	if(inet_aton(IP,IPdestino)==0){
		perror("Error al convertir IP destino");
	}else{
		printf("La IP a enviar es: %s\n", IP);
	}
}

int main(){
	int packet_socket,i;
	int indice;
	packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if(packet_socket==-1){
		perror("\nError al abrir el socket");
		exit(1);
	}else{
		printf("Exito al abrir el socket\n");
		obtenerIPdestino();
		indice = obtenerDatos(packet_socket);
		printf("\nEl  indice es: %d\n",indice);
		estructuraTrama(tramaEnv);
		enviarTrama(packet_socket,indice,tramaEnv);
		recibeTrama(packet_socket,tramaRec);
	}
	printf("///////////////La MAC destino es//////////////////\n");
	for(i=0;i<6;i++){
		printf("%.2x", MACdestino[i]);
	}
	printf("\n");
	//inet_aton();//Obtener manual
	close(packet_socket);
	return 0;
}