#include<iostream>
using namespace std;
const  double pi = 3.1415926;

class Figure{
public:
	Figure(){
		radius = 0;
	}
	Figure(double R){				//构造函数
		radius = R;
	}
	virtual double area(){			//面积
		return 0.0;
	}
	virtual double volume(){		//体积
		return 0.0;
	}
protected:
	double radius;					//半径
};

class Sphere : public Figure{		//球
public:
	Sphere(){
		radius = 0;
	}
	Sphere(double R){
		radius = R;
	}
	virtual double area(){
		return 4 * pi * radius * radius;
	}
	virtual double volume(){
		return (4 * pi * radius * radius * radius)/3;
	}
};

class Column : public Figure{	//圆柱体
public:
	Column(){
		r = 0;
		h = 0;
	}
	Column(double R, double H){
		r = R;
		h = H;
	}
	virtual double area(){
		return 2 * pi * r * h + 2 * pi * r * r;
	}
	virtual double volume(){
		return pi * r * r * h;
	}
protected:
	double r, h;
};

void output_area(Figure& p){
	cout << p.area() << endl;
}

void output_volume(Figure& p){
	cout << p.volume() << endl;
}

int main()
{
	Sphere s(2);
	output_area(s);
	output_volume(s);
	Column c(2,6);
	output_area(c);
	output_volume(c);
	return 0;
}