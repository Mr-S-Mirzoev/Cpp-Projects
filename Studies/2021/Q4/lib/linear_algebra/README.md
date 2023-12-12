# Linear algebra library for C++

Matrix class which enables efficient vector and matrix storage and operations on them.

## Indexing
`
Matrix m supports m[{i, j}] indexing
Vector v supports m[i] indexing

double& operator[](Index idx);
double  operator[](Index idx) const;
`

## Arithmetical operations

Element-wise:
`
Matrix a, b;
a.dot(b), a + b, a - b
`

Multiplexing:
`
Matrix a, b;
a * b
`

Power:
`
Matrix a;
a ^ (3), a ^ (-4), a ^ (0)
`
Matrix operator^(int pow);

## Block matrix tools

To split matrix into [A1 A2] or [ B1 / B2] (horizontaly)
`
void split(Matrix *a, Matrix *b, std::size_t idx, bool horizontal = false) const;
`

Merge matrix accordingly:
`
Matrix merge(const Matrix &a, const Matrix &b, bool horizontal = false);
`

## Print matrix

ostream support:
`
Matrix a = eye(4);
std::cout << a << std::endl;
`
