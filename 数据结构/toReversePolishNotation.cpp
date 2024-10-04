#include "toReversePolishNotation.h"
#include "FixedLengthContainers.h"
#include <string>

namespace Mikami
{
	std::string toReversePolishNotation(const std::string& input)
	{//��׺���ʽת��Ϊ��׺���ʽ
		//����ջ������˳�� �ϸ񵥵�����(������) �� ��������(�ҽ����)
		//������ջ���Ż��ƻ����Ϲ���,�򵯳�ջ��Ԫ��ֱ���÷��Ž�ջ����Ȼ���Ϲ���
		//answer: 2 3 7 4 - * + 8 4 / +
		//std::string in = "2+3*(7-4)+8/4";
		//std::string in = "2";
	
		enum SymbleType { number, ope, openparenthesis, closeparenthesis, dot, symbleerror };
		enum OperatorPrecedence { higher = 10, lower, equal };
	
		auto readx = [](char x)->SymbleType {
			if (x >= '0' && x <= '9') return number;	//������
			else if (x == '.') return dot;				//��С����
			else if (x == '+' || x == '-' || x == '*' || x == '/') return ope;	//�������
			else if (x == '(') return openparenthesis;	//��������
			else if (x == ')') return closeparenthesis;	//��������
			else return symbleerror;
			};
		auto order = [](char s1, char s2)-> OperatorPrecedence {
			if (s2 == '(')
				return higher;	//��Ϊ'('���ȼ���� in order to ��������Ŷ��ܷ���'('��
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
				//�ҽ����(������)
				if (it == input.begin()) {
					if (*it == '-') result += *it;
					break;
				}
				else if (readx(*(it - 1)) != number && readx(*(it - 1)) != closeparenthesis) {
					if (*it == '-') result += *it;
					break;
				}
	
				//������(�Ӽ��˳�)
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
				ops.pop();	//����������
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
		result.pop_back();	//����ĩβ�ո�
		return result;
	}
}
