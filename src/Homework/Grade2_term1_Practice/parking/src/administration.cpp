//停车场管理
#include <iostream>
#include "../lib/Car.h"			//定义车辆结构体
#include <string>
#include "../lib/Stack_1.h"		//顺式栈(重载了[]运算符，方便查找)
#include "../lib/Queue.h"		//链式队列(重载了[]运算符，方便查找)
using namespace std;
int n;
stack<car> st;
queue<car> que;

void arrive(car& c) {	//到达操作
	if(st.size() < n) {	//停车场没满
		c.number = st.size() + 1;	//编号
		c.pos = 0;	//位置在停车场
		st.push(c);
	}
	else {	//停车场满了
		c.pos = 1;	//位置在便道
		que.push(c);
	}
}

void leave(car& c) {
	for(int i = 0; i < st.size(); i++) {	//找停车场
		if(st[i].ID == c.ID) {
			tm tmp = c.leave_time;
			c = st[i];	c.leave_time = tmp;
		}
	}
	for(int i = 0; i < que.size(); i++) {	//找便道
		if(que[i].ID == c.ID) {
			tm tmp = c.leave_time;
			c = que[i];	c.leave_time = tmp;
		}
	}
	if(c.pos) {	//如果在便道上, 直接离开即可
		que.erase(c);
		cout << "该车(" << "车牌号为: " << c.ID <<  ")离开便道, 不收费" << endl;
	}
	else {	//在停车场
		if(c.number == st.size()) {	//停车场最后面
			st.pop();
			cout << "该车("<< "车牌号为: " << c.ID <<")在停车场停留" << ceil(c()/60.0) << "分钟" << endl;
			cout << "应缴纳" << need_money(c) << "元" << endl;
		}
		else {	//在停车场中间
			queue<car> t;	//辅助队列
			while(st.size() != c.number) {	//后面的车让路
				car x = st.top();	
				x.number -= 1; //后面的车依次前进一个车位
				st.pop();	t.push(x);
			}
			st.pop();
			cout << "该车("<< "车牌号为: " << c.ID <<")在停车场停留" << ceil(c()/60.0) << "分钟" << endl;
			cout << "应缴纳" << need_money(c) << "元" << endl;
			while(!t.empty()) {	//让路的车重新进入停车场
				car x = t.front();
				st.push(x);	t.pop();
			}
			if(st.size() < n && !que.empty()) {	//如果停车场有空位并且便道有车等待
				car x = que.front();
				que.pop();
				x.arrive_time = c.leave_time;	//开始计算收费
				x.number = st.size() + 1;		//车位编号
				x.pos = 0;						//进入停车场
				st.push(x);
			}
		}
	}
}

int main()
{
	cout << "输入狭长通道最大容量: " << endl;
	cin >> n;
	car c;
	while(true) {
		cout << "\n请输入操作(到达或离去)" << endl;
		int flag = add_data(c);
		if(!flag) {	//到达
			arrive(c);
			if(!c.pos)
				cout << "汽车("<< "车牌号为: " << c.ID <<")在停车场的位置为: " << c.number << endl;
			else
				cout << "汽车("<< "车牌号为: " << c.ID <<")停在便道"<< endl;
		}
		else {	//离开
			leave(c);
		}
	}
	return 0;
}