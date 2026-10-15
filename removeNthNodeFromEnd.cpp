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

    

    

     int getSize(){
        int sz=0;
        Node* temp = head;
        while(temp != NULL){
            temp=temp->next;
            sz++;
        }
        return sz;
    }


    void removeNth(int n){//TC: O(n), SC: O(1)
        int size=getSize();
        Node* prev =head;

        for(int i=1;i<(size-n);i++){
            prev=prev->next;
        }

        Node* toDel=prev->next;
        cout<<"going to delete: "<<toDel->data<<endl;

        prev->next=prev->next->next;
    }

};

int main(){
List ll;
ll.push_back(1);
ll.push_back(2);
ll.push_back(3);
ll.push_back(4);
ll.push_back(6);
ll.push_back(5);
ll.printList();
ll.removeNth(2);
ll.printList();

return 0;    
}