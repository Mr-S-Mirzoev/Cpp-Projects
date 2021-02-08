#include <iostream>
#include <initializer_list>
#include <vector>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class List {
    ListNode *first = nullptr;
public:
    List (const std::initializer_list<int> &inlst) {
        ListNode *cur;
        for (auto &value : inlst) {
            if (!first) {
                first = new ListNode(value);
                cur = first;
            } else {
                cur->next = new ListNode(value);
                cur = cur->next;
            }
        }
    }

    List (ListNode *arg_first): first(arg_first) {}

    ListNode *get_first() const {
        return first;
    }

    friend std::ostream& operator << (std::ostream &os, const List &ls) {
        ListNode *cur = ls.get_first();

        std::cout << "[ ";

        while (cur) {
            std::cout << cur->val << " ";
            cur = cur->next;
        } 

        std::cout << "]";

        return os;
    }

    ~List() {
        ListNode *next;
        ListNode *cur = first;
        while (cur) {
            next = cur->next;
            delete cur;
            cur = next;
        } 
    }
};

class Solution {
    int next (std::vector<ListNode*>& lists) {
        int imin = -1;
        int minval;
        int i;
        
        for (i = 0; i < lists.size(); ++i) {
            if (!lists[i])
                continue;
            
            
            if (imin == -1 || minval > lists[i]->val) {
                imin = i;
                minval = lists[i]->val;
            }
        }
    
        return imin;
    }
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        ListNode *start = nullptr;
        ListNode *last = nullptr;
        int current_imin = next(lists);
        
        while (current_imin != -1) {
            int value = lists[current_imin]->val;
            lists[current_imin] = lists[current_imin]->next;
            ListNode *current = new ListNode(value);
            
            if (!last) {
                start = current;
            } else {
                last->next = current;
            }
            
            last = current;
            current_imin = next(lists);
        }
        
        return start;
    }
};

int main(int argc, char const *argv[])
{
    List l1 ({1, 4, 5});
    List l2 ({1, 3, 4});
    List l3 ({2, 6});

    std::cout << "Merging 3 lists: " << std::endl;
    std::cout << "List 1: " << l1 << std::endl; 
    std::cout << "List 2: " << l2 << std::endl; 
    std::cout << "List 3: " << l3 << std::endl; 
    
    std::vector <ListNode *> lists;
    lists.push_back(l1.get_first());
    lists.push_back(l2.get_first());
    lists.push_back(l3.get_first());

    Solution s;
    List res(s.mergeKLists(lists));
    std::cout << "Merged lists: " << res << std::endl;

    return 0;
}
