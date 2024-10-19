#include <iostream>

using namespace std;

const int MOD = 1e9 + 83;  // Modulo to avoid overflow

// Node structure for the linked list
struct Node {
    int data;
    Node* next;

    // Constructor to initialize node data
    Node(int value) : data(value), next(nullptr) {}
};


class HashLinkedList {
private:
    Node* head;       // Pointer to the first node 
    Node* tail;       // Pointer to the last node 
    int size;         // Total nodes in the list
    int hashValue;    // Hash value for the list
    const int prime = 23;  // Prime number used for hashing

public:
    // Initialize an empty linked list
    HashLinkedList() : head(nullptr), tail(nullptr), size(0), hashValue(0) {}

    // Insert function
    void insert(int val) {
        Node* newNode = new Node(val);
        if (!head) {  // Check if the list is empty
            head = tail = newNode;  // Update head and tail if empty list
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
        updateHash(val);  // Update hash when a new node is inserted
    }

    // Function to update the hash value when new elements are inserted
    void updateHash(int val) {
        // Hash computation using rolling hash 
        hashValue = (hashValue * prime + val) % MOD;
    }

    // Function to get the current hash value
    int getHash() const {
        return hashValue;
    }

    // Delete function
    void deleting(int val) {
        if (!head) {
            cout << "Element cannot be deleted since the list is empty" << endl;
            return;
        }

        Node* temp = head;
        Node* prev = nullptr;

        // To delete the head node
        if (head->data == val) {
            temp = head;
            head = head->next;  // Set the head to next element
            delete temp;         
            Hash_recalc();
            return;
        }

        // Traverse the list to find the element to delete
        while (temp && temp->data != val) {
            prev = temp;         // Track the previous node
            temp = temp->next;   // Move to the next node
        }

        // If the value doesn't exist 
        if (!temp) {
            cout << "Element not found" << endl;
            return;
        }

        // Delete the node
        prev->next = temp->next;
        delete temp; 

        Hash_recalc();
    }

    // Search function
    bool search(int val) {
        Node* temp = head;
        while (temp) {
            if (temp->data == val) {  // Check if the current node's value matches the search value
                return true;  
            }
            temp = temp->next;  // Move to the next node
        }
        return false; 
    }
    // Function to recalculate the entire hash value after a deletion
    void Hash_recalc() {
        hashValue = 0;  // Reset hash for each element
        Node* temp = head; // set the current node to temp
        while (temp) { // iterate through the list 
            updateHash(temp->data);  // Update hash for this particular element
            temp = temp->next;
        }
    }
};

// Main function
int main() {
    HashLinkedList list1, list2;

    // Insert values into both lists
    list1.insert(15);
    list1.insert(30);
    list1.insert(45);

    list2.insert(15);
    list2.insert(30);
    list2.insert(45);

    // Check hash values (fast equivalence check)
    if (list1.getHash() == list2.getHash()) {
        cout << "The lists are equivalent." << endl;
    } else {
        cout << "The lists are not equivalent." << endl;
    }

    // Demonstrate insert, search, and delete
    list1.insert(40);
    cout << "After inserting 40 into list1, hash is: " << list1.getHash() << endl;

    list1.deleting(30);
    cout << "After deleting 30 from list1, hash is: " << list1.getHash() << endl;

    if (list1.search(15)) {
        cout << "15 found in list1." << endl;
    } else {
        cout << "15 not found in list1." << endl;
    }

    return 0;
}
