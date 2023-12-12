#include <queue>
#include <set>

class MinFriendlyCRUD
{
    std::set<int> set_;
    std::queue<std::set<int>::iterator> queue_;
    std::size_t N_;

public:
    MinFriendlyCRUD(std::size_t N) : N_(N) {}

    void update(int price)
    {
        if (queue_.size() == N_)
        {
            set_.erase(queue_.front());
            queue_.pop();
        }

        auto inserion = set_.insert(price);
        if (inserion.second)
            queue_.push(inserion.first);
        else
            throw std::logic_error("Failed to insert node to tree, possible memory error");
    }

    int getMinPriceInWindow() const { return *set_.cbegin(); }
};

enum OpType
{
    INSERT,
    GET,
    EXIT
};

int main(int argc, char const* argv[])
{
    std::size_t N;
    scanf("%lu", &N);
    MinFriendlyCRUD storage(N);

    int op;

    while (1)
    {
        scanf("%d", &op);

        switch (op)
        {
        case INSERT:
            int val;
            scanf("%d", &val);
            storage.update(val);
            break;

        case GET:
            printf("%d\n", storage.getMinPriceInWindow());
            break;

        default:
            return 0;
        }
    }
    return 0;
}
