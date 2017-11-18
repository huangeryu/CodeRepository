#ifndef KMP_H
#define KMP_H

#include<string>
#include<iostream>
class MyString
{
/*打印出状态转换表*/
friend void operator <<(std::ostream & os,MyString& ms);
/*从@param 中查找@ms*/
friend bool find(std::string& s,MyString& ms);
private:
	std::string str;
	int length;
	int* states;
public:
	MyString(std::string sample):str(sample)
	{
		length=sample.length();
		states=new int[length+1]();
		getStates();
	}

	virtual ~MyString()
	{
		delete states;
	}
	/*获得状态转换*/
	void getStates();
};

#endif
