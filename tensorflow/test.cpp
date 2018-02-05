#include<iostream>
#include "TestMode.h"
#include<Python.h>

int main()
{
    TestMode* t=new TestMode();
    for(int i=0;i<t->len;i++)
    {
        //std::cout<<t->data[i][COLUMN-1]<<std::endl;
    }
}