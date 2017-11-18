#ifndef __AC_H
#define __AC_H
#include<vector>
#include<algorithm>
#define _UNTERMINI 0	//非终端
#define _TERMINI 1		//终端

/*first,build tire tree
 *and then calculate failure function
 * finally,output the result set
 * */
class Node;
class line
{
public:
	char val;
	Node * prev;//相邻的上行点
	Node * next;//相邻的下行点
};
/*定义trie树的顶点*/
class Node
{
public:
	int id;		//状态值，唯一
	line* parent;//入度线
	std::vector<line*> lines;
	line* failure;//当匹配失效时，转移下一状态的出度线
	int flag;//表明当前状态是否是终端状态
	//get unique id
	void static generateID()
	{
		static int token=0;
		this->id=token++;
	}
	//constructor
	Node(int linesize=_DEFAULT_LINE_SIZE,int flag=_UNTERMINI):count(linesize),flag(flag)
	{
		generateID();
		failure=NULL;
		parent=NULL;
	}
	Node(line * parent):parent(parent)
	{
		new(this)Node();
	}
	line* search_and_return(char val)
	{
		for(auto m:lines)
		{
			if(m->val==val)return m;
		}
		return NULL;
	}
};

class TrieTree
{
public:
	Node* head;
	std::vector<std::string token> table;
	TrieTree(std::initializer_list<std::string> l)
	{
		for_each(l.begin(),l.end(),[](string& s){table.push_back(s)});
	}
	void buildTrieTree();
	void calculateFailure();
	void compairToken(std::vector<std::string>& vect,string target);
};

#endif
