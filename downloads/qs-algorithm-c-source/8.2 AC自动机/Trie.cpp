#include<iostream>
#include<string>
#include<cstring>
using namespace std;
const int maxn=100005;
const int maxz=26;//不同字符个数，例如数字10，小写字母26
int trie[maxn][maxz];
bool end[maxn];//标识单词结束 
int n,tot;//字符串数,下标 

void insert(string s){//将字符串s插入到字典树中
	int len=s.length(),p=1;
	for(int i=0;i<len;i++){
		int ch=s[i]-'a';//转换成数字
		if(!trie[p][ch]) 
			trie[p][ch]=++tot;//记录下标 
		p=trie[p][ch];	 	
	}
	end[p]=true;//标记单词结束 
}

bool search(string s){//在字典树中查找该字符串是否存在 
	int len=s.length(),p=1;
	for(int i=0;i<len;i++){
		p=trie[p][s[i]-'a'];
		if(!p)
			return false;
	}
	return end[p];
}

void dfs(int p){//深度优先遍历，用于测试 
	for(int i=0;i<26;i++){
		if(trie[p][i]){
			cout<<char(i+'a');
			dfs(trie[p][i]);
		}
	}
	cout<<endl;	
}

int main(){	
	string s;
	memset(trie,0,sizeof(trie));
	memset(end,false,sizeof(end));
	tot=1;
	cin>>n;
	while(n--){
		cin>>s;
		insert(s);
	}
	dfs(1);
	cout<<"输入要查询的字符串："<<endl;
	cin>>s;
	if(search(s))
		cout<<"查询成功！"; 
	else
		cout<<"查询失败！"; 
	return 0;
}
/*
5
good
very
map
goat
marry
*/
