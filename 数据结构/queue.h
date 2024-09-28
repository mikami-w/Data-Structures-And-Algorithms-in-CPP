#ifndef QUEUE_H
#define QUEUE_H

#include "IContainers.h"

namespace Mikami
{

	template<typename T>
	class Queue :public virtual IContainers
	{
	public:


	protected:
		T* front;	//队头,出元素
		T* rear;	//队尾,进元素


	};


}

#endif
