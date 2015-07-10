#pragma once
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

class ADOConn
{
public:
	ADOConn(void);
	~ADOConn(void);	
	// 连接指针
	_ConnectionPtr m_pConnection;
	// 结果集指针
	_RecordsetPtr m_pRecordset;
	// 初始化连接指针并连接数据库
	void OnInitADOConn(void);
	// 关闭记录集和连接并释放环境
	void ExitConnect(void);
	// 获得记录集
	_RecordsetPtr& GetRecordSet(_bstr_t bstrSQL, int mode_dynamic = 0);
	// 执行一条SQL语句
	BOOL ExecuteSQL(_bstr_t bstrSQL);
	// 备份数据库文件
	void BackUp(CString FilePath);
	// 还原数据库文件
	void Recovery(CString FilePath);
};
