#include<iostream>

int main()
{
    int a=0;
    int* p=(int*)a;
    std::cout<<sizeof(p)<<std::endl;
}