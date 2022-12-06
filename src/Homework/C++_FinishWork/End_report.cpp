// C++结课报告: 媒体资料借阅管理系统设计
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<map>
using namespace std;

class base{		//基类
public:
	int get_number() {return number;}
	string get_title() {return title;}
	string get_author() {return author;}
	string get_level() {return level;}

protected:
	void getBasedata(int n) {		//输入基本信息
		cout << "标题\t" << "作者" << endl;
		cin >> title >> author;
		number = n;
		cout << "请选择评级(0:不评级, 1:一般, 2:成人, 3:儿童)" << endl;
		int t;
		cin >> t;
		switch (t)
		{
		case 0:
			break;
		case 1:
			level = "一般";
			break;
		case 2:
			level = "成人";
			break;
		case 3:
			level = "儿童";
			break;
		default:
			break;
		}
	}

	int number;					//编号
	string title;				//标题
	string author;				//作者
	string level = "未评级";	//评级（未评级，一般，成人，儿童）
};

class book : public base{		//图书类
public:
	bool is_borrow = false;	//是否被借阅

	book() {}				//无参构造函数

	book(int _number, string _title, string _author, string _level, string _press, string _ISBN, int _pages) {	//有参构造函数
		number = _number;	title = _title;		author = _author;	level = _level;
		press = _press;		ISBN = _ISBN;		pages = _pages;
	}

	void getdata(int n) {	//输入特定信息
		getBasedata(n);
		cout << "出版社\t" << "ISBN号\t" << "页数" << endl;
		cin >> press >> ISBN >> pages;
	}

	void print() {			//输入信息
		cout << number << "\t\t" << title << "\t\t" << author << "\t\t" << level << "\t\t" 
		<< press << "\t\t" << ISBN << "\t\t" << pages << endl;
	}

	string get_press() {return press;}
	string get_ISBN() {return ISBN;}
	int get_pages() {return pages;}

private:
	string press;	//出版社
	string ISBN;	//ISBN号（十位数字）
	int pages;		//页数
};

class video : public base{	//视频光盘类
public:
	bool is_borrow = false;	//是否被借阅

	video() {}				//无参构造函数

	video(int _number, string _title, string _author, string _level, string _publisher, string _prodict_year, int _time) {	//有参构造函数
		number = _number;	title = _title;	author = _author;	level = _level;
		publisher = _publisher;		prodict_year = _prodict_year;	time = _time;
	}

	void getdata(int n) {	//输入特定信息
		getBasedata(n);
		cout << "出品者名字\t" << "出品年份\t" << "视频时长(单位为min)" << endl;
		cin >> publisher >> prodict_year >> time;
	}

	void print() {			//输出信息
		cout << number << "\t\t" << title << "\t\t" << author << "\t\t" << level << "\t\t"
		<< publisher << "\t\t" << prodict_year << "\t\t" << time << endl;
	}

	string get_publisher() {return publisher;}
	string get_prodict_year() {return prodict_year;}
	int get_time() {return time;}

private:
	string publisher;		//出品者名字
	string prodict_year;	//出品年份
	int time;				//视频时长
};

class picture : public base{	//图画类
public:
	bool is_borrow = false;	//是否被借阅

	picture() {}			//无参构造函数

	picture(int _number, string _title, string _author, string _level, string _prodict_nation, int _length, int _width) {	//有参构造函数
		number = _number;	title = _title;	author = _author;	level = _level;
		prodict_nation = _prodict_nation;		length = _length;	width = _width;
	}

	void getdata(int n) {	//输入特定信息
		getBasedata(n);
		cout << "出品国籍\t" << "长(以厘米计算)\t" << "宽(以厘米计算)\t" << endl;
		cin >> prodict_nation >> length >> width;
	}

	void print() {		//输出信息
		cout << number << "\t\t" << title << "\t\t" << author << "\t\t" << level << "\t\t" 
		<< prodict_nation << "\t\t" << length << "\t\t" << width << endl;
	}

	string get_prodict_nation() {return prodict_nation;}
	int get_length() {return length;}
	int get_width() {return width;}

private:
	string prodict_nation;	//出品国籍
	int length;				//长（以厘米记）
	int width;				//宽（以厘米记）
};

