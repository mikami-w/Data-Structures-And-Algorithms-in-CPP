#include "FixedLengthContainers.h"
#include <sstream>
#include <string>
#include <cmath>

namespace Mikami
{
	double solvePolishNotation(const std::string& input)
	{//求前缀表达式的值
		std::stringstream iss(input);	//做输入流

		struct Obj {
			double num;
			char oper;
			enum Type {
				number, operation
			}type;
		}buf{};	//做输入缓冲

		auto readobj = [&]()->bool {
			if (iss >> buf.num) {
				if (iss.rdstate() == std::ios_base::eofbit) return 0;

				buf.type = Obj::number;
			}
			else {
				if (iss.rdstate() == std::ios_base::eofbit) return 0;
				iss.clear();	//清除读取数字失败的state
				iss.unget();
				iss.clear();	//清除可能的unget失败的state(当字符为乘除)
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

		double lv, rv;	//循环中的运算数
		while (!ins.empty()) {
			if (ins.top().type == Obj::number)
				nums.push(ins.pop().num);
			else if (ins.top().type == Obj::operation) {
				try {
					//前缀表达式从右向左读取时等价于左右操作数相反的后缀表达式
					lv = nums.pop();
					rv = nums.pop();
					nums.push(caculate(ins.pop().oper, lv, rv));
				}
				catch (...) {	//0作除数或underflow(表达式有误)
					return nan("");
				}
			}
		}

		double result = nums.pop();
		if (!nums.empty())	//若剩余不止一个数,则表达式有误
			return nan("");
		else
			return result;

	}

}