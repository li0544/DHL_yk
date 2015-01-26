CString strLog;
//向记事本中写入消息
void sendLog(CString sMsg)
{
	HWND hw = FindWindow("Notepad", "无标题 - 记事本");
	if (hw != 0)
	{
		HWND hw_edit = FindWindowEx(hw, 0, "Edit", NULL);
		if (hw_edit != 0)
		{
			int i_len = SendMessage(hw_edit, WM_GETTEXTLENGTH, 0, 0);
			char* cstr = new char[i_len+1];
			SendMessage(hw_edit, WM_GETTEXT, i_len+1,(LPARAM)cstr);
			CString s1 = cstr;
			sMsg = s1 + sMsg;
			SendMessage(hw_edit, WM_SETTEXT, 0, (LPARAM)(LPCTSTR)sMsg);
		}
	}
}

void sendLog()
{
	sendLog(strLog);
}

void sendLog(int i)
{
	strLog.Format("%d", i);
	sendLog();
}

void sendLog(LPCTSTR s1)
{
	strLog.Format("%s", s1);
	sendLog();
}

void sendLog(LPCTSTR s1, int i)
{
	strLog.Format("%s", s1);
	strLog.Format(strLog, i);
	sendLog();
}