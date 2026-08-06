//program 7.6 最大匹配问题 ISAP
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=210;
const int M=10210;
int cnt;
int head[N],pre[N],h[N],g[N];
struct Edge{
   int v,next;
   int cap,flow;
}E[M<<1];//双边

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

void adde(int u,int v,int c){
    add(u,v,c);
    add(v,u,0);
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
					while(u!=s){
						int j=pre[u];
						E[j].flow+=d;
						E[j^1].flow-=d;
						u=E[j^1].v;
					}
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
			++g[h[u]];
			if(u!=s)
				u=E[pre[u]^1].v;
        }
    }
    return ans;
}

void printflow(int m){//输出配对方案
	cout<<"------ 配对方案如下：-----"<<endl;
	for(int i=1;i<=m;i++)
    	for(int j=head[i];~j;j=E[j].next)
	        if(E[j].flow>0){
	        	cout<<i<<"--"<<E[j].v<<endl;
	        	break;
	        }
}

int main(){
	int t;//测试用例数 
//    freopen("C:\\7.4\\7.4-3.in","r",stdin);
//    freopen("C:\\7.4\\7.4-3.out","w",stdout); 
	cin>>t;
    while(t--){
    	int m,n,u,v,total;
    	cin>>m>>n;
    	init();
    	total=m+n;
    	for(int i=1;i<=m;i++)
        	adde(0,i,1);//源点到女推销员的边
    	for(int j=m+1;j<=total;j++)
        	adde(j,total+1,1);//男推销员到汇点的边
    	while(cin>>u>>v,u+v!=-2)
        	adde(u,v,1);
    	cout<<ISAP(0,total+1,total+2)<<endl;
//	    printflow(m);//输出配对方案
    }
    return 0;
}
/*测试用例
1
5 7
1 6
1 8
2 7
2 8
2 11
3 7
3 9
3 10
4 12
4 9
5 10
-1 -1
*/ 
