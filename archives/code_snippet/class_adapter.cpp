#include <iostream>

class Target
{
public:
    Target() {}
    virtual ~Target() {}

public:
    virtual void Request() = 0;
};

class Adaptee
{
public:
    Adaptee(){}
    virtual ~Adaptee() {}

public:
    virtual void SpecificRequest() = 0;
};

class Adapter : public Target, public Adaptee
{
public:
    Adapter() {}
    ~Adapter() {}

public:
    void Request()
    {
        std::cout << "Transfer Specific Request to Reuest" << std::endl;
        SpecificRequest();
        std::cout << "Finally, Request" << std::endl;
    }

    void SpecificRequest()
    {
        std::cout << "Specific Request" << std::endl;
    }
};

int main()
{
    Target *target = new Adapter();
    target->Request();

    delete target;
    target = nullptr;

    return 0;
}
