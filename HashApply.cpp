#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector> 
#include <string>
#include <map>
using namespace std;


// 1. 给定一个数组或字符串，找出第一个重复的数字或字符
void func1(const vector<int>& vec) {
    unordered_set<int> set;
    for(auto num : vec) {
        auto it = set.find(num);
        if(it == set.end()) {
            set.insert(num);
        } else {
            cout << "第一个重复的数字是：" << num << endl;
            break;
        }
    }
}
// 2. 给定一个数组或字符串，找出所有重复的数字或字符
void func2(const vector<int>& vec) {
    unordered_set<int> set;
    cout << "重复的数字是：";
    for(auto num : vec) {
        auto it = set.find(num);
        if(it == set.end()) {
            set.insert(num);
        } else {
            cout << num << " ";
        }
    }
    cout << endl;
}
// 3. 给定一个数组或字符串，找出所有重复的数字或字符以及出现的次数
void func3(const vector<int>& vec) {
    unordered_map<int, int> map;
    for(auto num : vec) {
        // 如果num不在vec中，插入键num以及默认的值1
        // 如果num在vec中，值+1
        map[num]++;
    }
    cout << "重复的数字以及出现的次数:" << endl;
    for(auto it : map) {
        if(it.second > 1) {
            cout << "num:" << it.first << " cnt:" << it.second << endl;  
        }
    }
}
// 4. 给定一个数组或字符串，找出第一个没有重复的数字或字符
void func4(const vector<int>& vec) {
    unordered_map<int, int> map;
    for(auto num : vec) {
        map[num]++;
    }
    for(auto num : vec) {
        if(map[num] == 1) {
            cout << "第一个没有重复的数字是：" << num << endl;
            break;
        }
    }
}
// 5. 过滤掉重复的数字，每个数字保留一次
void func5(const vector<int>& vec) {
    unordered_set<int> set;
    for(auto num : vec) {
        set.insert(num);
    }
    for(auto it : set) {
        cout << it << " ";
    }
    cout << endl;
}
int main() {
    vector<int> vec{1, 2, 3, 5, 2, 1, 4, 4, 4, 4, 5, 6};
    func1(vec);
    func2(vec);
    func3(vec);
    func4(vec);
    func5(vec);
    return 0;
}