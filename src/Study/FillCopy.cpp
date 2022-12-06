/*文件复制*/
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ifstream in ("FillCopy.cpp");
	ofstream out ("FillCopy2.cpp");
	string line;
	while(getline(in,line))
	{
		out << line << '\n';
	}
	return 0;
}