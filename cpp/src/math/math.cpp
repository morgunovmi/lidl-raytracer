#include "math/math.h"

namespace slr {
    template <typename T>
    T clip(const T& n, const T& lower, const T& upper) {
        return std::max(lower, std::min(n, upper));
    }

template<>
    template<>
    Vec3<int>::Vec3(const Vec3<float>& v) : x(static_cast<int>(v.x + .5)),
                                            y(static_cast<int>(v.y + .5)),
                                            z(static_cast<int>(v.z + .5)) {
    }

    template<>
    template<>
    Vec3<float>::Vec3(const Vec3<int>& v) : x(static_cast<float>(v.x)), y(static_cast<float>(v.y)), z(
            static_cast<float>(v.z)) {
    }

    Matrix::Matrix(std::size_t row, std::size_t col) : mCols(col), mRows(row),
                                                       mMatrix(std::vector<std::vector<float>>(row,
                                                                                               std::vector<float>(col,
                                                                                                                  0.f))) {
    }

    Matrix Matrix::eye(std::size_t size) {
        Matrix mat{size, size};
        for (std::size_t i = 0; i < size; ++i) {
            for (std::size_t j = 0; j < size; ++j) {
                mat[i][j] = (i == j) ? 1 : 0;
            }
        }
        return mat;
    }

    std::vector<float>& Matrix::operator[](std::size_t i) {
        assert(i < mRows);
        return mMatrix[i];
    }

    Matrix Matrix::operator*(const Matrix& m) const {
        assert(mCols == m.mRows);
        Matrix res{mRows, m.mCols};
        for (std::size_t i = 0; i < mRows; ++i) {
            for (std::size_t j = 0; j < m.mCols; ++j) {
                for (std::size_t k = 0; k < mCols; ++k) {
                    res[i][j] += mMatrix[i][k] * m.mMatrix[k][j];
                }
            }
        }
        return res;
    }

    Matrix Matrix::transpose() {
        Matrix res{mCols, mRows};
        for (std::size_t i = 0; i < mRows; ++i) {
            for (std::size_t j = 0; j < mCols; ++j) {
                res[j][i] = mMatrix[i][j];
            }
        }
        return res;
    }

    std::ostream& operator<<(std::ostream& s, const Matrix& m) {
        for (const auto& vec: m.mMatrix) {
            s << "| ";
            for (const auto val: vec) {
                s << val << " ";
            }
            s << "|\n";
        }
        return s;
    }
}
