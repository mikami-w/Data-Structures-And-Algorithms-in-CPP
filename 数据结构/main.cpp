/*
�����뷨:��vector������dequeָ���б�,��dequeʵ��stack��queue
vector:ʹ�þ�̬����,���ڴ治��������,����ȫ�����ݵ����������ɾ��ԭ����
deque:��ָ���б�����������ڴ�,ʵ�ּ������ռ������ȡ
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