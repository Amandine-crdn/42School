#ifndef DOG_HPP
#   define DOG_HPP

#   include "AAnimal.hpp"
#   include "Brain.hpp"
#   include <iostream>

class Dog : public AAnimal {

    public:
        Dog();
        ~Dog();
        Dog(Dog const &cpy);
        Dog& operator=(Dog const &op);

        void makeSound() const;
        void setBrain( std::string idea );
        void getBrain() const;
        void setValue(int i);
        int  getValue() const;

    private:
        Brain *_brain;
        int    _value;
};

#endif