#include <iostream>
#include <stack> 
#include <cctype>
#include <cstring>

using namespace std;

void calculate(stack<int>& numbers, stack<char>& operations) {
	//precondition :numbers is not negative integer
	//postcondition : result is an integer
	int number1, number2;
	number2 = numbers.top();
	numbers.pop();
	number1 = numbers.top();
	numbers.pop();

	cout << "number : " << number1 << " ,"<< number2 << endl;

	switch (operations.top()) {
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
	case '^':
		for (int i = 0; i < number2; i++)
			number1 *= number1;
		numbers.push(number1); break;
	case '%':
		if (number1 == 0 || number2 == 0) {
			printf("Error!\n");
		}
		else
			numbers.push(number1 & number2); break;
	}
	operations.pop();

	cout << numbers.top() << endl;
}

double read_stack(istream& ins) {
	stack<int> numbers;
	stack<char> operations;
	int number;
	char symbol;

	while (ins && ins.peek() != '\n') {
		//���� ���ڰ� ���ö� ���� ����
		if (isdigit(ins.peek())) {
			ins >> number;
			numbers.push(number);
		}
		else if (strchr("+-*/%^", ins.peek()) != NULL) {
			ins >> symbol;
			operations.push(symbol);
		}
		else if (ins.peek() == ')') {
			ins.ignore();
			calculate(numbers, operations);
		}
		else
			ins.ignore();
	}
	
	cout << numbers.top();
	
	return numbers.top();
}

int main() {
	
	read_stack(cin);
}

//empty ����ִ��� Ȯ��, size ������ ��ȯ, top �����ִ� ���� Ȯ��, push ������ ����, pop top�� ������ ����

//Only non-negative integers can be input as operands
//number stack , operations stack


//Only 6 binary operators can be used as operators : ^, *, /, %, +, - (+,- < */% < ^)


//result is always an integer and it can be a negative integer


//When exceptions such as unbalanced parenthesis, "/0" "%0" occur, print "Error!\n" and process next input lines.