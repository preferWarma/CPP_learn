//定义节点
#include <iostream>
using namespace std;

class HTNode {
public:
	char ch;		//字符
	int weight;		//权重
	HTNode* left;	//左孩子
	HTNode* right;	//右孩子
	//三个构造函数
	HTNode(int w) : weight(w) {}
	HTNode(char c, int w) : ch(c), weight(w), left(nullptr), right(nullptr) {}
	HTNode(char c, int w, HTNode* l, HTNode* r) : ch(c), weight(w), left(l), right(r) {}
	bool operator > (const HTNode& node) const {	//重载比较运算符方便排序
		return weight > node.weight;
	}
};
