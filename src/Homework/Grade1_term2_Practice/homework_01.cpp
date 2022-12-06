/*支持四则运算，运算数可以为整型和浮点型*/
/*时间复杂度O(n),空间复杂度O(n)*/
#include <iostream>
#include <string>
#include <stack>
using namespace std;

//是否为一级运算符
bool isone(char c)
{
	return (c == '+' || c == '-');
}

//是否为二级运算符
bool istwo(char c)
{
	return (c == '*' || c == '/');
}

/* 将中缀表达式转化为后缀表达式
1.从左到右扫描每一个字符。如果扫描到的字符是操作数（如a、b等），就直接输出这些操作数。
2.如果扫描到的字符是一个操作符，分三种情况：
（1）如果堆栈是空的，直接将操作符存储到堆栈中（push）
（2）如果该操作符的优先级大于堆栈出口的操作符，就直接将操作符存储到堆栈中（push）
（3）如果该操作符的优先级低于堆栈出口的操作符，就将堆栈出口的操作符导出（pop）, 直到该操作符的优先级大于堆栈顶端的操作符。将扫描到的操作符导入到堆栈中（push）。
3.如果遇到的操作符是左括号"（”，就直接将该操作符输出到堆栈当中。该操作符只有在遇到右括号“)”的时候移除。这是一个特殊符号该特殊处理。
4.如果扫描到的操作符是右括号“）”，将堆栈中的操作符导出（pop）到output中输出，直到遇见左括号“（”。将堆栈中的左括号移出堆栈（pop ）。继续扫描下一个字符
5.如果输入的中缀表达式已经扫描完了，但是堆栈中仍然存在操作符的时候，我们应该讲堆栈中的操作符导出并输入到output 当中。
*/
string shorten(string m)
{
	stack<char> s;
	string sur; //后缀表达式
	int i;
	char w;

	for (i = 0; i < m.size(); i++)
	{
		if (isdigit(m[i]) || m[i] == '.') //如果是操作数
		{
			while (isdigit(m[i]) || m[i] == '.')
				sur += m[i++];
			i--;
			sur += ' '; // ' '用于分隔相邻的数字
		}
		else if (isone(m[i])) //如果是一级操作符
		{
			while (s.size() && (isone(s.top()) || istwo(s.top()))) //栈不为空且栈顶不为括号时
			{
				sur += s.top();
				s.pop();
			}
			s.push(m[i]);
		}
		else if (m[i] == ')') //如果是右括号
		{
			while (s.top() != '(')
			{
				sur += s.top();
				s.pop();
			}
			s.pop(); //将'('出栈
		}
		else if (istwo(m[i])) //如果是二级操作符
		{
			while (s.size() && istwo(s.top())) //栈不为空且栈顶为二级运算符时
			{
				sur += s.top();
				s.pop();
			}
			s.push(m[i]);
		}
		else //栈为空或者为'('时
			s.push(m[i]);
	}
	while (s.size()) //将剩余操作符添加到后缀表达式中
	{
		sur += s.top();
		s.pop();
	}
	return sur;
}


//计算十的n次方
double tentimes(int n)
{
	double res = 1;
	for (int i = 0; i < n; i++)
	{
		res *= 10;
	}
	return res;
}

//将字符串数字转化为double类型
double str2double(string s)
{
	double res = 0;
	char c;
	int dec = 0; //dec变量决定计算整数部分还是小数部分
	for (int i = 1; i <= s.size(); i++)
	{
		c = s[i - 1];
		if (c == '.')
			dec = i; //确定'.'的位置为第i位
		else if (!dec)
			res = res * 10 + c - '0'; //计算整数部分
		else
			res += (c - '0') / tentimes(i - dec); //计算小数部分
	}
	return res;
}

//计算后缀表达式的值
double calculate(string s)
{
	double res, t;
	stack<double> num; //数字栈
	string temp;
	int i;
	for (i = 0; i < s.size(); i++)
	{
		temp = "";
		if (isdigit(s[i]) || s[i] == '.') //isdight函数判断是否是数字字符
		{
			while (isdigit(s[i]) || s[i] == '.')
				temp += s[i++]; //如果最后一位是数字，这样做会出错
			num.push(str2double(temp)); //将要运算的数字压栈
		}
		else
		{
			switch (s[i]) 
			{
			case '+':
				t = num.top();
				num.pop();
				t += num.top();
				num.pop();
				num.push(t);
				break;
			case '-':
				t = num.top();
				num.pop();
				t = num.top() - t;
				num.pop();
				num.push(t);
				break;
			case '*':
				t = num.top();
				num.pop();
				t *= num.top();
				num.pop();
				num.push(t);
				break;
			case '/':
				t = num.top();
				num.pop();
				t = num.top() / t;
				num.pop();
				num.push(t);
				break;
			default:
				cout << "输入了非法字符，会得出错误结果!" << endl;
				exit(EXIT_FAILURE);
				break;
			}//后缀运算，读取到操作符就将栈顶数和与其相邻的数进行运算
		}
	}//循环结束后，栈顶元素即为所求
	res = num.top();
	return res;
}

//主函数
int main()
{
	string mid, sur;
	cout << "请输入中缀表达式:" << endl; 
	cin >> mid;
	sur = shorten(mid);
	cout << "运行成功，后缀运算符表达式为: " << endl;
	cout << sur << endl;
	cout << "计算结果是: " << calculate(sur) << endl;
	cin.get();
	return 0;
}
