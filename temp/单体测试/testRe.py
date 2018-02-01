#!/usr/bin/python
#coding:utf-8
import re
import xlrd
data=xlrd.open_workbook('/home/huangeryu/Desktop/CodeRepository/temp/CanData描述.xlsx')
table=data.sheets()[0]
istr=table.cell(138,25).value
ilist=istr.strip().split('\n')
pattern=re.compile(u'^【?(((\d+(～\d+)?)|[ABCDEF])[bh]?)】?:?(.*)')
mylist=[]
for line in ilist:
    print line
    match=pattern.match(line)
    if match:
        temp=[]
        print match.groups()
        print match.group(0)