#include <iostream>
#include <mutex>

template<typename T>
class Singleton {
public:
    static T* Instance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new T();
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

    static T *m_instance;
};

template<typename T>
T *Singleton<T>::m_instance = nullptr;

class A
{
public:
    void SayHello()
    {
        std::cout << "hello world" << std::endl;
    }
};

int main()
{
    A *a1 = Singleton<A>::Instance();
    A *a2 = Singleton<A>::Instance();
    if (a1 == a2)
    {
        std::cout << "Got the same instance" << std::endl;
    }
    else
    {
        std::cout << "unexpected error" << std::endl;
    }

    a1->SayHello();

    return 0;
}