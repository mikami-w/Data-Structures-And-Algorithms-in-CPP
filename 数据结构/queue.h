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
		T* front;	//��ͷ,��Ԫ��
		T* rear;	//��β,��Ԫ��


	};


}

#endif
