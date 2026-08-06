#include<iostream>
using namespace std;
#define N 100
int father[N];
int n,m;

void init(){//初始化集合号 
    for(int i=1;i<=n;i++)
    	father[i]=i;
}

int Find(int x){//查找x的集合号 
    if(x!=father[x])
    	father[x]=Find(father[x]);
    return father[x];
}

void Union(int x,int y){//合并两个元素所在的集合
	int a,b;
    a=Find(x);
    b=Find(y);
    if(a!=b)
    	father[b]=a;
}

int main(){
    int x,u,v,sum=0;
    cout<<"input n and m:"<<endl;
    cin>>n>>m;
    init();
    cout<<"input u and v"<<endl;
    for(int i=1;i<=m;i++){
        cin>>u>>v;
        Union(u,v);
    }
    for(int i=1;i<=n;i++){
        x=Find(i);
        cout<<father[i]<<" ";
        if(father[i]==i)
        	sum++;
    }
    cout<<endl;
    cout<<"sum = "<<sum<<endl;
    return 0;
}
/*
10 9
1 2
3 4
5 2
4 6
2 6
8 7
9 7
1 6
2 4
*/
