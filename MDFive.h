#pragma once

class MDFive
{
public:
	MDFive(void);
	~MDFive(void);
private:
	// 明文字符串
	CString plaint;
	// 密文字符串
	CString cipher;
	unsigned A,B,C,D,a,b,c,d,i,len,flen[2],x[16]; //i临时变量,len文件长,flen[2]为64位二进制表示的文件初始长度
public:
	// 获得明文字符串
	int SetPlaint(CString str);
	// 计算加密后的值
	CString GetCiph(void);
	// md5核心算法
	void md5(void);
};
