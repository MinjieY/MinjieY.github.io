//program 7.6 最大匹配问题 匈牙利算法 
#include<iostream>
#include<cstring>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=210;
const int M=10210;
int match[N],head[N];
bool vis[N];
int cnt;

struct Edge{
   int v,next;
}E[M<<1];

void init(){//初始化 
    memset(head,-1,sizeof(head));
	memset(match,0,sizeof(match));
    cnt=0;
}

void add(int u,int v){
    E[cnt].v=v;
    E[cnt].next=head[u];
    head[u]=cnt++;
}

void adde(int u,int v){
    add(u,v);
    add(v,u);
}

void print(int n){//输出配对方案
	cout<<"----------配对方案如下：----------"<<endl;
	for(int i=1;i<=n;i++)
		if(match[i])
			cout<<match[i]<<"--"<<i<<endl;
}

bool maxmatch(int u){//为u找匹配点，找到返回true，否则返回false
	for(int i=head[u];~i;i=E[i].next){//检查u的所有邻接点 
		int v=E[i].v;
		if(!vis[v]){
			vis[v]=1;
			if(!match[v]||maxmatch(match[v])){//v未匹配或者为v的匹配点找到了其他匹配
				match[v]=u;//u和v匹配
				return true;
			}
		}
    }
    return false;
}

int main(){
    int n,m,total,u,v;
    int t;//测试用例数 
	cin>>t;
    while(t--){
	    cin>>m>>n;
	    init();
	    total=m+n;
		while(cin>>u>>v,u+v!=-2)
			adde(u,v);
	    int num=0;
		for(int i=1;i<=m;i++){
	        memset(vis,0,sizeof(vis));
	        if(maxmatch(i))
	            num++;
	    }
	    cout<<num<<endl;
	    //print(total);//输出配对方案
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
