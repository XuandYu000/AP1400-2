#include "hw1.h"

#include <random>
#include <iostream>
#include <iomanip>
#include <stdexcept>

namespace algebra {
    Matrix matrixCreator(size_t n, size_t m, double k) {
        Matrix res;
        for(size_t i = 0; i < n; i++) {
            std::vector<double> arr;
            for(size_t j = 0; j < m; j++) {
                arr.push_back(k);
            }
            res.push_back(arr);
        }
        return res;
    }

    Matrix matrixCreator(const Matrix& matr) {
        size_t rows = matr.size();
        size_t cols = matr[0].size();

        Matrix res;
        for(size_t i = 0; i < rows; i++) {
            std::vector<double> arr;
            for(size_t j = 0; j < cols; j++) {
                arr.push_back(matr[i][j]);
            }
            res.push_back(arr);
        }
        return res;
    }

    Matrix zeros(size_t n, size_t m) {
        return matrixCreator(n, m, 0);
    }

    Matrix ones(size_t n, size_t m) {
        return matrixCreator(n, m, 1);
    }

    Matrix random(size_t n, size_t m, double min, double max) {
        if(min > max) {
            throw std::logic_error("Min cannot be greater than max.");
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);

        Matrix res;
        for(size_t i = 0; i < n; i++) {
            std::vector<double> arr;
            for(size_t j = 0; j < m; j++) {
                arr.push_back(dis(gen));
            }
            res.push_back(arr);
        }
        return res;
    }

    void show(const Matrix& matrix) {
        for(auto& i : matrix) {
            for(auto& j : i) {
                std::cout << std::fixed << std::setprecision(3) << j << " ";
            }
            std::cout<<std::endl;
        }
    }

