#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <type_traits>
#include <initializer_list>
#include "IContainers.h"
// vector:使用静态数组,若内存不足则扩容,复制全部数据到扩容数组后删除原数组

namespace Mikami
{
	template<typename T, int INITSIZE = 128>
	class Vector :public virtual IContainers
	{
	public:
		struct iterator
		{
			using iterator_category = std::random_access_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = T*;
			using referrence = T&;
			using self = iterator;

			explicit iterator() :p(nullptr) {}
			explicit iterator(T* p_) :p(p_) {}

			bool operator==(const self& it) { return p == it.p; }
			bool operator!=(const self& it) { return p != it.p; }
			bool operator<(const self& it) { return p < it.p; }
			bool operator>(const self& it) { return p > it.p; }
			bool operator<=(const self& it) { return !(p > it.p); }
			bool operator>=(const self& it) { return !(p < it.p); }
			referrence operator*() { return *p; }
			self& operator++() { ++p; return *this; }		//前缀
			self operator++(int) { return iterator(p++); }	//后缀
			self& operator--() { --p; return *this; }		//前缀
			self operator--(int) { return iterator(p--); }	//后缀
			self operator+(int diff) { return iterator(p + diff); }
			friend self operator+(int diff, self it);
			self operator-(int diff) { return iterator(p - diff); }
			std::ptrdiff_t operator-(const self& it) { return p - it.p; }

		private:
			T* p;
		};

		virtual size_t capacity() { return _capacity; }
		virtual size_t size() { return _size; }
		virtual void clear() { _size = 0; }
		virtual bool empty() { return (bool)_size; }
		virtual void swap(IContainers& obj);

		Vector() :_capacity(INITSIZE), _size(0) { _data = new T[INITSIZE]; }
		Vector(size_t count, const T& value);
		Vector(std::initializer_list<T> li);
		~Vector() { delete[] _data; }
		bool full() { return _capacity == _size; }
		T& operator[](int index) { if (index < _capacity) return _data[index]; else throw std::out_of_range("Index is out of range.(Mikami::Vector<T, INITSIZE>::operator[](int))"); }
		T& at(int index) { if (index < _size) return _data[index]; else throw std::out_of_range("Index is out of range.(Mikami::Vector<T, INITSIZE>::at(int))"); }
		T& front() { return _data[0]; }
		T& back() { if (_size) return _data[_size - 1]; else throw std::out_of_range("Vector is empty."); }
		T* data() { return _data; }
		//const T* data() const { return _data; }
		T pop_back() { if (_size) return _data[_size--]; else throw std::out_of_range("Vector is empty."); }
		void push_back(const T& value) { expand_if_full(); _data[_size++] = value; }
		iterator begin() { return iterator(_data); }
		iterator end() { return iterator(_data + _size); }
		void append(std::initializer_list<T> li) { append(li.begin(), li.end()); }
		void append(iterator begin, iterator end);

	private:
		T* _data;
		size_t _capacity;
		size_t _size;

		void _expand(size_t multiple = 2);
		void expand_if_full(size_t newdata = 1);
	};

	template<typename T, int INITSIZE>
	typename Vector<T, INITSIZE>::iterator::self operator+(int diff, typename Vector<T, INITSIZE>::iterator::self it) { return iterator(it.p + diff); }

	template<typename T, int INITSIZE>
	void Vector<T, INITSIZE>::swap(IContainers& obj)
	{
		Vector<T, INITSIZE>& _obj = dynamic_cast<Vector<T, INITSIZE>&>(obj);

		T* tdata = _data;
		_data = _obj._data;
		_obj._data = tdata;

		auto tsize = _size;
		_size = _obj._size;
		_obj._size = tsize;

		auto tcapacity = _capacity;
		_capacity = _obj._capacity;
		_obj._capacity = tcapacity;
	}

	template<typename T, int INITSIZE>
	inline Vector<T, INITSIZE>::Vector(size_t count, const T& value) :_capacity(count <= INITSIZE ? INITSIZE : count * 1.5), _size(count)
	{
		static_assert(std::is_constructible<T, const T&>::value,
			"Type T must be copy-constructible.(Mikami::Vector<T, INITSIZE>::Vector(int,const T&)");

		_data = new T[_capacity];
		for (int i = 0; i < count; ++i)
			*(_data + i) = value;
	}
	template<typename T, int INITSIZE>
	inline Vector<T, INITSIZE>::Vector(std::initializer_list<T> li) :_size(li.size()), _capacity(li.size() <= INITSIZE ? INITSIZE : li.size() * 1.5)
	{
		static_assert(std::is_constructible<T, const T&>::value,
			"Type T must be copy-constructible.(Mikami::Vector<T, INITSIZE>::Vector(std::initializer_list<T>))");

		_data = new T[_capacity];
		int i = 0;
		for (auto x : li)
			_data[i++] = T(x);
	}

	template<typename T, int INITSIZE>
	inline void Vector<T, INITSIZE>::append(iterator _begin, iterator _end)
	{
		expand_if_full(_end - _begin);
		for (int i = 0; _begin < _end; ++_begin, ++i) {
			_data[_size + i] = *_begin;
		}
	}

	template<typename T, int INITSIZE>
	inline void Vector<T, INITSIZE>::_expand(size_t multiple)
	{
		if constexpr (	// 无需构造函数
			std::is_fundamental<T>::value ||
			std::is_pointer<T>::value ||
			std::is_reference<T>::value
			) {
			T* _old = _data;
			_data = new T[_capacity *= multiple];
			memcpy(_data, _old, _size * sizeof(T));
			delete[] _old;
		}
		else {	// 需要移动与复制构造函数
			static_assert(std::is_constructible<T, T&&>::value && std::is_constructible<T, const T&>,
				"Type T must be copy-constructible and move-constructible.(Mikami::Vector<T, INITSIZE>::_expand(int))");

			T* _old = _data;
			_data = new T[_capacity *= multiple];

			for (int i = 0; i < _size; ++i)
				_data[i] = std::move(_old[i]);

			delete[] _old;
		}
	}

	template<typename T, int INITSIZE>
	inline void Vector<T, INITSIZE>::expand_if_full(size_t newdata)
	{
		size_t need = newdata - (_capacity - _size);
		if (need > 0)
			_expand(1 + need / _capacity + (need % _capacity ? 1 : 0));
	}

}

#endif
