#pragma once
// 127.0.0.1은 loop-back IP라 해서, 자기 자신에게 연결되는 IP 주소를 말한다.
const char serverIP[] = "127.0.0.1";
// 클라이언트에서 서버로 접속하기 위한 포트
const int IOCP_Port = 12345;

#include <WinSock2.h>
class AutoWSACleanup
{
public:
	~AutoWSACleanup()
	{
		WSACleanup();
	}
};