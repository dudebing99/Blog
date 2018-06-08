#include <iostream>

class Singleton {
public:
    static Singleton* Instance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new Singleton();
        }

        return m_instance;
    }

    static void Release()
    {
        if (m_instance != nullptr)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }

private:
    Singleton() {}
    Singleton(const Singleton&) {}
    Singleton& operator=(const Singleton&) {}

    static Singleton *m_instance;
};

Singleton *Singleton::m_instance = nullptr;

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

    singleton1->Release();

    return 0;
}

