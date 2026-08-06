//program 6.3 旅行商问题 优先队列式分支限界法 
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int inf=1e7;
const int N=105;
int g[N][N];
int bestx[N]; //当前最优路径
int bestl; //当前最短路径长度
int n,m;  //结点数,边数

struct node{
    int cl; //当前已走过的路径长度
    int id; //当前序号
    int x[N];//当前路径
    node() {}
    node(int _cl,int _id){
        cl=_cl;
        id=_id;
    }
};

bool operator <(const node &a, const node &b){//优先队列的优先级,cl值越小越优先
    return a.cl>b.cl;
}

void traveling_prioritybfs(){//优先队列式分支限界法
    priority_queue<node> q; //创建一个优先队列
    node newnode=node(0,2);//创建根节点
    for(int i=1;i<=n;i++)
    	newnode.x[i]=i; //初时化新结点解向量
    q.push(newnode);//根结点入队
    while(!q.empty()){
        node cur=q.top();//取队头
        q.pop(); //队头出队
        int t=cur.id;//当前处理的序号
        if(t==n){//搜到倒数第2个结点时,判断是否更新最优解，
            //例如当前找到一个路径(1243)，到达4号结点时，立即判断g[4][3]和g[3][1]是否有边相连，
            //如果cl+g[4][3]+g[3][1]<bestl，则更新最优值和最优解
        	if(cur.cl+g[cur.x[n-1]][cur.x[n]]+g[cur.x[n]][1]<bestl){
            	bestl=cur.cl+g[cur.x[n-1]][cur.x[n]]+g[cur.x[n]][1];
                for(int i=1;i<=n;i++)
                	bestx[i]=cur.x[i];
        	}
            continue;
        }
    	if(cur.cl>=bestl)//判断当前结点是否满足限界条件，如果不满足不再扩展
        	continue;
        for(int j=t;j<=n;j++){//排列树 
            if(g[cur.x[t-1]][cur.x[j]]!=inf){//如果x[t-1]与x[j]有边相连
                int cl=cur.cl+g[cur.x[t-1]][cur.x[j]];
                if(cl<bestl){//有可能得到更短的路线
                    newnode=node(cl,t+1);
                    for(int i=1;i<=n;i++)
                    	newnode.x[i]=cur.x[i];//复制以前的解向量
                    swap(newnode.x[t],newnode.x[j]);//交换x[t]、x[j]两个元素的值
                    q.push(newnode);//新结点入队
                }
            }
        }
    }
}

void init(){//初始化
    bestl=inf;
    memset(g,0x3f,sizeof(g));
    memset(bestx,0,sizeof(bestx));
}

void print(){//打印路径
    cout<<"最短路径:  ";
    for(int i=1;i<=n;i++)
        cout<<bestx[i]<<"-->";
    cout<<"1"<<endl;
}

int main(){
    int t;//测试用例数 
	int u,v,w;//u,v代表结点，w代表u和v之间路的长度;
    cin>>t;
    while(t--){
    	cin>>n>>m;
    	init();
	    for(int i=1;i<=m;i++){
	        cin>>u>>v>>w;
	        g[u][v]=g[v][u]=w;
	    }
    	traveling_prioritybfs();
    	cout<<bestl<<endl;
//    	print();
    }
    return 0;
}
/*测试数据
1
4 6
1 2 15
1 3 30
1 4 5
2 3 6
2 4 12
3 4 3
*/ 
