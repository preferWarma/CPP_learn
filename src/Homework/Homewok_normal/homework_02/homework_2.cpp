/*输入10个人的名字，按从大到小排序输出*/
#include<iostream>
#include<string>
#include<vector> //vector容器
#include<algorithm> //sort函数
using namespace std;

//定义排序方式
bool cmp(string a, string b)
{
	return a > b;
}

int main()
{
	vector<string> name;
	string str;
	for(int i = 0; i < 10; i++)
	{
		cin >> str;
		name.push_back(str);
	}
	sort(name.begin(),name.end(),cmp);
	for(string s : name)
	{
		cout << s << " ";
	}
	cout << endl;
	return 0;
}
//LiYi LiEr LiSan LiSi LiWu ZhangYi ZhangEr ZhangSan ZhangSi ZhangWu