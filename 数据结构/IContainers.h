#ifndef ICONTAINERS_H
#define ICONTAINERS_H

namespace Mikami
{
	class IContainers
	{
	public:
		virtual ~IContainers() = default;
		virtual size_t capacity() = 0;
		virtual size_t size() = 0;
		virtual void clear() = 0;
		virtual bool empty() = 0;
		virtual void swap(IContainers& obj) = 0;
	};
}

#endif // !ICONTAINERS_H
