//program 3.2 二分搜索 
#include<iostream>
#include<algorithm>
using namespace std;
const int M=10005;
int s[M];

int BinarySearch(int s[],int n,int x){
	int low=0,high=n-1;  //low指向有序数组的第一个元素，high指向有序数组的最后一个元素
	while(low<=high){
		int middle=(low+high)/2; //middle为查找范围的中间值
		if(x==s[middle])       //x等于中间元素，查找成功
			return middle;
		else if(x>s[middle])  //x大于中间元素，则在前半部分查找
		    	low=middle+1;
		    else             //x小于中间元素，则在后半部分查找
		    	high=middle-1;
	}
    return -1;
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
        int k=BinarySearch(s,n,x);
        if(k==-1)
        	cout<<"-1"<<endl;
        else
        	cout<<k+1<<endl;
    }
    return 0;
}
