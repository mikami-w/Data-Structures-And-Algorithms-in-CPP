/*
初步想法:用vector来管理deque指针列表,用deque实现stack和queue
vector:使用静态数组,若内存不足则扩容,复制全部数据到扩容数组后删除原数组
deque:用指针列表管理多段连续内存,实现假连续空间随机存取
*/

#include <iostream>
#include "app.h"

int main()
{
	TestVector();
	std::cout << std::endl;

	TestFixedLengthStackAndQueue();
	std::cout << std::endl;

	TestPolishNotationSolution();
	std::cout << std::endl;

	return 0;
}