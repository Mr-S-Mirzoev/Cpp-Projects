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

struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* reverseList(ListNode* head)
{
    ListNode* cur = head;
    ListNode* prev = nullptr;
    ListNode* next = nullptr;

    while (cur)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    return prev;
}

class Solution
{
public:
    bool isPalindrome(ListNode* head)
    {
        unsigned N = 1;
        ListNode* cur = head;
        if (cur->next == nullptr)
            return true;

        while (cur->next)
        {
            ++N;
            cur = cur->next;
        }

        cur = head;
        unsigned i = 1;
        while (i < (N >> 1))
        {
            ++i;
            cur = cur->next;
        }

        ListNode* middle = cur;
        ListNode* secondList = middle->next;
        middle->next = nullptr;

        secondList = reverseList(secondList);

        i = 0;
        cur = head;
        ListNode* cur2 = secondList;
        bool notPalindrome = false;
        while (i < (N >> 1))
        {
            ++i;
            if (cur->val != cur2->val)
                notPalindrome = true;

            cur = cur->next;
            cur2 = cur2->next;
        }

        secondList = reverseList(secondList);
        middle->next = secondList;

        return !notPalindrome;
    }
};

int main(int argc, char const* argv[])
{
    ListNode* head = new ListNode(0, new ListNode(1, new ListNode(0)));
    Solution s;
    std::cout << s.isPalindrome(head) << std::endl;
    return 0;
}
