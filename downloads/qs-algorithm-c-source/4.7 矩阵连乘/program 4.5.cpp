//program 4.7 矩阵连乘 
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=105;
const int inf=0x3f3f3f3f;
int p[maxn],m[maxn][maxn],s[maxn][maxn];

int matrixchain(int n){ //求最优值 
    memset(m,0,sizeof(m));
    memset(s,0,sizeof(s));
    for(int d=2;d<=n;d++){ //问题规模d
        for(int i=1;i<=n-d+1;i++){ //区间起点 
        	int j=i+d-1; //区间终点
        	m[i][j]=inf; //初始化为无穷大，后面需要找最小值 
        	for(int k=i;k<j;k++){ //枚举从i到j-1的所有决策，求最优值，记录最优策略
                int temp=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
                if(temp<m[i][j]){
                    m[i][j]=temp;
                    s[i][j]=k;
                }
            }
        }
    }
    return m[1][n];
}

void print(int i,int j){ //构造最优解 
    if(i==j){
       cout<<"A["<<i<<"]";
       return ;
    }
    cout<<"(";
    print(i,s[i][j]);
    print(s[i][j]+1,j);
    cout<<")";
}

int main(){
    int t,n; //测试用例数，矩阵个数 
    cin>>t;
    while(t--){
    	cin>>n;
    	for(int i=0;i<=n;i++)
        	cin>>p[i];
    	cout<<matrixchain(n)<<endl;
    	//print(1,n);
		//cout<<endl;
    }
    return 0;
}
/*测试数据
2
5
3 5 10 8 2 4
8
4 8 12 7 9 30 4 65 52
*/ 
