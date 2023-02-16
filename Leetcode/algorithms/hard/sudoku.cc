#include <vector>
#include <stdexcept>
#include <queue>
#include <cassert>
#include <array>
#include <iostream>

constexpr short to_digit(char c) {
    return c - '0';
}
constexpr char to_char(short v) {
    return v == 0 ? '.' : v + '0';
}

template <size_t size>
class BitSet {
public:
/*
    BitSet(std::vector <int> &v) {
        assert(size == v.size());

        for (int i = 0; i < size; ++i)
            storage[i / BITS] = v[i];
    }
*/
/*
    BitSet() {
        storage = new size_t[STORAGE_SIZE]();
    }
    BitSet(BitSet const& other) {
        storage = new size_t[STORAGE_SIZE];
        for (unsigned i = 0; i < STORAGE_SIZE; ++i)
            storage[i] = other.storage[i];
    }
    BitSet(BitSet && other) {
        storage = other.storage;
        other.storage = nullptr;
    }
    ~BitSet() {
        delete [] storage;
    }
*/  
    BitSet() {
        storage.resize(STORAGE_SIZE);
    }
    BitSet(BitSet const& other) {
        storage = other.storage;
    }
    BitSet(BitSet && other) {
        storage = std::move(other.storage);
    }

    BitSet& operator=(BitSet const& other) {
        for (unsigned i = 0; i < STORAGE_SIZE; ++i)
            storage[i] = other.storage[i];

        return *this;
    }

    void print() const {
        for (int i = 0; i < size; ++i)
            std::cout << ((storage[i / BITS] >> (i % BITS)) & 1) << " ";

        std::cout << std::endl;
    }

    void insert(size_t elem) {
        assert(elem < size);
        storage[elem / BITS] |= ((size_t)1 << (elem % BITS));
    }
    void erase (size_t elem) {
        assert(elem < size);
        storage[elem / BITS] &= ~((size_t)1 << (elem % BITS));
    }
    bool in(size_t elem) {
        assert(elem < size);
        return (storage[elem / BITS] >> (elem % BITS)) & 1;
    }

    BitSet intersect(BitSet const& other) const {
        BitSet<size> res;
        for (unsigned i = 0; i < STORAGE_SIZE; ++i)
            res.storage[i] = storage[i] & other.storage[i];

        return res;
    }
    BitSet merge(BitSet const& other) const {
        BitSet<size> res;
        for (unsigned i = 0; i < STORAGE_SIZE; ++i)
            res.storage[i] = storage[i] | other.storage[i];

        return res;
    }
    BitSet invert() const {
        BitSet<size> res;
        for (unsigned i = 0; i < STORAGE_SIZE; ++i)
            res.storage[i] = storage[i] ^ FLAGS;

        return res;
    }

    std::vector<short> get_extra() const {
        std::vector<short> extra;
        for (unsigned i = 0; i < size; ++i)
            if (((storage[i / BITS] >> (i % BITS)) & 1) == 0)
                extra.push_back(i);

        return extra;
    }
private:
//    size_t *storage = nullptr;
    constexpr static unsigned BITS = sizeof(size_t) << 3;
    constexpr static unsigned STORAGE_SIZE = (size + BITS - 1) / BITS;
    std::vector <size_t> storage;
    constexpr static size_t FLAGS = -1;
};

class SudokuBoard
{
private:
    std::vector <BitSet <9>> grid_vals_;
    std::vector <BitSet <9>> col_vals_;
    std::vector <BitSet <9>> row_vals_;
    std::vector <std::vector <short>> board_;
    std::size_t N_, M_;
    std::queue <std::pair <unsigned, unsigned>> unknown_;
    unsigned stuck_count = 0;
    unsigned last_size = 0;
public:
    SudokuBoard(std::vector<std::vector<char>> const& char_board): N_(char_board.size()) {
        if (!N_) 
            throw std::logic_error("Empty sudoku board");

        M_ = char_board[0].size();

        if (!M_) 
            throw std::logic_error("Empty sudoku board");

        if ((N_ % 3) || (M_ % 3)) 
            throw std::logic_error("Sizes should be 3 multipliers");

        grid_vals_.resize((N_ / 3) * (M_ / 3));
        col_vals_.resize(M_);
        row_vals_.resize(N_);

        board_.resize(N_);
        for (unsigned i = 0; i < N_; ++i) {
            board_[i].resize(M_);

            for (unsigned j = 0; j < M_; ++j) {
                short value = 0;
                if (char_board[i][j] == '.')
                    unknown_.push({i, j});
                else if (isdigit(char_board[i][j]))
                    value = to_digit(char_board[i][j]);
                else
                    throw std::logic_error("Unknown char in board representation: " + std::to_string(char_board[i][j]));

                update_board(i, j, value);
            }
        }
    }

