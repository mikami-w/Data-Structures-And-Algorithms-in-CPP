#ifndef FIXEDLENGTHCONTAINERS_H
#define FIXEDLENGTHCONTAINERS_H
#include <exception>

namespace Mikami
{
	template<typename T, int CAPACITY>
	class FLStack
	{
	public:
		FLStack() :_bottom(new T[CAPACITY]), _top(_bottom) {}
		~FLStack() { delete[] _bottom; }
		bool empty() { return _top == _bottom; }
		bool full() { return _top - _bottom >= CAPACITY; }
	
		void push(const T& obj) {
			if (!full()) *(_top++) = obj;
			else throw std::overflow_error("Stack is full.Cannot do operation push.");
		}
		T pop() {
			if (!empty()) return *(--_top);
			else throw std::underflow_error("Stack is empty.Cannot do operation pop.");
		}
		T top() { return *(_top - 1); }
	
	private:
		T* _bottom;
		T* _top;
	};
	
	template<typename T, int CAPACITY>
	class FLQueue
	{
	public:
		FLQueue() :_data(new T[CAPACITY]), _front(0), _rear(0) {}
		~FLQueue() { delete[] _data; }
		bool empty() { return _front == _rear; }
		bool full() { return (_rear - _front + CAPACITY) % CAPACITY >= CAPACITY - 1; } //为与空队列区分,实际容量为CAPACITY-1
	
		void in_queue(const T& obj) {
			if (!full()) {
				_data[_rear] = obj;
				_rear = (_rear + 1) % CAPACITY;
			}
			else throw std::overflow_error("Queue is full.Cannot do operation Inqueue.");
		}
		T de_queue() {
			if (!empty()) {
				T temp = _data[_front];
				_front = (_front + 1) % CAPACITY;
				return temp;
			}
			else throw std::underflow_error("Queue is empty.Cannot do operation Dequeue.");
		}
		T front() { return _data[_front]; }
		T* data() { return _data; }
	private:
		T* _data;
		int _front;
		int _rear;
	};
}


#endif
