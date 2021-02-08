using std::cin;
using std::cout;

class S
{
    bool has_value = false;
    bool has_eof = true;
    int value = 0;
public:
    S() {
        int x;
        if (cin >> x) {
            value += x;
            has_value = true;
            has_eof = false;
        }
    }
    S (S &&other) {
        int x;
        has_value = true;
        if (cin >> x) {
            value += other.value + x;
            has_eof = false;
        } else {
            value = other.value;
        }
    }
    ~S () {
        if (has_eof && has_value) {
            cout << value << std::endl;
        }
    }
    explicit operator bool() const {
        return !has_eof;
    }
};
