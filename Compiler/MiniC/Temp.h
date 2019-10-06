// Temp.h: interface for the CTemp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEMP_H__B2DC8BC0_5BC8_4253_A50B_4FCAA02811A1__INCLUDED_)
#define AFX_TEMP_H__B2DC8BC0_5BC8_4253_A50B_4FCAA02811A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
using namespace std;
class CTemp  
{
public:
	CTemp();
	virtual ~CTemp();
	string text;
	static int _temp;
private:
	int n;
	static int next();
	

};

#endif // !defined(AFX_TEMP_H__B2DC8BC0_5BC8_4253_A50B_4FCAA02811A1__INCLUDED_)
