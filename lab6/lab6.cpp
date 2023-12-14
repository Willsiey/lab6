#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

struct Product {
    std::string name;
    double price;
};

struct Order {
    int orderNumber;
    std::string orderDate;
    std::vector<Product> products;

    double totalCost() const {
        double sum = 0.0;
        for (const auto& product : products) {
            sum += product.price;
        }
        return sum;
    }
};

std::vector<Order> readOrdersFile(const std::string& filename) {
    std::vector<Order> orders;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return orders;
    }

    int errorCount = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Order order;
        if (!(iss >> order.orderNumber >> order.orderDate)) {
            std::cerr << "Ошибка чтения строки: " << line << std::endl;
            errorCount++;
            continue;
        }

        // Чтение продуктов
        Product product;
        while (iss >> product.name >> product.price) {
            order.products.push_back(product);
        }

        orders.push_back(order);
    }

    if (errorCount > 0) {
        std::cerr << "Количество строк с ошибками: " << errorCount << std::endl;
    }

    return orders;
}


void analyzeWriteFile(const std::vector<Order>& orders, const std::string& outputFilename) {
    std::ofstream outFile(outputFilename);
    if (!outFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи: " << outputFilename << std::endl;
        return;
    }

    double total = 0.0;
    double maxCost = 0.0;
    double minCost = std::numeric_limits<double>::max();

    for (const auto& order : orders) {
        double cost = order.totalCost();
        total += cost;
        if (cost > maxCost) maxCost = cost;
        if (cost < minCost) minCost = cost;
    }

    double average = orders.empty() ? 0 : total / orders.size();
    outFile << "Средняя стоимость заказа: " << average << "\n";
    outFile << "Максимальная стоимость заказа: " << maxCost << "\n";
    outFile << "Минимальная стоимость заказа: " << minCost << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::string inputFile = "data.txt";  // Имя файла для чтения
    std::string outputFile = "analys.txt";  // Имя файла для записи результатов

    std::vector<Order> orders = readOrdersFile(inputFile);
    analyzeWriteFile(orders, outputFile);

    std::cout << "Анализ завершен и записан в файл: " << outputFile << std::endl;
    return 0;
}