class reader{	//读者类
public:
	reader() {get_saved();}						//无参构造函数
	void save() {		//存盘
		ofstream borrow_b_out("borrow_b.txt");
		for(book i : b) {
			borrow_b_out << i.get_number() << "\t" << i.get_title() << "\t"
			<< i.get_author() << "\t" << i.get_level() << "\t"
			<< i.get_press() << "\t" << i.get_ISBN() << "\t" << i.get_pages() << endl;
		}
		borrow_b_out.close();
		ofstream borrow_v_out("borrow_v.txt");
		for(video i : v) {
			borrow_v_out << i.get_number() << "\t" << i.get_title() << "\t"
			<< i.get_author() << "\t" << i.get_level() << "\t"
			<< i.get_publisher() << "\t" << i.get_prodict_year() << "\t"
			<< i.get_time() << endl;
		}
		borrow_v_out.close();
		ofstream borrow_p_out("borrow_p.txt");
		for(picture i : p) {
			borrow_p_out << i.get_number() << "\t" << i.get_title() << "\t"
			<< i.get_author() << "\t" << i.get_level() << "\t"
			<< i.get_prodict_nation() << "\t" << i.get_length() << "\t" 
			<< i.get_width() << endl;
		}
		borrow_b_out.close();
	}

	void get_saved(){	//读盘
		int number;
		string title, author, level;
		ifstream borrow_b_in("borrow_b.txt");
		string press, ISBN;
		int pages;
		while(borrow_b_in >> number >> title >> author >> level >> press >> ISBN >> pages) {
			rest--;
			b.push_back(book(number, title, author, level, press, ISBN, pages));
		}
		borrow_b_in.close();

		ifstream borrow_v_in("borrow_v.txt");
		string publisher, prodict_year;
		int time;
		while(borrow_v_in >> number >> title >> author >> level >> publisher >> prodict_year >> time) {
			rest--;
			v.push_back(video(number, title, author, level, publisher, prodict_year, time));
		}
		borrow_v_in.close();

		ifstream borrow_p_in("borrow_p.txt");
		string prodict_nation;
		int length, width;
		while(borrow_p_in >> number >> title >> author >> level >> prodict_nation >> length >> width) {
			rest--;
			p.push_back(picture(number, title, author, level, prodict_nation, length, width));
		}
		borrow_p_in.close();
	}
	string name;		//读者姓名
	vector<book> b;		//借阅的图书
	vector<video> v;	//借阅的视频光盘
	vector<picture> p;	//借阅的图画
	int rest = 5;		//剩余可借阅本数
};

class storehouse{	//仓库类
public:
	book finded_book;		//查找到的book对象
	video finded_video;		//查找到的video对象
	picture finded_picture;	//查找到的picture对象
	void add() {			//往仓库里面添加物品信息, 编号唯一, 不添加相同编号
		cout << "请输入需要添加的编号: " << endl;
		int n;
		cin >> n;
		if(store_n.find(n) != store_n.end()) {
			cout << "编号重复,添加失败, 是否需要重新添加(0:否, 1:是)" << endl;
			int is;
			cin >> is;
			add();
		}
		else {
			cout << "请选择需要添加的类型(1:图书, 2:视频光盘, 3:图画)" << endl;
			int is;
			cin >> is;
			store_n[n] = is;	//把编号添加到编号库里
			switch (is)
			{
			case 1: {
				book b;
				b.getdata(n);
				store_b.push_back(b);
				break;
			}
			case 2: {
				video v;
				v.getdata(n);
				store_v.push_back(v);
				break;
			}
			case 3: {
				picture p;
				p.getdata(n);
				store_p.push_back(p);
				break;
			}
			default:
				break;
			}
		}
	}

	int find_title(string t) {		//按标题查找,返回值为查找结果(1:图书, 2:视频光盘, 3:图画, 0:未找到)
		for(book i : store_b) {
			if(i.get_title() == t) {
				finded_book = i;
				return 1;
			}
		}
		for(video i : store_v) {
			if(i.get_title() == t) {
				finded_video = i;
				return 2;
			}
		}
		for(picture i : store_p) {
			if(i.get_title() == t) {
				finded_picture = i;
				return 3;
			}
		}
		return 0;
	}

	int find_number(int n) {	//按编号查询
		if(store_n.find(n) != store_n.end()) {
			switch (store_n[n])
			{
			case 1: {
				for(book i : store_b) {
					if(i.get_number() == n) {
						finded_book = i;
						return 1;
					}
				}
				break;
			}
			case 2: {
				for(video i : store_v) {
					if(i.get_number() == n) {
						finded_video = i;
						return 2;
					}
				}
				break;
			}
			case 3: {
				for(picture i : store_p) {
					if(i.get_number() == n) {
						finded_picture = i;
						return 3;
					}
				}
				break;
			}
			default:
				break;
			}
		}
		return 0;
	}

