
struct AtMsg
{
	wchar_t chatroomid[50] = { 0 };
	wchar_t memberwxid[50] = { 0 };
	wchar_t membernickname[50] = { 0 };
	wchar_t msgcontent[100] = { 0 };
};

void SendRoomAtMsg(AtMsg* msg);
//发送艾特消息
void SendRoomAtMsg(wchar_t* chatroomid, wchar_t* memberwxid, wchar_t* membernickname, wchar_t* message);