    Matrix multiply(const Matrix& matrix, double c) {
        Matrix res = matrixCreator(matrix);

        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        for(size_t i = 0; i < rows; i++) {
            for(size_t j = 0; j < cols; j++) {
                res[i][j] *= c;
            }
        }

        return res;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
        if(matrix1.empty()) {
            return Matrix{};
        }
        if(matrix1[0].size() != matrix2.size()) {
            throw std::logic_error("The number of columns of matrix1 must be equal to the number of rows of matrix2.");
        }

        Matrix res = zeros(matrix1.size(), matrix2[0].size());
        for(size_t i = 0, len1 = matrix1.size(); i < len1; i++) {
            for(size_t j = 0, len2 = matrix2[0].size(); j < len2; j++) {
                for(size_t k = 0, len3 = matrix2.size(); k < len3; k++) {
                    res[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        return res;
    }

    Matrix sum(const Matrix& matrix, double c) {
        if (matrix.empty()) {
            return Matrix{};
        }
        Matrix res = matrixCreator(matrix);
        for (size_t i = 0, len1 = res.size(); i < len1; i++){
            for (size_t j = 0, len2 = res[0].size(); j < len2; j++) {
                res[i][j] += c;
            }
        }
        return res;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
        if(matrix1.empty() && matrix2.empty()) {
            return Matrix{};
        }
        if (matrix1.size() != matrix2.size() || matrix1[0].size() != matrix2[0].size()) {
            throw std::logic_error("The size of both matrix must be equal.");
        }
        Matrix res = matrixCreator(matrix1);
        for (size_t i = 0, len1 = res.size(); i < len1; i++){
            for (size_t j = 0, len2 = res[0].size(); j < len2; j++) {
                res[i][j] += matrix2[i][j];
            }
        }
        return res;
    }

    Matrix transpose(const Matrix& matrix) {
        if(matrix.empty()) {
            return Matrix{};
        }

        Matrix resMatrix = matrixCreator(matrix[0].size(), matrix.size(), 0);
        for(size_t i = 0, len1 = resMatrix.size(); i < len1; i++) {
            for(size_t j = 0, len2 = resMatrix[i].size(); j < len2; j++) {
                resMatrix[i][j] = matrix[j][i];
            }
        }

        return resMatrix;
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m) {
        size_t rows = matrix.size();
        size_t cols = matrix[0].size();
        if (n >= rows || m >= cols) {
            throw std::logic_error("The n must less than rows of matrix, the m must less than cols of matrix.");
        }

        Matrix resMatrix = zeros(matrix.size() - 1, matrix[0].size() - 1);
        for(size_t i = 0, len1 = matrix.size(), ii = 0; i < len1; i++, ii++) {
            if(i == n) {
                ii --;
                continue;
            }
            for(size_t j = 0, len2 = matrix[0].size(), jj = 0; j < len2; j++, jj++) {
                if(j == m) {
                    jj --;
                    continue;
                }
                resMatrix[ii][jj] = matrix[i][j];
            }
        }
        return resMatrix;
    }

    double determinant(const Matrix& matrix) {
        if(matrix.empty()) return 1.0;
        if (matrix.size() != matrix[0].size()) {
            throw std::logic_error("The matrix must be square.");
        }
        if(matrix.size() == 1) {
            return matrix[0][0];
        }

        double res = 0;
        for(size_t j = 0, len = matrix.size(); j < len; j++) {
            auto flag = [](int x){return (x & 1) == 1 ? -1 : 1 ;};
            res += flag(j) * matrix[0][j] * determinant(minor(matrix, 0, j));
        }

        return res;
    }

    Matrix inverse(const Matrix& matrix) {
        if (matrix.empty()) { return Matrix{};}

        if (matrix.size() != matrix[0].size()) {
            throw std::logic_error("The matrix must be square.");
        }

        // Get the determinant.
        double det = determinant(matrix);
        if(det == 0) {
            throw std::logic_error("The matrix doesn't have an inverse when the determinant is zero.");
        }

        // Get the cofactor matrix of the original matrix.
        auto flag = [](int x){return (x & 1) == 1 ? -1 : 1;};
        Matrix resMatrix = zeros(matrix.size(), matrix[0].size());
        for (size_t i = 0, len1 = matrix.size(); i < len1; i++) {
            for (size_t j = 0, len2 = matrix[i].size(); j < len2; j++) {
                resMatrix[i][j] = flag(i + j) * determinant(minor(matrix, i, j));
            }
        }

        // Transpose the cofactor matrix.
        resMatrix = transpose(resMatrix);

        // Multiply 1/determinant(original matrix)
        return multiply(resMatrix, 1 / det);
    }

    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
        if (matrix1.empty() && matrix2.empty()) {return Matrix{};}

        if(axis == 0 && matrix1[0].size() != matrix2[0].size()) {
            throw std::logic_error("The size of columns of two matrix should be equal if axis = 0.");
        }

        if(axis == 1 && matrix1.size() != matrix2.size()) {
            throw std::logic_error("The size of rows of two matrix should be equal if axis = 1.");
        }

        Matrix resMatrix;
        if(!axis) {
            resMatrix = zeros(matrix1.size() + matrix2.size(), matrix1[0].size());
            size_t rowNum = 0;
            int colSize = matrix1[0].size();
            while(rowNum != matrix1.size() + matrix2.size()) {
                if(rowNum < matrix1.size()) {
                    for(int j = 0; j < colSize; j++) {
                        resMatrix[rowNum][j] = matrix1[rowNum][j];
                    }
                } else {
                    for(int j = 0; j < colSize; j++) {
                        resMatrix[rowNum][j] = matrix2[rowNum - matrix1.size()][j];
                    }
                }
                rowNum ++;
            }
        } else {
            resMatrix = zeros(matrix1.size(), matrix1[0].size() + matrix2[0].size());
            size_t rowSize = matrix1.size();
            for (int i = 0; i < rowSize; i++) {
                size_t colNum = 0;
                while(colNum != matrix1[0].size() + matrix2[0].size()) {
                    if(colNum < matrix1[0].size()) {
                        resMatrix[i][colNum] = matrix1[i][colNum];
                    } else {
                        resMatrix[i][colNum] = matrix2[i][colNum - matrix1[0].size()];
                    }
                    colNum++;
                }
            }
        }
        return resMatrix;
    }

    Matrix ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
        if (r1 >= matrix.size() || r2 >= matrix.size()) {
            throw std::logic_error("The row's number should be less than the size of rows.");
        }
        if(r1 == r2) return matrix;
        if(r1 > r2) std::swap(r1, r2);
        Matrix resMatrix;
        for(size_t i = 0, len1 = matrix.size(); i < len1; i++) {
            if(i == r1) {
                resMatrix.push_back(matrix[r2]);
            } else if (i == r2) {
                resMatrix.push_back(matrix[r1]);
            } else {
                resMatrix.push_back(matrix[i]);
            }
        }
        return resMatrix;
    }

    Matrix ero_multiply(const Matrix& matrix, size_t r, double c) {
        if (r >= matrix.size()) {
            throw std::logic_error("The row's number should be less than the size of rows.");
        }
        Matrix resMatrix;
        for(size_t i = 0, len1 = matrix.size(); i < len1; i++) {
            if(i == r) {
                std::vector<double> specialRow;
                for (size_t j = 0, len2 = matrix[i].size(); j < len2; j++) {
                    specialRow.push_back(matrix[i][j] * c);
                }
                resMatrix.push_back(specialRow);
            } else {
                resMatrix.push_back(matrix[i]);
            }
        }
        return resMatrix;
    }

    Matrix ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
        if (r1 >= matrix.size() || r2 >= matrix.size()) {
            throw std::logic_error("The row's number should be less than the size of rows.");
        }

        std::vector<double> specialRow;
        for (size_t j = 0, len2 = matrix[r2].size(); j < len2; j++) {
            specialRow.push_back(matrix[r2][j] + matrix[r1][j] * c);
        }

        Matrix resMatrix;
        for (size_t i = 0, len1 = matrix.size(); i < len1; i++) {
            if(i == r2) {
                resMatrix.push_back(specialRow);
            } else {
                resMatrix.push_back(matrix[i]);
            }
        }

        return resMatrix;
    }

    Matrix upper_triangular(const Matrix& matrix) {
        if (matrix.empty()) return Matrix{};
        if (matrix.size() != matrix[0].size()) {
            throw std::logic_error("non-square matrices have no upper triangular form");
        }

        Matrix resMatrix = matrixCreator(matrix);
        auto flag = [](double x, double y){return x >= y ? 1 : -1;};
        for (size_t i = 0, len1 = matrix.size(); i < len1; i++) {
            if (resMatrix[i][i] == 0) {
                for(size_t j = i + 1; j < len1; j++) {
                    if(resMatrix[j][j] != 0) {
                        resMatrix = ero_swap(resMatrix, i, j);
                        break;
                    }
                }
            }
            for (size_t j = i + 1; j < len1; j++) {
                double multiplier = flag(resMatrix[i][i] * resMatrix[i][i], resMatrix[j][i] * resMatrix[j][i]) * resMatrix[j][i] / resMatrix[i][i];
                resMatrix = ero_sum(resMatrix, i, multiplier, j);
            }
        }

        return resMatrix;
    }
}