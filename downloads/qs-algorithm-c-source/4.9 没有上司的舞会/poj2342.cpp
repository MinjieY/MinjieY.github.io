#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int N=6000+10;
int val[N],dp[N][2],fa[N],n;
vector<int>E[N];

void dfs(int u){
	dp[u][0]=0;//初始化
	dp[u][1]=val[u];//初始化
	for(int i=0;i<E[u].size();i++){//求解u的所有子节点v
		int v=E[u][i];
		dfs(v);//递归求解v为根的子树
		dp[u][0]+=max(dp[v][1],dp[v][0]);//递归返回时，状态转移
		dp[u][1]+=dp[v][0];
	}
}

int main(){
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++){
			scanf("%d",&val[i]);
			E[i].clear();
			fa[i]=-1;
		}
		int a,b;
		while(scanf("%d%d",&a,&b)){
	        if(a==0&&b==0) break;
	        E[b].push_back(a);//b是a的直接上司，因此a是b的子节点，a存储到E[b]中
	        fa[a]=b; //a父节点是b
		}
	    int root=1;
	    while(fa[root]!=-1) root=fa[root];//找到树根root 
	    dfs(root);
	    printf("%d\n",max(dp[root][1],dp[root][0]));
    }
    return 0;
}
