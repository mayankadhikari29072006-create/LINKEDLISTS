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
private:
    Node* head;
    Node* tail;

public:
    List(){
        head = NULL;
        tail = NULL;
    }

    ~List() {
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

    void pop_back(){
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

    
};

int main(){
List ll;
ll.push_back(1);
ll.push_back(2);
ll.push_back(3);
ll.push_back(4);
ll.push_back(5);
ll.push_back(6);
ll.printList();
cout<<ll.searchItr(3)<<"\n";
cout<<ll.searchItr(7)<<"\n";

return 0;    
}