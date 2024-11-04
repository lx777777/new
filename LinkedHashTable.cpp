#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

class HashTable {
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75) 
        : useBucketNum_(0)
        , loadFactor_(loadFactor)
        , primeIdx_(0)
        {
            if(size != primes_[0]) {
                for(; primeIdx_ < PRIME_SIZE; primeIdx_++) {
                    if(primes_[PRIME_SIZE] > size) {
                        break;
                    }
                }
                if(primeIdx_ == PRIME_SIZE) {
                    primeIdx_--;
                }
            }
            table_.resize(primes_[primeIdx_]);
        }
public:
    void insert(int key) {
        double factor = useBucketNum_*1.0 / table_.size();
        if(factor > loadFactor_) {
            expand();
        }
        int idx = key % table_.size();
        if(table_[idx].empty()) {
            useBucketNum_++;
            table_[idx].emplace_back(key);
        } else {
            auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
            if(it == table_[idx].end()) {
                table_[idx].emplace_back(key);
            }
        }
    }
    void erase(int key) {
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        if(it != table_[idx].end()) {
            table_[idx].erase(it);
            if(table_[idx].empty()) {
                useBucketNum_--;
            }
        }
    }
    bool find(int key) {
        int idx = key % table_.size();
        auto it = ::find(table_[idx].begin(), table_[idx].end(), key);
        return it != table_[idx].end();
    }
    void show() {
        // cout << table_.size() << endl;
        for(int i = 0; i < table_.size(); i++) {
            cout << "数组位置为" << i << "的下标处：";
            if(!table_[i].empty()) {
                for(auto it = table_[i].begin(); it != table_[i].end(); ++it) {
                    cout << *it << " ";
                }
                cout << endl;
            } else {
                cout << "null" << endl;
            }
        }
        cout << "-------------------------" << endl;
    }
private:
    void expand() {
        ++primeIdx_;
        if(primeIdx_ == PRIME_SIZE) {
            cout << "Expand fail." << endl;
        }
        vector<list<int>> oldTable;
        table_.swap(oldTable);
        table_.resize(primes_[primeIdx_]);

        for(auto list : oldTable) {
            for(auto key : list) {
                int idx = key % table_.size();
                if(table_[idx].empty()) {
                    useBucketNum_++;
                } 
                table_[idx].emplace_back(key);
            }
        }
    }
private:
    vector<list<int>> table_;
    int useBucketNum_;
    double loadFactor_;

    static const int PRIME_SIZE = 10; // 素数表的大小
    static int primes_[PRIME_SIZE];  // 素数表
    int primeIdx_;  // 当前使用的素数在素数表中的下标
};
int HashTable::primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main() {
    HashTable hash;
    hash.insert(18);
    hash.insert(11);
    hash.insert(23);
    hash.insert(111);
    hash.insert(209);
    hash.insert(87);
    hash.insert(56);
    hash.insert(58);
    hash.insert(61);
    hash.show();
    if(hash.find(56)) {
        hash.erase(56);
    }
    hash.show();
}