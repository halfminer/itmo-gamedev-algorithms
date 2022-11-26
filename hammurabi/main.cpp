#include <iostream>
#include "utils.h"
#include "resources.h"

int main() {
    resources city;

    for (size_t round = 0; round < utils::ROUNDS && !city.checkLooseCondition(); round++) {
        std::cout << "Round: " << round + 1 << std::endl;
    }
    return 0;
}