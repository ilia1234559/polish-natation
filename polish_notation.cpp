#include <iostream>
#include <conio.h>
using namespace std;

struct Stack
{
	char info;
	int prior;
	Stack* next;
};


Stack* createStack(Stack* top, char inf)
{
	Stack* el = NULL;
	el = new Stack;
	el->next = top;
	el->info = inf;
	if (el->info == '+' || el->info == '-')
		el->prior = 1;
	else if (el->info == '*' || el->info == '/')
		el->prior = 2;
	else if (el->info == '(')
		el->prior = 0;
	return el;
}

Stack* show(Stack* top) {
	cout << top->info;
	top = top->next;
	return top;
}

int proverka(Stack* top, int priority)
{
	if (top->prior > priority || top->prior == priority)
		return 1;
	else if (top->prior < priority)
		return 2;
}

Stack* del_stack(Stack* top)
{
	if (top != NULL)
	{
		Stack* buf = top;
		top = buf->next;
		delete buf;
		return top;
	}
}



double result(char* str)
{
	Stack* top = NULL;
	Stack* buf = NULL;
	int i;
	char ss, ss1, ss2, ssR = 'z' + 1;
	double p1, p2, res, mas[50];
	/*for (i = 0; i < 50; i++)
	{
		mas[i] = 0;
	}*/
	cout << "Введите данные:" << endl;
	for (i = 0; str[i] != '\0'; ++i)
	{
		ss = str[i];
		if (ss >= 'a' && ss <= 'z')// && mas[int(ss - 'a')] == 0)
		{
			cout << ss << " = ";
			cin >> mas[int(ss - 'a')];
		}
	}
	for (i = 0; str[i] != '\0'; ++i)
	{
		ss = str[i];
		if (!(ss == '+' || ss == '-' || ss == '*' || ss == '/'))
			top = createStack(top, ss);
		else
		{
			ss2 = top->info;
			Stack* buf = top;
			top = top->next;
			delete buf;

			ss1 = top->info;
			buf = top;
			top = top->next;
			delete buf;

			p2 = mas[int(ss2 - 'a')];
			p1 = mas[int(ss1 - 'a')];
			switch (ss) {
			case '+': res = p1 + p2; break;
			case '-': res = p1 - p2; break;
			case '*': res = p1 * p2; break;
			case '/': res = p1 / p2; break;
			}
			mas[int(ssR - 'a')] = res;
			top = createStack(top, ssR);
			ssR++;
		}
	}
	return res;
}

int main()
{
	setlocale(LC_ALL, "ru");
	int prioritySK = 0, // (
		priorityPL = 1, // '+' 
		priorityDEL = 2; // '*'  
	Stack* top = NULL;
	int i = 0;
	int j = 0;
	char s[26], aim[26];
	s[i] = '121';
	cout << "Введите выражение:\n";
	while ((i < 25) && (!(s[i] <= 'a' && s[i] >= 'z' || s[i] == '(' || s[i] == ')' || s[i] == '-' || s[i] == '+' || s[i] == '*' || s[i] == '/')))
	{
		s[i] = _getch();
		if (s[i] >= 'a' && s[i] <= 'z')
		{
			cout << s[i];
			aim[j] = s[i];
			i++;
			j++;
		}

		if (s[i] == '(')
		{
			cout << s[i];
			top = createStack(top, s[i]);
			i++;
			continue;
		}

		if (s[i] == '+')
		{
			cout << s[i];
			if (top == NULL)
			{
				top = createStack(top, s[i]);
			}
			else
			{
				if (proverka(top, priorityPL) == 1)
				{
					aim[j] = top->info;
					j++;
					top->info = s[i];
				}
				else if (proverka(top, s[i]) == 2)
				{
					top = createStack(top, s[i]);
				}
			}
			i++;
		}

		if (s[i] == '-')
		{
			cout << s[i];
			if (top == NULL)
			{
				top = createStack(top, s[i]);
			}
			else
			{
				if (proverka(top, priorityPL) == 1)
				{
					aim[j] = top->info;
					j++;
					top->info = s[i];
				}
				else if (proverka(top, s[i]) == 2 || 0)
				{
					top = createStack(top, s[i]);
				}
			}
			i++;
		}

		if (s[i] == '*')
		{
			cout << s[i];
			if (top == NULL)
			{
				top = createStack(top, s[i]);
			}
			else
			{
				if (proverka(top, priorityDEL) == 1)
				{
					aim[j] = top->info;
					j++;
					top->info = s[i];
				}
				else if (proverka(top, s[i]) == 2 || 0)
				{
					top = createStack(top, s[i]);
				}
			}
			i++;
		}

		if (s[i] == '/')
		{
			cout << s[i];
			if (top == NULL)
			{
				top = createStack(top, s[i]);
			}
			else
			{
				if (proverka(top, priorityDEL) == 1)
				{
					aim[j] = top->info;
					j++;
					top->info = s[i];
				}
				else if (proverka(top, s[i]) == 2 || 0)
				{
					top = createStack(top, s[i]);
				}
			}\
				i++;
		}

		if (s[i] == ')')
		{
			cout << s[i];
			while (top->info != '(')
			{
				aim[j] = top->info;
				j++;
				Stack* buf = top;
				top = top->next;
				delete buf;
			}
			if (top->info == '(')
			{
				Stack* buf = top;
				top = top->next;
				delete buf;
			}
			i++;
			continue;
		}

		/*if (s[i] == 8)
		{
			cout << "\nНапишите варажение заново: ";
			for (int j = 0; j < 26; j++)
			{
				s[j] = NULL;
			}
			i = 0;
			continue;
		}*/

		if (s[i] == 13)
			break;
	}
	while (top != NULL)
	{
		aim[j] = top->info;
		j++;
		top = top->next;
	}
	cout << endl;
	s[i] = '\0';
	i = 0;
	aim[j] = '\0';

	cout << endl << "Обратная польская запись: " << aim << endl;
	cout << "Ответ:" << result(aim);
	return 0;
}
