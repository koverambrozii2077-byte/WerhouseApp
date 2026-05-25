#include <iostream>
#include <locale>

#ifdef _WIN32
    #include <windows.h>
#endif

void setupConsole() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001); 
        SetConsoleCP(65001);        
        setlocale(LC_ALL, "ru_RU.UTF-8");
    #else
        std::locale::global(std::locale("ru_RU.UTF-8"));
    #endif
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