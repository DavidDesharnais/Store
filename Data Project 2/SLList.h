#pragma once

template <typename Type> class SLLIter;

template<typename Type>
class SLList
{
protected:

	friend class SLLIter <Type>;

private:
	unsigned int listSize;

	struct Node
	{
		Type element;
		Node *next;
	};

	Node* head;

	void Recursion(const Node* theNode)
	{
		if (theNode == nullptr)
			return;
		else
		{
			Recursion(theNode->next);
			addHead(theNode->element);
		}
	}

public:
	SLList()
	{
		head = nullptr;
		listSize = 0;
	}

	~SLList()
	{
		clear();
	}


	SLList<Type>& operator=(const SLList<Type>& that)
	{
		if (this != &that)
		{
			/*listSize = that.listSize;
			head = that.head;
			Node* tmp = head;
			for (unsigned int i = 0; i < listSize; i++)
			{
				tmp = tmp->next;
			}*/

			Recursion(that.head);
		}
		return *this;
	}

	SLList(const SLList<Type>& that)
	{
		head = nullptr;
		*this = that;
	}

	void addHead(const Type& v)
	{
		Node* tmp = new Node;
		tmp->element = v;
		tmp->next = head;
		head = tmp;
		listSize++;
	}

	void clear()
	{
		Node* tmp;
		while (head != nullptr)
		{
			tmp = head;
			head = head->next;
			delete tmp;
		}
		listSize = 0;
	}

	void insert(SLLIter<Type>& index, const Type& v)
	{
		Node* tmp = new Node;
		tmp->element = v;
		if (index.cur != head)
		{
			index.prev->next = tmp;
			tmp->next = index.cur;
			index.cur = tmp;
		}

		else
		{
			tmp->next = index.cur;
			head = tmp;
			index.cur = tmp;
		}
		listSize++;
	}

	void remove(SLLIter<Type> index)
	{
		if (size() != 0)
		{
			if (index.cur != head)
			{
				index.prev->next = index.cur->next;
				delete index.cur;
				index.cur = index.prev->next;
				listSize--;
			}
			else
			{
				head = head->next;
				delete index.cur;
				index.cur = head;
				listSize--;
			}
		}
	}

	unsigned int size() const { return listSize; }

};

template<typename Type>
class SLLIter
{
protected:

	friend class SLList <Type>;

private:
	typename SLList<Type>::Node* cur;
	typename SLList<Type>::Node* prev;
	SLList<Type>* list;

public:
	SLLIter(SLList<Type>& listToIterate)
	{
		list = &listToIterate;
		cur = list->head;
		prev = nullptr;
	}

	void begin()
	{
		prev = nullptr;
		cur = list->head;
	}

	bool end() const
	{
		if (cur == nullptr)
		{
			return true;
		}
		return false;
	}

	SLLIter<Type>& operator++()
	{
		if (cur != nullptr)
		{
			prev = cur;
			cur = cur->next;
		}
		return *this;
	}

	Type& current() const
	{
		return cur->element;
	}
};