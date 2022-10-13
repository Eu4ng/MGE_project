#pragma comment(lib,"ws2_32.lib")

#include <iostream>
#include <WinSock2.h>
#include <thread>

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
		void Init() {
			WSAStartup(MAKEWORD(2, 2), &this->wsaData);
			this->hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
			this->tAddr.sin_family = AF_INET;
			this->tAddr.sin_port = htons(PORT);
			this->tAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
		}

		void Connect() {
			connect(this->hSocket, (SOCKADDR*)&this->tAddr, sizeof(this->tAddr));
		}

		void Send(char cMsg[]) {
			send(this->hSocket, cMsg, strlen(cMsg), 0);
		}

		void Recv() {
			recv(this->hSocket, this->cBuffer, PACKET_SIZE, 0);
			printf("Recv Msg : %s\n", this->cBuffer);
		}
		
		void DisConnect() {
			closesocket(this->hSocket);
			WSACleanup();
		}
};

void func1() {
	MySocket s;
	s.Init();
	s.Connect();
	while (true) {
		s.Recv();
	}
}

int main()
{
	std::thread t1(func1);
	t1.join();

	return 0;
}