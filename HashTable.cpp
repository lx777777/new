#include <iostream>
#include <string>
using namespace std;

// 线性探测哈希表
/*
    缺陷：
        1. 发生哈希冲突的时候，接近O(n)的时间复杂度，存储变慢了
        2. 多线程环境中，操作基于数组实现的哈希表需要给数组整体添加互斥锁来保证哈希表的原子操作
*/

class Student {
public:
    Student(int id = 0, string name = "")
        : id_(id)
        , name_(name)
    {} 
    int getId() const { return id_; }
    string getName() const { return name_; }
    bool operator==(const Student& stu) {
        return this->id_ == stu.id_;
    }
private:
    int id_;
    string name_;
};
// 桶的状态
enum State {
    STATE_UNUSER,
    STATE_USING,
    STATE_DEL,
};

// 桶的类型
struct Bucket {
    Bucket(Student key = Student(), State state = STATE_UNUSER)
        : key_(key)
        , state_(state)
    {}
    Student key_;
    State state_;
};
class HashTable {
public:
    HashTable(int size = primes_[0], double loadFactor = 0.75)
        : useBucketNum_(0)
        , loadFactor_(loadFactor)
        , primeIdx_(0) 
        {
            // 把用户输入的size调整为素数表中最近的较大的素数
            if(size != primes_[0]) {
                for(; primeIdx_ < PRIME_SIZE; primeIdx_++) {
                    if(primes_[primeIdx_] > size) {
                        break;
                    }
                }
                // 如果size大于素数表中的最后一个元素，将其调整为最后一个元素
                if(primeIdx_ == PRIME_SIZE) {
                    primeIdx_--;
                }
            }
            tableSize_ = primes_[primeIdx_];
            table_ = new Bucket[tableSize_];
        }
        ~HashTable() {
            delete[] table_;
            table_ = nullptr;
        }
public:
    // 插入元素
    bool insert(const Student& key) {
        // 考虑扩容（动态桶的装载因子大于桶的装载因子）
        double factor = useBucketNum_*1.0 / tableSize_;
        // cout << "factor : " << factor << endl;
        if(factor > loadFactor_) {
            expand();
        }
        int idx = key.getId() % tableSize_;
        
        int i = idx;
        do {
            if(table_[i].state_ != STATE_USING) {
                table_[i].state_ = STATE_USING;
                table_[i].key_ = key;
                useBucketNum_++;
                return true;
            }
            i = (i + 1) % tableSize_;
        } while(i != idx);
        // // 如果idx位置没有被占用，直接插入进去
        // if(table_[idx].state_ != STATE_USING) {
        //     table_[idx].state_ = STATE_USING;
        //     table_[idx].key_ = key;
        //     return true;
        // }
        // // 如果该位置被占用，则向后寻找新的空闲位置插入，如果超过tablesize_下标，则从开始0下标寻找
        // for(int i = (idx+1)%tableSize_; i != idx; i = (i+1)%tableSize_) {
        //     if(table_[i].state_ != STATE_USING) {
        //         table_[i].state_ = STATE_USING;
        //         table_[i].key_ = key;
        //         return true;
        //     }
        // }
        return false;
    }   

    // 删除元素 遍历桶的元素，如果发现桶的状态是未使用的，则不需要再遍历了（未使用的桶后面不会存在正在使用的桶）
    void erase(Student key) {
        int idx = key.getId() % tableSize_;
        int i = idx;
        do {
            if(table_[i].state_ == STATE_USING && table_[i].key_ == key) {
                table_[i].state_ = STATE_DEL;
                useBucketNum_--;
                // cout << "Delete element:" << key.getId() << endl;
            }
            i = (i+1)%tableSize_;
        } while(table_[i].state_ != STATE_UNUSER && i != idx);
    }
    // 查询
    bool find(Student key) {
        int idx = key.getId() % tableSize_;
        int i = idx;
        do {
            if(table_[i].state_ == STATE_USING && table_[i].key_ == key) {
                return true;
            }
            i = (i+1)%tableSize_;
        } while(table_[i].state_ != STATE_UNUSER && i != idx);
        return false;
    }
    void show() {
        cout << "tableSize_ :" << tableSize_ << endl;
        for(int i = 0; i < tableSize_; i++) {
            if(table_[i].state_ == STATE_USING) {
                cout << "数组下标为" << i << "的位置:学生的id为" << table_[i].key_.getId() << " 学生的姓名为" << table_[i].key_.getName() << endl;
            }
        }
    }
private:
    void expand() {
        ++primeIdx_;
        if(primeIdx_ == PRIME_SIZE) {
            cout << "Expand fail." << endl;
        }
        Bucket* newTable = new Bucket[primes_[primeIdx_]];
        for(int i = 0; i < tableSize_; i++) {
            if(table_[i].state_ == STATE_USING) {
                // 把table_中的正在使用的桶的数据重新哈希到newTable中
                int idx = table_[i].key_.getId() % primes_[primeIdx_];
                int k = idx;
                do {
                    if(newTable[k].state_ != STATE_USING) {
                        newTable[k].state_ = STATE_USING;
                        newTable[k].key_ = table_[i].key_;
                        break;
                    }
                    k = (k+1)%primes_[primeIdx_];
                } while(k != idx);
            }
        }
        delete[] table_;
        table_ = newTable;
        tableSize_ = primes_[primeIdx_];
    }
private:
    Bucket* table_;    // 指向动态开辟的哈希表
    int tableSize_;    // 哈希表当前的长度
    int useBucketNum_; // 已经使用的桶的个数
    double loadFactor_; // 哈希表的装载因子

    static const int PRIME_SIZE = 10; // 素数表的大小
    static int primes_[PRIME_SIZE];  // 素数表
    int primeIdx_;  // 当前使用的素数在素数表中的下标
};
int HashTable::primes_[PRIME_SIZE] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

void test() {
    int data = 3;
    for(int i = data; i < 1000; ++i) {
        int j = 2;
        for(; j < i; ++j) {
            if(i % j == 0) {
                break;
            }
        }
        if(i == j) {
            cout << i << " ";
        }
    }
}

int main() {
    HashTable hash;
    hash.insert(Student(100, "s100"));
    hash.insert(Student(200, "s200"));
    hash.insert(Student(300, "s300"));
    hash.insert(Student(400, "s400"));
    hash.insert(Student(500, "s500"));
    hash.insert(Student(600, "s600"));
    hash.insert(Student(700, "s700"));
    hash.show();
    if(hash.find(Student(700, "s700"))) {
        hash.erase(Student(700, "s700"));
    }
    hash.show();
}