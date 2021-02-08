using namespace std;

template<class T>
inline static T my_rho (const T &a, const T &b) {
    return std::abs(a - b);
}

template<class T>
inline static T my_min (const T &a, const T &b, const T &size) {
    T mini = my_rho(a, b);
    return (size - mini < mini) ? size - mini : mini;
}

template<class T>
class Coord
{
public:
    typedef T value_type;
    value_type row, col;
    Coord(value_type r = T(), value_type c = T()) : row(r), col(c) {};
};

template<class T>
T dist(const Coord<T> &box, const Coord<T> &a, const Coord<T> &b)
{
    if (my_min(a.row, b.row, box.row) < my_min(a.col, b.col, box.col)) {
        return my_min(a.col, b.col, box.col);
    } else {
        return my_min(a.row, b.row, box.row);
    }
}
