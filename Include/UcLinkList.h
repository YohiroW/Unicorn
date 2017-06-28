#ifndef _UC_LINKLIST_H_
#define _UC_LINKLIST_H_
//
#include "UcObject.h"

namespace Unicorn
{
	template<class T>
	struct Node
	{
		Node* next;
		T elem;
	};

	template<class T>
	class LinkList: public Object
	{
	public:
		LinkList();
		~LinkList();

		//insert behind the 'loc' node
		bool insert(const int& loc, T data);
		bool append(T data);
		Node<T>* remove(T data);
		//
		unsigned int getLength() const;
		Node<T>* getLinkHead() const;
		//
		bool isEmpty();

		virtual void destroy();

	private:
		Node<T>* _linkHead;
		Node<T>* _linkRear;
		unsigned int _length;
	};

	template<class T>
	bool LinkList<T>::isEmpty()
	{
		return _length == 0;
	}

	template<class T>
	Node<T>* LinkList<T>::getLinkHead() const
	{
		return _linkHead;
	}

	template<class T>
	LinkList<T>::LinkList() :
		_length(0)
	{
		_linkHead = new Node<T>;
		_linkHead->next = NULL;
		_linkRear = _linkHead;
	}

	template<class T>
	LinkList<T>::~LinkList()
	{
		this->destroy();
	}

	template<class T>
	Node<T>* LinkList<T>::remove(T data)
	{
		if (!_linkHead->next){
			return NULL;
		}

		Node<T>* p = _linkHead->next;
		Node<T>* pre = _linkHead;
		Node<T>* deletedNode = NULL;
		while (p)
		{
			if (p->elem == data)
			{
				deletedNode = p;
				pre->next = p->next;
				break;
			}
			pre = p;
			p = p->next;
		}

		_length--;
		return deletedNode;
	}

	template<class T>
	bool LinkList<T>::append(T data)
	{
		Node<T>* node = new Node<T>;
		node->next = NULL;
		node->elem = data;

		node->next = _linkHead->next;
		_linkHead->next = node;

		++_length;
		return true;
	}

	template<class T>
	bool LinkList<T>::insert(const int& loc, T data)
	{
		Node<T>* node = new Node<T>;
		node->next = NULL;
		node->elem = data;

		Node<T>* p = _linkHead->next;
		unsigned int len = 0;
		while (p)
		{
			if (loc == len)
			{
				node->next = p->next;
				p->next = node;
				break;
			}
			len++;
			p = p->next;
		}
		++_length;

		return true;
	}

	template<class T>
	unsigned int LinkList<T>::getLength() const
	{
		return _length;
	}

	template<class T>
	void LinkList<T>::destroy()
	{
		Node<T>* p = _linkHead->next;
		Node<T>* q = p;
		while (p)
		{
			q = p->next;
			UCSafeDelete(p);
			p = q;
		}
	}

}

#endif