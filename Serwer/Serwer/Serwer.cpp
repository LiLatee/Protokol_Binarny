#include "stdafx.h"

#include <winsock.h>
#include <cstdio>
#include <iostream>
#include <bitset>

#define MY_PORT 3490   // port, z którym bêd¹ siê ³¹czyli u¿ytkownicy
#define BACK_LOG 10     //jak du¿o mo¿e byæ oczekuj¹cych po³¹czeñ w kolejce
#define MAXDATASIZE 100 

char komunikat[] = "\0";

void bitsToChar(std::bitset<8>bits);
int main()
{
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
	{
		fprintf(stderr, "WSAStartup failed.\n");
		exit(1);
	}



	int sockfd; //deskryptor gniazda
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}
	int new_fd; // adres przychodz¹cy - deskryptor
	sockaddr_in myAddr; // mój adres
	sockaddr_in theirAddr; // adres przychodz¹cy
	myAddr.sin_family = PF_INET;
	myAddr.sin_port = htons(MY_PORT); // numer portu
	myAddr.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr("192.168.43.121"); //mój adres
	memset(&myAddr.sin_zero, '\0', 8);

	if (bind(sockfd, (struct sockaddr *) &myAddr, sizeof(struct sockaddr)) == -1)
	{
		perror("bind");
		exit(1);
	}
	if (listen(sockfd, BACK_LOG) == -1)
	{
		perror("listen");
		exit(1);
	}


	int sin_size;
	//datagram
	char *bufor = "\0";//(char*)malloc(65535);
	while (1)
	{
		sin_size = sizeof(struct sockaddr_in);
		if ((new_fd = accept(sockfd, (struct sockaddr*)&theirAddr, &sin_size)) == -1)
		{
			perror("accept");
			continue;
		}
		printf("server: got connection from %s\n", inet_ntoa(theirAddr.sin_addr));
		
		
		int numbytes;
		char buf[100];
		while (1)
		{
			std::cin >> buf;
			numbytes = send(new_fd, buf, 100 - 1, 0);
			buf[numbytes] = '\0';
			printf("Received: %s\n", buf);
		}
		
		closesocket(new_fd);
	}
}

void dodawanie();
void odejmowanie();
void mnozenie();
void dzielenie();
void modulo();
void rownosc();
void potegowanie();
void pierwiastkowanie();

void bitsToChar(std::bitset<8>bits)
{
	std::string s = bits.to_string();
	const char * c = s.c_str();
	strcat_s(komunikat, sizeof komunikat, c);
}