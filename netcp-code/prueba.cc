#include <iostream>

class Base {
public:
    virtual void foo() const {
        std::cout << "Base::foo()" << std::endl;
    }

    void bar() {
        std::cout << "Base::bar()" << std::endl;
    }
};

class Derived : public Base {
public:
    // Error: Cannot override a final function
    void foo() const override {
        std::cout << "Derived::foo()" << std::endl;
    }

    // Error: Cannot override a final function
    void bar() {
        std::cout << "Derived::bar()" << std::endl;
    }
};

int main() {
    Base baseObj;
    baseObj.foo();
    baseObj.bar();

    std::endl(std::cout);

    Derived derivedObj;
    derivedObj.foo();
    // Error: 'void Derived::bar()' marked 'final', but is not overridden
    derivedObj.bar();

    std::endl(std::cout);

    Base* ptBase = new Base;
    ptBase->foo();
    ptBase->bar();

    std::endl(std::cout);

    ptBase = new Derived;
    ptBase->foo();
    ptBase->bar();

    return 0;
}
