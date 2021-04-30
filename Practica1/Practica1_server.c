#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
int main()
{   
    //Declaramos la variable perteneciente al socket
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0), lbind, tam, lreciv, opc = 1;
    //Creo mensaje 
    unsigned char paqReciv [512], msj[100];

    struct sockaddr_in SERVIDOR, CLIENTE;  
    if (udp_socket == -1)
    {
        perror("\nError al abrir el socket");
        exit(0);
    }
    else
    {
        SERVIDOR.sin_family = AF_INET;
        SERVIDOR.sin_port = htons(8080);
        SERVIDOR.sin_addr.s_addr = INADDR_ANY;

        //Crea estructura de cliente
        CLIENTE.sin_family = AF_INET;
        CLIENTE.sin_port = htons(8080);
        CLIENTE.sin_addr.s_addr = inet_addr("192.168.0.124");
        
        lbind = bind(udp_socket, (struct sockaddr *)&SERVIDOR, sizeof(SERVIDOR));
        if (lbind == -1)
        {
            perror("\n Error al asignar un nombre al socket");
            exit(0);
        }
        else
        {
            //Recibe mensaje
            perror("Esperando mensaje...");
            lreciv = sizeof(CLIENTE);
            tam = recvfrom(udp_socket,paqReciv,512,0,(struct sockaddr *)&CLIENTE, &lreciv);
            while (opc != 0)
            {
                if(tam == -1)
            {
                perror("\n Error al recibir");
                exit(0);
            } 
                else
                {
                    printf("El mensaje es: %s", paqReciv);
                    //Envia mensaje
                    printf("\nIngrese el mensaje que desee enviar: ");
                    fflush(stdin);
                    scanf("%[^\n]s", msj);
                    tam = sendto(udp_socket,msj,strlen(msj)+1,0,(struct sockaddr *)&CLIENTE, sizeof(CLIENTE));
                    if(tam == -1)
                    {
                        perror("\nError al enviar");
                        exit(0);
                    } 
                    else
                    {
                        perror("\nExito al enviar");
                    }
                    printf("\nDesea recibir otro mensaje?\nPulse 1 para enviar otro, caso contrario pulse 0: ");
                    scanf("%d", &opc);
                    system("clear");
            }
            }
        }
    }
    close(udp_socket);
    return 0;
}