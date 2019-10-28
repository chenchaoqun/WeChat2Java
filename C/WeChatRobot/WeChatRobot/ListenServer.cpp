#include <stdio.h>
#include <afxwin.h>
#include "ListenServer.h"
#include "CJsonObject.hpp"
#include "message.h"
#include <iostream>
#include <fstream>
#include "SendAtMessage.h"

#define IP_ADDR "127.0.0.1"
#define GROUP_PORT 8090
#define PERSONAL_PORT 8089

struct MessageStruct
{
	wchar_t wxid[40];
	wchar_t content[MAX_PATH];
};

using namespace std;

void BeginListener()
{
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(GROUP_PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(s, (LPSOCKADDR)&addr, sizeof(addr));
	if (WSAGetLastError() == WSAEADDRINUSE)
	{
		//端口已被占用
		return;
	}
	else
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ListenServer, NULL, 0, NULL);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ListenMessageServer, NULL, 0, NULL);
	}
}

wstring wstring_To_UTF8(const std::wstring& str)
{
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, NULL, NULL, NULL);
	return str;
}

//监听个人发来的信息
void ListenMessageServer() {
	WSADATA  wsaData;
	SOCKET   sSerSock;
	sockaddr_in  serAddr;
	sockaddr_in  acc_sin;
	int  acc_sin_len;
	int recv_len;
	char szMsg[200];

	if (WSAStartup(0x0101, &wsaData) != 0)
	{
		fprintf(stderr, "WSAStartup failed: %d\n", GetLastError());
		return;
	}

	if ((sSerSock = ::socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		fprintf(stderr, "Socket() failed: %d\n", WSAGetLastError());
		return;
	}

	serAddr.sin_family = AF_INET;
	//监听个人信息的端口
	serAddr.sin_port = ::htons(PERSONAL_PORT);
	serAddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDR);
	if (bind(sSerSock, (LPSOCKADDR)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		fprintf(stderr, "bind(sock) failed: %d\n", ::WSAGetLastError());
		return;
	}
	//将socket由主动发送转为被动监听,当存在半连接时放入队列中，队列大小设置为20
	if (listen(sSerSock, 20) != 0)
	{
		return;
	}

	acc_sin_len = sizeof(acc_sin);
	
	while (1)
	{
		SOCKET   sAccSock;
		sAccSock = accept(sSerSock, (struct sockaddr*) & acc_sin, &acc_sin_len);
		if (sAccSock < 0)
		{
			continue;
		}
		recv_len = recv(sAccSock, szMsg, strlen(szMsg), 0);
		if (recv_len == SOCKET_ERROR)
		{
			continue;
		}
		else {
			/* recv_len 为接收数据的真实长度，此语句去除多余的无效字符。（在末尾加入字符串结束符号'\0'）*/
			szMsg[recv_len] = '\0';
			string str(szMsg);

			neb::CJsonObject oJson(str);
			
			//获取艾特消息
			string userId;
			string message;
			oJson.Get("userId", userId);
			oJson.Get("message", message);

			MessageStruct* msg = new MessageStruct;
			mbstowcs(msg->wxid, userId.c_str(), strlen(userId.c_str()) + 1);
			mbstowcs(msg->content, message.c_str(), strlen(message.c_str()) + 1);
			//查找窗口
			CWnd* pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
			COPYDATASTRUCT MessageData;

			MessageData.dwData = WM_SendTextMessage;
			MessageData.cbData = sizeof(MessageStruct);
			MessageData.lpData = msg;

			pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&MessageData);

			delete msg;
			closesocket(sAccSock);
		}
		if (recv_len == 0)
		{
			continue;
		}
	}
	closesocket(sSerSock);
	WSACleanup();
}


//监听群聊,进行艾特回复
void ListenServer() {
	WSADATA  wsaData;
	SOCKET   sSerSock;
	
	sockaddr_in  serAddr;
	sockaddr_in  acc_sin;
	int  acc_sin_len;
	int recv_len;
	char szMsg[200];

	if (WSAStartup(0x0101, &wsaData) != 0)
	{
		fprintf(stderr, "WSAStartup failed: %d\n", GetLastError());
		return;
	}

	if ((sSerSock = ::socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		fprintf(stderr, "Socket() failed: %d\n", WSAGetLastError());
		return;
	}

	serAddr.sin_family = AF_INET;
	//监听群聊端口
	serAddr.sin_port = ::htons(GROUP_PORT);
	serAddr.sin_addr.S_un.S_addr = inet_addr(IP_ADDR);
	if (bind(sSerSock, (LPSOCKADDR)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		fprintf(stderr, "bind(sock) failed: %d\n", ::WSAGetLastError());
		return;
	}
	//将socket由主动发送转为被动监听,当存在半连接时放入队列中，队列大小设置为20
	if (listen(sSerSock, 20) != 0)
	{
		return;
	}
	acc_sin_len = sizeof(acc_sin);

	while (1)
	{
		SOCKET   sAccSock;
		sAccSock = accept(sSerSock, (struct sockaddr*) & acc_sin, &acc_sin_len);
		if (sAccSock < 0)
		{
			continue;
		}
		recv_len = recv(sAccSock, szMsg, strlen(szMsg), 0);
		if (recv_len == SOCKET_ERROR)
		{
			continue;
		}
		else {
			/* recv_len 为接收数据的真实长度，此语句去除多余的无效字符。（在末尾加入字符串结束符号'\0'）*/
			szMsg[recv_len] = '\0';
			string str(szMsg);

			neb::CJsonObject oJson(str);

			//获取艾特消息
			string chatRoomId;
			string userId;
			string nickName;
			string message;
			oJson.Get("chatRoomId", chatRoomId);
			oJson.Get("userId", userId);
			oJson.Get("nickName", nickName);
			oJson.Get("message", message);

			AtMsg* msg = new AtMsg;
			mbstowcs(msg->chatroomid, chatRoomId.c_str(), strlen(chatRoomId.c_str()) + 1);
			mbstowcs(msg->memberwxid, userId.c_str(), strlen(userId.c_str()) + 1);
			mbstowcs(msg->membernickname, nickName.c_str(), strlen(nickName.c_str()) + 1);
			mbstowcs(msg->msgcontent, message.c_str(), strlen(message.c_str()) + 1);

			SendRoomAtMsg(msg);

			delete msg;
			closesocket(sAccSock);
		}
		if (recv_len == 0)
		{
			continue;
		}
	}
	//关闭监听端口
	closesocket(sSerSock);
	//功能是终止Winsock 2 DLL (Ws2_32.dll) 的使用
	WSACleanup();
}