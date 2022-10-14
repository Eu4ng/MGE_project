#include "MySocket.h"

void MySocket::Init()
{
	WSAStartup(MAKEWORD(2, 2), &this->wsaData);
	this->hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	this->tAddr.sin_family = AF_INET;
	this->tAddr.sin_port = htons(PORT);
	this->tAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
}

void MySocket::Connect() {
	connect(this->hSocket, (SOCKADDR*)&this->tAddr, sizeof(this->tAddr));
}

void MySocket::Send(char cMsg[]) {
	send(this->hSocket, cMsg, strlen(cMsg), 0);
}

std::string MySocket::Recv() {
	recv(this->hSocket, this->cBuffer, PACKET_SIZE, 0);
	// char * -> string (깊은 복사)
	std::string str(this->cBuffer);
	// 버퍼 비우기
	memset(this->cBuffer, '\0', strlen(this->cBuffer));
	return str;
}

void MySocket::DisConnect() {
	closesocket(this->hSocket);
	WSACleanup();
}