# Linear algebra library for C++

Matrix class which enables efficient vector and matrix storage and operations on them.

## Indexing
`
Matrix m supports m[{i, j}] indexing
Vector v supports m[i] indexing

double& operator[](Index idx);
double  operator[](Index idx) const;
`
Matrix& operator=(Matrix &&rhs);
Matrix& operator=(const Matrix &rhs);
bool operator==(const Matrix &rhs) const;

#define ELEMENT_WISE_OPERATION_DEF(NAME) Matrix& NAME(const Matrix &rhs)
ELEMENT_WISE_OPERATION_DEF(operator+);
ELEMENT_WISE_OPERATION_DEF(operator-);
ELEMENT_WISE_OPERATION_DEF(dot);

Matrix operator*(const Matrix &rhs);
Matrix operator^(int pow);
/**
    * A = this[:idx] (so it has to be > 0)
    * B = this[idx:]
    */
void split(Matrix *a, Matrix *b, std::size_t idx, bool horizontal = false) const;

friend std::ostream& operator<<(std::ostream& os, const Matrix& m);