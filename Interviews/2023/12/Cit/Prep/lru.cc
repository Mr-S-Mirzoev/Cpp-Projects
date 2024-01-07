#include <list>
#include <unordered_map>

template <typename KeyType, typename ValueType>
class LeastRecentCache
{
    struct StorageElement
    {
        ValueType value;
        typename std::list<KeyType>::iterator it;
    };
    std::unordered_map<KeyType, StorageElement> storage_;
    std::list<KeyType> order_;
    int max_size_;

public:
    void insert(KeyType key, ValueType&& value)
    {
        if (storage_.size() == max_size_)
        {
            storage_.erase(order_.front());
            order_.pop_front();
        }

        storage_[key] = std::move(value);
        order_.emplace_back(std::move(key));
    }
}