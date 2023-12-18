#ifndef OPS_H
#define OPS_H

#include <vector>
#include <memory>
#include "tensor.h"

class Function {
  protected:

  public:
    const std::vector<Tensor*> inputs;
    Function(const std::vector<Tensor*> inputs): inputs(inputs) {}

    virtual Tensor forward(const std::vector<Tensor>& args) {
        throw std::runtime_error("forward not implemented for " + std::string(typeid(*this).name()));
    }

    virtual std::vector<Tensor*> backward(const Tensor& grad_output) {
        throw std::runtime_error("backward not implemented for " + std::string(typeid(*this).name()));
    }

    template<typename F, typename... Tensors>
    static Tensor apply(Tensors... tensors) {
        static_assert(std::is_base_of<Function, F>::value, "F must be a subclass of Function");
        
        std::vector<Tensor*> tensorVec = {tensors...};
        auto ctx = std::make_shared<F>(tensorVec);

  
        std::vector<Tensor> tensorsVec;
        for (auto& tensor : tensorVec) {
            tensorsVec.push_back(tensor->data);
        }

        Tensor retData = ctx->forward(tensorsVec);
        Tensor ret(retData);

        ret._ctx = ctx;
        return ret;
    }
};


class Mul : public Function {
  private:
    Tensor x, y;

  public:
    /* using Function::Function; // Inherit constructors */
    Mul(const std::vector<Tensor*>& tensors)
        : Function(tensors) {}

    Tensor forward(const std::vector<Tensor>& args) override {
        this->x = args[0];
        this->y = args[1];
        return x * y;
    }

    std::vector<Tensor*> backward(const Tensor& grad_output) override {
      return {new Tensor(this->y * grad_output), new Tensor(this->x * grad_output)};
    }
};



#endif
