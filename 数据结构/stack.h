#ifndef STACK_H
#define STACK_H

#include "IContainers.h"
#include"List.h"

namespace Mikami
{
	template<typename T>
	class IStack :public virtual IContainers
	{
	public:
		virtual int size() = 0;
		virtual T pop() = 0;
		virtual void push(const T&) = 0;
		virtual T top() = 0;
		virtual bool empty() = 0;
	};
}


#endif