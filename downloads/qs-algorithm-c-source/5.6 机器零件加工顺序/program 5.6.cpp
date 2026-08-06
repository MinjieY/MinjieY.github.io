//program 5.6 机器零件加工顺序 
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=105;
const int inf=0x3f3f3f3f;
int n,bestf,f1,f2;//f1在第一台机器上加工的完成时间,f2在第二台机器上加工的完成时间
int x[maxn],bestx[maxn]; //x[i]表示第i个皇后放置在第i行第x[i]列

struct node{
    int x,y;//机器零件在第一台机器上的加工时间x和第二台机器上的加工时间y
}T[maxn];

void backtrack(int t){
    if(t>n){
        for(int i=1;i<=n;i++) //记录最优解 
        	bestx[i]=x[i];
        bestf=f2;   //记录最优值
        return ;
    }
    for(int i=t;i<=n;i++){//排列树
        f1+=T[x[i]].x;
        int temp=f2;
        f2=max(f1,f2)+T[x[i]].y;
        if(f2<bestf){  //限界条件
            swap(x[t],x[i]);  //交换
            backtrack(t+1);   //继续深搜
            swap(x[t],x[i]);  //还原现场，复位反操作
        }
        f1-=T[x[i]].x;//还原现场
        f2=temp;
    }
}

void print(){
	cout<<"最优机器零件加工顺序:";
    for(int i=1;i<=n;i++) //输出最优加工顺序
    	cout<<bestx[i]<<" ";
    cout<<endl;
}

int main(){
    int t;//测试用例数 
    cin>>t;
    while(t--){
		cin>>n;
	    for(int i=1;i<=n;i++){
	        cin>>T[i].x>>T[i].y;
	        x[i]=i;
	    }
    	bestf=inf; //初始化为无穷大 
    	f1=f2=0;
    	memset(bestx,0,sizeof(bestx));
    	backtrack(1);         // 深搜排列树
    	cout<<bestf<<endl;
    	//print();
    }
    return 0 ;
}
/*测试数据 
2
6
5 7
1 2
8 2
5 4
3 7
4 4
7
3 7
8 2
10 6
12 18
6 3
9 10
15 4
*/
