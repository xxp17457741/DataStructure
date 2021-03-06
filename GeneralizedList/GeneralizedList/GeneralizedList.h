#pragma once

#include<iostream>
#include<assert.h>

using namespace std;


enum Type
{
	HEAD,//头节点
	VALUE,//值
	SUB//子表节点
};

struct GeneralizedNode//广义表节点
{
	GeneralizedNode(const Type& type = HEAD,const char& value='0')
	:_next(NULL)
	,_SubLink(NULL)
	, _type(type)
	{
		_value = value;
	}
	Type _type;//节点类型
	GeneralizedNode* _next;//指向同层下一个节点的地址
	union
	{
		char _value;//值
		GeneralizedNode* _SubLink;//指向子表指针
	};
};

class Generalized
{
public:
	Generalized()
	:_head(NULL)
	{}
	Generalized(const char *str)
		:_head(NULL)
	{
		_head = _CreatList(str);
	}
	Generalized(const Generalized& g)
		:_head(NULL)
	{
		_head=CopyGeneralized(g._head);
	}
	/*Generalized& operator=(Generalized g)
	{
		swap(_head, g._head);
		return *this;
	}*/
	Generalized& operator=(const Generalized& g)
	{
		if (this != &g)
		{
			GeneralizedNode *tmp = CopyGeneralized(g._head);
			_DelGeneralized(_head);
			_head =tmp;
		}
		return *this;
	}

	~Generalized()
	{
		_DelGeneralized(_head);
		_head = NULL;
	}
	void Print()
	{
		_Print(_head);
	}
	size_t Size()
	{
		return _Size(_head);
	}
	size_t Depth()
	{
		return _Depth(_head);
	}
protected:
	size_t _Depth(GeneralizedNode *head)
		//深度是计算广义表中最深的表的深度
	{
		int depth = 1;//刚开始默认最深的表深度为1
		GeneralizedNode* cur = head;
		while (cur)
		{
			if (cur->_type == SUB)//若遇到子表
			{
				int subdepth = _Depth(cur->_SubLink);//递归计算子表的深度
				if (subdepth+1 > depth)//若子表深度加1（广义表的目前最深度）大于原来广义表的深度
				{
					depth = subdepth+1;//重置广义表最深度置
				}
			}
			cur = cur->_next;
		}
		return depth;
	}
	size_t _Size(GeneralizedNode *head)//广义表中元素的个数
	{
		int count = 0;
		
		GeneralizedNode* cur = head;
		while (cur)
		{
			if (cur->_type == VALUE)
			{
				count++;
			}
			else if (cur->_type == SUB)
			{
				count += _Size(cur->_SubLink);
			}
			cur = cur->_next;
		}
		return count;
	}
	GeneralizedNode* CopyGeneralized(GeneralizedNode* head)
	{
		GeneralizedNode* chead = new GeneralizedNode(HEAD);
		 GeneralizedNode* cur = head->_next;
		 GeneralizedNode* _cur = chead;
		while (cur)
		{
			if (cur->_type == VALUE)
			{
				_cur->_next = new GeneralizedNode(VALUE, cur->_value);
				_cur = _cur->_next;
			}
			else if (cur->_type == SUB)
			{
				
				_cur->_next = new GeneralizedNode(SUB);
				_cur = _cur->_next;
				_cur->_SubLink=CopyGeneralized(cur->_SubLink);
			}
			cur = cur->_next;
		}
		return chead;
	}

	void _DelGeneralized(GeneralizedNode* head)
	{
		if (head == NULL)
			return;
		GeneralizedNode* cur = head;
		GeneralizedNode* del = NULL;
		while (cur)
		{
			del = cur;
			if (cur->_type == SUB)//遇到子表节点时看做子问题
			{
				_DelGeneralized(cur->_SubLink);
			}
			cur = cur->_next;
			delete del;
		}
	}
	bool IsValue(char ch)
	{
		if ((ch >= '0'&& ch <= '9') || (ch >= 'a'&& ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
			return true;
		else
			return false;
	}
	void _Print(GeneralizedNode* &head)
	{
		assert(head);
		GeneralizedNode* cur = head;
		bool IsInTable = true;
		while (cur)
		{
			if (cur->_type == HEAD)
			{
				cout << "(";
				cur = cur->_next;
				if (cur == NULL)
					cout << ")";
			}
			else if (cur->_type == VALUE)
			{
				cout << cur->_value;
				if (cur->_next != NULL)
					cout << ",";
				else
				{
					cout << ")";
					return;
				}
				cur = cur->_next;
			}
			else if(cur->_type == SUB)
			{
				_Print(cur->_SubLink);
				if (cur->_next != NULL)
					cout << ",";
				else
					cout << ")";
				cur = cur->_next;
			}
		}
	}
	GeneralizedNode* _CreatList(const char* &str)
	{

		assert(str && *str == '(');
		++str;
		GeneralizedNode* head = new GeneralizedNode(HEAD);
		GeneralizedNode* cur = head;
		while (*str)
		{
			if (IsValue(*str))//若节点值是合法值
			{
				cur->_next = new GeneralizedNode(VALUE,*str);//则创建一个值节点
				cur = cur->_next;
				str++;
			}
			else if (*str == '(')//遇到'('表示它是一个子表节点
			{
				cur->_next = new GeneralizedNode(SUB);//创建一个子表节点
				cur = cur->_next;
				cur->_SubLink = _CreatList(str);//递归解决子表的创建
			}
			else if (*str == ')')//遇到')'说明一个广义表或者子表结束
			{
				++str;
				return head;//返回子表的头节点，或广义表的头节点
			}
			else
				++str;
		}
		assert(false);
		return head;
	}
private:
	GeneralizedNode* _head;
};
