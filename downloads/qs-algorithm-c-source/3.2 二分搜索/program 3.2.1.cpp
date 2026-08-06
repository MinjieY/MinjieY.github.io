//program 3.2 二分搜索，递归算法 
#include<iostream>
#include<algorithm>
using namespace std;
const int M=10005;
int s[M];

int BinarySearch(int s[],int x,int low,int high){
	if(low>high) //递归结束条件
        return -1; 
    int middle=(low+high)/2;  //计算middle值(查找范围的中间值) 
	if(x==s[middle])          //x等于s[middle]，查找成功
    	return middle; 
    else if(x<s[middle])      //x小于s[middle]，则在前半部分查找
        	return BinarySearch(s,x,low,middle-1); 
        else               //x大于s[middle]，则在后半部分查找
        	return BinarySearch(s,x,middle+1,high);
}

int main(){
	int t,n,x; //测试用例数，元素个数，待查找元素 
	cin>>t;
    while(t--){
        cin>>n;
        for(int i=0;i<n;i++)
        	cin>>s[i];
		sort(s,s+n); //升序排序 
		for(int i=0;i<n;i++) //输出有序序列 
        	cout<<s[i]<<" ";
        cout<<endl;
        cin>>x; //输入要查找的元素
        int k=BinarySearch(s,x,0,n-1);
        if(k==-1)
        	cout<<"-1"<<endl;
        else
        	cout<<k+1<<endl;
    }
    return 0;
}
