#include "FileIO.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool FileIO::loadFromFile(const std::string& filename, std::vector<Product>& outProducts) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "[INFO] Файл " << filename << " не найден. Начинаем с пустого склада.\n";
        return false;
    }
    
    outProducts.clear();
    std::string line;
    int lineNum = 0;
    
    while (std::getline(file, line)) {
        lineNum++;
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string idStr, name, category, priceStr, quantityStr;
        
        // ПОРЯДОК: id, name, category, price, quantity
        if (std::getline(ss, idStr, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, category, ',') &&
            std::getline(ss, priceStr, ',') &&
            std::getline(ss, quantityStr, ',')) {
            
            try {
                int id = std::stoi(idStr);
                double price = std::stod(priceStr);    // ← 4-е поле = цена
                int quantity = std::stoi(quantityStr); // ← 5-е поле = количество
                
                outProducts.push_back(Product(id, name, category, price, quantity));
                std::cout << "[DEBUG] Загружен: ID=" << id << ", " << name 
                          << ", цена=" << price << ", кол-во=" << quantity << "\n";
                          
            } catch (const std::exception& e) {
                std::cout << "[ERROR] Строка " << lineNum << ": " << e.what() << "\n";
            }
        } else {
            std::cout << "[ERROR] Строка " << lineNum << ": неверный формат\n";
        }
    }
    
    file.close();
    std::cout << "[OK] Загружено " << outProducts.size() << " товаров\n";
    return true;
}

bool FileIO::saveToFile(const std::string& filename, const std::vector<Product>& products) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR] Не удалось открыть файл для записи: " << filename << "\n";
        return false;
    }
    
    for (const auto& p : products) {
        // ПОРЯДОК: id, name, category, price, quantity
        file << p.id << ","
             << p.name << ","
             << p.category << ","
             << p.price << ","      // ← цена на 4-м месте
             << p.quantity << "\n"; // ← количество на 5-м месте
             
        std::cout << "[DEBUG] Записан: ID=" << p.id << ", " << p.name 
                  << ", цена=" << p.price << ", кол-во=" << p.quantity << "\n";
    }
    
    file.close();
    std::cout << "[OK] Сохранено " << products.size() << " товаров в " << filename << "\n";
    return true;
}