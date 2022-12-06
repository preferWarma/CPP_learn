/*模仿二维数组，使用引用调用和引用返回*/
#include <iostream>
#include <iomanip> //使用setw()
using namespace std;

struct twodim
{
	int r;
	int c;
	float *a;
};

//初始化数组
void get_twodim(twodim &s, int row, int col)
{
	s.r = row;
	s.c = col;
	s.a = new float[row*col]; //用一维数组模仿二维数组
	
}

//返回i行j列的值
float &val(twodim &s, int i, int j)
{
	//按行优先计算
	return s.a[i * s.c + j]; 
}

//释放数组空间
void free_twodim(twodim &s)
{
	delete[] s.a;
}

int main()
{
	twodim s;
	int i, j;
	get_twodim(s, 3, 4);

	for (i = 0; i < 3; i++)
		for (j = 0; j < 4; j++)
			val(s, i, j) = i + j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 4; j++)
			cout << setw(5) << val(s, i, j);

		cout << endl;
	}
	free_twodim(s);
	return 0;
}
