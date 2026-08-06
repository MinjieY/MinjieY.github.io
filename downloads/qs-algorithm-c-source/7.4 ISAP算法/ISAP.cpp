#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100;
const int M=10000;
int cnt,d;
int head[N],pre[N],h[N],g[N];
struct Edge{
   int v,next;
   int cap,flow;
}E[M];

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

void set_h(int t,int n){//标高 
    queue<int> q;
    memset(h,-1,sizeof(h));
    memset(g,0,sizeof(g));
    h[t]=0;
    q.push(t);
    while(!q.empty()){
		int u=q.front();q.pop();
		++g[h[u]];//高度为h[u]的节点个数
		for(int i=head[u];~i;i=E[i].next){
			int v=E[i].v;
			if(h[v]==-1){
				h[v]=h[u]+1;
				q.push(v);
			}
        }
    }
    cout<<"初始化高度"<<endl;
    cout<<"h[ ]=";
    for(int i=1;i<=n;i++)
       cout<<"\t"<<h[i];
    cout<<endl;
}

int ISAP(int s,int t,int n){
    set_h(t,n);
    int ans=0,u=s,d;
    while(h[s]<n){
        int i=head[u];
		if(u==s)
           d=inf;
        for(;~i;i=E[i].next){
			int v=E[i].v;
			if(E[i].cap>E[i].flow&&h[u]==h[v]+1){
				u=v;
                pre[v]=i;
                d=min(d,E[i].cap-E[i].flow);
                if(u==t){
					cout<<endl;
					cout<<"增广路径："<<t;
					while(u!=s){
						int j=pre[u];
						E[j].flow+=d;
						E[j^1].flow-=d;
						u=E[j^1].v;
						cout<<"--"<<u;
					}
					cout<<"增流："<<d<<endl;
					ans+=d;
					d=inf;
                }
                break;
            }
        }
		if(i==-1){
			if(--g[h[u]]==0)
				break;
			int hmin=n-1;
			for(int j=head[u];~j;j=E[j].next)
				if(E[j].cap>E[j].flow)
					hmin=min(hmin,h[E[j].v]);
			h[u]=hmin+1;
			cout<<"重贴标签后高度"<<endl;
			cout<<"h[ ]=";
			for(int i=1;i<=n;i++)
				cout<<"  "<<h[i];
			cout<<endl;
			++g[h[u]];
			if(u!=s)
				u=E[pre[u]^1].v;
		}	
    }
    return ans;
}

void printg(int n){//输出网络
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

void printflow(int n){//输出实流边
	cout<<endl;
	cout<<"----------实流边：----------"<<endl;
	for(int i=1;i<=n;i++)
		for(int j=head[i];~j;j=E[j].next)
			if(E[j].flow>0){
				cout<<"v"<<i<<"--"<<"v"<<E[j].v<<"\t"<<E[j].flow;
				cout<<endl;
        	}
}
/*
请输入结点个数n和边数m:
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
int main(){
    int n,m;
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
    cout<<endl;
    printg(n);//输出初始网络
    cout<<"网络的最大流值:"<<ISAP(1,n,n)<<endl;
    cout<<endl;
    printg(n);//输出最终网络
    printflow(n);//输出实流边
    return 0;
}
