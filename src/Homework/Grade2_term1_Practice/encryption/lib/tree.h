//完成哈夫曼树的构建
#include "node.h"	//定义节点的头文件
#include <map>		//用map保存编码对照表
#include <fstream>	//读写文件
#include <queue>	//需要使用优先队列
#define prior_que priority_queue<HTNode, vector<HTNode>, greater<HTNode>>	//宏定义一下优先队列类型, 大顶堆, 小的数据先出队
using namespace std;

int a[128] = {0};			//哈希法处理ASCII字符

//通过字符串统计字符的频率, 返回记录结果的优先队列
prior_que count(string PATH) {
	ifstream in(PATH);
	string t;
	prior_que ans;
	while (getline(in, t)) {
		for (int i = 0; i < t.size(); i++)	{
			try	{	//异常处理
				if(t[i] < 0 || t[i] >= 128) {
					string y;
					int x = i;
					y += t[i];
					throw x;
					throw y;
				}
				else
					a[t[i]]++;
			}
			catch(const int e) {
				cerr << e << endl;
			}
			catch(const string e) {
				cerr << e << endl;
			}
		}
	}
	for(int i = 0; i < 128; i++) {
		if(a[i]) {	//如果字符存在
			HTNode * node = new HTNode(char(i), a[i]);
			ans.push(*node);
			delete node;
		}
	}
	in.close();
	return ans;
}

prior_que statistic_queue;	//记录字符及其频度的优先队列

/**
 * 创建哈夫曼树
 * @param 无
 * @return 哈夫曼树的根节点
*/
HTNode Create_Tree() {
	prior_que que = statistic_queue;
	while(que.size() >= 2) {
		HTNode* left = new HTNode(que.top());	que.pop();
		HTNode* right = new HTNode(que.top());	que.pop();
		HTNode parent('@', left->weight + right->weight, left, right);	//@字符用于代替中间的节点字符
		que.push(parent);
	}
	return que.top();
}

/**
 * 输出字符及其频度
 * @param que 存储字符及其频度的优先队列
*/
void show_que(prior_que que) {
	while(!que.empty()) {
		HTNode node = que.top();
		que.pop();
		cout << node.ch << " : " << node.weight << endl;
	}
}

/**
 * 层次遍历哈夫曼树
 * @param root 哈夫曼树的根节点
 * @return 一个vector<vector<pair<char, int>>>类型的结果
*/
vector<vector<pair<char, int>>> levelorder(HTNode* root) {	//层次遍历哈夫曼树
	queue<HTNode*> que;
	if(root != nullptr)
		que.push(root);
	vector<vector<pair<char, int>>> ans;
	while(!que.empty()) {
		int size = que.size();
		vector<pair<char, int>> vec;	//记录每一层的结果
		for(int i = 0; i < size; i++) {
			HTNode * node = que.front();
			que.pop();
			vec.push_back({node->ch, node->weight});
			if(node->left)		//左孩子入队
				que.push(node->left);
			if (node->right)	//右孩子入队
				que.push(node->right);
		}
		ans.push_back(vec);
	}
	return ans;
}
vector<vector<pair<char, int>>> order_res;	//哈夫曼树的层次遍历结果

void show_vec(vector<vector<pair<char, int>>> res) {
	for(auto i : res) {
		for(auto j : i) {
			cout << "{" <<  j.first << " : " << j.second << "}" << " ";
		}
		cout << endl;
	}
}

map<char, string> code_map;		//编码对照表

/**
 * 获取编码表，使用map存入结果: map<char, string> code_map;
 * @param root 哈夫曼树的根节点
 * @param code 路径编码, 左0右1
 * @param path 到根节点的路径
*/
void get_CodeMap(HTNode * root, string code, string& path) {
	string s = path;
	s += code;
	if(root != nullptr) {
		if(root->ch == '@') {	//是中间节点
			get_CodeMap(root->left, "0", s);	//左0
			get_CodeMap(root->right, "1", s);	//右1
		}
		else {	//编码节点
			code_map[root->ch] = s;	//记录结果
		}
	}
}

void show_map(map<char, string> Code_Map)
{
	for(auto i : Code_Map) {
		cout << i.first << "\t:\t" << i.second << endl;
	}
}