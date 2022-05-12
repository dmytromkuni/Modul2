#include "task3.h"

#include <iostream>

template<class T>
task3::Stack<T>::Node::Node(T value)
{
	this->value = value;
}

template<class T>
void task3::Stack<T>::printStack()
{
	Node* iter1 = head;
	while (iter1 != nullptr)
	{
		std::cout << iter1->value << " ";
		iter1 = iter1->next;
	}
	std::cout << "\n\n";
}

template<class T>
T task3::Stack<T>::top()
{
	return this->tail->value;
}

template<class T>
void task3::Stack<T>::pop()
{
	Node* iter1 = tail;

	if (iter1 != nullptr)
	{
		if (iter1->prev != nullptr)
		{
			tail->prev->next = nullptr;
			Node* temp = tail;
			tail = tail->prev;
			delete(temp);
			temp = NULL;
		}

		else
		{
			Node* temp = tail;
			tail = nullptr;
			head = nullptr;
			delete(temp);
			temp = NULL;
		}

		return;
	}


	else
	{
		std::cout << "NO MORE ELEMENTS IN THE STACK";
		return 0;
	}
}

template<class T>
bool task3::Stack<T>::empty()
{
	if (this->head != nullptr) false;
	else return true;
}

template<class T>
void task3::Stack<T>::push(T value)
{
	Node* node = new Node(value);
	if (head == nullptr)
	{
		head = node;
		tail = node;
	}
	else
	{
		node->prev = tail;
		tail->next = node;
		tail = node;
	}
}

void task3::ExpressionTree::print(Node* iter)
{
	if (iter == nullptr) return;
	else
	{
		std::cout << iter->val << " ";
		print(iter->l_child);
		print(iter->r_child);
	}
}

int task3::precedence(char input)
{
	if (input == '&')
		return 3;
	else if (input == '|')
		return 2;
	else if (input == '-')
		return 2;
	else
		return -1;
}

void task3::ExpressionTree::print(Node* iter)
{
	if (iter == nullptr) return;
	else
	{
		std::cout << iter->val << " ";
		print(iter->l_child);
		print(iter->r_child);
	}
}

void task3::ExpressionTree::del(Node* iter)
{
	if (iter == nullptr) return;

	del(iter->l_child);
	del(iter->r_child);

	delete iter;
}

void task3::infix_to_postfix(char* input, char* result)
{
	task3::Stack<char> stack;
	int count = 0;

	for (int i = 0; i < strlen(input); i++)
	{
		char cur = input[i];

		if (task3::is_num_var(cur))
		{
			result[count] = cur;
			count++;
		}

		else if (cur == '(')
			stack.push(cur);

		else if (cur == ')')
		{
			while (stack.top() != '(')
			{
				result[count] = stack.top();
				count++;
				stack.pop();
			}
			stack.pop();
		}

		else if (cur == '-'
			&& (task3::is_num_var(input[i + 1]) || i == 0))
			stack.push('-');

		else
		{
			if (cur == ' ')
				continue;
			while (!stack.empty()
				&& (task3::precedence(cur) <= task3::precedence(stack.top())))
			{
				result[count] = stack.top();
				count++;
				stack.pop();				
			}
			stack.push(cur);
		}
	}

	while (!stack.empty()) {
		result[count] = stack.top();
		count++;
		stack.pop();
	}
	return;
}

bool task3::is_num_var(char input)
{
	if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')
		|| (input >= '0' && input <= '9'))
		return true;
	else
		return false;
}

void task3::ExpressionTree::build(char* input)
{
	task3::ExpressionTree::Node* x, * y, * z;
	task3::Stack<ExpressionTree::Node*> stack;


	int l = strlen(input);
	for (int i = 0; i < l; i++)
	{
		if (input[i] == '+' || input[i] == '-' || input[i] == '*'
			|| input[i] == '/' || input[i] == '^'
			|| input[i] == '%')
		{
			z = new task3::ExpressionTree::Node(input[i]);
			x = stack.top();
			stack.pop();
			y = stack.top();
			stack.pop();
			z->l_child = y;
			z->r_child = x;
			stack.push(z);
			this->head = z;
		}
		else if (input[i] == '#')
		{
			z = new task3::ExpressionTree::Node(input[i]);
			x = stack.top();
			stack.pop();
			z->l_child = x;
			stack.push(z);
			this->head = z;
		}
		else
		{
			z = new task3::ExpressionTree::Node(input[i]);
			stack.push(z);
		}
	}
}