#include <iostream>
#include <locale>

void setupConsole() {
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::locale::global(std::locale("en_US.UTF-8"));
    // Не отключаем синхронизацию на macOS
}

#include "Menu.h"

int main() {
    setupConsole();
    
    std::cout << "=== Warehouse App ===" << std::endl;
    std::cout << "Система учёта товаров на складе\n" << std::endl;
    
    Menu menu("data/products.txt");
    menu.run();
    
    return 0;
}