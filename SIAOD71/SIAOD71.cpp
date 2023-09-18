#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 100;

bool isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int getPriority(char c) {
	if (c == '+' || c == '-') {
		return 1;
	}
	else if (c == '*' || c == '/') {
		return 2;
	}
	else {
		return 0;
	}
}

string infixToPrefix(string expression) {
	reverse(expression.begin(), expression.end());

	for (int i = 0; i < expression.length(); i++) {
		if (expression[i] == '(') {
			expression[i] = ')';
		}
		else if (expression[i] == ')') {
			expression[i] = '(';
		}
	}

	string prefix = "";
	string temp = "";

	for (int i = 0; i < expression.length(); i++) {
		// Если символ является операндом, добавьте его в префиксную нотацию
		if (!isOperator(expression[i]) && expression[i] != '(' && expression[i] != ')') {
			prefix += expression[i];
		}
		// Если символ является оператором, добавьте его во временную строку
		else if (isOperator(expression[i])) {
			while (!temp.empty() && getPriority(temp[0]) >= getPriority(expression[i])) {
				prefix += temp[0];
				temp.erase(temp.begin());
			}
			temp = expression[i] + temp;
		}
		// Если символ является открывающей скобкой, добавьте ее во временную строку
		else if (expression[i] == '(') {
			temp = expression[i] + temp;
		}
		// Если символ является закрывающей скобкой, выньте все операторы из временной строки и добавьте их в префиксную нотацию
		else if (expression[i] == ')') {
			while (temp[0] != '(') {
				prefix += temp[0];
				temp.erase(temp.begin());
			}
			temp.erase(temp.begin());
		}
	}

	while (!temp.empty()) {
		prefix += temp[0];
		temp.erase(temp.begin());
	}

	reverse(prefix.begin(), prefix.end());

	return prefix;
}

class QueueArray {
private:
	int arr[MAX_SIZE];
	int front, rear;

public:
	QueueArray() {
		front = -1;
		rear = -1;
	}

	bool isEmpty()
	{
		return (front == -1 && rear == -1);
	}

	bool isFull()
	{
		return (rear + 1) % MAX_SIZE == front ? true : false;
	}

	void enqueue(int x)
	{
		if (isFull()) {
			cout << "Queue is full\n";
			return;
		}

		if (isEmpty()) {
			front = rear = 0;
		}
		else {
			rear = (rear + 1) % MAX_SIZE;
		}

		arr[rear] = x;
	}

	void dequeue() {
		if (isEmpty()) {
			cout << "Queue is empty\n";
			return;
		}
		else if (front == rear) {
			front = rear = -1;
		}
		else {
			front = (front + 1) % MAX_SIZE;
		}
	}

	int peek() {
		if (isEmpty()) {
			cout << "Queue is empty\n";
			return -1;
		}

		return arr[front];
	}

	void makeEmpty() {
		front = rear = -1;
	}
};

class Node {
public:
	int data;
	Node* next;
};

class QueueNode {
private:
	Node* front;
	Node* rear;
public:
	QueueNode() {
		front = NULL;
		rear = NULL;
	}

	bool isEmpty() {
		return front == NULL && rear == NULL;
	}

	void enqueue(int x) {
		Node* temp = new Node();
		temp->data = x;
		temp->next = NULL;

		if (isEmpty()) {
			front = rear = temp;
			return;
		}

		rear->next = temp;
		rear = temp;
	}

	void dequeue()
	{
		if (isEmpty()) {
			cout << "Queue is empty\n";
			return;
		}

		if (front == rear) {
			front = rear = NULL;
		}
		else {
			Node* temp = front;
			front = front->next;
			delete temp;
		}
	}

	int peek()
	{
		if (isEmpty()) {
			cout << "Queue is empty\n";
			return -1;
		}

		return front->data;
	}

	void makeEmpty()
	{
		while (!isEmpty()) {
			dequeue();
		}
	}
};

int main() {

	setlocale(LC_ALL, "ru-RU");
	cout << "Практическая работа №7. \"Однонаправленный динамический список\". ИКБО-07-22. Шилов Павел" << endl;

	int userInput;

	cout << "Выберите задание:\n";
	cout << "1 - Демонстрация работы очереди на массивах\n";
	cout << "2 - Демонстрация работы очереди на списках\n";
	cout << "3 - Функция преобразования инфиксного выражения\n";
	cout << "0 - выход\n";

	cin >> userInput;

	while (userInput != 0)
	{

		if (userInput == 1)
		{
			QueueArray queueArray;
			cout << "В очередь добавили 10" << endl;
			queueArray.enqueue(10);
			cout << "В очередь добавили 20" << endl;
			queueArray.enqueue(20);
			cout << "В очередь добавили 30" << endl;
			queueArray.enqueue(30);
			cout << "В очередь добавили 40" << endl;
			queueArray.enqueue(40);

			cout << "Верхний элемент: " << queueArray.peek() << "\n";

			cout << "Из очереди убрали верхний элемент" << endl;
			queueArray.dequeue();
			cout << "Из очереди убрали верхний элемент" << endl;
			queueArray.dequeue();

			cout << "Верхний элемент после \"dequeue\": " << queueArray.peek() << "\n";

			queueArray.makeEmpty();

			if (queueArray.isEmpty())
			{
				cout << "Очеред пуста.\n";
			}
			else
			{
				cout << "Очередь не пуста.\n";
			}
		}

		if (userInput == 2)
		{
			QueueNode queueNode;
			cout << "В очередь добавили 10" << endl;
			queueNode.enqueue(10);
			cout << "В очередь добавили 20" << endl;
			queueNode.enqueue(20);
			cout << "В очередь добавили 30" << endl;
			queueNode.enqueue(30);
			cout << "В очередь добавили 40" << endl;
			queueNode.enqueue(40);

			cout << "Верхний элемент: " << queueNode.peek() << "\n";

			cout << "Из очереди убрали верхний элемент" << endl;
			queueNode.dequeue();
			cout << "Из очереди убрали верхний элемент" << endl;
			queueNode.dequeue();

			cout << "Верхний элемент после двух \"dequeue\": " << queueNode.peek() << "\n";

			cout << "Очистили очередь." << endl;
			queueNode.makeEmpty();

			if (queueNode.isEmpty()) {
				cout << "Очеред пуста.\n";
			}
			else
			{
				cout << "Очередь не пуста.\n";
			}
		}

		if (userInput == 3)
		{
			string infix;
			cin >> infix;
			string prefix = infixToPrefix(infix); //a+b-c*k/(d*e-f)
			cout << "Получившийся префикс: " << prefix;
		}

		if (userInput == 0)
			break;

		cin >> userInput;

		system("CLS");
		cout << "Выберите задание:\n";
		cout << "1 - Демонстрация работы очереди на массивах\n";
		cout << "2 - Демонстрация работы очереди на списках\n";
		cout << "3 - Функция преобразования инфиксного выражения\n";
		cout << "0 - выход\n";
	}

	return 0;
}