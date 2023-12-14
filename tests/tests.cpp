#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>

std::vector<std::vector<int>> genRandMatrix(int rows, int cols, int minVal, int maxVal, double zero) {
    if (zero < 0.0 || zero > 1.0) {
        throw std::invalid_argument("Недопустимое значение вероятности");
    }

    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols, 0));

    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double randomValue = static_cast<double>(rand()) / RAND_MAX;
            if (randomValue < zero) {
                matrix[i][j] = 0;
            }
            else {
                matrix[i][j] = rand() % (maxVal - minVal + 1) + minVal;
            }
        }
    }

    return matrix;
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }
}

int countNonZeroColumns(const std::vector<std::vector<int>>& matrix, int tColumn) {
    if (tColumn < 0 || tColumn >= matrix[0].size()) {
        throw std::runtime_error("Неверный номер столбца");
    }

    int rowCount = matrix.size();
    int nonZeroColumns = 0;

    for (int i = 0; i < rowCount; ++i) {
        if (matrix[i][tColumn] != 0) {
            nonZeroColumns++;
        }
    }

    return nonZeroColumns;
}

int main() {
    try {
        setlocale(LC_ALL, "Russian");
        int rows, cols, targetColumn;
        int minValue = -5;
        int maxValue = 5;
        double zeroProbability = 0.3;  // Предусматриваемая ошибка: вероятность больше 1.0

        // Ввод размера матрицы
        std::cout << "Введите количество строк матрицы: ";
        std::cin >> rows;
        std::cout << "Введите количество столбцов матрицы: ";
        std::cin >> cols;

        // Ввод номера столбца для проверки
        std::cout << "Введите номер столбца для проверки: ";
        std::cin >> targetColumn;

        std::vector<std::vector<int>> matrix = genRandMatrix(rows, cols, minValue, maxValue, zeroProbability);

        std::cout << "Сгенерированная матрица:\n";
        printMatrix(matrix);

        int result = countNonZeroColumns(matrix, targetColumn);

        std::cout << "\nКоличество ненулевых элементов в столбце " << targetColumn << ": " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}