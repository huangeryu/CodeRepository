#include "kmp.h"
int main()
{
	std::string source,sample;
	std::cout<<"input source string:";
	getline(std::cin,source);
	std::cout<<"\ninput sample string:";
	getline(std::cin,sample);
	MyString ms(sample);
	std::cout<<"\n"<<ms;
	if(find(source,ms))std::cout<<"YRS!\n";
	else std::cout<<"NO!\n";
}
