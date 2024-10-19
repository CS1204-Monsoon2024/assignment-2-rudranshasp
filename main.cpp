#include "HashTable.cpp"

int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printtable();
    ht.insert(6);
    ht.printtable();
    ht.insert(15);
    ht.printtable(); 
    ht.insert(25);
    ht.printtable();
    ht.remove(15);
    ht.printtable();
    ht.insert(29);  
    ht.printtable(); 

    int find = ht.search(22);
    std::cout << "Found at:" << find << std::endl;

    return 0;
}
