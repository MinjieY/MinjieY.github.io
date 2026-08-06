//program 4.5 编辑距离 
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1005;
char str1[N],str2[N];
int d[N][N]; //d[i][j]表示str1前i个字符和str2前j个字符的编辑距离。

int editdistance(char *str1,char *str2){
    int m=strlen(str1);
    int n=strlen(str2);//取字符串大小
    for(int i=0;i<=m;i++)//当第二个串长度为0，编辑距离初始化为i
        d[i][0]=i;
    for(int j=0;j<=n;j++)//当第一个串长度为0，编辑距离初始化为j
        d[0][j]=j;
    for(int i=1;i<=m;i++){//遍历两个数组
        for(int j=1;j<=n;j++){
            int diff;//判断str[i]是否等于str2[j],相等为0，不相等为1
            if(str1[i-1]==str2[j-1])//相等
                diff=0;
            else
                diff=1;
            int temp=min(d[i-1][j]+1,d[i][j-1]+1);//先两者取最小值
            d[i][j]=min(temp,d[i-1][j-1]+diff);//再取最小值，相当于三者取最小值
        }
    }
    return d[m][n];
}

int main(){
    int t;//测试用例数 
    cin>>t;
    while(t--){
		cin>>str1;
    	cin>>str2;
    	cout<<editdistance(str1,str2)<<endl;
    }
    return 0;
}
