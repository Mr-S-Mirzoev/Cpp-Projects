#include <iostream>
#include <vector>

struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* reverseK(ListNode* head, int k)
{
    ListNode* cur = head;
    ListNode* prev = nullptr;
    ListNode* next = nullptr;

    while (k)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;

        --k;
    }

    return prev;
}

ListNode* reverseKGroup(ListNode* head, int k)
{
    ListNode* cur = head;
    ListNode* first = nullptr;
    ListNode* next = nullptr;
    ListNode* group_end = nullptr;
    ListNode* prev = nullptr;

    if (k == 1)
        return head;

    while (cur)
    {
        unsigned q = 1;
        group_end = cur;
        while (group_end)
        {
            group_end = group_end->next;
            if (group_end)
                ++q;

            if (q == k)
                break;
        }

        if (q < k)
        {
            if (!first)
                return head;

            prev->next = cur;
            return first;
        }

        next = group_end->next;
        group_end->next = nullptr;

        reverseK(cur, k);

        if (!first)
            first = group_end;
        else
            prev->next = group_end;

        prev = cur;
        cur = next;
    }

    return (first) ? first : head;
}

void print(ListNode* head)
{
    if (head == nullptr)
    {
        std::cout << "Empty LinkedList" << std::endl;
    }
    else
    {
        ListNode* current = head;
        while (current)
        {
            std::cout << current->val << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

int main(int argc, char const* argv[])
{
    ListNode* lst = new ListNode(1, new ListNode(2, new ListNode(3)));
    print(lst);
    print(reverseKGroup(lst, 1));
    return 0;
}
