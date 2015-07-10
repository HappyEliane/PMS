#include "StdAfx.h"
#include "ADOConn.h"

ADOConn::ADOConn(void)
{
}

ADOConn::~ADOConn(void)
{
}

// ��ʼ������ָ�벢�������ݿ�
void ADOConn::OnInitADOConn(void)
{
	//��ʼ��OLE/COM�⻷��
	::CoInitialize(NULL);
	try
	{
		//����connection����
		m_pConnection.CreateInstance("ADODB.Connection");
		//���������ַ���
		_bstr_t strConnect = "DRIVER=SQL server;Database=rsgl;Server=WYN";
		m_pConnection->Open(strConnect,"","",adModeUnknown);
	}
	//��׽�쳣
	catch (_com_error e)
	{
		//��ʾ������Ϣ
		AfxMessageBox(e.Description());
	}
	return;
}

// �رռ�¼�������Ӳ��ͷŻ���
void ADOConn::ExitConnect(void)
{
	//�رռ�¼��������
	//if(m_pRecordset != NULL)
		//m_pRecordset->Close();
	m_pConnection->Close();
	//�ͷŻ���
	::CoUninitialize();
}

// ��ü�¼��
_RecordsetPtr& ADOConn::GetRecordSet(_bstr_t bstrSQL, int mode_dynamic)
{
	try
	{
		//�������ݿ⣬���connection����Ϊ�գ��������������ݿ�
		if (m_pConnection == NULL)
			OnInitADOConn();
		//������¼������
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		//ȡ�ñ��еļ�¼
		if (mode_dynamic == 0)
		{
			m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(),adOpenStatic , adLockOptimistic,adCmdText);
		}else{
			m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(),adOpenDynamic , adLockOptimistic,adCmdText);
		}
	}
	catch (_com_error e)
	{
		e.Description();
	}
	//���ؼ�¼��
	return m_pRecordset;
}

// ִ��һ��SQL���
BOOL ADOConn::ExecuteSQL(_bstr_t bstrSQL)
{
	_variant_t RecordsAffected;
	try
	{
		_variant_t var;
		//�Ƿ����������ݿ�
		if(m_pConnection == NULL)
			OnInitADOConn();
		m_pConnection->Execute(bstrSQL, &RecordsAffected, adCmdText);
		return true;
	}
	catch (_com_error e)
	{
		e.Description();
		return false;
	}
}

// �������ݿ��ļ�
void ADOConn::BackUp(CString FilePath)
{
	//::CoInitialize(NULL);
	if (FilePath != "")
	{
		try
		{
			//�������ݿ�
	//		OnInitADOConn();
			_bstr_t vSQL;
			vSQL = "backup database rsgl to disk = '"+FilePath+"'";
			ExecuteSQL(vSQL);
			ExitConnect();
			AfxMessageBox("���ݿⱸ�ݳɹ�!");
		}
		catch(_com_error e)// ��׽�쳣
		{
			// ��ʾ������Ϣ
			AfxMessageBox(e.Description());
		}
	}
	else
	{
		AfxMessageBox("��ָ����������·��!");
	}
	//::CoUninitialize();
}

// ��ԭ���ݿ��ļ�
void ADOConn::Recovery(CString FilePath)
{
	::CoInitialize(NULL);
	if (FilePath != "")
	{
		try
		{
			m_pConnection.CreateInstance("ADODB.Connection");
			_bstr_t strConnect = "DRIVER=SQL server; Server=(local); Database=master";
			m_pConnection->Open(strConnect,"","",adModeUnknown);
			_bstr_t vSQL;
			vSQL= "restore database rsgl from disk = '"+FilePath+"' with replace";
			m_pConnection->Execute(vSQL, NULL, adCmdText);
			ExitConnect();
			AfxMessageBox("���ݿ⻹ԭ�ɹ�!");
		}		
		catch (_com_error e)
		{
			AfxMessageBox(e.Description());
		}
	}
	else
	{
		AfxMessageBox("��ָ����ԭ����·��!");
	}
	::CoUninitialize();
}
