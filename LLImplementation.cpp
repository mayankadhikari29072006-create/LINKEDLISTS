#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node* next;

    Node(int val){
        data=val;
        next=NULL;
    }

    ~Node(){
        if(next!=NULL){
            delete next;
            next=NULL;
        }
    }
};

class List{
public:
    Node* head;
    Node* tail;


    List(){
        head = NULL;
        tail = NULL;
    }

    ~List() {

         if(tail !=NULL){
            tail->next=NULL;
        }
        if(head!=NULL){
            delete head;
            head=NULL;
        }
    }
    void push_front(int val){
        Node* newNode= new Node(val); //dynamic

        if(head==NULL){
            head=tail=newNode;
        } else{
            newNode->next=head;
            head=newNode;
        }

    }

    void push_back(int val){
        Node* newNode= new Node(val);

        if(head==NULL){
            head=tail=newNode;
        } else {
            tail->next=newNode;
            tail=newNode;
        }
    }

    void printList(){
        Node* temp=head;
        while(temp!=NULL){
            cout<<temp->data<<" -> ";
            temp=temp->next;
        }
        cout<<"NULL\n";
    }

    void insert(int val,int pos){
    if(pos<0){
        cout<<"position is INVALID\n";
        return;
    }
    if(pos==0){
        push_front(val);
        return;
    }

    Node* temp=head;
    for(int i=0; i<pos-1 && temp!=NULL; i++){
        temp=temp->next;
    }
    if(temp==NULL){
        cout<<"position is INVALID\n";
        return;
    }

    Node* newNode=new Node(val);
    newNode->next=temp->next;
    temp->next=newNode;
    if(temp==tail) tail=newNode;
}

    void pop_front(){
    if(head==NULL){
        cout<<"LL is empty\n";
        return;
    }

    Node* temp=head;
    head=head->next;
    if(head==NULL){
        tail=NULL;   // list became empty
    }
    temp->next=NULL;
    delete temp;
}

    void pop_back(){

        if(head==NULL){
            cout<<"LL is empty\n";
            return;
        }
        if(head==tail){
            delete head;
            head=tail=NULL;
            return;
        }
        Node* temp=head;

        while(temp->next->next != NULL){
            temp=temp->next;
        }

        temp->next=NULL; //temp=tail's prev
        delete tail;
        tail=temp;
    }

    int searchItr(int key){
        Node* temp = head;
        int idx = 0;

        while(temp!=NULL){
            if(temp->data==key){
                return idx;
            }
            temp=temp->next;
            idx++;
        }

        return -1;
    }

    int helper(Node* h, int key){
        if(h==NULL){
            return -1;
        }

        if(h->data==key){
            return 0;
        }

        int idx=helper(h->next,key);
        if(idx==-1){
            return -1;
        }
        return idx+1;
    }

    int searchRec(int key){
    return helper(head,key);
    }

    void reverse(){
        Node* curr=head;
        Node* prev=NULL;
        tail=head;

        while(curr != NULL){
         Node* next = curr-> next;
         curr->next =prev;   
            
        //updations for next itr
        prev=curr;
        curr=next;
    }
    head = prev;
    }

     int getSize(){
        int sz=0;
        Node* temp = head;
        while(temp != NULL){
            temp=temp->next;
            sz++;
        }
        return sz;
    }


    void removeNth(int n){
    int size = getSize();
    if(n < 1 || n > size){ cout << "INVALID\n"; return; }
    if(n == size){ pop_front(); return; }

    Node* prev = head;
    for(int i = 1; i < size - n; i++) prev = prev->next;

    Node* toDel = prev->next;
    prev->next = toDel->next;
    if(toDel == tail){ tail = prev;}
    toDel->next = NULL;          // otherwise Node's destructor deletes the rest of the list!
    delete toDel;
}


};

    bool isCycle(Node* head){
        Node* slow=head;
        Node* fast=head; 

        while(fast != NULL && fast->next!=NULL){
            slow=slow->next;//1
            fast=fast->next->next;//2

            if(slow==fast){
                cout<<"cycle exists\n";
                return true;
            }
        }
        cout<<"cycles doesn't exist\n";
        return false;
    }

    void removeCycle(Node* head){
        //detect cycle
        Node* slow=head;
        Node* fast=head;
        bool isCycle=false;

        while(fast!=NULL&& fast->next != NULL){
            slow=slow->next;
            fast=fast->next->next;

            if(slow==fast){
                cout<<"cycle exists\n";
                isCycle=true;
                break;
            }
        }

        if(!isCycle){
            cout<<"cycle doesn't exist\n";
            return;
        }

        slow=head;
        if(slow==fast){//special case: tail->head
            while(fast->next != slow){
                fast=fast->next;
            }
            fast->next=NULL;//remove cycle

        } else {
            Node* prev=fast;
            while(slow != fast){
                slow=slow->next;
                prev=fast;
                fast=fast->next;
            }
            prev->next=NULL;//remove cycle
        }
        cout<<"cycle removed\n";
    }

   


