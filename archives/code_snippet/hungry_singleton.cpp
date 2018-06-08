#include <iostream>

class Singleton {
public:
    static Singleton* Instance()
    {
        return &m_instance;
    }

private:
    Singleton() {}
    Singleton(const Singleton&) {}
    Singleton& operator=(const Singleton&) {}

    static Singleton m_instance;
};

Singleton Singleton::m_instance;

int main()
{
    Singleton *singleton1 = Singleton::Instance();
    Singleton *singleton2 = Singleton::Instance();

    if (singleton1 == singleton2)
    {
        std::cout << "Got the same instance" << std::endl;
    }
    else
    {
        std::cout << "unexpected error" << std::endl;
    }

    return 0;
}
