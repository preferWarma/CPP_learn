//哈夫曼编码与译码
#include "../lib/tree.h"		//生成哈夫曼树的头文件
#include <windows.h>	//进度条改色用

using namespace std;

HTNode root(0);	//哈夫曼树的根节点

//从数据文件中读入字符及每个字符的权值，建立哈夫曼树HuffTree
void Initialzation(string PATH) {
	statistic_queue = count(PATH);	//存储字符频度的优先队列
	root = Create_Tree();
	order_res = levelorder(&root);
	string t = "";
	get_CodeMap(&root, "", t);		//生成编码对照表code_map
}

//用已建好的哈夫曼树，对from文件中的文本进行编码形成报文，将报文写在文件to中
void Encode(string from, string to) {
	ifstream in(from);
	ofstream out(to, ios::app);
	string data = "";	//记录每一行的明文
	while(getline(in, data)) {
		string t = "";	//记录每一行的编码结果
		for(int i = 0; i < data.size(); i++) {
			t += code_map[data[i]];
		}
		out << t << endl;
	}
	in.close();
	out.close();
}

//利用已建好的哈夫曼树，对文件CodeFile.data中的代码进行解码形成原文，结果存入文件Textfile.txt中
void Decode(string from, string to) {
	ifstream in(from);
	ofstream out(to, ios::app);
	string t;	//记录每行的编码文
	string ans;	//记录每行的解码结果
	while(getline(in, t)) {
		ans = "";
		HTNode copy_root = root;
		HTNode * PHead = &copy_root;
		for(int i = 0; i < t.size(); i++) {
			if (t[i] == '0')
				PHead = PHead->left;	//往左寻找
			else if(t[i] == '1')
				PHead = PHead->right;	//往右寻找
			if(PHead->ch != '@') {	//找到字符节点
				ans += PHead->ch;
				PHead = &copy_root;	//重新从根节点向下寻找下一个字符
			}
		}
		out << ans << endl;
	}
	in.close();
	out.close();
}

//输出DataFile.data中出现的字符以及各字符出现的频度（或概率）；输出ToBeTran.data及其报文Code.txt；输出CodeFile.data及其原文Textfile.txt
void Output() {
	int choose;
	while(true) {
		// system("cls");
		cout << "\n1. 显示DataFile.data中出现的字符以及各字符出现的频度" << endl;
		cout << "2. 显示构建的哈夫曼树的层次遍历结果" << endl;
		cout << "3. 显示字符编码对照表" << endl;
		cout << "4. 输出ToBeTran.data及其报文Code.txt" << endl;
		cout << "5. 输出CodeFile.data及其原文Textfile.txt" << endl;
		cout << "0. 返回主菜单" << endl;
		cout << "\n请输入0——5" << endl;
		cin >> choose;
		cout << endl;
		switch (choose)
		{
		case 1: {
			show_que(statistic_queue);
			// system("pause");
			break;
		}
		case 2: {
			show_vec(order_res);
            // system("pause");
			break;
		}
		case 3: {
			show_map(code_map);
			// system("pause");
			break;
		}
		case 4: {
			string t;
			ifstream in("../data/ToBeTran.data");
			cout << "ToBeTran.data的明文的内容为: \n" << endl;
			while(getline(in, t)) {
				cout << t << endl;
			}
			in.close();

			ifstream i("../data/Code.txt");
			cout << "\n明文ToBeTran.data加密后的报文Code.txt的内容为: \n" << endl;
			while(getline(i, t)) {
				cout << t << endl;
			}
			cout << endl;
			i.close();
			// system("pause");
			break;
		}
		case 5: {
			string t;
			ifstream in("../data/CodeFile.data");
			cout << "CodeFile.data加密报文的内容为: \n" << endl;
			while(getline(in, t)) {
				cout << t << endl;
			}
			ifstream i("../data/Textfile.txt");
			cout << "\nCodeFile.data加密报文的原文Textfile.txt的内容为: \n" << endl;
			while(getline(i, t)) {
				cout << t << endl;
			}
			cout << endl;
			i.close();
			// system("pause");
			break;
		}
		case 0:
			return;
		default:
			break;
		}
	}
}

//改色函数
void SetColor(unsigned short ForeColor, unsigned short BackGroundColor) {
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);	//获取标准输出的句柄
	SetConsoleTextAttribute(hStdout, (ForeColor) | (BackGroundColor << 4));	//改色
}

//进度条函数
void progress_bar() {
	for (int i = 1; i <= 50; i++) {
		SetColor(0, 14);
		printf(" ");
		printf("%d%%", i << 1);
		Sleep(51 - i);
		printf("\b\b\b");
	}
	SetColor(15, 0);
}

//主函数
int main()
{
	int choose;
	while(true) {
		// system("cls");
		cout << "\n1. 构建哈夫曼树" << endl;
		cout << "2. 编码明文" << endl;
		cout << "3. 解码报文" << endl;
		cout << "4. 输出" << endl;
		cout << "0. 结束程序" << endl;
		cout << "\n请选择0——4" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1: {
			Initialzation("../data/DataFile.data");
			progress_bar();
			cout << "\n哈夫曼树构建完成" << endl;
			// system("pause");
			break;
		}
		case 2: {
			Encode("../data/ToBeTran.data", "../data/Code.txt");
			progress_bar();
			cout << "\n编码完成, 结果已存入文件中，可选择“4. 输出”进行查看" << endl;
			// system("pause");
			break;
		}
		case 3: {
			Decode("../data/CodeFile.data", "../data/Textfile.txt");
			progress_bar();
			cout << "\n解码完成, 结果已存入文件中，可选择“4. 输出”进行查看" << endl;
			// system("pause");
			break;
		}
		case 4: {
			Output();
			break;
		}
		case 0:
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
		}
	}
	return 0;
}
