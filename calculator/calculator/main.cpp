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

	if (numbers.empty() != 1) {
		number2 = numbers.top();
		numbers.pop();
		number1 = numbers.top();
		numbers.pop();
		symbol = operations.top();
		operations.pop();

		std::cout << "cal : " << number1 << symbol << number2 << endl;

		switch (symbol) {
			//연산자 확인
		case '+':numbers.push(number1 + number2); break;
		case '-':numbers.push(number1 - number2); break;
		case '*':numbers.push(number1 * number2); break;
		case '/':
			if (number1 == 0 || number2 == 0) {
				printf("Error!\n");
				while (numbers.empty() != 1)
					numbers.pop();
				while (operations.empty() != 1)
					operations.pop();
				operations.push('E');
				break;
			}
			else
				numbers.push(number1 / number2); break;
		case '^':numbers.push(pow(number1, number2)); break;
		case '%':
			if (number1 == 0 || number2 == 0) {
				printf("Error!\n");
				while (numbers.empty() != 1)
					numbers.pop();
				while (operations.empty() != 1)
					operations.pop();
				operations.push('E');
				break;
			}
			else
				numbers.push(number1 % number2); break;
		}

		if (numbers.empty() != 1) {
			if (operations.empty() != 1 && operations.top() == 'E')
				cout << "EEEEE" << endl;
			cout << "result : " << numbers.top() << endl;
		}
	}
}

double read_stack(istream& ins) {
	stack<int> numbers;
	stack<char> operations;
	int number;
	char symbol;

	while (1) {
		if (ins.peek() == '0') {
			cout << "end" << endl;
			return 0;
		}

		while (ins && ins.peek() != '\n') {
			//개행 문자가 나올때 까지 읽음
			if (operations.empty() != 1 && operations.top() == 'E')
				break;
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
				else if (operations.empty() == 1 || operations.top() == '(') { //stack이 비어있을 때
					operations.push(symbol);
				}

				else {
					if (symbol == '^') {
						if (operations.top() == '^') {
							calculate(numbers, operations);
						}
						if (operations.empty() != 1 && operations.top() == 'E')
							break;
						else
							operations.push(symbol);
					}
					else if (symbol == '*' || symbol == '/' || symbol == '%') {
						if (operations.top() == '^') {
							calculate(numbers, operations);
						}
						if (operations.empty() != 1 && operations.top() == 'E')
							break;
						else
							operations.push(symbol);
					}
					else {
						calculate(numbers, operations);
						if (operations.empty() != 1 && operations.top() == 'E')
							break;
						else
							operations.push(symbol);
					}
				}
			}
			else if (ins.peek() == ')') {
				ins.ignore();
				while (operations.top() != '(') {
					calculate(numbers, operations);
					if (operations.empty() != 1 && operations.top() == 'E')
						break;
				}
				if (operations.top() == '(')
					operations.pop();

			}
			else
				ins.ignore();
		}
		if (ins.peek() == '\n')
			ins.ignore();
		//입력된 내용 모두 stack 저장 완료


		while (operations.empty() != 1) {
			if (operations.top() == 'E')
				break;
			calculate(numbers, operations);
		}

		if (operations.empty() != 1 && operations.top() == 'E')
			operations.pop();
	}
	if (numbers.empty() == 1)
		return 0;
	else
		return 1;

}

int main() {

	read_stack(cin);
}

//Only non-negative integers can be input as operands
//number stack , operations stack

//result is always an integer and it can be a negative integer

//When exceptions such as unbalanced parenthesis, "/0" "%0" occur, print "Error!\n" and process next input lines.