#ifndef LIST_H
#define LIST_H

namespace Mikami
{
	template<typename T>
	struct Node {
		T data;
		Node* next;
	};

	template<typename T>
	class IList
	{
	public:
		virtual void append(const T& x) = 0;
		virtual void insert(int i, const T& x) = 0;
		virtual void remove(int i) = 0;
		virtual int size() = 0;
		virtual void clear() = 0;
		virtual T& operator[](int i) = 0;
	};

	template<typename T>
	class List :public IList<T>
	{
	protected:
		Node<T>* head;
		int _size;

	public:
		List();
		List(T* begin, T* end);
		~List();
		int size();
		void append(const T& x);
		void reverse();
		void insert(int i, const T& x);
		void remove(int i);
		void clear();
		T& operator[](int i);

	};

	template<typename T>
	List<T>::List() :_size(0)
	{
		head = new Node<T>;
		head->next = nullptr;
	}

	template<typename T>
	List<T>::List(T* begin, T* end) :_size(0)
	{
		head = new Node<T>;
		head->next = nullptr;
		while (begin != end)
			append(*(begin++));
	}

	template<typename T>
	List<T>::~List()
	{
		clear();
		delete head;
	}

	template<typename T>
	int List<T>::size()
	{
		return _size;
	}

	template<typename T>
	void List<T>::append(const T& x)
	{
		Node<T>* p = head;
		while (p->next)
			p = p->next;
		Node<T>* q = new Node<T>;
		q->data = x;
		q->next = nullptr;
		p->next = q;
		_size++;
	}

	template<typename T>
	void List<T>::reverse()
	{
		Node<T>* p = nullptr,
			* q = head->next,
			* r = q->next;

		while (r->next) {
			q->next = p;

			p = q;
			q = r;
			r = r->next;
		}
		q->next = p;
		r->next = q;
		head->next = r;
	}

	template<typename T>
	void List<T>::insert(int i, const T& x)
	{
		Node<T>* p = head->next;
		while (i--)
			p = p->next;
		Node<T>* q = new Node<T>;
		q->data = x;
		q->next = p->next;
		p->next = q;
		_size++;
	}

	template<typename T>
	void List<T>::remove(int i)
	{
		Node<T>* p = head;
		while (i--)	//p指向待删除节点的前一个节点
			p = p->next;
		Node<T>* q = p->next;
		p->next = q->next;
		delete q;
		_size--;
	}

	template<typename T>
	void List<T>::clear()
	{
		Node<T>* p = head->next, * q = nullptr;
		while (p) {
			q = p;
			p = p->next;
			delete q;
		}
		head->next = nullptr;
		_size = 0;
	}

	template<typename T>
	T& List<T>::operator[](int i)
	{
		Node<T>* p = head->next;
		while (i--)
			p = p->next;
		return p->data;
	}
}

#endif
