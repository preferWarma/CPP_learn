/*设计和实现整型集合类*/
/*	
添加构造函数完成初始化
能添加一个元素，元素不重复
能删除一个元素
输出所有元素
求两个集合对象的交集
求两个集合对象的并集
求两个集合对象的差集
*/
#include<iostream>
#include<vector>
using namespace std;

class set
{
public:
	set(){										//初始化构造函数
	}
	set(const vector<int> nums){				//初始化构造函数
		num = nums;
	}
	set(const set& s){							//复制构造函数
		num = s.num;
	}
	void add(int a){							//添加一个不重复的元素
		int flag = 0;
		for(int i = 0; i < num.size(); i++){
			if(num[i] == a)
				flag = 1;
		}
		if(!flag)
			num.push_back(a);
	}
	void erase(int a){							//删除指定元素
		for(int i = 0; i < num.size(); i++){
			if(num[i] == a){
				for(int j = i; j < num.size() - 1; j++){
					num[j] = num[j+1];
				}
				num.resize(num.size()-1);
				return;
			}
		}
		return;
	}
	void print(){
		for(int a : num)
			cout << a << " ";
		cout << endl;
	}
	set operator &(const set num2){					//重载运算符'&'表示交集
		set result;
		for(int a : num){
			for(int b : num2.num){
				if(a==b)
					result.add(a);
			}
		}
		return result;
	}
	set operator +(const set num2){					//重载运算符'+'表示并集
		set result(num);
		for(int a : num2.num){
			result.add(a);
		}
		return result;
	}
	set operator -(const set num2){					//重载运算符'-'表示差集
		set result(num);
		set t = (*this & num2);
		for(int a : t.num){
			result.erase(a);
		}
		return result;
	}
private:
	vector<int> num;
};

int main()
{
	set s1({1,2,3,4,5});
	set s2({4,5,6,7,8});
	set s3 = (s1 + s2);		//s3 = 1,2,3,4,5,6,7,8
	s3.print();
	set s4 = (s1 & s2);		//s4 = 4,5
	s4.print();
	set s5 = (s1 - s2);		//s5 = 1,2,3
	s5.print();
	return 0;
}