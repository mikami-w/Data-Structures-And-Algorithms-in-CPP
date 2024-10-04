#include "FixedLengthContainers.h"
#include <sstream>
#include <string>
#include <cmath>

namespace Mikami
{
	double solvePolishNotation(const std::string& input)
	{//��ǰ׺���ʽ��ֵ
		std::stringstream iss(input);	//��������

		struct Obj {
			double num;
			char oper;
			enum Type {
				number, operation
			}type;
		}buf{};	//�����뻺��

		auto readobj = [&]()->bool {
			if (iss >> buf.num) {
				if (iss.rdstate() == std::ios_base::eofbit) return 0;

				buf.type = Obj::number;
			}
			else {
				if (iss.rdstate() == std::ios_base::eofbit) return 0;
				iss.clear();	//�����ȡ����ʧ�ܵ�state
				iss.unget();
				iss.clear();	//������ܵ�ungetʧ�ܵ�state(���ַ�Ϊ�˳�)
				iss >> buf.oper;
				buf.type = Obj::operation;
			}
			return 1;
			};
		auto caculate = [](char oper, double lv, double rv)->double {
			switch (oper)
			{
			case '+':return lv + rv;
			case '-':return lv - rv;
			case '*':return lv * rv;
			case '/': {
				if (rv == 0)
					throw "division by zero.";
				return lv / rv;
			}

			default:
				throw "Unsupported operator.";
				return nan("");
			}
			};

		FLStack<Obj, 40> ins;		//input stack
		FLStack<double, 40> nums;	//number stack

		while (readobj())
			ins.push(buf);
		ins.push(buf);

		double lv, rv;	//ѭ���е�������
		while (!ins.empty()) {
			if (ins.top().type == Obj::number)
				nums.push(ins.pop().num);
			else if (ins.top().type == Obj::operation) {
				try {
					//ǰ׺���ʽ���������ȡʱ�ȼ������Ҳ������෴�ĺ�׺���ʽ
					lv = nums.pop();
					rv = nums.pop();
					nums.push(caculate(ins.pop().oper, lv, rv));
				}
				catch (...) {	//0��������underflow(���ʽ����)
					return nan("");
				}
			}
		}

		double result = nums.pop();
		if (!nums.empty())	//��ʣ�಻ֹһ����,����ʽ����
			return nan("");
		else
			return result;

	}

}