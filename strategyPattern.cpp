#include <iostream>
using namespace std;

/*
    策略模式：行为型模式，定义了一系列算法，并将每个算法封装起来，使它们可以互换使用
             策略模式的核心思想是分离算法，选择实现
    应用程序中可以根据当前数据的特性选择最优的排序算法。
*/
class SortStrategy {
public:
    virtual ~SortStrategy() = default;
    virtual string sortMethod() = 0;
};
// 具体策略：快速排序
class QuickSort : public SortStrategy {
public:
    string sortMethod() {
        return "The method of sort is quick sort.";
    }
};
// 具体策略：选择排序
class SelectSort : public SortStrategy {
public:
    string sortMethod() {
        return "The method of sort is select sort.";
    }
};
// 环境类
class Container {
public:
    Container(SortStrategy* strategy) : strategy_(strategy) {}
    void setSort(SortStrategy* strategy) {
        strategy_ = strategy;
    }
    void sortMethod() {
        cout << strategy_->sortMethod() << endl;
    }
private:
    SortStrategy* strategy_;
};

int main() {
    QuickSort* quicksort = new QuickSort();
    SelectSort* selectSort = new SelectSort();

    // Container 类通过更换其内部持有的策略对象，可以灵活地改变排序算法，而不需要修改内部逻辑。
    // 这种方式使得添加新的排序策略变得简单，而不影响现有代码，从而提高了代码的可维护性和可扩展性。
    Container* con = new Container(quicksort);
    con->sortMethod();
    con->setSort(selectSort);
    con->sortMethod();
}