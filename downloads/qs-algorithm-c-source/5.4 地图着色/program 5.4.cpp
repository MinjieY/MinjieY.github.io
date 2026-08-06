//program 5.4 地图着色 
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=105;
int g[maxn][maxn]; //邻接矩阵存储图
int x[maxn]; //是否将第i个结点的色号
int sum;   //记录解的个数
int n,e,m;  //结点数，边数，颜色数

bool check(int t){//约束条件
    for(int j=1;j<t;j++){
        if(g[t][j]&&x[j]==x[t]) //如果t与j邻接且色号是否相同
            return false;
    }
    return true;
}

void backtrack(int t){
    if(t>n){//到达叶子,找到一个着色方案
        sum++;
//        cout<<"第"<<sum<<"种方案：";
//        for(int i=1;i<=n;i++) //输出该着色方案
//            cout<<x[i]<<" ";
//        cout<<endl;
		return ;
    }
    for(int i=1;i<=m;i++){ //每个结点尝试m种颜色
        x[t]=i; //第t个结点涂第i种颜色 
        if(check(t))
            backtrack(t+1);
    }
}

int main(){
	int u,v;//边的两端点 
	int t;//测试用例数 
	cin>>t;
	while(t--){
    	cin>>n>>m>>e;//结点数，颜色数，边数 
		memset(g,0,sizeof(g));
		for(int i=1;i<=e;i++){
        	cin>>u>>v;
        	g[u][v]=g[v][u]=1;
    	}
	    sum=0;
	    backtrack(1);
	    cout<<sum<<endl;
    }
    return 0;
}
/*测试数据 
2
7 3
12
1 2
1 3
1 4
2 3
2 5
3 4
3 5
4 5
4 7
5 6
5 7
6 7
5 4
8
1 2
1 3
2 3
2 4
2 5
3 4
3 5
4 5
*/
