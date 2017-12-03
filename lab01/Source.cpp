#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <conio.h>
using namespace std;

struct NODE
{
	float num;
	NODE *next;
};

class stack
{
private:
	NODE *head;

public:
	stack();
	void push(float);
	float pop();
	int nElements();
	float display();
};

class RPN : public stack
{
public:
	void add();
	void subtract();
	void multiply();
	void divide();
};


stack::stack()
{
	head = NULL;
}

void stack::push(float a_number)
{
	NODE *temp = new NODE;
	if (temp)
	{
		temp->num = a_number;
		temp->next = head;
		head = temp;
	}
}

float stack::pop()
{
	float number = 0;


	if (!head)
	{
		return 0;
	}
	else
	{
		NODE *temp = head;
		number = head->num;
		head = temp->next;
		delete temp;
	}
	return number;
}

int stack::nElements()
{
	int counter = 0;
	for (NODE *node = head; node; node = node->next)
	{
		counter++;
	}
	return counter;
}

float stack::display()
{


	if (nElements() != 1)
	{
		cout << "Error: too many operands" << endl;
		return 1;
	}
	
	else //(nElements() > 0)
	{
		float temp = pop();
		cout << temp << endl;
		push(temp);

		return temp;

	}
	
}


void RPN::add()
{
	if (nElements() >= 2)
	{
		push(pop() + pop());
	}
}

void RPN::subtract()
{
	if (nElements() >= 2)
	{
		push(0 - pop() + pop());
	}
}

void RPN::multiply()
{
	if (nElements() >= 2)
	{
		push(pop() * pop());
	}
}

void RPN::divide()
{
	if (nElements() >= 2)
	{
		push(1 / pop() * pop());
	}



}

//Прототип функції для isOperator
bool isOperator(const string& input);

//Прототип функції для perforOperation
int performOperation(const string& input, RPN& calculator);

int main() 
{

	RPN calculator;
	string input;

	float num;

	cout << "Reverse Polish Notation Calculator: " << endl;
	cout << "Input expression:\n";


	while (input != "0")
	{
	
			// отримати дані
			cin >> input;

			// перевірити дані (чи це числа)

			if (istringstream(input) >> num)
			{
				//функція push
				calculator.push(num);
			}

			// перевірити дані (чи це оператори)
			else if (isOperator(input))
			{
				performOperation(input, calculator);
			}
			
		}
	_getch(); 
	return 0;
}

bool isOperator(const string& input)
{
	static const string operators = "-+*/";
	if (input.length() == 1) // належний розмір, щоб бути оператором
	{
		return operators.find_first_of(input[0]) != string::npos;
		
	}
	return false;
}



int performOperation(const string& input, RPN& calculator)
{
	
	switch (input[0])
	{
	case '+': calculator.add();
		calculator.display();
		break;
	case '-': calculator.subtract();
		calculator.display();
		break;
	case '*': calculator.multiply();
		calculator.display();
		break;
	case '/':  calculator.divide();
		calculator.display();
		break;
	}
	return 0;
}