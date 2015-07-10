#include "StdAfx.h"
#include "ADOConn.h"

ADOConn::ADOConn(void)
{
}

ADOConn::~ADOConn(void)
{
}

// 初始化连接指针并连接数据库
void ADOConn::OnInitADOConn(void)
{
	//初始化OLE/COM库环境
	::CoInitialize(NULL);
	try
	{
		//创建connection对象
		m_pConnection.CreateInstance("ADODB.Connection");
		//设置连接字符串
		_bstr_t strConnect = "DRIVER=SQL server;Database=rsgl;Server=WYN";
		m_pConnection->Open(strConnect,"","",adModeUnknown);
	}
	//捕捉异常
	catch (_com_error e)
	{
		//显示错误信息
		AfxMessageBox(e.Description());
	}
	return;
}

// 关闭记录集和连接并释放环境
void ADOConn::ExitConnect(void)
{
	//关闭记录集和连接
	//if(m_pRecordset != NULL)
		//m_pRecordset->Close();
	m_pConnection->Close();
	//释放环境
	::CoUninitialize();
}

// 获得记录集
_RecordsetPtr& ADOConn::GetRecordSet(_bstr_t bstrSQL, int mode_dynamic)
{
	try
	{
		//连接数据库，如果connection对象为空，则重新连接数据库
		if (m_pConnection == NULL)
			OnInitADOConn();
		//创建记录集对象
		m_pRecordset.CreateInstance(__uuidof(Recordset));
		//取得表中的记录
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
	//返回记录集
	return m_pRecordset;
}

// 执行一条SQL语句
BOOL ADOConn::ExecuteSQL(_bstr_t bstrSQL)
{
	_variant_t RecordsAffected;
	try
	{
		_variant_t var;
		//是否已连接数据库
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

// 备份数据库文件
void ADOConn::BackUp(CString FilePath)
{
	//::CoInitialize(NULL);
	if (FilePath != "")
	{
		try
		{
			//连接数据库
	//		OnInitADOConn();
			_bstr_t vSQL;
			vSQL = "backup database rsgl to disk = '"+FilePath+"'";
			ExecuteSQL(vSQL);
			ExitConnect();
			AfxMessageBox("数据库备份成功!");
		}
		catch(_com_error e)// 捕捉异常
		{
			// 显示错误信息
			AfxMessageBox(e.Description());
		}
	}
	else
	{
		AfxMessageBox("请指定备份数据路径!");
	}
	//::CoUninitialize();
}

// 还原数据库文件
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
			AfxMessageBox("数据库还原成功!");
		}		
		catch (_com_error e)
		{
			AfxMessageBox(e.Description());
		}
	}
	else
	{
		AfxMessageBox("请指定还原数据路径!");
	}
	::CoUninitialize();
}
