#ifndef TENSOR_H
#define TENSOR_H

#include <iostream>
#include <vector>
#include <memory>

class Function;

class Tensor {
  private:
    const std::vector<Tensor*> srcs;

  public:
    float data;
    std::shared_ptr<Function> _ctx;
    Tensor* grad;

    Tensor() { }

    Tensor(float d, const std::vector<Tensor*>& srcs = {})
      : data(d), srcs(srcs), grad (nullptr) {}

    // copy constructor should we keep the sources and grad?
    Tensor(const Tensor& other): grad(nullptr) { data = other.data; }

    // copy assignment operator
    Tensor& operator=(const Tensor& other) noexcept {
      if (this != &other) {  // Protect against self-assignment
          data = other.data;  // Copy the data field
          grad = nullptr;   
      }
      return *this;
    }

    // move assignment operator
    Tensor& operator=(Tensor&& other) noexcept {
        if (this != &other) {
            delete grad;  // Release any existing resource.

            data = other.data;
            /* srcs = std::move(other.srcs); */
            /* grad = other.grad; */

            other.grad = nullptr;  // Again, prevent the source from deleting the memory.
        }
        return *this;
    }

    // move constructor 
    Tensor(Tensor&& other) noexcept
      : data(other.data), srcs(std::move(other.srcs)), grad(other.grad) {
        // Optionally set the source object's members to default values
        /* std::cout << "Move constructor " << other << std::endl; */
        other.data = 0;
        other.grad = nullptr;
    }

    ~Tensor() {
        delete grad;
    }

    Tensor operator+(const Tensor& other) { return Tensor(data + other.data, {this, const_cast<Tensor*>(&other)}); }
    Tensor operator-(const Tensor& other) { return Tensor(data - other.data, {this, const_cast<Tensor*>(&other)}); }
    Tensor operator*(const Tensor& other) { return Tensor(data * other.data, {this, const_cast<Tensor*>(&other)}); }
    Tensor operator/(const Tensor& other) { return Tensor(data / other.data, {this, const_cast<Tensor*>(&other)}); }

    friend std::ostream& operator<<(std::ostream& os, const Tensor& tensor);

    void backward();
};


#endif
