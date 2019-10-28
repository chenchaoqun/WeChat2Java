#pragma once
#include <iostream>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

void sendMessageBySocket(string message);

void sendMessageBySocket(wstring message);

string wstring2string(wstring wstr);