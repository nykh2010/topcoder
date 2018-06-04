#pragma once
class user
{
public:
	user(CString id);
	virtual ~user(void);
	void setname(CString &name);
	CString getname();
	void setcorporation(CString &name);
	CString getcorporation();
private:
	CString name;
	CString corporation;
	CString id;
};

class CUser
{
public:
	CUser(void);
	~CUser(void);
	void setname(CString &name);
	CString getname();
	void setcorporation(CString &name);
	CString getcorporation();
public:
	CString name;
	CString corporation;
	CString id;
};