	void find_kind() {		//按类型查询
		int is;
		cout << "请输入需要查询的类型(1:图书, 2:视频光盘, 3:图画)" << endl;
		cin >> is;
		switch (is)
			{
			case 1: {
				if(store_b.size() != 0) {
					cout << "编  号\t" << "\t标  题\t" << "\t作  者\t" << "\t评级\t" << "\t出 版 社\t" << "\tISBN号\t" << "\t页数" << endl;
					for(book i : store_b) {
						i.print();
					}
				}
				else {
					cout << "该类别没有物品" << endl;
				}
				break;
			}
			case 2: {
				if(store_v.size() != 0) {
					cout << "编  号\t" << "\t标  题\t" << "\t作  者\t" << "\t评级\t" << "\t出品者名字\t" << "\t出品年份\t" << "\t视频时长" << endl;
					for(video i : store_v) {
						i.print();			
					}
				}
				else {
					cout << "该类别没有物品" << endl;
				}
				break;
			}
			case 3: {
				if(store_p.size() != 0) {
					cout << "编  号\t" << "\t标  题\t" << "\t作  者\t" << "\t评级\t" << "\t出品国籍\t" << "\t长\t" << "\t宽" << endl;
					for(picture i : store_p) {
							i.print();
					}
				}
				else {
					cout << "该类别没有物品" << endl;
				}
				break;
			}
			default:
				break;
			}
	}

	void display() {		//显示物品库的所有信息
		string line;
		ifstream book_in("book.txt");
		cout << "图书类" << endl;
		while(getline(book_in, line)) {
			cout << line << endl;
		}
		book_in.close();
		cout << endl << endl << "视频光盘类" << endl;
		ifstream video_in("video.txt");
		while(getline(video_in, line)) {
			cout << line << endl;
		}
		video_in.close();
		cout << endl << endl << "图画类" << endl;
		ifstream picture_in("picture.txt");
		while(getline(picture_in, line)) {
			cout << line << endl;
		}
		picture_in.close();
	}

	void change() {			//修改物品信息
		int n;
		if(empty()) {
			cout << "当前物品库为空!" << endl;
			return;
		}
		cout << "请输入需要修改的物品的编号:" << endl;
		cin >> n;
		int select = find_number(n);
		if(select == 0) {
			cout << "该编号不存在" << endl;
			return;
		}
		string title, author, level;
		switch (select)
		{
		case 1: {
			int i = index_b(finded_book);
			cout << "请输入修改后的信息" << endl;
			cout << "标  题\t" << "作  者\t" << "评级\t" << "出 版 社\t" << "ISBN号\t" << "页数" << endl;
			string press, ISBN;
			int pages;
			cin >> title >> author >> level >> press >> ISBN >> pages;
			store_b[i] = book(n, title, author, level, press, ISBN, pages);
			cout << "修改成功" << endl;
			return;
		}
		case 2: {
			int i = index_v(finded_video);
			cout << "请输入修改后的信息" << endl;
			cout << "标  题\t" << "作  者\t" << "评级\t" << "出品者名字\t" << "出品年份\t" << "视频时长" << endl;
			string publisher, prodict_year;
			int time;
			cin >> title >> author >> level >> publisher >> prodict_year >> time;
			store_v[i] = video(n, title, author, level, publisher, prodict_year, time);
			cout << "修改成功" << endl;
			return;
		}
		case 3: {
			int i = index_p(finded_picture);
			cout << "请输入修改后的信息" << endl;
			cout << "标  题\t" << "作  者\t" << "评级\t" << "出品国籍\t" << "长\t" << "宽" << endl;
			string prodict_nation;
			int length, width;
			cin >> title >> author >> level >> prodict_nation >> length >> width;
			store_p[i] = picture(n, title, author, level, prodict_nation, length, width);
			cout << "修改成功" << endl;
			return;
		}
		default:
			break;
		}
	}

	bool erase(int n) {			//删除物品信息（通过编号删除）
		int select = find_number(n);
		if(select == 0) {
			return false;
		}
		switch (select)
		{
		case 1: {
			int i = index_b(finded_book);
			store_b.erase(store_b.begin() + i);
			store_n.erase(n);
			return true;
		}
		case 2: {
			int i = index_v(finded_video);
			store_v.erase(store_v.begin() + i);
			store_n.erase(n);
			return true;
		}
		case 3: {
			int i = index_p(finded_picture);
			store_p.erase(store_p.begin() + i);
			store_n.erase(n);
			return true;
		}
		default:
			break;
		}
		return false;
	}

