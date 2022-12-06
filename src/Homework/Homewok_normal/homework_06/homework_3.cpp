/*扑克牌类的设计*/
#include<iostream>
#include<cstdlib>
using namespace std;
class card
{
public:
	int value;			//大小
	char huase;			//花色
};

class cardgame
{
public:
	cardgame();		//构造函数
	void shuffle();	//随即洗牌
	void print();		//输出
private:
	card a[54];
};

int main()
{
	cardgame pai;
	cout << "----------------洗牌前----------------" << endl;
	pai.print();
	pai.shuffle();
	cout << "\n----------------洗牌后----------------" << endl;
	pai.print();
	return 0;
}

cardgame::cardgame(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 13; j++){
			a[i*13 + j].value = j + 1;
			a[i*13 + j].huase = i + 3;
		}
	}
	a[52].value = 99;		//小王大小
	a[52].huase = 1;		//小王花色
	a[53].value = 99;		//大王花色
	a[53].huase = 1;		//大王花色
}

void cardgame::shuffle(){
	for(int i = 0; i < 54; i++)
	{
		int r1 = rand() % 54;
		int r2 = rand() % 54;
		if(r1 != r2){
			swap(a[r1], a[r2]);		//如果两个随机数不相同，则交换
		}
	}
}

void cardgame::print(){
	for(int i = 0; i < 54; i++){
		cout << a[i].value << ": " << a[i].huase << "\t";
		if((i + 1) % 13 == 0)
			cout << endl;
	}
}
