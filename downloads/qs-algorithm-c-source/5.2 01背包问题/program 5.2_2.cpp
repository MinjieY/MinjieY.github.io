//program 5.2 01背包 上界优化 
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=105;
int n; //物品数量
double W; //背包容量
double w[maxn],v[maxn];//w[i]表示第i个物品的重量，v[i]表示第i个物品的价值
double a[maxn],b[maxn];//辅助数组
double cw,cp,bestp; //当前重量，当前价值，最优值
bool x[maxn];  //x[i]表示第i个物品是否放入背包
bool bestx[maxn];  //最优解

struct node{//定义物品结构体，包含物品序号和单位重量价值
    int id; //物品序号
    double p;//单位重量价值
}q[maxn];

bool cmp(node a1,node a2){//按照物品单位重量价值由大到小排序
    return a1.p>a2.p;
}

double bound(int i){//计算上界（已装入物品价值+剩余物品(第i~n种物品)装满剩余容量获得的最大价值）  
    double cleft=W-cw;//剩余容量
    double brp=0.0;
    while(i<=n&&a[i]<cleft){
        cleft-=a[i];
        brp+=b[i];
        i++;
    }
    if(i<=n)//通过切割装满背包
        brp+=b[i]/a[i]*cleft;
    return cp+brp;
}

void backtrack(int t){//回溯法，t为层次 
    if(t>n){//到达叶子
        for(int j=1;j<=n;j++)//记录最优解 
            bestx[j]=x[j];
        bestp=cp;//记录最优值 
        return ;
    }
    if(cw+a[t]<=W){//如果满足约束条件，搜索左子树
        x[t]=1;
        cw+=a[t];
        cp+=b[t];
        backtrack(t+1);
        cw-=a[t];//还原现场 
        cp-=b[t];
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
}

int main(){
    int t;//t表示测试用例数
    cin>>t;
    while(t--){
	    cin>>n>>W;
	    for(int i=1;i<=n;i++){
	    	cin>>w[i]>>v[i];
	    	q[i].id=i;
	    	q[i].p=v[i]/w[i];
		}
		sort(q+1,q+n+1,cmp);
		for(int i=1;i<=n;i++){//把排序后的数据传递过去
        	a[i]=w[q[i].id];//a[]为排序后的物品重量
        	b[i]=v[q[i].id];//b[]为排序后的物品价值
    	}
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
