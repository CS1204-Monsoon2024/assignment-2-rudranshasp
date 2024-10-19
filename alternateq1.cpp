#include <iostream>

using namespace std;

class ListNode {
public:
    int data;
    ListNode* next;

    ListNode(int val) : data(val), next(nullptr) {}
};

class HashedLinkedList {
private:
    ListNode* head;
    long long listHash;   // To store the rolling hash of the entire list
    const int p = 29;     // For polynomial hash
    const int m = 1e9 + 9; // To avoid overflow

    // Function to calculate (p^index) % m using a fast exponentiation algorithm
    long long modPow(int base, int exp, int mod) {
        long long result = 1;
        long long base_mod = base % mod;
        while (exp > 0) {
            if (exp % 2 == 1) {
                result = (result * base_mod) % mod;
            }
            base_mod = (base_mod * base_mod) % mod;
            exp /= 2;
        }
        return result;
    }

    // Function to update the list hash on insertion or deletion
    void updateHash(int data, int index, bool add) {
        long long dataContribution = (data * modPow(p, index, m)) % m; // Calculate data's contribution to hash
        if (add) {
            listHash = (listHash + dataContribution) % m;
        } else {
            listHash = (listHash - dataContribution + m) % m; // Adjust hash on deletion
        }
    }

public:
    HashedLinkedList() : head(nullptr), listHash(0) {}

    // Insert a node at the end of the list
    void insert(int data) {
        ListNode* newNode = new ListNode(data);
        int index = 0;

        if (!head) {
            head = newNode;
        } else {
            ListNode* current = head;
            while (current->next) {
                current = current->next;
                index++;
            }
            current->next = newNode;
        }
        updateHash(data, index, true); // Update hash after insertion
    }

    // Delete a node with the given data
    bool deleteNode(int data) {
        if (!head) return false;

        int index = 0;

        // If the node to be deleted is the head
        if (head->data == data) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
            updateHash(data, index, false); // Update hash after deletion
            return true;
        }

        // Search for the node to delete
        ListNode* current = head;
        while (current->next && current->next->data != data) {
            current = current->next;
            index++;
        }

        if (!current->next) return false; // Node not found

        // Delete the node
        ListNode* temp = current->next;
        current->next = current->next->next;
        delete temp;
        updateHash(data, index + 1, false); // Update hash after deletion
        return true;
    }

    // Check if two lists are equivalent by comparing their hashes
    bool fastEquivalenceCheck(const HashedLinkedList& otherList) const {
        return listHash == otherList.listHash;
    }

    // Print the list (for debugging purposes)
    void printList() const {
        ListNode* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }
};

int main() {
    HashedLinkedList list1, list2;

    // Insert some elements in list1
    list1.insert(1);
    list1.insert(2);
    list1.insert(3);

    // Insert the same elements in list2
    list2.insert(1);
    list2.insert(2);
    list2.insert(3);

    // Check for equivalence
    if (list1.fastEquivalenceCheck(list2)) {
        cout << "The two lists are equivalent." << endl;
    } else {
        cout << "The two lists are not equivalent." << endl;
    }
 return 0;
}
