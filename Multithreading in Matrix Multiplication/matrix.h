#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <thread>
#include "thread_pool.h"
#include "random.h"

template <typename T>
class Matrix
{
    /*
          l
     ._ _ _ _ _. 
     |         |
    h|         |
     |         |
     !_ _ _ _ _!
    */
    unsigned h, l;
    std::vector <T> *rows;
    static void multiplication_i_j(T &res, Matrix &a, Matrix &b, unsigned i, unsigned j) {
        res = T();
        for (unsigned k = 0; k < a.l; ++k)
            res += a[i][k] * b[k][j];
    }
public:
    Matrix(unsigned h, unsigned l, bool random = false, T min = T(), T max = T()): l(l), h(h), rows(new std::vector <T>[h]) {
        for (unsigned i = 0; i < h; ++i)
            rows[i].resize(l);
        if (random) 
            for (unsigned i = 0; i < h; ++i)
                for (unsigned j = 0; j < l; ++j)
                    rows[i][j] = getRand(min, max);
    }

    // multiplication
    static Matrix <T> multiply (Matrix <T> &a, Matrix <T> &b, unsigned threads_q = 1) {
        if (a.l != b.h)
            throw std::logic_error("a.l != b.h");

        Matrix <T> c(a.h, b.l);
        if (threads_q) {
            // Create threads at requested quantity, by the idea - number of cores + 1
            ThreadPool p (threads_q);
            for (unsigned i = 0; i < c.h; ++i) // Assigning c.h * c.l jobs
                for (unsigned j = 0; j < c.l; ++j)
                    p.doJob(std::bind(multiplication_i_j, std::ref(c[i][j]), std::ref(a), std::ref(b), i, j));
            // Thread Pool goes out of scope, so it is destroyed.
        } else {
            for (unsigned i = 0; i < c.h; ++i)
                for (unsigned j = 0; j < c.l; ++j)
                    multiplication_i_j(c[i][j], a, b, i, j);
        }
        return c;
    }

    // getters
    unsigned length() { return l; }
    unsigned height() { return h; }
    std::vector <T>& operator[] (unsigned i) { return rows[i]; }

    // ostream
    friend std::ostream& operator<< (std::ostream &out, Matrix <T> &x) {
        for (unsigned i = 0; i < x.h; ++i) {
            for (auto &value : x.rows[i]) 
                out << value << ' ';
            out << std::endl;
        }
        return out;
    }
};

#endif