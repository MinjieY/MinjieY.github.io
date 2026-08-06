//program 6.2 01背包 优先队列bfs AC 3ms
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int maxn=105;
int n; //物品数量
double W; //背包容量
double w[maxn],v[maxn];//w[i]表示第i个物品的重量，v[i]表示第i个物品的价值
double a[maxn],b[maxn];//辅助数组
double bestp,sumv; //当前重量，当前价值，最优值，总价值  
bool bestx[maxn];  //最优解

struct goods{//定义物品结构体，包含物品序号和单位重量价值
    int idx;
	double p;//单位重量价值
}g[maxn];

bool cmp(goods a1,goods a2){//按照物品单位重量价值由大到小排序
    return a1.p>a2.p;
}

struct node{
    double cp,up; //cp当前放入背包的物品价值，up=cp+brp
    double rw; //剩余容量
    int id; //物品号
    node() {}
    node(double _cp,double _up,double _rw,int _id){
        cp=_cp;
        up=_up;
        rw=_rw;
        id=_id;
    }
};

bool operator <(const node &a, const node &b){//队列的优先级，up越大越优先
    return a.up<b.up;
}

double bound(int i,double cleft){//计算brp，剩余物品装满剩余容量获得的最大价值 
    double brp=0.0;
	while(i<=n&&a[i]<cleft){
        cleft-=a[i];//排序后的物品重量 
        brp+=b[i];//排序后的物品价值 
        i++;
    }
    if(i<=n)//通过切割装满背包
        brp+=b[i]/a[i]*cleft;
    return brp;
}

void knapsack_prioritybfs(){
    priority_queue<node> q; //创建一个优先队列,优先级为装入购物车的物品价值上界up
    q.push(node(0,bound(1,W),W,1)); //根结点入队 
    while(!q.empty()){ //如果队列不空
        node cur,lc,rc;//定义三个结点型变量
        cur=q.top();//取出队头元素
        q.pop(); //队头元素出队
        cout<<cur.cp<<" "<<cur.up<<" "<<cur.rw<<" "<<cur.id<<endl;
        int t=cur.id;//当前物品序号
        if(t>n) continue;
        if(cur.up<bestp) continue;
        if(a[t]<=cur.rw){ //满足约束条件，可以放入
			lc=node(cur.cp+b[t],cur.up,cur.rw-a[t],t+1);//生成左孩子 
            if(lc.cp>bestp)//比最优值大更新
            	bestp=lc.cp;
            q.push(lc);//左孩子入队
        }
        double up=cur.cp+bound(t+1,cur.rw);
        if(up>bestp){//满足限界条件
            rc=node(cur.cp,up,cur.rw,t+1);//生成右孩子 
            q.push(rc);//右孩子入队
        }
    }
}

int main(){
    int t;//t表示测试用例数 
    cin>>t;
    while(t--){
	    cin>>n>>W;
	    bestp=0.0;
	    for(int i=1;i<=n;i++){
	    	cin>>w[i]>>v[i];
	    	g[i].idx=i;
	    	g[i].p=v[i]/w[i];
		}
		sort(g+1,g+n+1,cmp);
		for(int i=1;i<=n;i++){//把排序后的数据传递过去
        	a[i]=w[g[i].idx];//a[]为排序后的物品重量
        	b[i]=v[g[i].idx];//b[]为排序后的物品价值
    	}
	    knapsack_prioritybfs();
	    cout<<bestp<<endl;
    }
    return 0;
}
/*测试数据 
1
4 10
2 6
5 3
4 5
2 4
*/
