#include "Menu.h"
#include "FileIO.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <sstream>
#include "Menu.h"

Menu::Menu(const std::string& filePath) : dataFilePath(filePath) {
    std::vector<Product> loaded;
    if (FileIO::loadFromFile(dataFilePath, loaded)) {
        warehouse.setProducts(loaded);
        std::cout << "[OK] Загружено " << loaded.size() << " товаров из " << dataFilePath << "\n";
    } else {
        std::cout << "[INFO] Файл данных не найден. Начинаем с пустого склада.\n";
    }
}

void Menu::printHeader(const std::string& title) {
    std::cout << "\n========== " << title << " ==========\n";
}

void Menu::waitForEnter() {
    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Menu::showAllProducts() {
    showProducts(warehouse.getAllProducts(), "ВСЕ ТОВАРЫ");
}

void Menu::showProducts(const std::vector<Product>& products, const std::string& title) {
    printHeader(title);
    if (products.empty()) {
        std::cout << "Нет товаров.\n";
        return;
    }
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(20) << "Название"
              << std::setw(15) << "Категория"
              << std::setw(10) << "Цена"
              << std::setw(10) << "Кол-во"
              << std::setw(12) << "Стоимость" << "\n";
    std::cout << std::string(72, '-') << "\n";
    
    for (const auto& p : products) {
        std::cout << std::left << std::setw(5) << p.id
                  << std::setw(20) << p.name
                  << std::setw(15) << p.category
                  << std::setw(10) << p.price
                  << std::setw(10) << p.quantity
                  << std::setw(12) << p.totalCost() << "\n";
        
        // Дополнительная проверка: если цена меньше 1 рубля, но количество большое
        if (p.price < 1.0 && p.quantity > 100) {
            std::cout << "[WARNING] Возможно, цена и количество перепутаны для товара ID=" << p.id << "\n";
        }
    }
}
// Функция для безопасного получения целого числа от пользователя
int getIntInput(const std::string& prompt) {
    std::string input;
    int value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        // Проверка на пустую строку
        if (input.empty()) {
            std::cout << "Ошибка: введите число!\n";
            continue;
        }
        
        // Проверка, что все символы - цифры (или минус для отрицательных)
        bool valid = true;
        for (size_t i = 0; i < input.length(); i++) {
            if (i == 0 && input[i] == '-') continue;
            if (!isdigit(input[i])) {
                valid = false;
                break;
            }
        }
        
        if (!valid) {
            std::cout << "Ошибка: введите число (только цифры)!\n";
            continue;
        }
        
        std::stringstream ss(input);
        ss >> value;
        return value;
    }
}

// Функция для безопасного получения числа с плавающей точкой
double getDoubleInput(const std::string& prompt) {
    std::string input;
    double value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        if (input.empty()) {
            std::cout << "Ошибка: введите число!\n";
            continue;
        }
        
        bool valid = true;
        int dots = 0;
        for (size_t i = 0; i < input.length(); i++) {
            if (i == 0 && input[i] == '-') continue;
            if (input[i] == '.') {
                dots++;
                if (dots > 1) valid = false;
                continue;
            }
            if (!isdigit(input[i])) {
                valid = false;
                break;
            }
        }
        
        if (!valid) {
            std::cout << "Ошибка: введите число (цифры и точку)!\n";
            continue;
        }
        
        std::stringstream ss(input);
        ss >> value;
        return value;
    }
}

// Функция для безопасного получения строки (не пустой)
std::string getStringInput(const std::string& prompt, bool allowEmpty = false) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        if (!allowEmpty && input.empty()) {
            std::cout << "Ошибка: строка не может быть пустой!\n";
            continue;
        }
        
        return input;
    }
}

