#ifndef AP_HW1_H
#define AP_HW1_H

#include <vector>

using size_t = std::size_t;
using Matrix = std::vector<std::vector<double>>;
namespace algebra {
    /*
     * Return a matrix with 0 in all entries
     *                      1 in all entries
     * Usage:
     *      algebra::zeros(1, 1)
     *      algebra::ones(1, 1)
     * */
    Matrix zeros(size_t n, size_t m);
    Matrix ones (size_t n, size_t m);

    /*
     * Return a matrix with all entries between min and max
     * Note: Don't use rand and srand functions. Instead, use <random> library introduced in c++11
     * Usage:
     *      algebra::random(2, 3, 0, 10)
     * */
    Matrix random(size_t n, size_t m, double min, double  max);

    /*
     * Display the matrix in a beautiful way. Each element of the matrix
     * should have exactly 3 decimal places.
     * Note: Use the <iomanip> library to display.
     * Usage:
     *      algebra::show(algerbra::Matrix zeros(1, 1))
     * */
    void show(const Matrix& matrix);

    /*
     * Multiply the matrix into the constant scalar c.
     * */
    Matrix multiply(const Matrix& matrix, double c);

    /*
     * Multiply matrix1 into matrix2.
     * */
    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2);

    /*
     * Add c to all entries of matrix.
     * */
    Matrix sum(const Matrix& matrix, double  c);

    /*
     * Add 2 matrix to each other.(It is an element-wise addition.)
     * */
    Matrix sum(const Matrix& matrix1, const Matrix& matrix2);

    /*
     * Generate the transpose matrix of the input matrix.
     * */
    Matrix transpose(const Matrix& matrix);

    /*
     * Create the minor of the matrix with respect to nth row and mth column.
     * However, the indices in cpp start from 0.
     * eg:
     * M = {{a, b, c}, {d, e, f}, {g, h, i}}
     * algebra::minor(M, 1, 1) :
     *      {{a, c}, {g, i}}
     * */
    Matrix minor(const Matrix& matrix, size_t n, size_t m);

    /*
     * Calculate the determinant of matrix
     * Note: The matrix must be square.
     *      It is useful to make use of the function of minor.
     * */
    double determinant(const Matrix& matrix);

    /*
     * Generate the matrix's inverse.
     * Note: 1. The matrix must be square.
     *       2. The determinant of the matrix must not be zero.
     *       3. The inverse of an empty matrix is still an empty matrix.
     *       4. The inverse of a matrix is the transpose matrix with entry (i, j) is the cofactor matrix of the original
     *       matrix multiplies 1/determinant(the original matrix).
     * */
    Matrix inverse(const Matrix& matrix);

    /*
     * Concatenate two matrix with specified axis.
     * Note: axis = 0 : on top of each other.
     *       axis = 1 : alongside each other.
     * */
    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis = 0);

    /*
     * Elementary row operations(ero)
     * ero_swap: swapping two rows.
     * ero_multiply: multiplying a row into a constant number.
     * ero_sum: multiplying a row into a constant number and add it to another row.
     * Note: All the rows should contain in the matrix.
     * */
    // swap r1th row with r2th
    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2);
    // multiplies every element in rth row with constant numberc
    Matrix ero_multiply(const Matrix& matrix, size_t r, double c);
    // add r1th * c into r2th
    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2);

    /*
     * Calculate the upper triangular form of the matrix using the ERO operations defined before.
     * Note: 1. to make a upper triangular matrix you have to zero out all the elements which are below the main diagonal,
     * using the elements on the main diagonal.
     *       2. If we come across a zero on our main diagonal, we swap the first row with nonzero diagonal and the row.
     * */
    Matrix upper_triangular(const Matrix& matrix);
}
#endif //AP_HW1_H
