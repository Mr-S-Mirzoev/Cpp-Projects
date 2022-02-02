#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <string>

class PrefixTree {
    struct PrefixTreeNode {
        std::unordered_map <char, PrefixTreeNode*> children;
        virtual unsigned get_count() const {
            throw std::logic_error("Unimplemented for non-leaf nodes");
        }
        virtual void inc_count() {
            throw std::logic_error("Unimplemented for non-leaf nodes");
        }
    };

    struct TerminatingPrefixTreeNode: PrefixTreeNode {
        unsigned get_count() const final {
            return count;
        }
        void inc_count() final {
            ++count;
        }
    private:
        unsigned count = 1;
    };

    PrefixTreeNode* tree_;
    unsigned subs_len_;
    unsigned N_;
    std::unordered_map <PrefixTreeNode *, unsigned> visit_count_;

    bool match_single(const std::string &s, unsigned start) {
        unsigned end = start + subs_len_;
        PrefixTreeNode *cur = tree_;
        for (unsigned i = start; i < end; ++i) {
            auto it = cur->children.find(s[i]);
            if (it == cur->children.end())
                return false;

            cur = it->second;
        }

        auto v_count_it = visit_count_.find(cur);
        if (v_count_it != visit_count_.end()) {
            if (v_count_it->first->get_count() < ++(v_count_it->second))
                return false;
        } else
            visit_count_.insert({cur, 1});
        
        return true;
    }

    void print(const std::string& prefix, const PrefixTreeNode* node, bool notLast, char c) const {
        if (node != nullptr) {
            std::cout << prefix << (notLast ? "├──" : "└──" );
            unsigned idx = node->children.size();

            // print the value of the node
            if (!idx--) {
                std::cout << c << "(" << node->get_count() << ")" << std::endl;
            } else {
                std::cout << c << std::endl;

                for (auto el : node->children)
                    print(prefix + (notLast ? "│  " : "   "), el.second, (idx-- != 0), el.first);
            }
        }
    }

    void add_sub(std::string const& s) {
        PrefixTreeNode *cur = tree_;
        for (unsigned i = 0; i < s.size(); ++i) {
            auto it = cur->children.find(s[i]);
            if (it == cur->children.end()) {
                PrefixTreeNode *newnode;
                if (i == s.size() - 1)
                    newnode = new TerminatingPrefixTreeNode;
                else
                    newnode = new PrefixTreeNode;

                auto insertion_result = cur->children.insert({
                    s[i],
                    newnode
                });

                if (!insertion_result.second)
                    throw std::runtime_error("Failed to insert substring into prefix tree");

                it = insertion_result.first;
            } else {
                if (i == s.size() - 1)
                    it->second->inc_count();
            }

            cur = it->second;
        }
    }
public:
    PrefixTree(std::vector<std::string> const &subs): 
        tree_(new PrefixTreeNode), N_(subs.size()) {
        if (!N_)
            throw std::logic_error("Empty subs list");
        
        subs_len_ = subs[0].length();
        for (auto s : subs)
            add_sub(s);
    }

    void print() const {
        unsigned idx = tree_->children.size() - 1;
        for (auto el : tree_->children) {
            print("", el.second, (idx != 0), el.first);
            --idx;
        }
    };

    unsigned full_substring_len() const {
        return subs_len_ * N_;
    }

    bool match_all(std::string const& s, unsigned start) {
        visit_count_.clear();
        for (unsigned i = 0; i < N_; ++i)
            if (!match_single(s, start + i * subs_len_))
                return false;

        return true;
    }
};

std::vector<int> findSubstring(std::string const& s, std::vector<std::string> const& words) {
    PrefixTree pt(words);
    pt.print();

    if (s.size() < pt.full_substring_len())
        return {};

    unsigned max_possible_idx = s.size() - pt.full_substring_len();
    std::vector<int> idx_start;

    for (unsigned i = 0; i <= max_possible_idx; ++i)
        if (pt.match_all(s, i))
            idx_start.push_back(i);
    
    return idx_start;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, std::vector<T> vec) {
    os<<"{ ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(os, " "));
    os<<"}";
    return os;
}

int main(int argc, char const *argv[])
{
    std::string s = "wordgoodgoodgoodbestword";
    std::vector<std::string> subs{"word", "good", "best", "good"};

    auto res = findSubstring(s, subs);
    std::cout << res << std::endl;
    return 0;
}

