#include "SendAtMessage.h"
#include "stdafx.h"

void SendRoomAtMsg(AtMsg* msg) {
	//获取句柄
	CWnd* pWnd = CWnd::FindWindow(NULL, L"WeChatHelper");
	COPYDATASTRUCT atmsgdata;
	atmsgdata.dwData = WM_SendAtMsg;
	atmsgdata.cbData = sizeof(AtMsg);
	atmsgdata.lpData = msg;
	//发送消息
	pWnd->SendMessage(WM_COPYDATA, NULL, (LPARAM)&atmsgdata);
}

void SendRoomAtMsg(wchar_t* chatroomid, wchar_t* memberwxid, wchar_t* membernickname, wchar_t* message) {

	AtMsg* msg = new AtMsg;
	wcscpy_s(msg->chatroomid, wcslen(chatroomid) + 1, chatroomid);
	wcscpy_s(msg->memberwxid, wcslen(memberwxid) + 1, memberwxid);
	wcscpy_s(msg->membernickname, wcslen(membernickname) + 1, membernickname);
	wcscpy_s(msg->msgcontent, wcslen(message) + 1, message);

	SendRoomAtMsg(msg);
	delete msg;
}