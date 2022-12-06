//链式向前星, 用于存储图
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3 + 10;
#define ll long long
int cnt = 0;    //边的编号
int n, e;   //节点数, 边数

struct Edge
{
    int to;     //边的终点
    int next;   //与这个边的起点相同的上一条边的编号
    int weight;      //权值
}edge[N];
ll head[N]; //haed[i]表示以i为起点的最后一条边的编号

void add_edge(int u, int v, int w) {    //添加边
    edge[cnt].to = v;           //终点
    edge[cnt].weight = w;       //权值
    edge[cnt].next = head[u];   //这个边的起点相同的上一条边的编号
    head[u] = cnt++;            //更新head
}

void travel() {		//遍历函数
    for(int i = 1; i <= n; i++) {   //遍历起点
        cout << "第" << i << "个起点的边:" << endl;
        for(int j = head[i]; j != -1; j = edge[j].next) {   //遍历每个起点的边
            cout << i << " " << edge[j].to << " " << edge[j].weight << endl;
        }
        cout << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    memset(head, -1, sizeof(head));
    cin >> n >> e;
    for(int i = 1; i <= e; i++) {   //初始化
        int from, to ,weight;
        cin >> from >> to >> weight;
        add_edge(from, to, weight);
    }
    travel();
    return 0;
}