	void borrow() {			//管理员负责将物品借阅给读者，数据保存到文件中
		string name;
		cout << "请输入你的名字" << endl;
		cin >> name;
		R.name = name;
		if(R.rest == 0) {
			cout << "您的借书数量已经达到上限" << endl;
			return;
		}
		cout << "请输入你想借的书的编号: " << endl;
		int n;
		cin >> n;
		int select = find_number(n);
		if(select == 0) {
			cout << "编号不存在" << endl;
		}
		else {
			switch (select)
			{
			case 1: {
				if(store_b[index_b(finded_book)].is_borrow) {
					cout << "该书已被借走" << endl;
					break;
				}
				R.b.push_back(finded_book);
				R.rest--;
				store_b[index_b(finded_book)].is_borrow = true;
				cout << "借阅成功" << endl;
				break;
			}
			case 2: {
				if(store_v[index_v(finded_video)].is_borrow) {
					cout << "该书已被借走" << endl;
					break;
				}
				R.v.push_back(finded_video);
				R.rest--;
				store_v[index_v(finded_video)].is_borrow = true;
				cout << "借阅成功" << endl;		
				break;
			}
			case 3: {
				if(store_p[index_p(finded_picture)].is_borrow) {
					cout << "该书已被借走" << endl;
					break;
				}
				R.p.push_back(finded_picture);
				R.rest--;
				store_p[index_p(finded_picture)].is_borrow = true;
				cout << "借阅成功" << endl;
				break;
			}
			default:
				break;
			}
		}
	}

	void statistic() {		//显示当前程序的物品
		if(empty()) {
			cout << "当前物品库为空!" << endl;
			return;
		}
		cout << "图书类: " << endl;
		if(store_b.size() != 0) {
			cout << "编  号\t" << "\t标   题\t" << "\t作  者\t" << "\t评级\t" << "\t出 版 社\t" << "\tISBN号\t" << "\t页数" << endl;
			for(book i : store_b) {
				i.print();
			}
		} 
		else {
				cout << "该类别没有物品" << endl;
		}
		cout << endl << endl;
		cout << "视频光盘类" << endl;
		if(store_v.size() != 0) {
			cout << "编  号\t" << "\t标   题\t" << "\t作  者\t" << "\t评级\t" << "\t出品者名字\t" << "\t出品年份\t" << "\t视频时长" << endl;
			for(video i : store_v) {
				i.print();			
			}
		}
		else {
				cout << "该类别没有物品" << endl;
		}
		cout << endl << endl;
		cout << "图画类" << endl;
		if(store_p.size() != 0) {
			cout << "编  号\t" << "\t标   题\t" << "\t作  者\t" << "\t评级\t" << "\t出品国籍\t" << "\t长\t" << "\t宽" << endl;
			for(picture i : store_p) {
					i.print();
			}
		}
		else {
				cout << "该类别没有物品" << endl;
		}
		cout << endl << endl;
	}

	void storage() {		//将当前程序的物品信息存入到文件中
		R.save();
		ofstream book_out("book.txt");
		for(book i : store_b) {
			book_out << i.get_number() << "\t" << i.get_title() << "\t"
			<< i.get_author() << "\t" << i.get_level() << "\t"
			<< i.get_press() << "\t" << i.get_ISBN() << "\t" << i.get_pages() << endl;
		}
		book_out.close();
		ofstream video_out("video.txt");
		for(video i : store_v) {
			video_out << i.get_number() << "\t" << i.get_title() << "\t"
			<< i.get_author() << "\t" << i.get_level() << "\t"
			<< i.get_publisher() << "\t" << i.get_prodict_year() << "\t"
			<< i.get_time() << endl;
		}
		video_out.close();
		ofstream picture_out("picture.txt");
		for(picture i : store_p) {
			picture_out << i.get_number() << "\t" << i.get_title() << "\t"
			<< i.get_author() << "\t" << i.get_level() << "\t"
			<< i.get_prodict_nation() << "\t" << i.get_length() << "\t" 
			<< i.get_width() << endl;
		}
		picture_out.close();
	}

	void init() {			//从文件中将物品信息读入程序的vector中
		int number;
		string title, author, level;
		ifstream book_in("book.txt");
		string press, ISBN;
		int pages;
		while(book_in >> number >> title >> author >> level >> press >> ISBN >> pages) {
			store_n[number] = 1;
			store_b.push_back(book(number, title, author, level, press, ISBN, pages));
		}
		book_in.close();

		ifstream video_in("video.txt");
		string publisher, prodict_year;
		int time;
		while(video_in >> number >> title >> author >> level >> publisher >> prodict_year >> time) {
			store_n[number] = 2;
			store_v.push_back(video(number, title, author, level, publisher, prodict_year, time));
		}
		video_in.close();

		ifstream picture_in("picture.txt");
		string prodict_nation;
		int length, width;
		while(picture_in >> number >> title >> author >> level >> prodict_nation >> length >> width) {
			store_n[number] = 3;
			store_p.push_back(picture(number, title, author, level, prodict_nation, length, width));
		}
		picture_in.close();
	}

