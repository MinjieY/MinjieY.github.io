#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100;
const int M=10000;
int cnt,d;
int head[N],pre[N];
bool vis[N];
struct Edge{
   int v,next;
   int cap,flow;
}E[M];
int n,m;

void init(){//初始化 
    memset(head,-1,sizeof(head));
    cnt=0;
}

void add(int u,int v,int c){
    E[cnt].v=v;
    E[cnt].cap=c;
    E[cnt].flow=0;
    E[cnt].next=head[u];
    head[u]=cnt++;
}

void printg(){//输出网络
	cout<<endl;
	cout<<"----------网络（链式前向星）：----------"<<endl;
	for(int i=1;i<=n;i++){
		cout<<"v"<<i<<"  ["<<head[i];
		for(int j=head[i];~j;j=E[j].next)
			cout<<"]--["<<E[j].v<<"\t"<<E[j].cap<<"\t"<<E[j].flow<<"\t"<<E[j].next;
		cout<<"]"<<endl;
   }
   cout<<endl;
}

bool bfs(int s,int t){
    memset(pre,-1,sizeof(pre));
    memset(vis,0,sizeof(vis));
    queue<int>q;
    vis[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];~i;i=E[i].next){
        	int v=E[i].v;
        	if(!vis[v]&&E[i].cap>E[i].flow){
                vis[v]=1;
                pre[v]=i;//边下标 
				q.push(v);
				if(v==t) return 1;//找到一条可增广路
			}	
		}
    }
    return 0;
}

int EK(int s,int t){
    int maxflow=0;
    while(bfs(s,t)){//可以增广
		int d=inf,v=t;
        while(v!=s){//找最小增量
            int i=pre[v];
			d=min(d,E[i].cap-E[i].flow);
			v=E[i^1].v;
        }
        maxflow+=d;
        cout<<"增广路径： "<<t; 
        v=t;
        while(v!=s){//沿可增广路增流
            int i=pre[v];
			E[i].flow+=d;
			E[i^1].flow-=d;
			v=E[i^1].v;
			cout<<"--"<<v; 
        }
        cout<<"\t增流："<<d<<endl;
        printg();//输出网络
    }
    cout<<endl<<"网络的最大流值: "<<maxflow<<endl;
    return maxflow;
}

void printflow(){//输出实流边
	cout<<endl;
	cout<<"----------实流边：----------"<<endl;
	for(int i=1;i<=n;i++)
		for(int j=head[i];~j;j=E[j].next)
			if(E[j].flow>0){
				cout<<"v"<<i<<"--"<<"v"<<E[j].v<<"\t"<<E[j].flow;
				cout<<endl;
        	}
}

int main(){
    int u,v,w;
    cout<<"请输入结点个数n和边数m:"<<endl;
    cin>>n>>m;
    init();
    cout<<"请输入两个结点u,v及边(u--v)的容量w:"<<endl;
    for(int i=1;i<=m;i++){
        cin>>u>>v>>w;
        add(u,v,w);
		add(v,u,0);
    }
    printg();//输出初始网络
    EK(1,n);
    printg();//输出最终网络
    printflow();//输出实流边
    return 0;
}

/*测试数据
6 9
1 3 10
1 2 12
2 4 8
3 5 13
3 2 2
4 6 18
4 3 5
5 6 4
5 4 6
*/
