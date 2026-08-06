#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=100+5;
const int inf=0x3f3f3f3f;
int dp[maxn][maxn],p[maxn];

int solve(int n){
    for(int d=2;d<=n;d++){//区间长度d 
        for(int i=1;i<=n-d+1;i++){//状态起点i，终点j 
            int j=i+d-1;
            dp[i][j]=inf;
            for(int k=i;k<j;k++)//枚举决策点k 
                dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]+p[i-1]*p[k]*p[j]);
        }
    }
    return dp[1][n];
}

int main(){
    int n; 
	scanf("%d",&n);
    memset(dp,0,sizeof(dp));
    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);
    printf("%d\n",solve(n-1));//矩阵n-1个 
    return 0;
}
