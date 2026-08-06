//program 6.2 01背包 普通队列bfs AC 831ms 
#include<iostream>
#include<queue>
using namespace std;
const int maxn=105;
int n; //物品数量
double W; //背包容量
double w[maxn],v[maxn];//w[i]表示第i个物品的重量，v[i]表示第i个物品的价值
double bestp,sumv; //当前重量，当前价值，最优值，总价值  
bool bestx[maxn];  //最优解

struct node{
    double cp,rp; //cp当前放入背包的物品价值，rp剩余物品的价值
    double rw; //剩余容量
    int id; //物品号
    node() {}
    node(double _cp,double _rp,double _rw,int _id){
        cp=_cp;
        rp=_rp;
        rw=_rw;
        id=_id;
    }
};

void knapsack_bfs(){
    queue<node> q; //创建一个普通队列(先进先出)
    q.push(node(0,sumv,W,1)); //根结点入队 
    while(!q.empty()){ //如果队列不空
        node cur,lc,rc;//定义三个结点型变量
        cur=q.front();//取出队头元素
        q.pop(); //队头元素出队
//        cout<<cur.cp<<" "<<cur.rp<<" "<<cur.rw<<" "<<cur.id<<endl;
        int t=cur.id;//当前物品序号
        if(t>n) continue;
		if(cur.cp+cur.rp<bestp) continue;
		int cp=cur.cp;
		int rp=cur.rp-v[t];
        if(w[t]<=cur.rw){ //满足约束条件，可以放入
            lc=node(cp+v[t],rp,cur.rw-w[t],t+1);//生成左孩子 
            if(lc.cp>bestp)//比最优值大更新
            	bestp=lc.cp;
            q.push(lc);//左孩子入队
        }
        if(cp+rp>bestp){//满足限界条件
            rc=node(cp,rp,cur.rw,t+1);//生成右孩子 
            q.push(rc);//右孩子入队
        }
    }
}

int main(){
    int t;//t表示测试用例数 
    cin>>t;
    while(t--){
	    cin>>n>>W;
	    bestp=0.0,sumv=0.0; //sumv为所有物品的总价值
	    for(int i=1;i<=n;i++){
	    	cin>>w[i]>>v[i];
	    	sumv+=v[i];
		} 
	    knapsack_bfs();
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
