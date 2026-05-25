#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <vector>
#include "Product.h"

class FileIO {
public:
    static bool loadFromFile(const std::string& filename, std::vector<Product>& outProducts);
    static bool saveToFile(const std::string& filename, const std::vector<Product>& products);
};

#endif