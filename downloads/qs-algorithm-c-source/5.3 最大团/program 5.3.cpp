//program 5.3 最大团 
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=105;
int g[maxn][maxn];  //邻接矩阵存储图
bool x[maxn];    //是否将第i个结点加入团中
bool bestx[maxn]; //最优解
int bestn;   //最优值
int cn;   //当前已放入团中的结点数
int n,m;  //结点数，边数

bool place(int t){ //判断是否可以把结点t加入团中
    for(int j=1;j<t;j++){ //结点t与前t-1个结点中被选中的结点是否有相连
        if(x[j]&&g[t][j]==0) //x[j]表示j是被选中的结点,a[t][j]==0表示t和j没有边相连
            return false;
    }
    return true;
}

void backtrack(int t){
    if(t>n){ //到达叶结点
        for(int i=1;i<=n;i++)//记录最优解 
            bestx[i]=x[i];
        bestn=cn;//记录最优值 
        return;
    }
    if(place(t)){ //满足约束条件，进入左子树，即把结点t加入团中
        x[t]=1;
        cn++;
        backtrack(t+1);
        cn--;
    }
    if(cn+n-t>bestn){ //满足限界条件，进入右子树
        x[t]=0;
        backtrack(t+1);
    }
}

int main() {
	int u,v;//边的两端点 
	int t;//测试用例数 
	cin>>t;
	while(t--){
    	cin>>n>>m;
		memset(g,0,sizeof(g));
		for(int i=1;i<=m;i++){
        	cin>>u>>v;
        	g[u][v]=g[v][u]=1;
    	}
	    cn=0,bestn=0;
	    backtrack(1);
	    cout<<bestn<<endl;
    }
    return 0;
}
/*测试数据 
2
5 8
1 2
1 3
1 4
1 5
2 3
3 4
3 5
4 5
4 5
1 2
1 4
2 3
2 4
3 4
*/
