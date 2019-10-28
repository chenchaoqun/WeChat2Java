#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <WINSOCK2.H>
#pragma comment(lib,"ws2_32.lib")

#define SERVER_ADDRESS "127.0.0.1" //服务器端IP地址      
#define PORT           8080         //服务器的端口号      
#define MSGSIZE        1024         //收发缓冲区的大小      

using namespace std;

//通过socket套接字发送数据到Java服务器
void sendMessageBySocket(string message)
{
	WSADATA wsaData;
	//连接所用套节字      
	SOCKET sClient;
	//保存远程服务器的地址信息      
	SOCKADDR_IN server;
	//收发缓冲区      
	char szMessage[MSGSIZE];
	//成功接收字节的个数      
	int ret;

	// Initialize Windows socket library
	int was = WSAStartup(0x0202, &wsaData);

	if (was < 0) {
		return;
	}

	// 创建客户端套节字      
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INET指明使用TCP/IP协议族；      
														 //SOCK_STREAM, IPPROTO_TCP具体指明使用TCP协议      
	// 指明远程服务器的地址信息(端口号、IP地址等)      
	memset(&server, 0, sizeof(SOCKADDR_IN)); //先将保存地址的server置为全0

	//声明地址格式是TCP/IP地址格式
	server.sin_family = PF_INET;
	//指明连接服务器的端口号，htons()用于 converts values between the host and network byte order    
	server.sin_port = htons(PORT);
	//指明连接服务器的IP地址  
	server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

	//结构SOCKADDR_IN的sin_addr字段用于保存IP地址，sin_addr字段也是一个结构体，sin_addr.s_addr用于最终保存IP地址      
	//inet_addr()用于将 形如的"127.0.0.1"字符串转换为IP地址格式      
	//连到刚才指明的服务器上
	//连接后可以用sClient来使用这个连接 
	connect(sClient, (struct sockaddr*) & server, sizeof(SOCKADDR_IN));      

	//server保存了远程服务器的地址信息      
	// 发送数据
	//sClient指明用哪个连接发送； szMessage指明待发送数据的保存地址 ；strlen(szMessage)指明数据长度      
	send(sClient, message.data(), strlen(message.data()), 0);

	// 释放连接和进行结束工作      
	closesocket(sClient);
	WSACleanup();
}
/*
	将wstring转为string
*/
string wstring2string(wstring wstr) {
	string result;
	//获取缓冲区大小，并申请空间，缓冲区大小是按字节计算的  
	int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//宽字节编码转换成多字节编码  
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//删除缓冲区并返回值  
	result.append(buffer);
	delete[] buffer;
	return result;
}

void sendMessageBySocket(wstring message) {
	sendMessageBySocket(wstring2string(message));
}