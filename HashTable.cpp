#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class HashTable {
private:
    vector<int> table;
    int m;              // Size of the hash table
    int numElements;    // Number of elements in the hash table
    static constexpr double loadFactor_threshold = 0.8;  // Load factor threshold

    // Hash function: h(k) = k % m
    int hashFunction(int key) {
        return key % m;
    }

    // Prime checker function
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;

        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Find the next prime number
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Resize the table to the next prime size
    void resizeTable() {
        int old_m = m;
        m = nextPrime(2 * old_m); // At least twice the old size and prime

        cout << "Table resized from " << old_m << " to " << m << endl;

        vector<int> old_table = table;
        table.clear();
        table.resize(m, -1);  // Initialize with -1
        numElements = 0;

        // Rehashing the old elements
        for (int i = 0; i < old_m; i++) {
            if (old_table[i] != -1) {
                insert(old_table[i]);
            }
        }
    }

    double loadFactor() {
        return (double)numElements / m;
    }

public:
    // Constructor
    HashTable(int size) {
        m = size;
        table.resize(m, -1); // Initialize table with size m and all -1
        numElements = 0;
    }

    // Insert key into the hash table
    void insert(int key) {
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        if (loadFactor() > loadFactor_threshold) {
            resizeTable();
        }

        int index = hashFunction(key);
        int i = 0;
        int newIndex = index;

        // Quadratic probing to find an empty slot
        while (table[newIndex] != -1) {
            i++;
            newIndex = (index + i * i) % m;

            if (i == m) {
                cout << "Max probing limit reached!" << endl;
                return;
            }
        }

        table[newIndex] = key;
        numElements++;
    }

    // Remove key from the hash table
    void remove(int key) {
        int index = hashFunction(key);
        int i = 0;
        int newIndex = index;

        while (table[newIndex] != -1) {
            if (table[newIndex] == key) {
                table[newIndex] = -1;
                numElements--;
                return;
            }
            i++;
            newIndex = (index + i * i) % m;
        }
        cout << "Element not found" << endl;
    }

    // Search for a key in the hash table
    int search(int key) {
        int index = hashFunction(key);
        int i = 0;
        int newIndex = index;

        while (table[newIndex] != -1) {
            if (table[newIndex] == key) {
                return newIndex;  // Return the index where the key is found
            }
            i++;
            newIndex = (index + i * i) % m;

            if (i == m) {
                break;  // If we have probed every position
            }
        }
        return -1;  // Key not found
    }

    // Print the current state of the hash table
    void printTable() {
        for (int i = 0; i < m; ++i) {
            if (table[i] == -1) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};