#include <iostream>
#include <string>
#include <ctime>
#include <iomanip> //控制域宽
using namespace std;

class Date
{
public:
	Date(){
		time_t t1 = time(0);
		tm *t = localtime(&t1);
		year = t->tm_year + 1900;
		month = t->tm_mon + 1;
		day = t->tm_mday;
	}
	Date(int y, int m, int d){
		year = y;
		month = m;
		day = d;
	}
	void print()
	{
		cout << setw(2) << setfill('0') << month << "-" << setw(2) << setfill('0') << day << "-" << year << endl;
	}

protected:
	int year; 			//当前年
	int month;	  		//当前月
	int day;		    //当前日
};

class ShortE : public Date
{
public:
	ShortE(){
	}
	ShortE(int y, int m, int d){
		year = y;
		month = m;
		day = d;
	}
	void print()
	{
		cout << setw(2) << setfill('0') << day << "-" << setw(2) << setfill('0') << month << "-" << year << endl;
	}
};

class MediumDate : public Date
{
public:
	MediumDate(){
	}
	MediumDate(int y, int m, int d){
		year = y;
		month = m;
		day = d;
	}
	void print()
	{
		const string m1[12] = {"Jan.", "Feb.", "Mar.", "Apr.", "May.", "Jun.", "Jul.", "Aug.", "Sept.", "Oct.", "Nov.", "Dec."};
		cout << m1[month - 1] << setw(2) << setfill('0') << day << "," << year << endl;
	}
};

class LongDate : public Date
{
public:
	LongDate(){
	}
	LongDate(int y, int m, int d){
		year = y;
		month = m;
		day = d;
	}
	void print()
	{
		const string m2[12] = {"January", "february", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
		cout << m2[month - 1] << " " << setw(2) << setfill('0') << day << ", " << year << endl;
	}
};

int main()
{
	Date d1(2002,11,3);
	d1.print();
	ShortE d2(2020,7,6);
	d2.print();
	MediumDate d3;
	d3.print();
	LongDate d4(2024,6,1);
	d4.print();
	return 0;
}