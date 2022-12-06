/*
	解9*9数独
*/
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        dfs(board);
    }
private:
    bool dfs(vector<vector<char>>& board) {
        for(int i = 0; i < board.size(); i++) {      		//遍历行
            for(int j = 0; j < board[0].size(); j++) {   	//遍历列
                if(board[i][j] == '.') {            		//如果此处空着
                    for(char k = '1'; k <= '9'; k++ ) {   	//试数
                        if(isVaild(board, i, j, k)) {
                            board[i][j] = k;    			//填数
                        if(dfs(board)) {
                            return true;    				//找到一种解法就可以了
                        }
                        board[i][j] = '.';  				//回溯
                    }
                }
                return false;           					//如果九个数都不行，说明数独无解
                }
                
            }
        }
        return true;
    }
    
    bool isVaild(vector<vector<char>>& board, int row, int col, char val) {
        //判断行是否有重复数
        for(int j = 0; j < 9; j++){
            if(board[row][j] == val)
                return false;
        }
        //判断列是否有重复数
        for(int i = 0; i < 9; i++) {
            if(board[i][col] == val)
                return false;
        }
        //判断九宫格是否有重复数
        int start_row = (row / 3) * 3;
        int start_col = (col / 3) * 3;
        for(int i = start_row; i < start_row + 3; i++) {
            for(int j = start_col; j < start_col + 3; j++) {
                if(board[i][j] == val)
                    return false;
            }
        }
        return true;
    }
};

int main() {
	vector<vector<char>> board = {
		{'5','3','.','.','7','.','.','.','.'},
		{'6','.','.','1','9','5','.','.','.'},
		{'.','9','8','.','.','.','.','6','.'},
		{'8','.','.','.','6','.','.','.','3'},
		{'4','.','.','8','.','3','.','.','1'},
		{'7','.','.','.','2','.','.','.','6'},
		{'.','6','.','.','.','.','2','8','.'},
		{'.','.','.','4','1','9','.','.','5'},
		{'.','.','.','.','8','.','.','7','9'} };
	Solution res;
	res.solveSudoku(board);
	int row = 0;
	for(vector<char>& s : board)	{							//每一行
		for(int col = 0; col < s.size(); col++) {				//每一个
			 cout << s[col] << " ";
			 if(col < 8 && (col + 1) % 3 == 0)
			 	cout << "| ";
		}
		cout << endl;
		if(row < 8 && (1 + row++) % 3 == 0) {
			cout << "—————   —————   ————— " << endl;
		}
	}
	return 0;
}