Node*splitAtMid(Node* head){
    Node* slow=head;
    Node* fast=head;
    Node* prev=NULL;

    while(fast!=NULL && fast->next!=NULL){
        prev=slow;
        slow=slow->next;
        fast=fast->next->next;
    }

    if(prev!=NULL){
        prev->next=NULL;//split at middle
    }
    return slow;//slow=rightHead
}

Node* merge(Node* left,Node* right){
    List ans;
    Node* i=left;
    Node* j=right;

    while(i!=NULL&& j!=NULL){
        if(i->data <= j->data){
            ans.push_back(i->data);
            i=i->next;
        }else{
            ans.push_back(j->data);
            j=j->next;
        }
    }

    while(i!=NULL){
        ans.push_back(i->data);
        i=i->next;
    }
    while(j!=NULL){
        ans.push_back(j->data);
        j=j->next;
    }

    Node* res = ans.head;
    ans.head = ans.tail = NULL;   // detach so ~List doesn't delete the merged nodes

    delete left;    // free old halves (needs your original recursive ~Node)
    delete right;

    return res;
}

 Node* mergeSortList(Node* head){
        if(head==NULL||head->next==NULL){
            return head;
        }


        Node* rightHead=splitAtMid(head);

        Node* left=mergeSortList(head);//left Head
        Node* right=mergeSortList(rightHead);//right Head

       return  merge(left, right);//head of sorted LL
    }

    void mergeSort(List& ll){
    ll.head = mergeSortList(ll.head);   // sort the nodes

    Node* t = ll.head;              // fix tail
    while(t != NULL && t->next != NULL){
        t = t->next;
    }
    ll.tail = t;
}

Node* reverse(Node* head){
    Node* prev=NULL;
    Node* curr=head;
    Node* next=NULL;

    while(curr!=NULL){
        next=curr->next;
        curr->next=prev;

        prev=curr;
        curr=next; 
    }

return prev;//prev is head of reversed LL
}

Node* zigZag(Node* head){
    Node* rightHead=splitAtMid(head);
    Node* rightHeadRev=reverse(rightHead);

    //alternate meging
    Node* left=head;
    Node* right=rightHeadRev;
    Node* tail=right;

    while(left!=NULL && right!=NULL){
        Node* nextLeft=left->next;
        Node* nextRight=right->next;

        left->next=right;
        right->next=nextLeft;

        tail=right;
        left=nextLeft;
        right=nextRight;
    }

    if(right != NULL){
        tail->next=right;
    }
    return head;
}

 void zigZagList(List& ll){
    ll.head = zigZag(ll.head);   // sort the nodes

    Node* t = ll.head;              // fix tail
    while(t != NULL && t->next != NULL){
        t = t->next;
    }
    ll.tail = t;
}

int main(){
List ll;
ll.push_front(3);
ll.push_front(2);
ll.push_front(1);
ll.printList();// 1->2->3->NULL
ll.push_back(4);
ll.push_back(5);
ll.printList();// 1->2->3->4->5->NULL

ll.insert(100,25); //position is INVALID
ll.printList(); // 1->2->3->4->5->NULL

ll.insert(100,2); 
ll.printList(); // 1->2->100->3->4->5->NULL

ll.pop_front();
ll.printList(); // 2->100->3->4->5->NULL

ll.pop_back();
ll.printList(); // 2->100->3->4->NULL

cout<<ll.searchItr(3)<<"\n";
cout<<ll.searchItr(7)<<"\n";

cout<<ll.searchRec(3)<<"\n";
cout<<ll.searchRec(7)<<"\n";

ll.reverse();
ll.printList();

ll.removeNth(2);
ll.printList();
ll.pop_back();
ll.pop_back();

ll.push_front(3);
ll.push_front(2);
ll.push_front(1);
ll.printList();
ll.tail->next=ll.head;//making loop 1->2->3->4->1
isCycle(ll.head);
removeCycle(ll.head);
ll.push_back(0);
ll.printList();
mergeSort(ll);
ll.printList();
ll.pop_front();
ll.push_back(5);
ll.printList();
zigZagList(ll);
ll.printList();

return 0;    
}