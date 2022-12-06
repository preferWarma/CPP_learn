#include<iostream>
#include<string>
using namespace std;
class Teacher{
protected:
    int no;                         //编号
    string name;                    //姓名
    float monthpay;                 //固定月薪
    float hour;                     //授课时常
    float hour_money;               //每课时补贴
    float salary;                   //月薪总额
    static int totalno;             //最大编号
public:
    Teacher(){
        no = totalno++;
        cout << "教师姓名: ";
        cin >> name;
        salary = 0.0;
    }
    virtual void pay() = 0;         //计算月薪函数
    virtual void display() = 0;     //输出教师信息函数
};

class professor : virtual public Teacher{       //教授
public:
    professor(){
        hour_money = 50;
    }
};

class one_professor : virtual public professor{   //一级教授
public:
    one_professor(){
        monthpay = 8000;
        cout << name << "授课的课时数";
        cin >> hour;
    }
    void pay(){
        salary = monthpay + hour * hour_money;
    }
    void display(){
        cout << "一级教授:" << name << " \t编号:" << no << "  本月工资:  " << salary << endl;
    }
};

class two_professor : virtual public professor{   //二级教授
public:
    two_professor(){
        monthpay = 7500;
        cout << name << "授课的课时数";
        cin >> hour;
    }
    void pay(){
        salary = monthpay + hour * hour_money;
    }
    void display(){
        cout << "二级教授:" << name << " \t编号:" << no << "  本月工资:  " << salary << endl;
    }
};

class associate_professor : virtual public Teacher{       //副教授
public:
    associate_professor(){
        hour_money = 30;
    }
};

class one_associate_professor : virtual public associate_professor{     //一级副教授
public:
    one_associate_professor(){
        monthpay = 7000;
        cout << name << "授课的课时数";
        cin >> hour;
    }
    void pay(){
        salary = monthpay + hour * hour_money;
    }
    void display(){
        cout << "一级副教授:" << name << "\t编号:" << no << "  本月工资:  " << salary << endl;
    }
};

class two_associate_professor : virtual public associate_professor{     //二级副教授
public:
    two_associate_professor(){
        monthpay = 6000;
        cout << name << "授课的课时数";
        cin >> hour;
    }
    void pay(){
        salary = monthpay + hour * hour_money;
    }
    void display(){
        cout << "二级副教授:" << name << "\t编号:" << no << "  本月工资:  " << salary << endl;
    }
};

class three_associate_professor : virtual public associate_professor{     //三级副教授
public:
    three_associate_professor(){
        monthpay = 5000;
        cout << name << "授课的课时数";
        cin >> hour;
    }
    void pay(){
        salary = monthpay + hour * hour_money;
    }
    void display(){
        cout << "三级副教授:" << name << "\t编号:" << no << "  本月工资:  " << salary << endl;
    }
};

class lecturer : virtual public Teacher{            //讲师
public:
    lecturer(){
        hour_money = 20;
        monthpay = 4500;
        cout << name << "授课的课时数";
        cin >> hour;
    }
    void pay(){
        salary = monthpay + hour * hour_money;
    }
    void display(){
        cout << "讲师:" << name << " \t编号:" << no << "  本月工资:  " << salary << endl;
    }
};

int Teacher::totalno = 1000;
int main()
{
    one_professor a1;
    two_professor a2;
    one_associate_professor b1;
    two_associate_professor b2;
    three_associate_professor b3;
    lecturer c;
    Teacher *t[6] = {&a1, &a2, &b1, &b2, &b3, &c};
    cout << "上述人员的基本信息为: " << endl;
    for(int i = 0; i < 6; i++){
        t[i]->pay();
        t[i]->display();
    }
    return 0;
}