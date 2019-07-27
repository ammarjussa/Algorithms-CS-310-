#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std; 

class node {
	public:
		int value;
		node* left;
		node* right;
		node* parent;

		node(int val) {
			this->value=val;
			left=NULL;
			right=NULL;
			parent=NULL;
		}
};

class BT {
	public:
		node* root;
		BT() {
			root=NULL;	
		}
		void insert(int val) {
			node* t=root;
			insertHelper(t, val);
		}

		void insertHelper(node* p, int val) {
			node* temp=new node(val);

			if(p==NULL) p=temp;
			else {
				queue<node*> q; 
			    q.push(p); 
			  
			    while (!q.empty()) { 
			        node* temp2 = q.front(); 
			        q.pop(); 
			  
			        if (!p->left) { 
			            p->left = temp;
			            p->left->parent=p; 
			            break; 
			        } else
			            q.push(p->left); 
			  
			        if (!p->right) { 
			            p->right = temp; 
			            p->right->parent=p;
			            break; 
			        } else
			            q.push(p->right); 
	    		} 
	    	}	
		}

		void printTree(node* temp,int level) {
		    if(temp==NULL)
		        return;

		    printTree(temp->right,level+1);
		    for (int i = 0; i < level; ++i)
		    {
		        cout << "|   ";
		    }

		    cout<<temp->value<<endl;
		    

		    printTree(temp->left,level+1);
		    
		}

		node* getRoot(){
    		return root;
    	}	



};


int main() {
	BT tree;
	int size;
	cout<<"Enter the number of values: "<<endl;
	cin>>size;
	cout<<"Enter values: "<<endl;
	for(int i=0;i<size;i++) {
		int a;
		cin>>a;
		tree.insert(a);
	}

	tree.printTree(tree.getRoot(),0);



	return 0;
}