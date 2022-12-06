/*类的继承*/
#include<iostream>
#include<string.h>
using namespace std;

class Animal
{
public:
	string mouth;
	
	void eat();
	void sleep();
	void drink();
};

class Pig : public Animal
{
public:
	void climb();
	void eat();
};

class Turtle : public Animal
{
public:
	void swim();
};

void Animal::eat()
{
	cout << "I am eating !" << endl;
}

void Animal::sleep()
{
	cout << "I am sleeping ,don't disturb me !" << endl;
}

void Animal::drink()
{
	cout << "I am drinking,water is my life" << endl;
}

void Pig::climb()
{
	cout << "猪急了会上树" << endl;
}

void Turtle::swim()
{
	cout << "乌龟会游泳" << endl;
}

void Pig::eat()
{
	//Animal::eat();
	cout << "猪吃的多" << endl;
}

int main()
{
	Pig pig;
	Turtle turtle;
	pig.eat();
	pig.climb();
	turtle.eat();
	turtle.swim();

	return 0;
}