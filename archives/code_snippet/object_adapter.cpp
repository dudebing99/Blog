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
    void SpecificRequest()
    {
        std::cout << "Specific Request" << std::endl;
    }
};

class Adapter : public Target
{
public:
    Adapter(Adaptee *adaptee) {}
    ~Adapter() {}

public:
    void Request()
    {
        std::cout << "Transfer Specific Request to Reuest" << std::endl;
        m_adaptee->SpecificRequest();
        std::cout << "Finally, Request" << std::endl;
    }

private:
    Adaptee * m_adaptee;
};

int main()
{
    Adaptee *adaptee = new Adaptee();
    Target *target = new Adapter(adaptee);
    target->Request();

    delete target;
    target = nullptr;

    return 0;
}
