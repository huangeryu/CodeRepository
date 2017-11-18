#include "kmp.h"
void MyString::getStates()
{
	if(length<=0)return;
	int t=0;//t当前最大的前后缀
	states[1]=0;
	for(int s=1;s<length;s++)
	{
		while(t>0&& str[t]!=str[s])t=states[t];//状态回退
		//当跳出while循环时，t==0 || str[t]==str[s]
		if(str[t]==str[s])
		{
			t++;
			states[s+1]=t;
		}
		else states[s+1]=0; //t==0 && str[t]!=str[s];
	}
}

void operator <<(std::ostream& os,MyString& ms)
{
	if(!ms.length)return;
	os<<"str="<<ms.str<<"\n";
	for(int i=1;i<=ms.length;i++)
	{
		os<<"states["<<i<<"]="<<ms.states[i]<<" ";
	}
	os<<"\n";
}

bool find(std::string& s,MyString& ms)
{
	if(!s.length())return false;
	int len=s.length();
	int t=0;
	for(int i=0;i<len;i++)
	{
		while(t>0&& s[i]!=ms.str[t])t=ms.states[t];//状态回退
		//t==0 || s[i]==ms.str[t]
		if(s[i]==ms.str[t])t++; //s[i]==ms.str[t]
		//else t==0;
		if(t>=ms.length)return true;
	}
	return false;
}
