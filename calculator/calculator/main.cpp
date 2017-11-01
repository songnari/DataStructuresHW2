#include <iostream>
#include <stack> 
using namespace std;
double read_stack(istream& ins) {
	stack<int> numbers;
	stack<char> operations;
	double number;
	char symbol;

	while (ins &&ins.peek() != '\n') {
		//개행 문자가 나올때 까지 읽음
	}
}

void calcualate(stack<int>numbers, stack<char> operations) {
	//precondition :numbers is not negative integer
	//postcondition : result is an integer
	int operand1, operand2;
	operand2 = numbers.top();
	numbers.pop();
	operand1 = numbers.top();
	numbers.pop();
	
	switch (operations.top()) {
		//연산자 확인
	case '+':numbers.push(operand1 + operand2); break;
	case '-':numbers.push(operand1 - operand2); break;
	case '*':numbers.push(operand1 * operand2); break;
	case '/':
		if (operand1 == 0 || operand2 == 0) {
			printf("Error!\n");
		}
		else
			numbers.push(operand1 / operand2); break;
	case '^' :
		for (int i = 0; i < operand2; i++)
			operand1 *= operand1;
		numbers.push(operand1); break;
	case '%':
		if (operand1 == 0 || operand2 == 0) {
			printf("Error!\n");
		}
		else
			numbers.push(operand1 & operand2); break;
	}
	operations.pop();
}

//empty 비어있는지 확인, size 사이즈 반환, top 위에있는 인자 확인, push 데이터 삽입, pop top의 데이터 삭제

//Only non-negative integers can be input as operands
//number stack , operations stack


//Only 6 binary operators can be used as operators : ^, *, /, %, +, - (+,- < */% < ^)


//result is always an integer and it can be a negative integer


//When exceptions such as unbalanced parenthesis, "/0" "%0" occur, print "Error!\n" and process next input lines.