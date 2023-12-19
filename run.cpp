#include "src/ops.h"
#include "src/tensor.h"
#include <iostream>

int main() {
    /* Tensor a = Tensor(2); */
    /* Tensor b = Tensor(-3); */
    /* Tensor e = a * b; */
    /* Tensor d = e + c; */
    /* Tensor f = Tensor(-2); */
    /* Tensor L = d * f; */
    /* Tensor L1 = L; */
    /* std::cout << L; */

    Tensor a =  Tensor(2.0f);
    Tensor b =  Tensor(-3.0f);
    Tensor c =  Tensor(10);

    std::cout << "a: " << a << std::endl;
    std::cout << "b: "<< b << std::endl;
    std::cout << "c: "<< c << std::endl;
    Tensor result = a * b;
    Tensor resultt = c * a;
    Tensor resultt3 = resultt * b;
    Tensor result2 =  resultt3 * result;

    std::cout << "result: "<< result << std::endl;
    std::cout << "result2: "<< result2 << std::endl;
    result2.backward();
    std::cout << "a: "<< a << std::endl;
    std::cout << "b: "<< b << std::endl;
    std::cout << "c: "<< c << std::endl;
    std::cout << "result: "<< result << std::endl;
    std::cout << "result2: "<< result2 << std::endl;

        
    // fix this segmentation fault:
    Tensor why = a * b * c;
    std::cout << "why: "<< why << std::endl;
    why.backward();

    // when we call backward we should clear the grads (opt.zero_grads())
    // for now we'll do it manully while we dont have optmizers

}
