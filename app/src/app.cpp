#include <vector.h>

#include <iostream>
#include <stdexcept>
#include <vector>


int main() {
    try {
        std::cout << "Dummy\n";
        core::Vector<int> vec{};
        vec.pushBack(3);
        vec.pushBack(2);
        vec.pushBack(1);

        vec.popBack();

        for (auto it = vec.begin(); it != vec.end(); ++it) {
            int item = *it;
            std::cout << item;
        }

        for (auto n : vec) {
            std::cout << " " << n;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception occurred: " << ex.what();
    }

}