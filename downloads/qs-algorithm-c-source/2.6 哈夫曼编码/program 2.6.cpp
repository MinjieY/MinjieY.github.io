//program 2.6 哈夫曼编码 
#include<iostream>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=10005;
const int maxbit=30;

typedef struct{ //结点结构体
    double weight;
    int parent;
    int lchild;
    int rchild;
    char value;
}HNodeType;

typedef struct{ //编码结构体
    int bit[maxbit];
    int start;
}HCodeType;
      
HNodeType HuffNode[maxn<<1]; //结点结构体数组
HCodeType HuffCode[maxn];//编码结构体数组

void HuffmanTree(HNodeType HuffNode[],int n){//构造哈夫曼树
    for(int i=0;i<2*n-1;i++){//初始化
        HuffNode[i].weight=0;
        HuffNode[i].parent=-1;
        HuffNode[i].lchild=-1;
        HuffNode[i].rchild=-1;
    }
    for(int i=0;i<n;i++)//输入n个叶子结点的信息和权值
        cin>>HuffNode[i].value>>HuffNode[i].weight;
    double m1,m2;//两个最小权值结点的权值，m1为最小，m2为次小 
    int x1,x2;//两个最小权值结点的编号 
    for(int i=0;i<n-1;i++){//执行n-1次合并
        m1=m2=inf;
        x1=x2=-1;
        for(int j=0;j<n+i;j++){//查找两个无双亲且权值最小的结点 
            if(HuffNode[j].parent==-1&&HuffNode[j].weight<m1){
                m2=m1;
                x2=x1;
                m1=HuffNode[j].weight;
                x1=j;
            }
            else if(HuffNode[j].parent==-1&&HuffNode[j].weight<m2){
                m2=HuffNode[j].weight;
                x2=j;
            }
        }
        //更新5项信息 
        HuffNode[x1].parent=n+i;
        HuffNode[x2].parent=n+i;
        HuffNode[n+i].weight=m1+m2;
        HuffNode[n+i].lchild=x1;
        HuffNode[n+i].rchild=x2;
    }
}

void HuffmanCode(HCodeType HuffCode[],int n){//哈夫曼树编码
    HCodeType cd; //定义一个临时变量来存放求解编码时的信息
    int c,p;
    for(int i=0;i<n;i++){
        c=i;
        p=HuffNode[c].parent;
        cd.start=n-1;
        while(p!=-1){
            if(HuffNode[p].lchild==c)
                cd.bit[cd.start]=0;
            else
                cd.bit[cd.start]=1;
            cd.start--;//前移一位
            c=p;
            p=HuffNode[c].parent;
        }
        //把叶子结点的编码信息从临时编码cd中复制出来，放入编码结构体数组
        for(int j=cd.start+1;j<n;j++)
        	HuffCode[i].bit[j]=cd.bit[j];
        HuffCode[i].start=cd.start;
    }
}

int main(){
	int t,n;
	cin>>t;
	while(t--){
    	cin>>n;
    	HuffmanTree(HuffNode,n); //构造哈夫曼树
    	HuffmanCode(HuffCode,n); //哈夫曼编码
	    for(int i=0;i<n;i++){//输出已保存好的所有存在编码的哈夫曼编码
	        if(i!=0)
	            cout<<" ";
	        cout<<HuffNode[i].value<<": ";
	        for(int j=HuffCode[i].start+1;j<n;j++)
	            cout<<HuffCode[i].bit[j];
	    }
        cout<<endl;
	}
    return 0;
}
