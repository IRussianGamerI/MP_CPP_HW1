#include <iostream>
#include "shared_ptr.h"

class Animal {
public:
    Animal() = default;

    virtual ~Animal() = default;

    virtual void speak() = 0;
};

class Dog : public Animal {
public:
    void speak() override {
        std::cout << "Woof!" << std::endl;
    }

    ~Dog() override = default;
};

class Cat : public Animal {
public:
    void speak() override {
        std::cout << "Meow!" << std::endl;
    }

    ~Cat() override = default;
};

int main() {
    // This program can demonstrate you basic principles of polymorphism in C++
    // There will be an array of base class pointers to derived classes
    std::size_t length = 1 << 16;  // A very big number
    while (length > 10) {
        std::cin >> length;  // Enter the desired length of the array (0 to exit the program)
        if (length > 10) {
            std::cout << "Please, enter a number no greater than 10: ";
        }
        if (length == 0) {
            std::cout << "Goodbye!" << std::endl;
            return 0;
        }
    }

    using PtrToAnimal = smart_pointer::shared_ptr<Animal>;

    auto zoo = smart_pointer::make_shared<PtrToAnimal[]>(length, PtrToAnimal());

    // Now you are to fill the array with cats and dogs. 'Cat' is for cat, 'Dog' is for dog"
    for (std::size_t i = 0; i < length; ++i) {
        std::string type;
        std::cin >> type;  // Enter the type
        if (type == "Dog") {
            zoo[i].reset(new Dog());
        } else if (type == "Cat") {
            zoo[i].reset(new Cat());
        } else {
            std::cout << "Please, enter a valid type of the element of the array: ";
            --i;
        }
    }

    // Now you can check if the animals are speaking correctly by entering indices of animals you desire to check
    // Enter '0' to exit the program
    while (true) {
        std::size_t index = 0;
        // Enter the desired index of the animal (from 1 to length)
        std::cin >> index;
        if (index == 0) {
            break;
        }
        if (index > length) {
            std::cout << "Please, enter a valid index of the animal: ";
            continue;
        }
        // The animal says
        zoo[index - 1]->speak();
    }

    return 0;
}
