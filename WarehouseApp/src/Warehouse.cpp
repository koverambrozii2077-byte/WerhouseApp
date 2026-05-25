#include "Warehouse.h"
#include <algorithm>
#include <cctype>
#include <iostream> // Добавить для отладки

Warehouse::Warehouse() : nextId(1) {}

int Warehouse::generateNewId() const {
    int maxId = 0;
    for (const auto& product : products) {
        if (product.id > maxId) {
            maxId = product.id;
        }
    }
    return maxId + 1;
}

bool Warehouse::addProduct(const std::string& name, const std::string& category, double price, int quantity) {
    // Валидация входных данных
    if (name.empty() || category.empty() || price < 0 || quantity < 0) {
        std::cout << "[DEBUG] Ошибка валидации: name=" << name 
                  << ", price=" << price << ", quantity=" << quantity << "\n";
        return false;
    }
    
    // Поиск максимального ID среди существующих товаров
    int maxId = 0;
    for (const auto& product : products) {
        if (product.id > maxId) {
            maxId = product.id;
        }
    }
    
    // Создание нового товара со следующим ID
    int newId = maxId + 1;
    Product newProduct(newId, name, category, price, quantity);
    products.push_back(newProduct);
    
    // Обновляем nextId для возможного использования в других методах
    if (newId >= nextId) {
        nextId = newId + 1;
    }
    
    std::cout << "[DEBUG] Добавлен товар: ID=" << newProduct.id 
              << ", name=" << newProduct.name 
              << ", price=" << newProduct.price 
              << ", quantity=" << newProduct.quantity << "\n";
    
    return true;
}

bool Warehouse::editProduct(int id, const std::string& name, const std::string& category, double price, int quantity) {
    for (auto& p : products) {
        if (p.id == id) {
            if (name.empty() || category.empty() || price < 0 || quantity < 0) {
                std::cout << "[DEBUG] Ошибка редактирования: неверные данные\n";
                return false;
            }
            p.name = name;
            p.category = category;
            p.price = price;
            p.quantity = quantity;
            std::cout << "[DEBUG] Изменён товар ID=" << id << "\n";
            return true;
        }
    }
    std::cout << "[DEBUG] Товар с ID=" << id << " не найден\n";
    return false;
}

bool Warehouse::removeProductById(int id) {
    auto it = std::remove_if(products.begin(), products.end(), [id](const Product& p) { return p.id == id; });
    if (it != products.end()) {
        products.erase(it, products.end());
        return true;
    }
    return false;
}

bool Warehouse::removeProductByName(const std::string& name) {
    auto it = std::remove_if(products.begin(), products.end(), [&name](const Product& p) { return p.name == name; });
    if (it != products.end()) {
        products.erase(it, products.end());
        return true;
    }
    return false;
}

std::vector<Product> Warehouse::searchByName(const std::string& substring) const {
    std::vector<Product> result;
    std::string subLower = substring;
    std::transform(subLower.begin(), subLower.end(), subLower.begin(), ::tolower);
    for (const auto& p : products) {
        std::string nameLower = p.name;
        std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
        if (nameLower.find(subLower) != std::string::npos) {
            result.push_back(p);
        }
    }
    return result;
}

std::vector<Product> Warehouse::searchByCategory(const std::string& category) const {
    std::vector<Product> result;
    for (const auto& p : products) {
        if (p.category == category) result.push_back(p);
    }
    return result;
}

std::vector<Product> Warehouse::searchByPriceRange(double minPrice, double maxPrice) const {
    std::vector<Product> result;
    for (const auto& p : products) {
        if (p.price >= minPrice && p.price <= maxPrice) result.push_back(p);
    }
    return result;
}

std::vector<Product> Warehouse::sortByPrice(bool ascending) const {
    std::vector<Product> sorted = products;
    if (ascending) {
        std::sort(sorted.begin(), sorted.end(), [](const Product& a, const Product& b) { return a.price < b.price; });
    } else {
        std::sort(sorted.begin(), sorted.end(), [](const Product& a, const Product& b) { return a.price > b.price; });
    }
    return sorted;
}

std::vector<Product> Warehouse::sortByQuantity(bool ascending) const {
    std::vector<Product> sorted = products;
    if (ascending) {
        std::sort(sorted.begin(), sorted.end(), [](const Product& a, const Product& b) { return a.quantity < b.quantity; });
    } else {
        std::sort(sorted.begin(), sorted.end(), [](const Product& a, const Product& b) { return a.quantity > b.quantity; });
    }
    return sorted;
}

std::vector<Product> Warehouse::sortByName(bool ascending) const {
    std::vector<Product> sorted = products;
    if (ascending) {
        std::sort(sorted.begin(), sorted.end(), [](const Product& a, const Product& b) { return a.name < b.name; });
    } else {
        std::sort(sorted.begin(), sorted.end(), [](const Product& a, const Product& b) { return a.name > b.name; });
    }
    return sorted;
}

double Warehouse::totalWarehouseValue() const {
    double total = 0;
    for (const auto& p : products) total += p.totalCost();
    return total;
}

std::vector<Product> Warehouse::lowStockProducts(int threshold) const {
    std::vector<Product> result;
    for (const auto& p : products) {
        if (p.quantity <= threshold) result.push_back(p);
    }
    return result;
}

std::vector<Product> Warehouse::top3MostExpensive() const {
    std::vector<Product> sorted = sortByPrice(false);
    if (sorted.size() > 3) sorted.resize(3);
    return sorted;
}

void Warehouse::setProducts(const std::vector<Product>& newProducts) {
    products = newProducts;
    nextId = 1;
    for (const auto& p : products) {
        if (p.id >= nextId) nextId = p.id + 1;
    }
}

void Warehouse::clear() {
    products.clear();
    nextId = 1;
}