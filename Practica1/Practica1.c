#include <sys/socket.h>
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
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0), lbind, tam, opc = 1, lreciv;
    //Creo mensaje y buffer para recibir datos
    unsigned char msj[100], paqReciv[512];
    
    struct sockaddr_in local, remota;  

    if (udp_socket == -1)
    {
        perror("\nError al abrir el socket");
        exit(0);
    }
    else
    {
        local.sin_family = AF_INET;
        local.sin_port = htons(0);
        local.sin_addr.s_addr = INADDR_ANY;
        lbind = bind(udp_socket, (struct sockaddr *)&local, sizeof(local));
        if (lbind == -1)
        {
            perror("\n Error al asignar un nombre al socket");
            exit(0);
        }
        else
        {
            //Enlaza al socket remoto
            remota.sin_family = AF_INET;
            remota.sin_port = htons(8080);
            remota.sin_addr.s_addr = inet_addr("192.168.0.124");
            while (opc != 0)
            {
                printf("\nIngrese el mensaje que desee enviar: ");
                fflush(stdin);
                scanf("%[^\n]s", msj);
                tam = sendto(udp_socket,msj,strlen(msj)+1,0,(struct sockaddr *)&remota, sizeof(remota));
                if(tam == -1)
                {
                    perror("\n Error al enviar");
                    exit(0);
                } 
                else
                {
                    perror("\nExito al enviar");

                    //Espera recepcion de mensaje
                    lreciv = sizeof(remota);
                    tam = recvfrom(udp_socket,paqReciv,512,0,(struct sockaddr *)&remota, &lreciv);
                    if(tam == -1)
                    {
                        perror("\n Error al recibir");
                        exit(0);
                    } 
                    else
                    {
                        printf("El mensaje es: %s", paqReciv);
                    }
                }
                memset(msj,'\0',strlen(msj));
                printf("\nDesea enviar otro mensaje?\nPulse 1 para enviar otro, caso contrario pulse 0: ");
                scanf("%d", &opc);
                system("clear");
            }
        }
    }
    close(udp_socket);
    return 0;
}
    

