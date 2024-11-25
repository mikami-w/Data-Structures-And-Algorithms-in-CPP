#ifndef DEQUE_H
#define DEQUE_H

#include "iterator_deque.h"
#include <type_traits>
// deque:用指针列表(块数组)管理多段连续内存,实现不连续空间的假随机存取

#define M_MAP_MIN 8

namespace Mikami
{
	template<typename T, size_t CHUNK_CAPACITY = 256>
	class Deque
	{
		enum DirectionToExpand { front, back };

		friend class iterator_deque<T, CHUNK_CAPACITY>;
	public:
		using iterator = iterator_deque<T, CHUNK_CAPACITY>;


		const int CHUNK_SIZE = CHUNK_CAPACITY * sizeof(T);


		size_t capacity() { return _map_size * CHUNK_CAPACITY; }
		size_t size() { return _size; }
		void clear();
		bool empty() { return _begin == _end; }
		void swap(Deque<T, CHUNK_CAPACITY>& obj);


		Deque() :_map(nullptr), _map_size(0), _begin(), _end(), _size(0) {}
		Deque(size_t initsize) :
			_map_size(initsize / CHUNK_CAPACITY + 1 > M_MAP_MIN ? initsize / CHUNK_CAPACITY + 1 : M_MAP_MIN),
			_map(new T* [_map_size] {}), _begin(this, _map), _end(this, _begin + initsize), _size(initsize) {}

		Deque(size_t initsize, const T& value);
		Deque(const Deque<T>& obj);
		Deque(Deque<T>&& obj);

		
		T pop_back() { return *(--_end); }
		T pop_front() { return *(_begin++); }

		void push_back(const T& value) { _expand_if_full(DirectionToExpand::back, 1); *(_end++) = value; }
		void push_front(const T& value) { _expand_if_full(DirectionToExpand::front, 1); *(--_begin) = value; }


		void insert(iterator position, const T& x);
		void insert(iterator position, int n, const T& x);
		void insert(iterator begin, iterator end);


		const T& front() { return *_begin; }
		const T& back() { return *(_end - 1); }

	private:
		size_t _map_size;
		T** _map;	//指针数组 map
		T** _M_begin, _M_end;	// map 的首尾

		iterator _begin;
		iterator _end;
		size_t _size;

		void _init();
		void _expand_if_full(size_t newdata, DirectionToExpand direction);

	};

	template<typename T, size_t CHUNK_CAPACITY>
	inline Deque<T, CHUNK_CAPACITY>::Deque(size_t initsize, const T& value) :
		_map_size(initsize / CHUNK_CAPACITY + 1 > M_MAP_MIN ? initsize / CHUNK_CAPACITY + 1 : M_MAP_MIN),
		_map(new T* [_map_size] {}),
		_M_begin(_map + (_map_size >> 2)),
		_M_end(_M_begin),
		_begin(this, _M_begin),
		_end(this, _begin + initsize),
		_size(initsize)
	{
		static_assert(std::is_copy_constructible<T>::value,
			"Type T must be copy-constructible.(Mikami::Deque<T, CHUNK_CAPACITY>::Deque(size_t,const T&)");

		for (iterator it = _begin; it < _end; ++it)
			*it = value;
	}

	template<typename T, size_t CHUNK_CAPACITY>
	inline Deque<T, CHUNK_CAPACITY>::Deque(const Deque<T>& obj) :
		_map_size(obj._map_size),
		_map(new T* [_map_size] {}),
		_M_begin(_map + (_map_size >> 2)),
		_M_end(_M_begin + obj._map_size),
		_begin(this, _M_begin),
		_end(this, _M_end),
		_size(obj._size)
	{
		static_assert(std::is_copy_constructible<T>::value,
			"Type T must be copy-constructible.(Mikami::Deque<T, CHUNK_CAPACITY>::Deque(size_t,const T&)");

		for (iterator it = _begin, it_o = obj._begin; it < _end; ++it, ++it_o)
			*it = *it_o;

	}

	template<typename T, size_t CHUNK_CAPACITY>
	inline Deque<T, CHUNK_CAPACITY>::Deque(Deque<T>&& obj) :
		_map_size(obj._map_size),
		_map(obj._map),
		_M_begin(obj._M_begin),
		_M_end(obj._M_end),
		_begin(obj._begin),
		_end(obj._end),
		_size(obj._size)
	{
		obj._map = nullptr;
	}


	template<typename T, size_t CHUNK_CAPACITY>
	inline void Deque<T, CHUNK_CAPACITY>::clear()
	{
		_M_begin = (_map_size >> 2) + _map;
		_M_end = _M_begin;
		_size = 0;
		_begin = iterator(this, _M_begin);
		_end = _begin;
	}

	template<typename T, size_t CHUNK_CAPACITY>
	inline void Deque<T, CHUNK_CAPACITY>::swap(Deque<T, CHUNK_CAPACITY>& obj)
	{
		size_t _map_size_t = _map_size;
		T** _map_t = _map;
		T** _M_begin_t = _M_begin;
		T** _M_end_t = _M_end;
		iterator _begin_t = _begin;
		iterator _end_t = _end;
		size_t _size_t = _size;

		_map_size = obj._map_size;
		_map = obj._map;
		_M_begin = obj._M_begin;
		_M_end = obj._M_end;
		_begin = obj._begin;
		_end = obj._end;
		_size = obj._size;

		obj._map_size = _map_size_t;
		obj._map = _map_t;
		obj._M_begin = _M_begin_t;
		obj._M_end = _M_end_t;
		obj._begin = _begin_t;
		obj._end = _end_t;
		obj._size = _size_t;
	}

	template<typename T, size_t CHUNK_CAPACITY>
	inline void Deque<T, CHUNK_CAPACITY>::_init()
	{
		if (_map) return;	//如果map非空则已经有空间, 不进行初始化

		_map_size = M_MAP_MIN;
		_map = new T * [_map_size] {};
		_M_begin = _map + (_map_size >> 2);
		_M_end = _M_begin;
		_begin = iterator(this, _M_begin);
		_end = _begin;
		_size = 0;
	}

	template<typename T, size_t CHUNK_CAPACITY>
	inline void Deque<T, CHUNK_CAPACITY>::_expand_if_full(size_t newdata, DirectionToExpand direction)
	{
		//无需重置所有迭代器, 因为只有指针数组map改变, 数据所在chunk没有变

	}

}
#endif	// DEQUE_H
