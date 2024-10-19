#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class HashTable {
private:
    vector<int> table;
    int m;              
    int numElements;    
    
    static constexpr double loadFactor_threshold = 0.8; 
gi
    int hash(int key) {
        return key % m;
    }

    bool primecheck(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;

        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    int nextprime(int n) {
        while (!primecheck(n)) {
            n++;
        }
        return n;
    }

    void sizingtable() {
        int old_m = m;
        m = nextprime(2 * old_m); 

        cout << "Table resized from " << old_m << " to " << m << endl;

        vector<int> old_table = table;
        table.clear();
        table.resize(m, -1); 
        numElements = 0;

        for (int i = 0; i < old_m; i++) {
            if (old_table[i] != -1) {
                insert(old_table[i]);
            }
        }
    }

    double loadfactor() {
        return (double)numElements / m;
    }

public:
    HashTable(int size) {
        m = size;
        table.resize(m, -1); 
        numElements = 0;
    }

    void insert(int key) {
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        if (loadfactor() > loadFactor_threshold) {
            sizingtable();
        }

        int index = hash(key);
        int i = 0;
        int newIndex = index;

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

    void remove(int key) {
        int index = hash(key);
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

    int search(int key) {
        int index = hash(key);
        int i = 0;
        int newIndex = index;

        while (table[newIndex] != -1) {
            if (table[newIndex] == key) {
                return newIndex; 
            }
            i++;
            newIndex = (index + i * i) % m;

            if (i == m) {
                break;  
            }
        }
        return -1;  
    }

    void printtable() {
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
