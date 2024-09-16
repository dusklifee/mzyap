#include <iostream>
#include <vector>

class CMatrix {
private:
    int rows, cols;
    std::vector<std::vector<int>> matrix;

public:
    CMatrix(int r, int c) : rows(r), cols(c) {
        matrix.resize(rows, std::vector<int>(cols, 0));
    }

    void setMatrix(const std::vector<std::vector<int>>& data) {
        if (data.size() != rows || data[0].size() != cols) {
            std::cerr << "Error: Data dimensions do not match matrix dimensions.\n";
            return;
        }
        matrix = data;
    }

    void display() const {
        std::cout << "Matrix of size " << rows << "x" << cols << ":\n";
        for (const auto& row : matrix) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << "\n";
        }
    }

    CMatrix operator+(const CMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            std::cout << "Error: Matrix dimensions must match for addition\n";
            return CMatrix(0, 0); // Return an empty matrix
        }
        CMatrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }

    CMatrix operator-(const CMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            std::cout << "Error: Matrix dimensions must match for subtraction\n";
            return CMatrix(0, 0); // Return an empty matrix
        }
        CMatrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.matrix[i][j] = this->matrix[i][j] - other.matrix[i][j];
            }
        }
        return result;
    }

    CMatrix operator*(const CMatrix& other) const {
        if (cols != other.rows) {
            std::cout << "Error: Number of columns in the first matrix must match the number of rows in the second matrix\n";
            return CMatrix(0, 0); // Return an empty matrix
        }
        CMatrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result.matrix[i][j] = 0;
                for (int k = 0; k < cols; ++k) {
                    result.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];
                }
            }
        }
        return result;
    }

    std::vector<int> sumRows() const {
        std::vector<int> rowSums(rows, 0);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                rowSums[i] += matrix[i][j];
            }
        }
        return rowSums;
    }

    std::vector<int> sumCols() const {
        std::vector<int> colSums(cols, 0);
        for (int j = 0; j < cols; ++j) {
            for (int i = 0; i < rows; ++i) {
                colSums[j] += matrix[i][j];
            }
        }
        return colSums;
    }

    // Copy constructor
    CMatrix(const CMatrix& other) : rows(other.rows), cols(other.cols), matrix(other.matrix) {}

    // Assignment operator
    CMatrix& operator=(const CMatrix& other) {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            matrix = other.matrix;
        }
        return *this;
    }
};

int main() {
    // Set data for the first matrix
    std::vector<std::vector<int>> data1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    CMatrix mat1(3, 3);
    mat1.setMatrix(data1);

    // Set data for the second matrix
    std::vector<std::vector<int>> data2 = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };
    CMatrix mat2(3, 3);
    mat2.setMatrix(data2);

    std::cout << "First Matrix:\n";
    mat1.display();

    std::cout << "Second Matrix:\n";
    mat2.display();

    CMatrix result = mat1 + mat2;
    if (result.sumRows().size() > 0) {
        std::cout << "Matrix Addition:\n";
        result.display();
    }

    result = mat1 - mat2;
    if (result.sumRows().size() > 0) {
        std::cout << "Matrix Subtraction:\n";
        result.display();
    }

    result = mat1 * mat2;
    if (result.sumRows().size() > 0) {
        std::cout << "Matrix Multiplication:\n";
        result.display();
    }

    return 0;
}
