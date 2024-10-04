#include "toReversePolishNotation.h"
#include "FixedLengthContainers.h"
#include <string>

namespace Mikami
{
	std::string toReversePolishNotation(const std::string& input)
	{//中缀表达式转换为后缀表达式
		//符号栈按运算顺序 严格单调递增(左结合性) 或 单调递增(右结合性)
		//若待进栈符号会破坏以上规则,则弹出栈中元素直到该符号进栈后仍然符合规则
		//answer: 2 3 7 4 - * + 8 4 / +
		//std::string in = "2+3*(7-4)+8/4";
		//std::string in = "2";
	
		enum SymbleType { number, ope, openparenthesis, closeparenthesis, dot, symbleerror };
		enum OperatorPrecedence { higher = 10, lower, equal };
	
		auto readx = [](char x)->SymbleType {
			if (x >= '0' && x <= '9') return number;	//是数字
			else if (x == '.') return dot;				//是小数点
			else if (x == '+' || x == '-' || x == '*' || x == '/') return ope;	//是运算符
			else if (x == '(') return openparenthesis;	//是左括号
			else if (x == ')') return closeparenthesis;	//是右括号
			else return symbleerror;
			};
		auto order = [](char s1, char s2)-> OperatorPrecedence {
			if (s2 == '(')
				return higher;	//认为'('优先级最低 in order to 让任意符号都能放在'('上
			if (s1 == '+' || s1 == '-') {
				if (s2 == '+' || s2 == '-') return equal;
				else return lower;
			}
			else {
				if (s2 == '+' || s2 == '-') return higher;
				else return equal;
			}
			};
	
	
		using S = FLStack<char, 20>;
		S ops;	//operator stack
	
		std::string result = "";
	
	
		for (auto it = input.begin(); it < input.end(); ++it) {
			switch (readx(*it))
			{
			case number:
			{
				do {
					result += *(it++);
				} while (it != input.end() ? (readx(*it) == number || readx(*it) == dot) : 0);
				result += ' ';
				--it;
				break;
			}
			//case dot:
			//{
			//	result.pop_back();
			//	result += *it;
			//}
			case ope:
			{
				//右结合性(正负号)
				if (it == input.begin()) {
					if (*it == '-') result += *it;
					break;
				}
				else if (readx(*(it - 1)) != number && readx(*(it - 1)) != closeparenthesis) {
					if (*it == '-') result += *it;
					break;
				}
	
				//左结合性(加减乘除)
				if (ops.empty())
					ops.push(*it);
				else {
					switch (order(*it, ops.top()))
					{
					case higher:
					{
						ops.push(*it);
						break;
					}
					case lower:
					case equal:
					{
						while (!ops.empty()) {
							if (order(*it, ops.top()) != higher) {
								result += ops.pop();
								result += ' ';
							}
							else break;
						}
						ops.push(*it);
						break;
					}
					}
				}
				break;
			}
			case openparenthesis:
			{
				ops.push(*it);
				break;
			}
			case closeparenthesis:
			{
				while (readx(ops.top()) != openparenthesis) {
					result += ops.pop();
					result += ' ';
				}
				ops.pop();	//弹出左括号
				break;
			}
			case dot:
			default:
				throw "error!";
			}
		}
		while (!ops.empty()) {
			result += ops.pop();
			result += ' ';
		}
		result.pop_back();	//弹出末尾空格
		return result;
	}
}
