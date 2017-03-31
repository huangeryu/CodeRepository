//实现红黑树的插入与删除
#include"stdafx.h"
#include<assert.h>
#include<stdio.h>
//节点左旋，该节点是父节点的右孩子，以该节点为中心，
//父节点做逆时针翻转
//A-B ---> B-A
//返回值该结点
NodePoint RBTree::leftRotate(NodePoint head)
{
	if (head == NULL||head->parent==NULL)return head;
	assert(head == head->parent->right);
	NodePoint parent = head->parent;
	Color temp = head->color;
	head->color = parent->color;
	parent->color = temp;
	parent->right = head->left;
	if (head->left != NULL)head->left->parent = parent;
	head->left = parent;
	head->parent=parent->parent;
	if (head->parent != NULL)
	{
		head->parent->left == parent ?head->parent->left=head :head->parent->right=head ;
	}
	parent->parent = head;
	return head; 
}
//右旋，该节点是父节点的左孩子
NodePoint RBTree::rightRotate(NodePoint head)
{
	if (head == NULL || head->parent == NULL)return head;
	assert(head == head->parent->left);
	NodePoint parent = head->parent;
	Color temp = head->color;
	head->color=parent->color;
	parent->color = temp;
	parent->left = head->right;
	if (head->right != NULL)head->right->parent = parent;
	head->right = parent;
	head->parent = parent->parent;
	if (head->parent != NULL)
	{
		head->parent->left == parent ?head->parent->left=head :head->parent->right=head ;
	}
	parent->parent = head;
	return head;
}
//红黑树的插入操作
void RBTree::insertNode(NodePoint &head, int data)
{
	NodePoint p = searchByVal(head, data);
	if (p == NULL)
	{
		head = new Node{ data,NULL,NULL,NULL,0,BLACK };
		return;
	}
	if (p->parent == NULL)
	{
		p->color = BLACK;
		return;
	}
	while (p->parent->color!=BLACK)
	{
		NodePoint parent = p->parent;
		NodePoint grandFather = parent->parent;
		if (grandFather == NULL)
		{
			parent->color = BLACK;
		}
		if (grandFather->left == parent)
		{
			NodePoint parent_brother = grandFather->right;
			if (parent_brother != NULL)
			{
				if (parent_brother->color == RED)
				{
					grandFather->color = RED;
					parent->color = BLACK;
					parent_brother->color = BLACK;
					p = grandFather;
					if (p->parent == NULL)
					{
						p->color = BLACK;
						return;
					}
				}
				else
				{
					if (parent->left == p)
					{
						rightRotate(parent);
					}
					else
					{
						leftRotate(p);
						rightRotate(p);
						p = p->left;
					}
				}
			}
			else
			{
				if (parent->left == p)
				{
					rightRotate(parent);
				}
				else
				{
					leftRotate(p);
					rightRotate(p);
					p = p->left;
				}
			}
		}
		else if(grandFather->right==parent)
		{
			NodePoint parent_brother = grandFather->left;
			if (parent_brother != NULL)
			{
				if (parent_brother->color == RED)
				{
					parent->color = BLACK;
					parent_brother->color = BLACK;
					grandFather->color = RED;
					p = grandFather;
					if (p->parent == NULL)
					{
						p->color = BLACK;
						return;
					}
				}
				else
				{
					if (parent->left == p)
					{
						rightRotate(p);
						leftRotate(p);
						p = p->right;
					}
					else
					{
						leftRotate(parent);
					}
				}
			}
			else
			{
				if (parent->left == p)
				{
					rightRotate(p);
					leftRotate(p);
					p = p->right;
				}
				else
				{
					leftRotate(parent);
				}
			}
		}
	}
	while (head->parent != NULL)
	{
		head = head->parent;
	}
}
//红黑树的删除操作
//先寻找第一个值为@param data的节点
//然后再寻找该节点的后继节点p，
//根据p的兄弟节点进行调整，调整完后在删除节点p；
void RBTree::deleteNode(NodePoint &head, int data)
{
	NodePoint p = searchByVal(head, data);
	if (p->data == data)
	{
		NodePoint parent = p->parent;
		if (p->color == RED)
		{
			if (p->left == NULL)   //如果左子树为NULL，右子树必为NULL
			{//直接删除红色的叶子节点
				parent->left == p ? parent->left=NULL:parent->right=NULL ;
				delete p;
			}
			else
			{//左右子树都不为空，则需要找到p节点的后继节点replacement;
				NodePoint repm = p->right;
				while (repm->left!=NULL)
				{
					repm = repm->left;
				}
				//交换repm和p节点的data数据，然后根据repm的颜色进行调整
				p->data = repm->data;
				if (repm->color == RED)
				{//该红色节点一定是叶子节点
					repm->parent->left == repm ? repm->parent->left=NULL:repm->parent->right=NULL ;
					delete repm;
				}
				else
				{//该节点是黑色的节点，再根据该节点是否有红色的右孩子节点进行调整
					if (repm->right == NULL)
					{
						//删除黑色叶子节点,这里进行所谓的双黑的处理
						doubleBlackAdjust(repm);
						repm == NULL;
					}
					else
					{//右孩子为红色节点,该红色节点必为叶子节点
						NodePoint rc = repm->right;
						//把红色节点的数据，放到父节点中并且删除红色节点
						repm->data = repm->right->data;
						delete repm->right;
						repm->right = NULL;
					}
				}
			}
		}
		else
		{//p->color==BLACK
			if (p->left == NULL)
			{//如果p的左节点是NULL，则右节点要么是NULL，要么是红色的叶子节点
				if (p->right == NULL)
				{
					//删除黑色的叶子节点的调整
					doubleBlackAdjust(p);
					p == NULL;
				}
				else
				{//p的右节点必为红色
					NodePoint rc = p->right;
					p->data=rc->data;
					p->right = NULL;
					delete rc;
				}
			}
			else
			{//如果p的左节点不是NULL
				if (p->right == NULL)
				{//p的左节点必须是红色的叶子节点
					NodePoint lc = p->left;
					p->data = lc->data;
					p->left == NULL;
					delete lc;
				}
				else
				{//左右节点都不是NULL，需要找出p节点的后继节点，根据后继节点的颜色进行调整
					NodePoint repm = p->right;
					while (repm->left!=NULL)
					{
						repm=repm->left;
					}
					p->data=repm->data;
					//repm节点没有左孩子节点，如果repm节点为红色，则repm节点为红色的叶子节点
					if (repm->color == RED)
					{
						repm->parent->left == repm ?repm->parent->left=NULL :repm->parent->left=NULL ;
						delete repm;
					}
					else
					{//repm节点为黑色节点，则根据该节点是否有右节点进行调整
						if (repm->right == NULL)
						{
							//这里进行删除黑色叶子节点的调整
							doubleBlackAdjust(repm);
							repm == NULL;
						}
						else
						{//如果repm有右节点，则右节点必须为红色的节点
							NodePoint rc = repm->right;
							repm->data = rc->data;
							repm->right = NULL;
							delete rc;
						}
					}
				}
			}
		}
	}
}
//删除黑色的叶子节点的调整
void RBTree::doubleBlackAdjust(NodePoint head)
{//head节点必须有父节点
	assert(head->parent != NULL);
	NodePoint parent = head->parent;
	if (parent->left == head)
	{//head节点为parent节点的做孩子
		NodePoint brother = parent->right;
		assert(brother != NULL);
		if (brother->color == RED)
		{//情况1
			leftRotate(brother);
		}
		//重新获得head的父亲和兄弟节点
		parent = head->parent;
		brother = parent->right;
		//兄弟节点的颜色一定是黑色
		assert(brother->color == BLACK);
		if (brother->left==NULL&&brother->right==NULL)
		{//情况二
			parent->color = BLACK;
			brother->color = RED;
			parent->left = NULL;
			delete head;
			return;
		}
		else if(brother->left!=NULL && brother->right==NULL)
		{//情况三
			rightRotate(brother->left);
		}
		//重新获得兄弟节点
		brother = parent->right;
		if (brother->right != NULL)
		{//情况四
			leftRotate(brother);
			brother->right->color = BLACK;
			parent->left = NULL;
			delete head;
			return;
		}
	}
	else
	{//parent->right==head
		assert(parent != NULL);
		NodePoint brother = parent->left;
		if (brother->color == RED)
		{//情况一
			rightRotate(brother);
		}
		//重新获得父亲节点和兄弟节点
		parent = head->parent;
		brother = parent->left;
		if (brother->right == NULL&&brother->left == NULL)
		{
			parent->color = BLACK;
			brother->color = RED;
			parent->right = NULL;
			delete head;
		}
		else if(brother->right!=NULL&&brother->left==NULL)
		{
			leftRotate(brother->right);
		}
		//重新获得兄弟节点
		brother = parent->left;
		if (brother->left != NULL)
		{
			rightRotate(brother);
			brother->left->color = BLACK;
			parent->right = NULL;
			delete head;
			return;
		}
	}
}
void RBTree::travers_RBTree(NodePoint head)
{
	using namespace std;
	if (head == NULL)return;
	travers_RBTree(head->left);
	printf("%5d", head->data);
	travers_RBTree(head->right);
}
//根据值对红黑树进行搜索
//如果树是空的，返回NULL
//如果找到返回该节点，如果找不到则插入该节点，并返回该节点
NodePoint RBTree::searchByVal(NodePoint head, int data)
{
	if (head == NULL)return NULL;
	if (head->data == data)return head;
	else if (head->data > data)
	{
		if (head->left == NULL)
		{
			head->left = new Node{data,NULL,NULL,head,0,RED};
			return head->left;
		}
		searchByVal(head->left, data);
	}
	else
	{
		if (head->right == NULL)
		{
			head->right = new Node{ data,NULL,NULL,head,0,RED };
			return head->right;
		}
		searchByVal(head->right, data);
	}
}