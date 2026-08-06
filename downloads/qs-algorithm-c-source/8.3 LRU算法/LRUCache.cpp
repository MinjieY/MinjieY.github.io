#include<iostream> 
#include<map> //内部实现为红黑树，有序，时间复杂度O(logn) 
//#include<unordered_map> //内部实现为哈希表，无序，时间复杂度可达O(1)，c++11新特性
using namespace std;

struct DLNode{ //双向链表结点 
    int key,val;
    DLNode* pre;
    DLNode* next;
    DLNode(int _key,int _val): key(_key),val(_val),pre(NULL),next(NULL) {}
};

class LRUCache{
private:
    map<int,DLNode*> cache; //用map作为哈希表
    DLNode* head;
    DLNode* tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity): capacity(_capacity), size(0){ //初始化 
        head=new DLNode(0,0); //双向链表，添加头部和尾部结点
        tail=new DLNode(0,0);
        head->next=tail;
        tail->pre=head;
    }
    
    int get(int key){ //访问 
        if(!cache.count(key)){ //如果key不存在，返回-1 
            return -1;
        }
        DLNode* p=cache[key]; //如果key存在，先通过哈希表定位，再将该结点移到链表头部
        moveToHead(p);
        return p->val;
    }
    
    void put(int key,int val){ //存入 
        if(!cache.count(key)){ //如果key不存在
            if(size==capacity){ //缓存容量已满 
                DLNode* q=removeTail(); //删除链表尾结点
                cache.erase(q->key); //删除哈希表中对应项
                delete q; //释放空间，防止内存泄漏
                --size;
            }
            DLNode* p=new DLNode(key,val); //创建新结点
            addToHead(p); //添加到链表头部
            cache[key]=p; //添加到哈希表
            ++size; 
        }
        else{
            DLNode* p=cache[key]; //如果key存在，先通过哈希表定位，再修改val，并移到链表头部
            p->val=val;
            moveToHead(p);
        }
    }

    void addToHead(DLNode* p){ //添加p结点到链表头部
        p->pre=head;
        p->next=head->next;
        head->next->pre=p;
        head->next=p;
    }
    
    void removeNode(DLNode* p){ //删除p结点
        p->pre->next=p->next;
        p->next->pre=p->pre;
    }

    void moveToHead(DLNode* p){ //移动p结点到链表头部
        removeNode(p); //先删除 
        addToHead(p); //再添加 
    }

    DLNode* removeTail(){ //删除尾结点
        DLNode* p=tail->pre;
        removeNode(p);
        return p;
    }
    
    void print(){ //输出缓存内容
    	DLNode* p;
		if(head->next==tail)
    		cout<<"empty list"<<endl;
    	else{
    		p=head->next;
    		while(p!=tail){
    			cout<<p->key<<": "<<p->val<<endl;
    			p=p->next;
			}
		}
	}
};

int main(){
	LRUCache cache1=LRUCache(5);
	int opt,key,val;
	while(1){
		cout<<"请输入指令编号（1.put 2.get 3.print 0.exit）："<<endl;
		cin>>opt;
		if(opt==0) break;
		switch(opt){
			case 1:
				cout<<"请输入key val："<<endl; 
				cin>>key>>val;
				cache1.put(key,val);
				break;
			case 2:
				cout<<"请输入key："<<endl;
				cin>>key;
				cout<<cache1.get(key)<<endl;
				break;
			case 3:
				cache1.print();
				break; 
		}
	}
	return 0;
}
