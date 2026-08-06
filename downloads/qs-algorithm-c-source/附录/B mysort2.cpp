//mysort2
#include<iostream>
#include<algorithm>
using namespace std;

bool comp(int a,int b){
    return a<b;   //升序排列，如果改为return a>b，则为降序
}

int main(){
    int a[10]={7,4,5,23,2,73,41,52,28,60};
    for(int i=0;i<10;i++)
    	cout<<a[i]<<" ";
    cout<<endl;
    sort(a,a+10,comp);
    for(int i=0;i<10;i++)
    	cout<<a[i]<<" ";
    return 0;
}
