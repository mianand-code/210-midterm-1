// COMSC-210 | Midterm #1 | Mira Anand
// Module 8 - Midterm Exam
// IDE used: Visual Studio Code for Mac

#include <iostream>
using namespace std;

// declaration and initialization of const int variables
// the values being added to the linked list should be between 10 - 99 (MIN_NR, MAX_NR)
// the # of values being added to the linked list should be between 5 - 20 (MIN_LS, MAX_LS)
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// creation of DoublyLinkedList Class
class DoublyLinkedList {
// private member variables
private:
    struct Node { // struct definition within class
        int data; // holds a int value
        Node* prev; // pointer to previous node
        Node* next; // pointer to next node
        Node(int val, Node* p = nullptr, Node* n = nullptr) { // constructor within struct
            data = val; 
            prev = p;
            next = n;
        }
    };

    // pointers to head and tail
    Node* head;
    Node* tail;

// public member functions
public:
    // constructor that initializes the head and tail pointers
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // void insert_after(int value, int position) function header
    // DESCRIPTION: this function will create a new node, set the value of the new node, and add this new node to a certain position within the linked list
    // - the function ensures that the position is valid before proceeding with deletion
    // ARGUMENTS: int value, which is the number to be added to the list
    // - int position, which represents the position/index where the value should be added
    // RETURNS: nothing, void function
    void insert_after(int value, int position) {
        // ensures that position is greater than or equal to 0 before proceeding
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return; // exit the function
        }

        Node* newNode = new Node(value); // create a new node and set its value
        if (!head) { // if head is nullptr, the list is empty
            head = tail = newNode; // head and tail should be set to newNode in this case
            return; // exit the function
        }

        Node* temp = head; // set temp to head
        for (int i = 0; i < position && temp; ++i) // traverse list to find the position where insertion should be performed
            temp = temp->next; // set temp to next node until we find the position to insert

        if (!temp) { // if temp hits nullptr
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; // free newNode
            return; // exit the function
        }

        // code block handles insertion at middle or end of list
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}