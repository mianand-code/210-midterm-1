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
        newNode->next = temp->next; // newNode next should be set to temp's next
        newNode->prev = temp; // newNode previous should be set to temp
        if (temp->next) // if a node exists after temp
            temp->next->prev = newNode;
        else
            tail = newNode; 
        temp->next = newNode; 
    }

    // void delete_val(int value) function header
    // DESCRIPTION: this function will traverse the list to find a value to delete and then delete that value from the list
    // - deletion will not be performed if the linked list is empty. Function performs a check for that
    // - deletion will also not be performed if the value was not found in the list
    // ARGUMENTS: int value, which is the number to be added to the list
    // RETURNS: nothing, void function
    void delete_val(int value) {
        if (!head) return; // if head is equal to nullptr, the list is empty. Exit the function, no value to delete

        Node* temp = head; // set temp to head
        
        while (temp && temp->data != value) // traverse list to find value to be deleted
            temp = temp->next; // set temp to next node until we find the value to delete

        if (!temp) return; // if temp hits nullptr, the value was not found. Exit the function, nothing to delete

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; // deleting the head

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; // deleting the tail

        delete temp; // delete the value from the list
    }

    // void delete_pos(int pos) function header
    // DESCRIPTION: this function will traverse the list to find the position (index) of a value to delete and then delete that value from the list
    // - deletion will not be performed if the linked list is empty. Function performs a check for that
    // - deletion will also not be performed if the position is not within the bounds of the linked list
    // ARGUMENTS: int pos, which is the position/index of the value to be deleted from the list
    // RETURNS: nothing, void function
    void delete_pos(int pos) {
        if (!head) { // if head is equal to nullptr, the list is empty
            cout << "List is empty." << endl;
            return; // exit the function, no deletion can be performed
        }
    
        if (pos == 1) { // if position is equal to 1 (head)
            pop_front(); // pop_front() function call, deletes the head node
            return; // exit the function
        }
    
        Node* temp = head; // set temp to head
    
        for (int i = 1; i < pos; i++){ // traverse list to find the position of the value to be deleted
            if (!temp) { // if temp hits nullptr
                cout << "Position doesn't exist." << endl; // the position was not found
                return; // exit the function
            }
            else
                temp = temp->next; // set temp to next node until we find the position
        }
        if (!temp) { // perform another check to see if temp is equal to nullptr
            cout << "Position doesn't exist." << endl; // the position does not exist
            return; // exit the function
        }
    
        if (!temp->next) { // if the node we want to delete is the last node (tail)
            pop_back(); // pop_back() function call, deletes the tail node
            return; // exit the function
        }
    
        // code blocks deletes a node that is not located at the head or tail
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp; // delete the value from the list
    }

    // void push_back(int v) function header
    // DESCRIPTION: this function will create a new node, set the value of the new node, and add this new node to the end (tail) of the list
    // ARGUMENTS: int v, which is the number to be added to the list
    // RETURNS: nothing, void function
    void push_back(int v) {
        Node* newNode = new Node(v); // create a new node and set its value
        if (!tail) // if there's no tail, the list is empty
            head = tail = newNode;
        else { // if the list is NOT empty
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    // void push_front(int v) function header
    // DESCRIPTION: this function will create a new node, set the value of the new node, and add this new node to the front (head) of the list
    // ARGUMENTS: int v, which is the number to be added to the list
    // RETURNS: nothing, void function
    void push_front(int v) {
        Node* newNode = new Node(v); // create a new node and set its value
        if (!head) // if there's no head, the list is empty
            head = tail = newNode;
        else { // if the list is NOT empty
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    // void pop_front() function header
    // DESCRIPTION: this function will delete the head node from the linked list
    // - deletion will not be performed if the linked list is empty. Function performs a check for that
    // ARGUMENTS: no arguments/parameters
    // RETURNS: nothing, void function
    void pop_front() {

        if (!head) { // if head is equal to nullptr, the list is empty
            cout << "List is empty." << endl;
            return; // exit the function, head deletion cannot be performed
        }

        Node * temp = head; // set temp to head

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp; // delete head node
    }

    // void pop_back() function header
    // DESCRIPTION: this function will delete the tail node from the linked list
    // - deletion will not be performed if the linked list is empty. Function performs a check for that
    // ARGUMENTS: no arguments/parameters
    // RETURNS: nothing, void function
    void pop_back() {
        if (!tail) { // if tail is equal to nullptr, the list is empty
            cout << "List is empty." << endl;
            return; // exit the function, tail deletion cannot be performed
        }
        Node * temp = tail; // set temp to tail

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp; // delete tail node
    }

    // class destructor, to delete all nodes
    // do not need to call it in main(), since it is automatically called when an object goes out of scope
    ~DoublyLinkedList() {
        while (head) { // traverse list, while head does not hit nullptr
            Node* temp = head; // set temp to head
            head = head->next; // set head to the node after the one to be deleted
            delete temp; // perform deletion
        }
    }
    
    // void print() function header
    // DESCRIPTION: this function will output the contents of the linked list to the console
    // - if there are no contents, the user will be notified with a console message
    // ARGUMENTS: no arguments/parameters
    // RETURNS: nothing, void function
    void print() {
        Node* current = head; // set current to head, to start at the beginning of the list
        if (!current) { // if current is equal to nullptr, list is empty
            cout << "List is empty." << endl;
            return; // exit the function, nothing to print
        }
        while (current) { // traverse the list and display its contents, while current is NOT equal to nullptr
            cout << current->data << " ";
            current = current->next; // progress to next node
        }
        cout << endl;
    }

    // void print_reverse() function header
    // DESCRIPTION: this function will output the contents of the linked list to the console IN REVERSE
    // - if there are no contents, the user will be notified with a console message
    // ARGUMENTS: no arguments/parameters
    // RETURNS: nothing, void function
    void print_reverse() {
        Node* current = tail; // set current to tail, to start at the end of the list
        if (!current) { // if current is equal to nullptr, list is empty
            cout << "List is empty." << endl;
            return; // exit the function, nothing to print
        }
        while (current) { // traverse the list and display its contents, while current is NOT equal to nullptr
            cout << current->data << " ";
            current = current->prev; // progress to previous node, to print in reverse
        }
        cout << endl;
    }

    // void every_other_element() function header
    // DESCRIPTION:
    // ARGUMENTS:
    // RETURNS:
    void every_other_element() { // adding a new class method
        Node* current = head; // set current to head
        int position = 0; // to keep a track of the position of the element
        
                if (!current) { // if current is equal to nullptr, list is empty
            cout << "List is empty." << endl;
            return; // exit the function, nothing to print
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}