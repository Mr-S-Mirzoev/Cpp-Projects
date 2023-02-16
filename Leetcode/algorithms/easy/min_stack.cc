#include <vector>
#include <iostream>

class MinStack {
    int min_ = 0;
    int min_count_ = 0;
    std::vector <int> storage_;
public:
    /** initialize your data structure here. */
    MinStack() {}
    
    void push(int x) {
        storage_.push_back(x);

        if (storage_.size() == 1) {
            min_ = x;
            min_count_ = 1;
        } else {
            if (x < min_) {
                min_ = x;
                min_count_ = 1;
            } else if (x == min_) {
                ++min_count_;
            }
        }
    }
    
    void pop() {
        int last = *storage_.rbegin();
        storage_.pop_back();
        if (last == min_)
            --min_count_;

        if (min_count_ <= 0) {
            
            min_ = *storage_.begin();
            min_count_ = 1;
            
            for (auto v : storage_) {
                if (v < min_) {
                    min_count_ = 1;
                    min_ = v;
                } else if (v == min_) {
                    ++min_count_;
                }
            }
        }
    }
    
    int top() {
        return *storage_.rbegin();
    }
    
    int getMin() {
        return min_;
    }
};

int main(int argc, char const *argv[])
{
    MinStack* obj = new MinStack();
    obj->push(-1);
    obj->push(0);
    obj->push(-3);
    std::cout << obj->getMin() << std::endl;
    obj->pop();
    std::cout << obj->top() << std::endl;
    std::cout << obj->getMin() << std::endl;
    return 0;
}