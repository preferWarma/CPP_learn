#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;

class Mytel {					//描述单个号码
public:
	Mytel() {					//默认构造函数
	}
	Mytel(string n, string t) {	//有参构造函数
		name = n;
		telno = t;
	}
	void getdata() {			//输入电话号码和人名
		cin >> name >> telno;
	}

	void display() {			//输出
		cout << name << setw(12) << telno << endl;
	}

	string getname() {			//获得名字
		return name;
	}
	string gettelno() {			//获得号码
		return telno;
	}
	~Mytel() {					//默认析构函数
	}
private:
	string name;
	string telno;
};

class TelMyanager {		//管理电话号码
public:
	void init() {								//数据加载函数
		ifstream in("data.txt");				//以文本模式打开文件
		if(!in) {
			cout << "文件打开失败!" << endl;
			exit(EXIT_FAILURE);
		}
		string nam, tel;
		while(in >> nam >> tel) {
			a.push_back(Mytel(nam, tel));		//写入到vector里
		}
		cout << "加载成功" << endl;
		in.close();
	}

	void print() {								//输出电话簿
		Mytel s;
		cout << "所有朋友的信息为: " << endl;
		cout << "姓名" << '\t' << "电话号码" << endl;
		for(int i = 0; i < a.size(); i++) {
			a[i].display();
		}
	}

	void find_data() {							//查找联系人
		string findName;
		cout << "请输入需要查讯的姓名:" << endl;
		cin >> findName;
		cout << "查询结果: " << endl;
		cout << "姓名" << '\t' << "电话号码" << endl;
		for(int i = 0; i < a.size(); i++) {
			if(a[i].getname() == findName) {
				a[i].display();
				return;
			}
		}
		cout << "没有找到这个人的信息" << endl;
	}

	void add() {											//添加数据
		ofstream out("data.txt", ios::app|ios::out);		//以文本模式打开文件，并讲流指针置于文件末尾
		if(!out) {
			cout << "文件打开失败!" << endl;
			exit(EXIT_FAILURE);
		}
		Mytel s;
		cout << "姓名" << '\t' << "电话号码" << endl;
		s.getdata();
		out << s.getname() << " " << s.gettelno() << endl;	//将数据添加到文件里
		a.push_back(s);										//将数据复制到vector里
		cout << "添加成功" << endl;
		out.close();
	}

	void erase() {											//删除数据
		cout << "请输入需要删除的姓名: " << endl;
		string eraseName;
		cin >> eraseName;
		ofstream out("data.txt", ios::trunc);				//以文本模式打开文件
		int index = 0;
		for(int i = 0; i < a.size(); i++) {
			if(a[i].getname() == eraseName) {
				index = i;
				continue;
			}
			out << a[i].getname() << " " << a[i].gettelno() << endl;
		}
		a.erase(index + a.begin());							//从vector中删除
		cout << "删除成功" << endl;
		out.close();
	}

	void modify() {											//修改
		cout << "请输入需要修改的姓名" << endl;
		string modname;
		cin >> modname;
		ofstream out("data.txt", ios::trunc);				//以文本模式打开文件
		int index = 0;
		for(int i = 0; i < a.size(); i++) {
			if(a[i].getname() == modname) {
				cout << "请输入修改后的电话号码" << endl;
				string modtel;
				cin >> modtel;
				out << modname <<" " << modtel << endl;
				a[i] = Mytel(modname, modtel);
				cout << "修改成功" << endl;
				continue;
			}
			out << a[i].getname() << " " << a[i].gettelno() << endl;
		}
		out.close();
	}
private:
	vector<Mytel> a;
};

int main() 
{
	TelMyanager T;
	int choose;
	while(true) {
		cout << endl << endl;
		cout << "*************************电话拨系统************************" << endl;
		cout << "1.加载数据		2.输出数据		3.按姓名查询" << endl
			 << "4.添加数据		5.删除数据		6.修改数据" << endl
			 << "\t\t\t0.退出系统" << endl;
		cout << "**********************************************************" << endl;
		cout << "\n请选择(0——5): ";
		cin >> choose;
		switch (choose)
		{
		case 1:
			T.init();
			break;
		case 2:
			T.print();
			break;
		case 3:
			T.find_data();
			break;
		case 4:
			T.add();
			break;
		case 5:
			T.erase();
			break;
		case 6:
			T.modify();
			break;
		case 0:
			cout << "感谢使用!" << endl;
			exit(EXIT_SUCCESS);
		default:
			break;
		}
	}
	return 0;
}