	bool empty() {						//判断仓库是否为空
		if(store_b.empty() && store_v.empty() && store_p.empty()) {
			return true;
		}
		else
			return false;
	}
	void disp_finded(int t) {			//输出查找到的结果
		switch (t)
		{
		case 1: {
			cout << "编  号\t" << "\t标  题\t" << "\t作  者\t" << "\t评级\t" << "\t出 版 社\t" << "\tISBN号\t" << "\t页数" << endl;
			finded_book.print();
			break;
		}
		case 2: {
			cout << "编  号\t" << "\t标  题\t" << "\t作  者\t" << "\t评级\t" << "\t出品者名字\t" << "\t出品年份\t" << "\t视频时长" << endl;
			finded_video.print();
			break;
		}
		case 3: {
			cout << "编  号\t" << "\t标  题\t" << "\t作  者\t" << "\t评级\t" << "\t出品国籍\t" << "\t长\t" << "\t宽" << endl;
			finded_picture.print();
			break;
		}
		default:
			break;
		}
	}

	int index_b(book b) {		//返回下标
		for(int i = 0; i < store_b.size(); i++) {
			if(store_b[i].get_number() == b.get_number())
				return i;
		}
		return -1;
	}

	int index_v(video v) {		//返回下标
		for(int i = 0; i < store_v.size(); i++) {
			if(store_v[i].get_number() == v.get_number())
				return i;
		}
		return -1;
	}

	int index_p(picture p) {		//返回下标
		for(int i = 0; i < store_p.size(); i++) {
			if(store_p[i].get_number() == p.get_number())
				return i;
		}
		return -1;
	}

private:
	vector<book> store_b;		//图书库存
	vector<video> store_v;		//视频光盘库存
	vector<picture> store_p;	//图画库存
	map<int, int> store_n;		//编号库, 键为编号, 值为类型(1:图书, 2:视频光盘, 3:图画)
	reader R;
};

int main() 
{
	storehouse Store;
	reader R;
	int choose;
	while (true)
	{
		cout << endl << endl;
		cout << "*************************媒体资料借阅管理系统设计************************" << endl;
		cout << "1.添加物品\t\t2.查询物品\t\t3.显示仓库" << endl
			 << "4.编辑物品\t\t5.删除物品\t\t6.借阅物品" << endl
			 << "7.统计信息\t\t8.物品存盘\t\t9.读取物品" << endl
			 << "\t\t\t0.退出系统" << endl;
		cout << "***********************************************************************" << endl;
		cout << "\n请选择(0——9): ";
		cin >> choose;
		switch (choose)
		{
		case 1:
			Store.add();
			break;
		case 2: {
			cout << "请选择查询方式(1:按标题查询\t2.按编号查询\t3.按类别查询)" << endl;
			int is;
			cin >> is;
			switch (is)
			{
			case 1: {
				string t;
				cout << "请输入需要查询的标题:" << endl;
				cin >> t;
				int select = Store.find_title(t);
				if(select == 0) {
					cout << "该标题不查找, 查找失败!" << endl;
					break;
				}
				else {
					Store.disp_finded(select);
					break;
				}
			}
			case 2: {
				int n;
				cout << "请输入需要查询的编号:" << endl;
				cin >> n;
				int select = Store.find_number(n);
				if (select == 0) {
					cout << "该编号不存在, 查找失败!" << endl;
					break;
				}
				else {
					Store.disp_finded(select);
					break;
				}
			}
			case 3:
				Store.find_kind();
				break;
			default:
				break;
			}
			break;
		}
		case 3:
			Store.display();
			break;
		case 4:
			Store.change();
			break;
		case 5: {
			int n;
			
			cout << "请输入需要删除的编号:" << endl;
			cin >> n;
			if(Store.erase(n)) {
				cout << "删除成功!" << endl;
			}
			else {
				cout << "编号不存在, 删除失败!" << endl;
			}
			break;
		}
		case 6: {
			Store.borrow();
			break;
		}
		case 7:
			Store.statistic();
			break;
		case 8:
			Store.storage();
			cout << "存盘成功!" << endl;
			break;
		case 9:
			Store.init();
			cout << "读入成功!" << endl;
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