    void solve() {
        while (unknown_.size()) {
            auto[i, j] = unknown_.front();
            unknown_.pop();

            if (board_[i][j] == 0 && !solve(i, j))
                unknown_.push({i, j});

            // ToDo: remove
            if (unknown_.size() == last_size) {
                ++stuck_count;
                if (stuck_count == unknown_.size())
                    break;
            } else {
                last_size = unknown_.size();
                stuck_count = 1;
            }
            
            // std::cout << unknown_.size() << std::endl;
        }

        if (unknown_.size()) {
            // std::cout << "stuck with: " << unknown_.size() << std::endl;
            // std::cout << "using brute force" << std::endl;

            brute_force();
        }
    }

    std::vector <std::vector <char>> get_board() const {
        std::vector <std::vector <char>> res(N_);
        for (unsigned i = 0; i < N_; ++i) {
            res[i].resize(M_);

            for (unsigned j = 0; j < M_; ++j)
                res[i][j] = to_char(board_[i][j]);
        }

        return res;
    }
    
private:
    void update_board(unsigned i, unsigned j, short value) {
        board_[i][j] = (value > 0) ? value : 0;

        if (value > 0) {
            grid_vals_[(i / 3) * (M_ / 3) + (j / 3)].insert(value - 1);
            col_vals_[j].insert(value - 1);
            row_vals_[i].insert(value - 1);
        } else if (value < 0) {
            value = -value;
            grid_vals_[(i / 3) * (M_ / 3) + (j / 3)].erase(value - 1);
            col_vals_[j].erase(value - 1);
            row_vals_[i].erase(value - 1);
        }
    }

    bool brute_force() {
        for (int i = 0; i < N_; ++i) {
            for (int j = 0; j < M_; ++j) {
                if (!board_[i][j]) {
                    auto solutions = solutions_for_cell(i, j);
                    for (auto el : solutions) {
                        update_board(i, j, el + 1);
                        if (brute_force()) // prevents further recursion if a valid sudoko is found
                            return true;
                        else // clearing the cell if that character doesn't make a valid sudoko 
                            update_board(i, j, -el - 1);
                    }
                    return false; // returns false if no number can be filled in the empty cell
                }
            }
        }
        return true; // it means all cells are filled and hence a valid sudoko
    }

    std::vector <short> solutions_for_cell(unsigned i, unsigned j) {
        auto merge = grid_vals_[(i / 3) * (M_ / 3) + (j / 3)].merge(
            row_vals_[i].merge(col_vals_[j])
        );

        // merge.print();
        return merge.get_extra();
    }

    bool solve(unsigned i, unsigned j) {
        auto solutions = solutions_for_cell(i, j);

        if (solutions.size() == 1) {
            update_board(i, j, solutions[0] + 1);
            return true;
        }

        return false;
    }
};

int main(int argc, char const *argv[]) {
    /*
    std::vector < std::vector <char> > board = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    */

    std::vector < std::vector <char> > board = {
        {'.','.','9','7','4','8','.','.','.'},
        {'7','.','.','.','.','.','.','.','.'},
        {'.','2','.','1','.','9','.','.','.'},
        {'.','.','7','.','.','.','2','4','.'},
        {'.','6','4','.','1','.','5','9','.'},
        {'.','9','8','.','.','.','3','.','.'},
        {'.','.','.','8','.','3','.','2','.'},
        {'.','.','.','.','.','.','.','.','6'},
        {'.','.','.','2','7','5','9','.','.'}
    };
    SudokuBoard sb(board);
    sb.solve();
    auto res = sb.get_board();
    for (auto &row : res) {
        for (auto el : row)
            std::cout << el;
        std::cout << std::endl;
    }
    return 0;
}
