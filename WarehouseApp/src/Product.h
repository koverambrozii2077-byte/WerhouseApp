#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

struct Product {
    int id;
    std::string name;
    std::string category;
    double price;
    int quantity;

    Product() : id(0), price(0.0), quantity(0) {}
    Product(int i, const std::string& n, const std::string& c, double p, int q)
        : id(i), name(n), category(c), price(p), quantity(q) {}

    double totalCost() const { return price * quantity; }
};

#endif