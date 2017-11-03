#include <iostream>
#include <stack> 
#include <cctype>
#include <cstring>
#include <cmath>

using namespace std;

void calculate(stack<int>& numbers, stack<char>& operations) {
	//precondition :numbers is not negative integer
	//postcondition : result is an integer
	int number1, number2;
	char symbol;
	number2 = numbers.top();
	numbers.pop();
	number1 = numbers.top();
	numbers.pop();
	symbol = operations.top();
	operations.pop();

	std::cout << "cal : " << number1 << symbol << number2 << endl;

	switch (symbol){
		//������ Ȯ��
	case '+':numbers.push(number1 + number2); break;
	case '-':numbers.push(number1 - number2); break;
	case '*':numbers.push(number1 * number2); break;
	case '/':
		if (number1 == 0 || number2 == 0) {
			printf("Error!\n");
		}
		else
			numbers.push(number1 / number2); break;
	case '^':numbers.push(pow(number1,number2)); break;
	case '%':
		if (number1 == 0 || number2 == 0) {
			printf("Error!\n");
		}
		else
			numbers.push(number1 % number2); break;
	}
	cout << "result : " << numbers.top() << endl;
}

double read_stack(istream& ins) {
	stack<int> numbers;
	stack<char> operations;
	int number;
	char symbol;

	if (ins.peek() == '0') {
		cout << "end" << endl;
		return 0;
	}

	while (ins && ins.peek() != '\n') {
		//���� ���ڰ� ���ö� ���� ����
		
		if (isdigit(ins.peek())) {
			ins >> number;
			std::cout << "number : " << number << endl;
			numbers.push(number);
		}
		else if (strchr("+-*/%^(", ins.peek()) != NULL) {
			ins >> symbol;
			std::cout << "operator : " << symbol << endl;
			if (symbol == '(')
				operations.push(symbol);
			else if(operations.empty() == 1 || operations.top() == '(') { //stack�� ������� ��
				operations.push(symbol);
			}
			else {
				if (symbol == '^') {
					if (operations.top() == '^') {
						calculate(numbers, operations);
					}
					operations.push(symbol);
				}
				else if (symbol == '*' || symbol == '/' || symbol == '%') {
					if (operations.top() == '^') {
						calculate(numbers, operations);
					}
					operations.push(symbol);
				}
				else {
					calculate(numbers, operations);
					operations.push(symbol);
				}
			}
		}
		else if (ins.peek() == ')') {
			ins.ignore();
			while (operations.top() != '(') {
				calculate(numbers, operations);
			}
			if (operations.top() == '(')
				operations.pop();

		}
		else
			ins.ignore();
	}
	//�Էµ� ���� ��� stack ���� �Ϸ�

	while (operations.empty() != 1) {
		calculate(numbers, operations);
	}

	//calculate(numbers, operations);

	std::cout << numbers.top();
	
	return numbers.top();
}

int main() {
	
	read_stack(cin);
}

//empty ����ִ��� Ȯ��, size ������ ��ȯ, top �����ִ� ���� Ȯ��, push ������ ����, pop top�� ������ ����

//Only non-negative integers can be input as operands
//number stack , operations stack

//result is always an integer and it can be a negative integer

//When exceptions such as unbalanced parenthesis, "/0" "%0" occur, print "Error!\n" and process next input lines.