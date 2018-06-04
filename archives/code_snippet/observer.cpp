#include <iostream>
#include <list>
#include <string>

class Observer
{
public:
    Observer() {}
    virtual ~Observer() {}

public:
    virtual void Update(int status) = 0;
};

class ConcreteObserver : public Observer
{
public:
    ConcreteObserver() {}
    ~ConcreteObserver() {}

public:
    void Update(int status)
    {
        std::cout << "The target subject is changing status: " << status << std::endl;
    }
};

class Subject
{
public:
    Subject() {}
    virtual ~Subject() {}

public:
    virtual void Attach(Observer *observer) = 0;
    virtual void Detach(Observer *observer) = 0;
    virtual void Notify() = 0;
    virtual void SetStatus(int status) = 0;
    virtual int GetStatus() = 0;

private:
    int status;
};

class ConcreteSubject : public Subject
{
public:
    ConcreteSubject() {}
    virtual ~ConcreteSubject() {}

    void Attach(Observer *observer)
    {
        m_observers.push_back(observer);
    }

    void Detach(Observer* observer)
    {
        m_observers.remove(observer);
    }

    void Notify()
    {
        for (auto itor = m_observers.begin(); itor != m_observers.end(); itor++)
        {
            (*itor)->Update(m_status);
        }
    }

    void SetStatus(int status)
    {
        m_status = status;
    }

    int GetStatus()
    {
        return m_status;
    }

private:
    std::list<Observer*> m_observers;
    int m_status;
};

int main()
{
    Observer *observer = new ConcreteObserver();
    Subject *subject = new ConcreteSubject();

    subject->Attach(observer);
    subject->SetStatus(99);
    std::cout << "Subject's status: " << subject->GetStatus() << std::endl;
    subject->Notify();

    subject->Detach(observer);

    delete observer;
    observer = nullptr;
    delete subject;
    subject = nullptr;

    return 0;
}
