// Khai bao thu vien
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "libsocket.h"


#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#define PIN_RED 11
#define PIN_GREEN 13
#define PIN_BLUE 15
// Ham con(in file .c)
// ham con PWM led
void PWM_LED_RGB(int R,int G,int B)
{
	wiringPiSetupPhys();
	// Khoi tao PWM
	softPwmCreate(PIN_RED,0,100);
	softPwmCreate(PIN_GREEN,0,100);
	softPwmCreate(PIN_BLUE,0,100);
	// Write Pwm
	softPwmWrite(PIN_RED,R);
	softPwmWrite(PIN_GREEN,G);
	softPwmWrite(PIN_BLUE,B);
}
// Ham con nhan du lieu
int red,green,blue;
void rev_data(int FD_from_Client)
{
    char buf[1024];
    while (1)
    {
	memset(buf,0,sizeof(buf));
        // Nhan du lieu
        ssize_t check_size_rev = recv(FD_from_Client,&buf,1024,0);
        if(check_size_rev>0)
        {
            printf("%s\n",buf);
	    sscanf(buf,"%d%*c%d%*c%d",&red,&green,&blue);
	    PWM_LED_RGB(red,green,blue);
        }
        else if(check_size_rev==0)
            break;
            
    }
    close(FD_from_Client);
}


//--------------------HAM ACCEPT CLIENT---------------------------//
// Khoi tao bien struct tra ve 
struct Accept
{
    int acceptedSocketFD;
    struct sockaddr_in address;
    int error;
};

struct Accept* Accept_Client(int ServersocketFD)
{
    struct sockaddr_in C_Clientaddress;
    // Tien hanh accept
    int size_sockaddr_in = sizeof(struct sockaddr_in);
    int C_ClientsocketFD = accept(ServersocketFD,(struct sockaddr*)&C_Clientaddress,&size_sockaddr_in);
    // Cap phat bo nho
    struct Accept *accept_socket_client = malloc(sizeof(struct Accept));
    accept_socket_client->address = C_Clientaddress;
    accept_socket_client->acceptedSocketFD = C_ClientsocketFD;
    
    // Kiem tra accept
    if(C_ClientsocketFD<0)
    {
        accept_socket_client->error = C_ClientsocketFD;
        printf("Loi ket noi: %d\n",C_ClientsocketFD);
    }
    else
    {
     	 printf("Da co Client ket noi\n");
	 rev_data(C_ClientsocketFD);
    }
    return accept_socket_client;
}
 
//--------------------------------------------------------------------//


// Ham chinh
int main()
{
    // Gan socket
    int ServersocketFD = Create_Socket();
    // Tao dia chi 
    struct sockaddr_in* Serveraddress = Create_Address("",2000);
    // May chu tu ket noi den dia chi nay
    int resultbind =  bind(ServersocketFD,(struct sockaddr*)Serveraddress,sizeof(*Serveraddress));
    if(resultbind == 0)
        printf("Da co may chu\n");

    // Lang nghe cac ket noi //10 max
    int listenClient = listen(ServersocketFD,10);
    if(listenClient==0)
         printf("Listening...\n");

    Accept_Client(ServersocketFD);
    return 0;
}
