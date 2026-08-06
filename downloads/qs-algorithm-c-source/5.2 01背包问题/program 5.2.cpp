//program 5.2 01背包 
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=105;
int n; //物品数量
double W; //背包容量
double w[maxn],v[maxn];//w[i]表示第i个物品的重量，v[i]表示第i个物品的价值
double cw,cp,bestp; //当前重量，当前价值，最优值
bool x[maxn];  //x[i]表示第i个物品是否放入背包
bool bestx[maxn];  //最优解

double bound(int i){//计算上界（已装入物品价值+剩余物品(第i~n种物品)的总价值）
    double rp=0;
    while(i<=n){//依次计算剩余物品的价值
        rp+=v[i];
        i++;
    }
    return cp+rp;
}

void backtrack(int t){//回溯法，t为层次 
    if(t>n){//到达叶子
        for(int j=1;j<=n;j++)//记录最优解 
            bestx[j]=x[j];
        bestp=cp;//记录最优值 
        return ;
    }
    if(cw+w[t]<=W){//如果满足约束条件，搜索左子树
        x[t]=1;
        cw+=w[t];
        cp+=v[t];
        backtrack(t+1);
        cw-=w[t];//还原现场 
        cp-=v[t];
    }
    if(bound(t+1)>bestp){//如果满足限界条件，搜索右子树
        x[t]=0;
        backtrack(t+1);
    }
}

int knapsack(){
    cw=0.0,cp=0.0,bestp=0.0; //当前放入背包的物品重量，价值，最优值
    backtrack(1);
    cout<<bestp<<endl;
//    for(int i=1;i<=n;i++){ //输出最优解
//        if(bestx[i]==1)
//    		cout<<i<<" ";
//    }
//	cout<<endl;
}

int main(){
    int t;//t表示测试用例数 
    cin>>t;
    while(t--){
	    cin>>n>>W;
	    for(int i=1;i<=n;i++)
	        cin>>w[i]>>v[i];
	    knapsack();
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
