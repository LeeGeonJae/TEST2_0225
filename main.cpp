#include <Winsock2.h>
#include <iostream>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Winsock Error : " << GetLastError() << endl;
		exit(-1);
	}

	SOCKET ServerSocket;

	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Socket Error : " << GetLastError() << endl;
		exit(-1);
	}

	SOCKADDR_IN ServerAddr;

	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(5001);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "bind Error : " << GetLastError() << endl;
		exit(-1);
	}

	if (listen(ServerSocket, 0) == SOCKET_ERROR)
	{
		cout << "listen Error : " << GetLastError() << endl;
		exit(-1);
	}


	SOCKADDR_IN ClientAddr;
	int ClientAddrSize = sizeof(ClientAddr);
	SOCKET ClientSocket = 0;
	ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientAddr, &ClientAddrSize);
	if (ClientSocket == SOCKET_ERROR)
	{
		cout << "accept Error : " << GetLastError() << endl;
		exit(-1);
	}

	char Message[] = "show me the money.";
	send(ClientSocket, Message, strlen(Message) + 1, 0);

	recv(ClientSocket, Message, strlen(Message) + 1, 0);
	cout << "Client send : " << Message << endl;

	closesocket(ClientSocket);
	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}












