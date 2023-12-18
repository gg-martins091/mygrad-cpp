#include "tensor.h"
#include "ops.h"
#include <cassert>

std::ostream& operator<<(std::ostream& os, const Tensor& tensor) {
    os << "Tensor<data: " << tensor.data << ", srcs: [";
    for (size_t i = 0; i < tensor.srcs.size(); ++i) {
        if (i > 0) os << ", ";
        os << tensor.srcs[i]->data;  // Assuming you want to print the data of the source Tensors
    }

    os << "]>";
    
    if (tensor.grad != nullptr) {
        os << " with grad: " << tensor.grad->data;
    }

    return os;
}

void Tensor::backward() {
    std::cout << "backward()" << std::endl;

    grad = new Tensor(1.0f);
    std::vector<Tensor*> grads = _ctx->backward(*grad);

    assert(_ctx->inputs.size() == grads.size());


    for (size_t i = 0; i < grads.size(); i++) {
        _ctx->inputs[i]->grad = grads[i];
    }

    /* for (auto& tensor : srcs) { */
    /*     if (tensor && tensor->_ctx) { */
    /*         tensor->_ctx->backward(); // Call backward on the _ctx of each tensor */
    /*     } */
    /* } */

    /* srcs[0]->grad = new Tensor(srcs[1]->data); */
    /* srcs[1]->grad = new Tensor(srcs[0]->data); */

}
