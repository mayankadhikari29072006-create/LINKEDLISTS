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

        if(tail==NULL){
            head=tail=newNode;
        } else{
            newNode->next=head;
            head=newNode;
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

    

    void pop_front(){
        if(head==NULL){
            cout<<"LL is empty\n";
            return;
        }

        Node* temp=head;
        head=head->next;

        temp->next=NULL;
        delete temp;
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

int main(){
List ll;
ll.push_front(4);
ll.push_front(3);
ll.push_front(2);
ll.push_front(1);
ll.printList();
ll.tail->next=ll.head;
isCycle(ll.head);

return 0;    
}