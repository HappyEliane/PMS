#pragma once
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

class ADOConn
{
public:
	ADOConn(void);
	~ADOConn(void);	
	// ����ָ��
	_ConnectionPtr m_pConnection;
	// �����ָ��
	_RecordsetPtr m_pRecordset;
	// ��ʼ������ָ�벢�������ݿ�
	void OnInitADOConn(void);
	// �رռ�¼�������Ӳ��ͷŻ���
	void ExitConnect(void);
	// ��ü�¼��
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL, int mode_dynamic = 0);
	// ִ��һ��SQL���
	BOOL ExecuteSQL(_bstr_t bstrSQL);
	// �������ݿ��ļ�
	void BackUp(CString FilePath);
	// ��ԭ���ݿ��ļ�
	void Recovery(CString FilePath);
};
