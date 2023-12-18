#include "src/ops.h"
#include "src/tensor.h"
#include <iostream>

int main() {
    /* Tensor a = Tensor(2); */
    /* Tensor b = Tensor(-3); */
    /* Tensor c = Tensor(10); */
    /* Tensor e = a * b; */
    /* Tensor d = e + c; */
    /* Tensor f = Tensor(-2); */
    /* Tensor L = d * f; */
    /* Tensor L1 = L; */
    /* std::cout << L; */

    Tensor* a = new Tensor(2.0f);
    Tensor* b = new Tensor(-3.0f);

    std::cout << *a << std::endl;
    std::cout << *b << std::endl;
    auto result = Function::apply<Mul>(a, b);
    std::cout << result << std::endl;
    result.backward();
    std::cout << *a << std::endl;
    std::cout <<* b << std::endl;

    /* Tensor e = *a * *b; */ 

    /* std::cout << *a << std::endl; */
    /* std::cout << *b << std::endl; */
    

}
