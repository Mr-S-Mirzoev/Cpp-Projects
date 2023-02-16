namespace Game {
    template <typename T>
    class Coord {
    public:
        typedef T value_type;
        value_type row, col;
        Coord(value_type r = T(), value_type c = T()) : row(r), col(c) {};
    };

    template<class T>
    T dist(const Coord<T> &box, const Coord<T> &a, const Coord<T> &b)
    {
        T xd = std::abs(a.row - b.row);
        T yd = std::abs(a.col - b.col); 
        if (a.row < b.row) {
            return yd + std::max(xd - ((yd + (1 - (a.col & 1))) >> 1), T());
        } else {
            return yd + std::max(xd - ((yd + (1 - (b.col & 1))) >> 1), T());
        }
    }
}
