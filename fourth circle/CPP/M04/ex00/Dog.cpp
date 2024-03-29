#include "Dog.hpp"

Dog::Dog() {
    this->type = "Dog";
    std::cout << this->getType() << " Constructor" << std::endl;
}

Dog::~Dog() {
    std::cout << this->getType() << " Destructor" << std::endl;
}

Dog::Dog( Dog const &cpy ) : Animal() {
    this->type = cpy.type; 
    std::cout << this->getType() << " Copy Constructor" << std::endl;
}

Dog& Dog::operator=( Dog const &op ) {
    std::cout << this->getType() << " becomes ";
    if (op.getType() != this->getType())
        this->setType(op.type);
    std::cout << this->getType() << " by Surcharge d'Assignator" << std::endl;
    return (*this);
}

void Dog::makeSound() const{ 
    std::cout << " is Wouaaaf" << std::endl;
}