void Menu::run() {
    int choice;
    
    do {
        printHeader("ГЛАВНОЕ МЕНЮ");
        std::cout << "1. Добавить товар\n";
        std::cout << "2. Редактировать товар\n";
        std::cout << "3. Удалить товар (по ID)\n";
        std::cout << "4. Удалить товар (по названию)\n";
        std::cout << "5. Поиск по названию\n";
        std::cout << "6. Поиск по категории\n";
        std::cout << "7. Поиск по диапазону цен\n";
        std::cout << "8. Сортировка\n";
        std::cout << "9. Аналитика\n";
        std::cout << "10. Показать все товары\n";
        std::cout << "11. Сохранить в файл\n";
        std::cout << "0. Выход\n";
        
        choice = getIntInput("Ваш выбор: ");
        
        switch (choice) {
            case 1: {
                std::string name = getStringInput("Название: ");
                std::string category = getStringInput("Категория: ");
                double price = getDoubleInput("Цена: ");
                int quantity = getIntInput("Количество: ");
                
                if (price < 0) {
                    std::cout << "Ошибка: цена не может быть отрицательной!\n";
                } else if (quantity < 0) {
                    std::cout << "Ошибка: количество не может быть отрицательным!\n";
                } else if (warehouse.addProduct(name, category, price, quantity)) {
                    std::cout << "✓ Товар добавлен.\n";
                } else {
                    std::cout << "✗ Ошибка при добавлении товара.\n";
                }
                break;
            }
            case 2: {
                int id = getIntInput("ID товара: ");
                std::string name = getStringInput("Новое название: ");
                std::string category = getStringInput("Новая категория: ");
                double price = getDoubleInput("Новая цена: ");
                int quantity = getIntInput("Новое количество: ");
                
                if (price < 0) {
                    std::cout << "Ошибка: цена не может быть отрицательной!\n";
                } else if (quantity < 0) {
                    std::cout << "Ошибка: количество не может быть отрицательным!\n";
                } else if (warehouse.editProduct(id, name, category, price, quantity)) {
                    std::cout << "✓ Товар изменён.\n";
                } else {
                    std::cout << "✗ Ошибка: ID не найден или данные неверны.\n";
                }
                break;
            }
            case 3: {
                int id = getIntInput("ID товара для удаления: ");
                if (warehouse.removeProductById(id)) {
                    std::cout << "✓ Товар удалён.\n";
                } else {
                    std::cout << "✗ ID не найден.\n";
                }
                break;
            }
            case 4: {
                std::string name = getStringInput("Название товара: ");
                if (warehouse.removeProductByName(name)) {
                    std::cout << "✓ Товар удалён.\n";
                } else {
                    std::cout << "✗ Товар не найден.\n";
                }
                break;
            }
            case 5: {
                std::string substr = getStringInput("Часть названия: ", true);
                showProducts(warehouse.searchByName(substr), "РЕЗУЛЬТАТЫ ПОИСКА");
                break;
            }
            case 6: {
                std::string cat = getStringInput("Категория: ", true);
                showProducts(warehouse.searchByCategory(cat), "ТОВАРЫ КАТЕГОРИИ");
                break;
            }
            case 7: {
                double minP = getDoubleInput("Цена от: ");
                double maxP = getDoubleInput("Цена до: ");
                if (minP > maxP) {
                    std::cout << "Ошибка: минимальная цена не может быть больше максимальной!\n";
                } else {
                    showProducts(warehouse.searchByPriceRange(minP, maxP), "ТОВАРЫ В ДИАПАЗОНЕ ЦЕН");
                }
                break;
            }
            case 8: {
                printHeader("СОРТИРОВКА");
                std::cout << "1. По цене (возр)\n";
                std::cout << "2. По цене (убыв)\n";
                std::cout << "3. По кол-ву (возр)\n";
                std::cout << "4. По кол-ву (убыв)\n";
                std::cout << "5. По имени (А-Я)\n";
                std::cout << "6. По имени (Я-А)\n";
                
                int sub = getIntInput("Выбор: ");
                
                switch (sub) {
                    case 1:
                        showProducts(warehouse.sortByPrice(true), "СОРТИРОВКА ПО ЦЕНЕ (ВОЗР)");
                        break;
                    case 2:
                        showProducts(warehouse.sortByPrice(false), "СОРТИРОВКА ПО ЦЕНЕ (УБЫВ)");
                        break;
                    case 3:
                        showProducts(warehouse.sortByQuantity(true), "СОРТИРОВКА ПО КОЛ-ВУ (ВОЗР)");
                        break;
                    case 4:
                        showProducts(warehouse.sortByQuantity(false), "СОРТИРОВКА ПО КОЛ-ВУ (УБЫВ)");
                        break;
                    case 5:
                        showProducts(warehouse.sortByName(true), "СОРТИРОВКА ПО ИМЕНИ (А-Я)");
                        break;
                    case 6:
                        showProducts(warehouse.sortByName(false), "СОРТИРОВКА ПО ИМЕНИ (Я-А)");
                        break;
                    default:
                        std::cout << "Неверный выбор.\n";
                }
                break;
            }
            case 9: {
                printHeader("АНАЛИТИКА");
                std::cout << "Общая стоимость склада: " << std::fixed << std::setprecision(2) 
                          << warehouse.totalWarehouseValue() << " руб.\n";
                showProducts(warehouse.lowStockProducts(5), "ТОВАРЫ С ОСТАТКОМ <= 5 ШТ");
                showProducts(warehouse.top3MostExpensive(), "ТОП-3 САМЫХ ДОРОГИХ");
                break;
            }
            case 10:
                showAllProducts();
                break;
            case 11:
                if (FileIO::saveToFile(dataFilePath, warehouse.getAllProducts())) {
                    std::cout << "✓ Сохранено в " << dataFilePath << "\n";
                } else {
                    std::cout << "✗ Ошибка сохранения.\n";
                }
                break;
            case 0:
                std::cout << "Выход.\n";
                break;
            default:
                std::cout << "Неверный пункт меню. Введите число от 0 до 11.\n";
        }
        
        if (choice != 0) {
            waitForEnter();
        }
        
    } while (choice != 0);
}