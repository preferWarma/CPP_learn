//停车场管理
#include<iostream>
#include<cstdio>
#include<string>
#include<cmath>
#include<ctime>	//计算时间差
using namespace std;
const double price = 5;	//5元每小时

struct car {	//定义结构体存储汽车信息
	tm arrive_time;	//到达时间(格式xxxx-xx-xx-xx-xx)(24进制)精确到分钟
	tm leave_time;	//离去时间(格式xxxx-xx-xx-xx-xx)(24进制)精确到分钟
	string ID;		//车牌号
	int number;		//停车位编号(从1开始取)
	int pos;		//为0表示在停车场，为1表示在便道

	double operator()(){	//返回停留时间(单位: 秒)
		time_t time_1 = mktime(&arrive_time);
		time_t time_2 = mktime(&leave_time);
		return difftime(time_2, time_1);
	}
	bool operator == (car& c){
		if(this->ID == c.ID)
			return true;
		else
			return false;
	}
};

tm add_time() {
	tm info = {0};
	cout << "请输入时间信息: (格式xxxx-xx-xx-xx-xx)(24进制)精确到分钟: " << endl;
	scanf("%d-%d-%d-%d-%d",&info.tm_year, &info.tm_mon, &info.tm_mday, &info.tm_hour, &info.tm_min);
	info.tm_min -= 1;	info.tm_hour -= 1;	info.tm_mon -= 1;	//标准化
	info.tm_year -= 1900;	//标准化
	return info;
}

int add_data(car& c) {	//返回0为到达，返回1为离去
	string information;	cin >> information;
	cout << "请输入车牌号: " << endl;
	cin >> c.ID;
	if(information == "到达")
		c.arrive_time = add_time();
	else
		c.leave_time = add_time();
	return information == "离去";
}

double need_money(car& c) {
	return price * ceil(c() / 3600.0);
}