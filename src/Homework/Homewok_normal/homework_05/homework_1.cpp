/*Student类的实现*/
#include <iostream>
#include <string>
using namespace std;
class Student
{
	int no;		   //学号
	string name;   //姓名
	float score;   //成绩
	Student *per;  //前一个节点指针
	Student *next; //下一个节点指针

    static int  count;                          //总人数
    static float total;                         //总分
public:
	Student();
	Student *find(int i_no);					//按学号查找
	void edit(string i_newname, float i_score); //修改
	void erase();								//删除
	int add(Student *i_newStudent);				//增加
	int getno();								//获得学号
	string getname();							//获得名字
	float getscore();							//获得成绩
    void display();                             //打印全部学生
    static float sum();                         //求总成绩
    static float average();                     //求平均值
	static int maxno;							//最大学号
};

int Student::maxno = 1000;
int Student::count = 0;
float Student::total = 0;
int main()
{
	Student *studentroot = new Student();
	string input1;
	float input2;
	Student *tmp = nullptr;
	while (true)
	{
		cout << "输入指令: 查找(F), 增加(A), 编辑(E), 删除(D), 显示(P), 求和(S), 平均值(V), 退出(Q)" << endl;
		cin >> input1;
		if (input1 == "F" || input1 == "f")
		{
			cout << "输入学号";
			int id = -1;
			cin >> id;
			tmp = studentroot->find(id);
			if (tmp == nullptr)
			{
				cout << "没找到" << endl;
				continue;
			}
			cout << "学号: " << tmp->getno();
			cout << "\t姓名: ";
			string name;
			name = tmp->getname();
			if (name != "")
				cout << name ;
			else
				cout << "未输入" ;
			cout << "\t成绩: " << tmp->getscore() << endl;
		}
		else if (input1 == "A" || input1 == "a")
		{
			cout << "输入姓名，成绩: " << endl;
			cin >> input1 >> input2;
			tmp = new Student();
			tmp->edit(input1, input2);
			cout << "学号: " << studentroot->add(tmp) << endl;
		}
		else if (input1 == "E" || input1 == "e")
		{
			cout << "输入学号: ";
			int id = 0;
			cin >> id;
			tmp = studentroot->find(id);
			if (tmp == nullptr)
			{
				cout << "空号" << endl;
				continue;
			}
			cout << "新姓名, 新成绩: ";
			cin >> input1 >> input2;
			tmp->edit(input1, input2);
			cout << "更改成功" << endl;
		}
		else if (input1 == "D" || input1 == "d")
		{
			cout << "输入学号: ";
			int id = 0;
			cin >> id;
			tmp = studentroot->find(id);
			tmp->erase();
			cout << "已经成功删除" << endl;
			delete tmp;
		}
        else if(input1 == "P" || input1 == "p")
        {
            cout << "学号\t" << "姓名\t" << "成绩" << endl;
            studentroot->display();
        }
        else if(input1 == "S" || input1 == "s")
        {
            cout << "所有学生的成绩之和是: " << Student::sum() << endl;
        }
        else if(input1 == "V" || input1 == "v")
        {
            cout << "所有学生的成绩平均值是: " << Student::average() << endl;
        }
		else if (input1 == "Q" || input1 == "q")
			break;
		else
			cout << "输入有误" << endl;
	}
	delete studentroot;
	return 0;
}

Student::Student()
{
	score = 0.0;
	per = nullptr;
	next = nullptr;
}

Student *Student::find(int i_no)
{
	if (i_no == no)
		return this;
	if (next != nullptr)
		return next->find(i_no);
	return nullptr;
}

void Student::edit(string i_name, float i_score)
{
	if (i_name == "")
		return;
    total -= score;
    total += i_score;

	name = i_name;
	score = i_score;
}

void Student::erase()
{
	if (no < 0)
		return;
	if (per != nullptr)
		per->next = next;
	if (next != nullptr)
		next->per = per;
	next = nullptr;
	per = nullptr;

    count--;
    total -= this->score;
}

int Student::add(Student *i_newStudent)
{
	int no = maxno + 1;
	while (true)
	{
		if (find(no) == nullptr)
			break;
		no = no + 1;
	}
	Student *tmp = this;
	while (true)
	{
		if (tmp->next == nullptr)
			break;
		tmp = tmp->next;
	}
	tmp->next = i_newStudent;
	i_newStudent->next = nullptr;
	i_newStudent->per = tmp;
	i_newStudent->no = no;
    count++;
	return no;
}

int Student::getno(){
	return no;
}
string Student::getname(){
	return name;
}
float Student::getscore(){
	return score;
}

void Student::display(){
	Student * t = next;
    for(int i = 0 ;i < Student::count; i++){
        cout << t->no << "\t" << t->name << "\t" << t->score << endl;
		t = t->next;
    }
}

float Student::sum(){
    return Student::total;
}

float Student::average(){
    return Student::total / Student::count;
}