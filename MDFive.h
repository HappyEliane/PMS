#pragma once

class MDFive
{
public:
	MDFive(void);
	~MDFive(void);
private:
	// �����ַ���
	CString plaint;
	// �����ַ���
	CString cipher;
	unsigned A,B,C,D,a,b,c,d,i,len,flen[2],x[16]; //i��ʱ����,len�ļ���,flen[2]Ϊ64λ�����Ʊ�ʾ���ļ���ʼ����
public:
	// ��������ַ���
	int SetPlaint(CString str);
	// ������ܺ��ֵ
	CString GetCiph(void);
	// md5�����㷨
	void md5(void);
};
