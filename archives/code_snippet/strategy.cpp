#include <string>
#include <iostream>

class Strategy
{
public:
    Strategy() {}
    virtual ~Strategy() {}

public:
    virtual void AlgrithmInterface() = 0;
};

class ConcreteStrategyA : public Strategy
{
public:
    ConcreteStrategyA() {}
    ~ConcreteStrategyA() {}

public:
    void AlgrithmInterface()
    {
        std::cout << "ConcreteStategyA::AlgrithmInterface()" << std::endl;
    }
};

class ConcreteStrategyB : public Strategy
{
public:
    ConcreteStrategyB() {}
    ~ConcreteStrategyB() {}

public:
    void AlgrithmInterface()
    {
        std::cout << "ConcreteStrategyB::AlgrithmInterface()" << std::endl;
    }
};


class  Context
{
public:
    Context(Strategy *strategy)
    {
        m_strategy = strategy;
    }
    ~Context() {}

public:
    void DoAction()
    {
        m_strategy->AlgrithmInterface();
    }

private:
    Strategy * m_strategy;
};

int main()
{
    Strategy *strategy = new ConcreteStrategyA();
    Context *context = new Context(strategy);

    context->DoAction();

    delete strategy;
    strategy = nullptr;
    delete context;
    context = nullptr;

    return 0;
}