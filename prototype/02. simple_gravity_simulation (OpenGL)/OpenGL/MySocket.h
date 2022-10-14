#pragma once
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include<iostream>

#define SERVER_IP "127.0.0.1"
#define PORT 5050
#define PACKET_SIZE 1024

class MySocket
{
private:
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN tAddr = {};
	char cBuffer[PACKET_SIZE] = {};

public:
	void Init();
	void Connect();
	void Send(char cMsg[]);
	std::string Recv();
	void DisConnect();
};