#include "tensor.h"
#include "ops.h"
#include <cassert>

// START Override operators
std::ostream& operator<<(std::ostream& os, const Tensor& tensor) {
    os << "Tensor<data: " << tensor.data;
    if (tensor._ctx != nullptr) {
        os  << ", srcs: [";
        for (size_t i = 0; i < tensor._ctx->inputs.size(); ++i) {
            if (i > 0) os << ", ";
            os << tensor._ctx->inputs[i]->data;  // Assuming you want to print the data of the source Tensors
        }

        os << "]";
    }
    os << ">";
    
    if (tensor.grad != nullptr) {
        os << " with grad: " << tensor.grad->data;
    }

    return os;
}

Tensor Tensor::operator*(const Tensor& other) {
  return Function::apply<Mul>(this, const_cast<Tensor*>(&other));
}
// END Override operators


// START Backpropagation
std::vector<Tensor*> Tensor::_deepwalk(
        Tensor* tensor,
        std::set<const Tensor*>& visited,
        std::vector<Tensor*>& nodes
) {
    visited.insert(tensor);

    if (tensor->_ctx != nullptr) {
        for (auto input : tensor->_ctx->inputs) {
            if (visited.find(input) == visited.end()) {
                Tensor::_deepwalk(input, visited, nodes);
            } 
            nodes.push_back(tensor);
        }
    }

    return nodes;
}

std::vector<Tensor*> Tensor::deepwalk() {
    std::set<const Tensor*> visited = {};
    std::vector<Tensor*> nodes = {};
    return Tensor::_deepwalk(this, visited, nodes);
}

void Tensor::backward() {
    std::cout << "backward()" << std::endl;

    grad = new Tensor(1.0f);
    std::vector<Tensor*> tensors = deepwalk();
    for (Tensor* t : tensors) {
        std::vector<Tensor*> grads = t->_ctx->backward(*grad);
        for (size_t i = 0; i < grads.size(); i++) {
            t->_ctx->inputs[i]->grad = grads[i];
        }
    }
}

// END Backpropagation
