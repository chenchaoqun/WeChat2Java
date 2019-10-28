// COpenUrl.cpp: 实现文件
//

#include "stdafx.h"
#include "WeChatRobot.h"
#include "COpenUrl.h"
#include "afxdialogex.h"

// COpenUrl 对话框

IMPLEMENT_DYNAMIC(COpenUrl, CDialogEx)

COpenUrl::COpenUrl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OpenUrl, pParent)
	, m_urls(_T("www.baidu.com"))
{

}

COpenUrl::~COpenUrl()
{
}

void COpenUrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_urls);
}


BEGIN_MESSAGE_MAP(COpenUrl, CDialogEx)
	ON_BN_CLICKED(IDC_OPEN, &COpenUrl::OnBnClickedOpen)
END_MESSAGE_MAP()


// COpenUrl 消息处理程序


//************************************************************
// 函数名称: OnBnClickedOpen
// 函数说明: 打开浏览器按钮
// 作    者: GuiShou
// 时    间: 2019/9/10
// 参    数: void
// 返 回 值: void
//***********************************************************
void COpenUrl::OnBnClickedOpen()
{
	UpdateData(TRUE);
	
	MessageBoxA(NULL,"此功能目前还没有实现", "Tip", MB_OK);
	return;
	
}
