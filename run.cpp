#include "src/tensor.h"
#include <iostream>

int main() {
    Tensor t = Tensor(4);
    std::cout << t.v;
    Tensor a = Tensor(1);
    Tensor b = Tensor(2);
}
