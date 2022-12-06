//C++中元组的使用
#include <bits/stdc++.h>
using namespace std;

int main() 
{
    tuple<int, double, string> a;
	//get<index>(a)获得a的第index + 1个元素
	get<0>(a) = 1;
	get<1>(a) = 5.2;
	get<2>(a) = "元组";
	int x;
	double y;
	string z;
	//tie(argv) = tuple可以将元组中的数据读入到参数中
	tie(x, y ,z) = a;
	cout << x << " " << y << " " << z << endl;
    return 0;
}