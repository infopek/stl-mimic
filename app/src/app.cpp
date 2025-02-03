#include <vector.h>

#include <iostream>
#include <stdexcept>

int main() {
    try {
        std::cout << "Dummy\n";
        core::Vector vec{};
        vec.add(3);
        vec.add(2);
        vec.add(1);

        for (size_t i = 0; i < 3; i++) {
            std::cout << " " << vec[i];
        }

        vec.pop();

        for (size_t i = 0; i < 3; i++) {
            std::cout << " " << vec[i];
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what();
    }
}