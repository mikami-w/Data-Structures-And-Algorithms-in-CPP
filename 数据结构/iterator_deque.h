#ifndef ITERATOR_DEQUE_H
#define ITERATOR_DEQUE_H

template<typename T, size_t CHUNK_CAPACITY>
class Deque;

namespace Mikami
{
	template<typename T, size_t CHUNK_CAPACITY>
	class iterator_deque
	{
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using referrence = T&;
		using self = iterator_deque;
		using parent_type = Deque<T, CHUNK_CAPACITY>;
	
		explicit iterator_deque() :p(nullptr), parent(nullptr) {}
		explicit iterator_deque(parent_type* _parent, pointer _p) :p(_p), parent(_parent) {}
		bool operator==(const self& it) { return p == it.p; }
		bool operator!=(const self& it) { return p != it.p; }
		bool operator<=(const self& it) { return !(p > it.p); }
		bool operator>=(const self& it) { return !(p < it.p); }
		bool operator<(const self& it);
		bool operator>(const self& it);
		_forceinline referrence operator*() { return *p; }
		self& operator++();		//前缀
		self operator++(int);	//后缀
		self& operator--();		//前缀
		self operator--(int);	//后缀
		self operator+(int diff);
		friend self operator+(int diff, self it);
		self operator-(int diff);
		difference_type operator-(const self& it);
	
	
	private:
		T* p;
		parent_type* parent;
	
	};

	template<typename T, size_t CHUNK_CAPACITY>
	iterator_deque<T, CHUNK_CAPACITY>::self operator+(int diff, typename iterator_deque<T, CHUNK_CAPACITY>::self it)
	{

	}
}



#endif	// ITERATOR_DEQUE_H
