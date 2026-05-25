#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include <list>
#include <string>
#include "Product.h"

class Warehouse {
private:
    std::vector<Product> products; // можно заменить на std::list
    int nextId;

public:
    int generateNewId() const;
    Warehouse();

    // CRUD
    bool addProduct(const std::string& name, const std::string& category, double price, int quantity);
    bool editProduct(int id, const std::string& name, const std::string& category, double price, int quantity);
    bool removeProductById(int id);
    bool removeProductByName(const std::string& name);
    
    // Поиск
    std::vector<Product> searchByName(const std::string& substring) const;
    std::vector<Product> searchByCategory(const std::string& category) const;
    std::vector<Product> searchByPriceRange(double minPrice, double maxPrice) const;
    
    // Сортировка (возвращают копию)
    std::vector<Product> sortByPrice(bool ascending) const;
    std::vector<Product> sortByQuantity(bool ascending) const;
    std::vector<Product> sortByName(bool ascending) const;
    
    // Аналитика
    double totalWarehouseValue() const;
    std::vector<Product> lowStockProducts(int threshold = 5) const;
    std::vector<Product> top3MostExpensive() const;
    
    // Доступ к данным
    const std::vector<Product>& getAllProducts() const { return products; }
    void setProducts(const std::vector<Product>& newProducts);
    void clear();
    bool isEmpty() const { return products.empty(); }
};



#endif