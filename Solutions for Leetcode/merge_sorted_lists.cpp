#include <vector>
#include <iostream>

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

class Solution {
public:
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
    
    return 0;
}
