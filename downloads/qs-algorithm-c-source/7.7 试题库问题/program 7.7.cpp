//program 7.7 试题库问题 ISAP
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

void print(int m,int n){//输出抽取方案
	for(int i=1;i<=m;i++){//读每个题型的邻接表
    	for(int j=head[i];~j;j=E[j].next)//读第i个题型的邻接表
        	if(E[j].flow==1)
            	cout<<E[j].v-m<<"  ";
    	cout<<endl;
	}
}

int main(){
	int t;//测试用例数
	cin>>t;
    while(t--){
    	int m,n,c,num,total,sum=0;
    	cin>>m>>n;//题型数m和试题数n
    	init();
		total=m+n;//题型数m和试题数n
		for(int i=1;i<=m;i++){
			cin>>c;//每种题型的选题数 
			sum+=c;//累加选题数 
			adde(0,i,c);//源点到题型i的边，容量为c 
		}	
		for(int j=m+1;j<=total;j++){
			while(cin>>num,num)//num为试题j属于的题型号，为0时结束
				adde(num,j,1);//题型号num到试题j的边，容量为1
			adde(j,total+1,1);//试题j到汇点的边
		} 
        if(sum==ISAP(0,total+1,total+2))
			print(m,n);//输出抽取方案 
		else
			cout<<"impossible"<<endl;
    }
    return 0;
}
/*测试用例
1
4 15
2 0 3 2
1 2 0
2 3 0
1 4 0
2 3 0
2 4 0
1 2 3 0
3 0
4 0
4 0
2 3 4 0
3 0
2 0
1 0
1 4 0
4 0
*/ 
