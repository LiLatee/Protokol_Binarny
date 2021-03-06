#include "stdafx.h"
//Autorski protokół internetowy
//Wszelkie prawa zastrzeżone
//Napisany przez Marcina Hradowicza i Jakuba Hamerlińskiego
#include <winsock.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <bitset>
#include <vector>

#define MY_PORT 2500
void dodawanie();
void odejmowanie();
void mnozenie();
void dzielenie();
void modulo();
void rownosc();
void potegowanie();
void silnia();
std::string decimalToBinary(int liczba); // funkcja służąca do zamiany liczby na ciąg zer i jedynek

										 //bufor danych do wysłania w postaci string - segment
std::string buforS;

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
	{
		fprintf(stderr, "WSAStartup failed.\n");
		exit(1);
	}


	int sockfd; //deskryptor gniazda klienta
	int new_fd;//deskryptor gniazda serwera
	sockfd = socket(PF_INET, SOCK_STREAM, 0);


	//wczytywanie IP serwera
	char *DEST_IP;
	DEST_IP = (char*)malloc(17); // o co chodzi z tą alokacją pamięci
	printf("%s", "Podaj adres IP: \n");
	//scanf("%s", DEST_IP);
	DEST_IP = "192.168.0.106";

	//wczytywanie portu serwera
	u_short DEST_PORT;
	printf("%s", "Podaj port (3490): \n");
	//std::cin >> DEST_PORT;
	DEST_PORT = 3490;

	sockaddr_in theirAddr;
	theirAddr.sin_family = PF_INET;
	theirAddr.sin_port = htons(DEST_PORT);
	theirAddr.sin_addr.s_addr = inet_addr(DEST_IP);
	memset(&theirAddr.sin_zero, '\0', 8);

	//łączenie z serwerem
	if (connect(sockfd, (struct sockaddr *) & theirAddr, sizeof(struct sockaddr)) == -1)
	{
		perror("connect");
		exit(1);
	}
	printf("client: got connection to %s\n", inet_ntoa(theirAddr.sin_addr));
	
	//odbiór ID
	char id[43] ="\0";
	int  blad = recv(sockfd, id, 42, 0);
	if(blad < 0)
	{
		perror("recv");
		exit(1);
	}
	std::string IDS(id);
	std::cout << "Odebrano ID: " << IDS[7] << IDS[8] << IDS[9];
	std::cin.get();


	int wybor;
	while (1)
	{
		std::cout << "Operacje:\n";
		std::cout << "1. Dodawanie\n"; //000
		std::cout << "2. Odejmowanie\n"; //001
		std::cout << "3. Mnozenie\n"; //010
		std::cout << "4. Dzielenie\n"; //011
		std::cout << "5. Modulo\n"; //100
		std::cout << "6. Rownosc\n"; //101
		std::cout << "7. Potegowanie\n"; //110
		std::cout << "8. Silnia\n"; //111
		std::cout << "9. Rozlaczenie z serwerem\n"; //111
		std::cin >> wybor;
		switch (wybor)
		{
		case 1:
		{
			dodawanie();
			break;
		}
		case 2:
		{
			odejmowanie();
			break;
		}
		case 3:
		{
			mnozenie();
			break;
		}
		case 4:
		{
			dzielenie();
			break;
		}
		case 5:
		{
			modulo();
			break;
		}
		case 6:
		{
			rownosc();
			break;
		}
		case 7:
		{
			potegowanie();
			break;
		}
		case 8:
		{
			silnia();
			break;
		}
		case 9:
		{
			return 0;
		}
		default:
		{
			std::cout << "Podaj inna liczbe.\n";
			continue;
		}
		}
	}

	/*if (send(new_fd, bufor, 65534, 0) == -1)
	{
	perror("send");

	closesocket(new_fd);
	exit(0);
	}*/



	std::cin.get();

	closesocket(sockfd);

	return 0;
}


void dodawanie()
{
	buforS += "000";
	std::cout << "Podaj dwie liczby do dodania (max 65535): ";
	int l1, l2;
	std::cin >> l1 >> l2;
	if ((l1 || l2) > 65535)
	{
		std::cout << "Liczba zbyt duza. Koniec programu.\n";
		exit(1);
	}
	buforS += decimalToBinary(l1);
	buforS += decimalToBinary(l2);
}
void odejmowanie()
{
	buforS += "001";
	std::cout << "Podaj odjemna i odjemnik: (max 65535): ";
	int l1, l2;
	std::cin >> l1 >> l2;
	if ((l1 || l2) > 65535)
	{
		std::cout << "Liczba zbyt duza. Koniec programu.\n";
		exit(1);
	}
	buforS += decimalToBinary(l1);
	buforS += decimalToBinary(l2);
}
void mnozenie()
{
	buforS += "010";
	std::cout << "Podaj mnozna i mnoznik (max 65535): ";
	int l1, l2;
	std::cin >> l1 >> l2;
	if ((l1 || l2) > 65535)
	{
		std::cout << "Liczba zbyt duza. Koniec programu.\n";
		exit(1);
	}
	buforS += decimalToBinary(l1);
	buforS += decimalToBinary(l2);
}
void dzielenie()
{
	buforS += "011";
	std::cout << "Podaj dzielna i dzielnik (max 65535): ";
	int l1, l2;
	std::cin >> l1 >> l2;
	if ((l1 || l2) > 65535)
	{
		std::cout << "Liczba zbyt duza. Koniec programu.\n";
		exit(1);
	}
	buforS += decimalToBinary(l1);
	buforS += decimalToBinary(l2);
}
void modulo()
{
	buforS += "100";
	std::cout << "Podaj dzielna i dzielnik do dzielenia z reszta (max 65535): ";
	int l1, l2;
	std::cin >> l1 >> l2;
	if ((l1 || l2) > 65535)
	{
		std::cout << "Liczba zbyt duza. Koniec programu.\n";
		exit(1);
	}
	buforS += decimalToBinary(l1);
	buforS += decimalToBinary(l2);
}
void rownosc()
{
	buforS += "101";
	std::cout << "Podaj dwie liczby do porownania (max 65535): ";
	int l1, l2;
	std::cin >> l1 >> l2;
	if ((l1 || l2) > 65535)
	{
		std::cout << "Liczba zbyt duza. Koniec programu.\n";
		exit(1);
	}
	buforS += decimalToBinary(l1);
	buforS += decimalToBinary(l2);
}
void potegowanie()
{
	buforS += "110";
}
void silnia()
{
	buforS += "111";
	std::cout << "Podaj liczbe z ktorej obliczyc silnie (max 12): ";
	int l1, l2;
	std::cin >> l1 >> l2;
	if ((l1 || l2) > 65535)
	{
		std::cout << "Liczba zbyt duza. Koniec programu.\n";
		exit(1);
	}
	buforS += decimalToBinary(l1);
	buforS += decimalToBinary(l2);
}
std::string decimalToBinary(int liczba)
{
	/*std::stringstream a(liczba);
	int liczbaInt;
	a >> liczbaInt;*/

	if (liczba == 0) return "0";
	if (liczba == 1) return "1";

	if (liczba % 2 == 0)
		return decimalToBinary(liczba / 2) + "0";
	else
		return decimalToBinary(liczba / 2) + "1";
}