#include<cstdio>//缩点+Dinic 1263ms
#include<cstring>
#include<queue>
#include<algorithm>
#include<map>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1050;
const int M=10500;
int cnt,n,m;
int head[N],d[N];
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

bool bfs(int s,int t){//分层
    memset(d,0,sizeof(d));
    queue<int>q;
    d[s]=1;
    q.push(s);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(int i=head[u];~i;i=E[i].next){
        	int v=E[i].v;
        	if(!d[v]&&E[i].cap>E[i].flow){
                d[v]=d[u]+1;
				q.push(v);
				if(v==t)  return 1;
			}	
		}
    }
    return 0;
}

int dfs(int u,int flow,int t){//在分层的基础上dfs 
    if(u==t) return flow;
	int rest=flow;
    for(int i=head[u];~i&&rest;i=E[i].next){
    	int v=E[i].v;
    	if(d[v]==d[u]+1&&E[i].cap>E[i].flow){
            int k=dfs(v,min(rest,E[i].cap-E[i].flow),t);
			if(!k) d[v]=0;
			E[i].flow+=k;
			E[i^1].flow-=k;
			rest-=k;
		}	
	}
	return flow-rest;
}

int Dinic(int s,int t){
	int maxflow=0;
	while(bfs(s,t)){
		maxflow+=dfs(s,inf,t);
	}
	return maxflow;
}

int main(){
    int x,c;
	while(~scanf("%d%d",&n,&m)){
    	init();
		map<int,int> mp; 
        for(int i=0;i<n;i++){
            int res=0; 
            for(int j=0;j<m;j++){
                scanf("%d",&x);
                if(x) res|=(1<<j);
            }
            mp[res]++;
        }
        int nn=(1<<m),s=0,t=nn+m+1;
        for(int i=0;i<nn;i++){
            if(mp[i]==0) continue;
            adde(s,i+1,mp[i]);
            for(int j=0;j<m;j++){
                if(i&(1<<j))
                    adde(i+1,j+nn+1,mp[i]);
            }
        }
        for(int i=0;i<m;i++){
            scanf("%d",&c);
            adde(i+nn+1,t,c);
        }
        if(Dinic(s,t)==n) printf("YES\n");
        else printf("NO\n");
    }
    return 0 ;
}
