#include <vector.h>

#include <iostream>
#include <stdexcept>
#include <vector>


int main() {
    try {
        std::cout << "Dummy\n";
        core::Vector<int> vec{ 1, 2, 3, 5, 6, 7 };

        vec.insert(vec.begin() + 2, 12);

        for (auto n : vec) {
            std::cout << " " << n;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what();
    }

}