#include <iostream>
#include <vector>

class LinkedList {
    struct ListNode {
        ListNode *next;
        int value;
    };
    ListNode *head;
public:
    LinkedList(std::vector <int> const& data): head(nullptr) {
        if (data.size())
            head = new ListNode {nullptr, data[0]};

        ListNode *current = head;
        for (unsigned i = 1; i < data.size(); ++i) {
            current->next = new ListNode {nullptr, data[i]};
            current = current->next;
        }
    }

    void print() const {
        if (head == nullptr) {
            std::cout << "Empty LinkedList" << std::endl;
        } else {
            ListNode *current = head;
            while (current) {
                std::cout << current->value << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }

    void reverse() {
//cur = &1
//prev = null
//next = cur->next; // &2

//cur->next = prev;
//prev = cur;
//cur = next;
//next = cur->next
//if next == null
//    break;

        ListNode *cur = head;
        ListNode *prev = nullptr;
        ListNode *next = nullptr;

        while (cur) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }

        head = prev;
    }
};

/*
prev  cur next
cur             prev
1 -> 2 <- 3 <- 4
    .|.
     4
1 <- 2 <- 3
*/

//cur = &1
//prev = null
//next = cur->next; // &2

//cur->next = prev;
//prev = cur;
//cur = next;
//next = cur->next
//if next == null
//    break;


//next = cur->next->next;
//cur->next->next = cur
//tmp = prev
//prev = cur->next
//cur->next = tmp
//cur = prev

int main(int argc, char const *argv[])
{
    LinkedList lst({1, 2, 3});
    lst.print();
    lst.reverse();
    lst.print();
    return 0;
}
