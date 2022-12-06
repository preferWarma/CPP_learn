/*
N皇后问题:
			如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
皇后们的约束条件：
			不能同行,不能同列,不能同斜线。
*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<string> chess(n, string(n, '.'));
        dfs(n, chess, 0);
        return result;
    }

private:
    vector<vector<string>> result;
    void dfs(int n, vector<string>& chess, int row){
        if(row == chess.size()){
            result.push_back(chess);
            return;
        }
        for(int col = 0; col < n; col++){
            if(isVaild(n, chess, row, col)){   	//判断是否可放皇后
                chess[row][col] = 'Q';      	//放置皇后
                dfs(n, chess, row + 1);
                chess[row][col] = '.';      	//回溯
            }
        }
    }
    bool isVaild(int n, const vector<string>& chess, int row, int col){
        //判断列
        for(int i = 0; i < row; i++) {
            if(chess[i][col] == 'Q')
                return false;
        }
        //判断45度角
        for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if(chess[i][j] == 'Q')
                return false;
        }
        //判断135度角
        for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if(chess[i][j] == 'Q')
                return false;
        }
        return true;
    }
};

int main(){
	int n;
	cout << "请输入N皇后问题中的n: ";
	cin >> n;
	Solution s;
	vector<vector<string>> res = s.solveNQueens(n);
	cout << "总共有" << res.size() << "种解法" << endl;
	for(vector<string>& r : res){	//r表示每种解法
		for(string& s : r){			//s表示解法的每一行
			for(char c : s){		//c表示每一个棋子, '.'为空, 'Q'为皇后
				cout << c << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}