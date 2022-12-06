//迷宫问题
#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include "../lib/Stack_2.h"	//链式栈
#include <windows.h>	//改变路径的显示颜色
using namespace std;

int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}}; //方向数组 ,分别为下，上，右，左 ，输出分别设为0, 1, 2, 3
vector<vector<int>> matrix;	//迷宫矩阵
vector<vector<int>> visited;	//访问记录(0:未访问, 1:已访问)
vector<pair<int, int>> solution;	//记录节点结果
vector<vector<string>> run;	//记录方向的输出结果
map<pair<int, int>, pair<int, int>> pre;	//记录前驱节点
int m, n;	//矩阵的行和列
int start_x, start_y, end_x, end_y;	//起点坐标和终点坐标
int flag = 0;	//是否有通路

void init_run() {	//初始化结果列表
	run = vector<vector<string>>(m, vector<string>(n, " "));
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			run[i][j] = matrix[i][j] + '0';
}

void get_data() {
	ifstream in("../data/迷宫问题测试数据.txt");	//读入测试数据
	string s;
	while(getline(in, s)) {
		vector<int> t;
		for(char c : s) {
			if(c != ' ')
				t.emplace_back(c - '0');
		}
		matrix.emplace_back(t);
	}
	in.close();
	m = matrix.size();		//行
	n = matrix[0].size();	//列
	visited = vector<vector<int>>(m, vector<int>(n));
	init_run();
}

bool check(int x, int y) {	//检查该坐标点是否有障碍或已经被访问过
	if(x < 0 || x >= m || y < 0 || y >= n)
		return false;
	else
		return matrix[x][y] == 0 && visited[x][y] == 0;
}

int direction(pair<int, int>& a, pair<int, int>& b) {	//返回a -> b的方向参数
	for(int i = 0; i < 4; i++) {
		if(b.first == a.first + dir[i][0] && b.second == a.second + dir[i][1])
			return i;
	}
	return  -1;
}

void ouput1() {		//以三元组形式输出结果
	pair<int, int> p = {end_x, end_y};
	while(!(p.first == start_x && p.second == start_y)) {
		solution.push_back({p.first, p.second});
		p = pre[{p.first, p.second}];
	}
	solution.push_back({start_x, start_y});
	reverse(solution.begin(), solution.end());
	for(int i = 0; i < solution.size() - 1; i++) {
		cout << '(' << solution[i].first + 1 << ", " << solution[i].second + 1;
		int d = direction(solution[i], solution[i + 1]);
		cout << ", " << d << ')' << endl;
	}
	cout << '(' << end_x + 1 << ", " << end_y + 1 << ", 终)" << endl;
}

void solve1() {		//问题一，非递归
	init_run();
	visited = vector<vector<int>>(m, vector<int>(n));
	solution.clear();
	stack<pair<int, int>> s;	//链栈
	s.push({start_x, start_y});	//将起点压栈
	visited[start_x][start_y] = 1;
	while(!s.empty()) {
		pair<int, int> a = s.top();
		s.pop();
		if(a.first == end_x && a.second == end_y) {
			ouput1();
			return;
		}
		for(int i = 0; i < 4; i++) {
			int x = a.first + dir[i][0];
			int y = a.second + dir[i][1];
			if(!check(x, y)) {
				continue;
			}
			visited[x][y] = 1;
			pre[{x, y}] = a;
			s.push({x, y});
		}
	}
	cout << "无通路" << endl;
}

void output2() {	//以方阵的形式输出所有通路结果
	for(int i = 0; i < solution.size() - 1; i++) {
		int x = solution[i].first;
		int y = solution[i].second;
		int d = direction(solution[i], solution[i + 1]);
		if(d==0) run[x][y] = "D";
        if(d==1) run[x][y] = "U";
        if(d==2) run[x][y] = "R";
        if(d==3) run[x][y] = "L";
	}
	flag = 1;
	run[end_x][end_y] = "终";
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);	//获取标准输出的句柄
	for(auto i : run) {
		for(auto j : i) {
			if(j == "D" || j == "U" || j == "R" || j == "L") {
				SetConsoleTextAttribute(hStdout, 0x0c);	//改为红色
				cout << j << ' ';
			}
			else if(j == "终") {
				SetConsoleTextAttribute(hStdout, 0x0c);	//改为红色
				cout << j << ' ';
				SetConsoleTextAttribute(hStdout, 0x0F);	//恢复白色
			}
			else if(j == "1") {
				SetConsoleTextAttribute(hStdout, 0x60);	//改为黄色背景
				cout << j << ' ';
				SetConsoleTextAttribute(hStdout, 0x0F);	//恢复白色
			}
			else {
				SetConsoleTextAttribute(hStdout, 0x0F);	//恢复白色
				cout << j << ' ';
			}
		}
		cout << endl;
	}
	cout << endl;
	init_run();		//每次输出结果后初始化结果列表
}

void dfs(int x, int y) {	//dfs求所有通路, (x, y)为当前起点坐标
	solution.push_back({x, y});
	visited[x][y] = 1;
	if(x == end_x && y == end_y) {	//如果到达终点
		output2();
	}
	else {
		for(int i = 0; i < 4; i++) {	//四个方向依次遍历
			int xx = x + dir[i][0];	//下个方向的横坐标
			int yy = y + dir[i][1];	//下个方向的纵坐标
			if(check(xx,yy)) {
				dfs(xx, yy);
			}
			else	//下一个点不可行
				continue;
		}
	}
	visited[x][y] = 0;	//回溯
	solution.pop_back();	//回溯
}

void solve2() {	//递归
	init_run();
	visited = vector<vector<int>>(m, vector<int>(n));
	solution.clear();
	flag = 0;
	dfs(start_x, start_y);
	if(!flag) {
		cout << "无通路" << endl;
	}
}

int main() 
{
	get_data();
	cout << "请输入起点坐标: " << endl;
	cin >> start_x >> start_y;
	start_x--;	start_y--;	//转换为下标索引
	cout << "请输入终点坐标: " << endl;
	cin >> end_x >> end_y;
	end_x--;	end_y--;	//转换为下标索引
	int choose;
	while(true) {
		cout << "请选择任务:\n" << endl;
		cout << "1: 使用非递归方法(栈),以三元组的形式输出一条通路" << endl;
		cout << "2: 使用递归方法(dfs),求出所有通路以方阵的形式输出通路" << endl;
		cout << "0: 结束程序" << endl;
		cin >> choose;
		if(choose == 1)
			solve1();
		else if(choose == 2)
			solve2();
		else if(choose == 0)
			return 0;
		else
			cout << "输入错误" << endl;
	}
	return 0;
}