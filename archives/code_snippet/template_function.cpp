#include <iostream>
#include <string>

class AbstractClass
{
public:
    AbstractClass() {}
    virtual ~AbstractClass() {}

public:
    void TemplateMethod()
    {
        this->Primitive1();
        this->Primitive2();
    }

protected:
    virtual void Primitive1() = 0;
    virtual void Primitive2() = 0;
};

class ConcreteClass1 : public AbstractClass
{
public:
    ConcreteClass1() {}
    ~ConcreteClass1() {}
protected:
    void Primitive1()
    {
        std::cout << "ConcreteClass1::Primitive1()" << std::endl;
    }
    void Primitive2()
    {
        std::cout << "ConcreteClass1::Primitive2()" << std::endl;
    }
};

class ConcreteClass2 : public AbstractClass
{
public:
    ConcreteClass2() {}
    ~ConcreteClass2() {}
protected:
    void Primitive1()
    {
        std::cout << "ConcreteClass2::Primitive1()" << std::endl;
    }
    void Primitive2()
    {
        std::cout << "ConcreteClass2::Primitive2()" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    AbstractClass* p1 = new ConcreteClass1();
    AbstractClass* p2 = new ConcreteClass2();

    p1->TemplateMethod();
    p2->TemplateMethod();

    delete p1;
    p1 = nullptr;
    delete p2;
    p2 = nullptr;

    return 0;
}