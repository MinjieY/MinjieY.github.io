//program 4.8 01背包 
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=105;
const int maxw=10005;
int c[maxn][maxw];//c[i][j]表示前i个物品放入容量为j的背包获得的最大价值
int w[maxn],v[maxn];//w[i]表示第i个物品的重量，v[i]表示第i个物品的价值
bool x[maxn]; //x[i]表示第i个物品是否放入背包

int knapsack(int n,int W){
    for(int i=1;i<=n;i++){//计算c[i][j]
        for(int j=1;j<=W;j++){
        	if(j<w[i])  //当物品的重量大于背包的容量，则不放此物品
                c[i][j]=c[i-1][j];
            else    //否则比较此物品放与不放哪种情况使得背包内的价值最大
                c[i][j]=max(c[i-1][j],c[i-1][j-w[i]]+v[i]);
		} 
	}
    return c[n][W];
}

void print(int n,int W){//逆向构造最优解
    int j=W;
    for(int i=n;i>0;i--){
    	if(c[i][j]>c[i-1][j]){
            x[i]=1;
            j-=w[i];
        }
        else
            x[i]=0;
	}
    cout<<"装入背包的物品序号为:";
    for(int i=1;i<=n;i++){
    	if(x[i])
           cout<<i<<"  ";
	}  
    cout<<endl; 
}

int main(){
    int n,W,t;//n表示n个物品，W表示背包的容量，t表示测试用例数 
    cin>>t;
    while(t--){
	    cin>>n>>W;
	    for(int i=1;i<=n;i++)
	        cin>>w[i]>>v[i];
	    for(int i=1;i<=n;i++)//初始化第0列为0
        	c[i][0]=0;
    	for(int j=1;j<=W;j++)//初始化第0行为0
        	c[0][j]=0;
	    cout<<knapsack(n,W)<<endl;
	    //print(n,W);
    }
    return 0;
}
/*测试数据 
2
5 10
2 6
5 3
4 5
2 4
3 6
4 52
12 13
10 24
22 13
9 24
*/
