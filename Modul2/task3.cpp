#include "task3.h"

#include <string>

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
	if (this->tail != nullptr) return this->tail->value;
	else return NULL;
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
		std::cout << "NO MORE ELEMENTS IN THE STACK\n\n";
		return;
	}
}

template<class T>
bool task3::Stack<T>::empty()
{
	if (this->head == nullptr) return true;
	else return false;
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

task3::ExpressionTree::Node::Node(char val)
{
	this->val = val;
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

void task3::ExpressionTree::printGraph(const std::string& prefix, const task3::ExpressionTree::Node* node, bool isLeft)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (isLeft ? "|-- " : "|-- ");

		// print the value of the node
		std::cout << node->val << std::endl;

		// enter the next tree level - left and right branch
		task3::ExpressionTree::printGraph(prefix + (isLeft ? "|   " : "    "), node->l_child, true);
		task3::ExpressionTree::printGraph(prefix + (isLeft ? "|   " : "    "), node->r_child, false);
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
			bool lol = stack.empty();
			int kek = task3::precedence(cur);
			char based = stack.top();
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
	task3::Stack<task3::ExpressionTree::Node*> stack;

	int l = strlen(input);
	for (int i = 0; i < l; i++)
	{
		if (input[i] == '&' || input[i] == '|')
		{
			task3::ExpressionTree::Node* z = new task3::ExpressionTree::Node(input[i]);
			task3::ExpressionTree::Node* x = stack.top();
			stack.pop();
			task3::ExpressionTree::Node* y = stack.top();
			stack.pop();
			z->l_child = y;
			z->r_child = x;
			stack.push(z);
			this->head = z;
		}
		else if (input[i] == '-')
		{
			task3::ExpressionTree::Node* z = new task3::ExpressionTree::Node(input[i]);
			task3::ExpressionTree::Node* x = stack.top();
			stack.pop();
			z->l_child = x;
			stack.push(z);
			this->head = z;
		}
		else
		{
			task3::ExpressionTree::Node* z = new task3::ExpressionTree::Node(input[i]);
			stack.push(z);
		}
	}
}

int task3::ExpressionTree::simplify(Node* iter)
{
	if (iter == nullptr) return -1;
	else if (iter->val == '0') return 0;
	else if (iter->val == '1') return 1;
	else if (is_num_var(iter->val) && !std::isdigit(iter->val)) return 2;
	else
	{
		int left = simplify(iter->l_child);
		int right = simplify(iter->r_child);

		if (iter->val == '&')
		{
			if (left == 0 || right == 0)
			{
				del(iter->l_child);
				del(iter->r_child);
				iter->l_child = nullptr;
				iter->r_child = nullptr;
				iter->val = '0';
				return 0;
			}

			else if (left == 1)
			{
				del(iter->l_child);

				Node* temp = iter->r_child;

				iter->val = iter->r_child->val;
				iter->l_child = iter->r_child->l_child;
				iter->r_child = iter->r_child->r_child;

				delete temp;

				return right;
			}

			else if (right == 1)
			{
				del(iter->r_child);

				Node* temp = iter->l_child;

				iter->val = iter->l_child->val;
				iter->r_child = iter->l_child->r_child;
				iter->l_child = iter->l_child->l_child;

				delete temp;

				return left;
			}
		}

		if (iter->val == '|')
		{
			if (left == 1 || right == 1)
			{
				del(iter->l_child);
				del(iter->r_child);
				iter->l_child = nullptr;
				iter->r_child = nullptr;
				iter->val = '1';
				return 1;
			}

			else if (left == 0)
			{
				del(iter->l_child);

				Node* temp = iter->r_child;

				iter->val = iter->r_child->val;
				iter->l_child = iter->r_child->l_child;
				iter->r_child = iter->r_child->r_child;

				delete temp;

				return right;
			}

			else if (right == 0)
			{
				del(iter->r_child);

				Node* temp = iter->l_child;

				iter->val = iter->l_child->val;
				iter->r_child = iter->l_child->r_child;
				iter->l_child = iter->l_child->l_child;

				delete temp;

				return left;
			}
		}

		if (iter->val = '-')
		{
			if (left == 1)
			{
				iter->val = '0';
				del(iter->l_child);
				iter->l_child = nullptr;
				return 0;
			}
			else if (left == 0)
			{
				iter->val = '1';
				del(iter->l_child);
				iter->l_child = nullptr;
				return 1;
			}
			else if (iter->l_child->val == '-')
			{
				Node* temp = iter->l_child;

				iter->r_child = iter->l_child->l_child->r_child;
				iter->l_child = iter->l_child->l_child->l_child;
				iter->val = temp->l_child->val;

				delete(temp->l_child);
				delete(temp);

				int res = simplify(iter);

				return res;

			}
		}

		return 100;
	}

}

void task3::ExpressionTree::print_var(Node* iter)
{
	if (iter == nullptr) return;
	else
	{
		if (is_num_var(iter->val) && !std::isdigit(iter->val))
			std::cout << iter->val << "\n";

		print(iter->l_child);
		print(iter->r_child);
	}
}

