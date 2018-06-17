#include <string>
#include <iostream>

class Subject
{
public:
    Subject() {}
    virtual ~Subject() {}

public:
    virtual void Request() = 0;
};

class ConcreteSubject : public Subject
{
public:
    ConcreteSubject() {}
    ~ConcreteSubject() {}

public:
    void Request()
    {
        std::cout << "Done in ConcreteSubject" << std::endl;
    }
};

class Proxy : public Subject
{
public:
    Proxy(Subject *subject) 
    :m_subject(subject)
    {}
    ~Proxy() {}

public:
    void Request()
    {
        std::cout << "Call ConcreteSubject::Request() to do the job" << std::endl;
        m_subject->Request();
    }

private:
    Subject * m_subject;
};


int main()
{
    Subject *subject = new ConcreteSubject();
    Proxy *proxy = new Proxy(subject);

    proxy->Request();

    delete proxy;
    proxy = nullptr;
    delete subject;
    subject = nullptr;

    return 0;
}