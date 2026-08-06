//mysort1
#include<iostream>
#include<algorithm>
using namespace std;
int main(){
	int a[10]={7,4,5,23,2,73,41,52,28,60};
	for(int i=0;i<10;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	sort(a,a+10);
	for(int i=0;i<10;i++)
		cout<<a[i]<<" ";
	return 0;
}
