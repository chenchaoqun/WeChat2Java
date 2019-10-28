#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <WINSOCK2.H>
#pragma comment(lib,"ws2_32.lib")

#define SERVER_ADDRESS "127.0.0.1" //��������IP��ַ      
#define PORT           8080         //�������Ķ˿ں�      
#define MSGSIZE        1024         //�շ��������Ĵ�С      

using namespace std;

//ͨ��socket�׽��ַ������ݵ�Java������
void sendMessageBySocket(string message)
{
	WSADATA wsaData;
	//���������׽���      
	SOCKET sClient;
	//����Զ�̷������ĵ�ַ��Ϣ      
	SOCKADDR_IN server;
	//�շ�������      
	char szMessage[MSGSIZE];
	//�ɹ������ֽڵĸ���      
	int ret;

	// Initialize Windows socket library
	int was = WSAStartup(0x0202, &wsaData);

	if (was < 0) {
		return;
	}

	// �����ͻ����׽���      
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //AF_INETָ��ʹ��TCP/IPЭ���壻      
														 //SOCK_STREAM, IPPROTO_TCP����ָ��ʹ��TCPЭ��      
	// ָ��Զ�̷������ĵ�ַ��Ϣ(�˿ںš�IP��ַ��)      
	memset(&server, 0, sizeof(SOCKADDR_IN)); //�Ƚ������ַ��server��Ϊȫ0

	//������ַ��ʽ��TCP/IP��ַ��ʽ
	server.sin_family = PF_INET;
	//ָ�����ӷ������Ķ˿ںţ�htons()���� converts values between the host and network byte order    
	server.sin_port = htons(PORT);
	//ָ�����ӷ�������IP��ַ  
	server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

	//�ṹSOCKADDR_IN��sin_addr�ֶ����ڱ���IP��ַ��sin_addr�ֶ�Ҳ��һ���ṹ�壬sin_addr.s_addr�������ձ���IP��ַ      
	//inet_addr()���ڽ� �����"127.0.0.1"�ַ���ת��ΪIP��ַ��ʽ      
	//�����ղ�ָ���ķ�������
	//���Ӻ������sClient��ʹ��������� 
	connect(sClient, (struct sockaddr*) & server, sizeof(SOCKADDR_IN));      

	//server������Զ�̷������ĵ�ַ��Ϣ      
	// ��������
	//sClientָ�����ĸ����ӷ��ͣ� szMessageָ�����������ݵı����ַ ��strlen(szMessage)ָ�����ݳ���      
	send(sClient, message.data(), strlen(message.data()), 0);

	// �ͷ����Ӻͽ��н�������      
	closesocket(sClient);
	WSACleanup();
}
/*
	��wstringתΪstring
*/
string wstring2string(wstring wstr) {
	string result;
	//��ȡ��������С��������ռ䣬��������С�ǰ��ֽڼ����  
	int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
	char* buffer = new char[len + 1];
	//���ֽڱ���ת���ɶ��ֽڱ���  
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
	buffer[len] = '\0';
	//ɾ��������������ֵ  
	result.append(buffer);
	delete[] buffer;
	return result;
}

void sendMessageBySocket(wstring message) {
	sendMessageBySocket(wstring2string(message));
}