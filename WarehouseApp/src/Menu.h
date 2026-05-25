#ifndef MENU_H
#define MENU_H

#include "Warehouse.h"

class Menu {
private:
    Warehouse warehouse;
    std::string dataFilePath;
    
    void printHeader(const std::string& title);
    void waitForEnter();
    void showAllProducts();
    void showProducts(const std::vector<Product>& products, const std::string& title);
    
public:
    Menu(const std::string& filePath);
    void run();
    void debugShowProduct(const Product &p);
};

#endif