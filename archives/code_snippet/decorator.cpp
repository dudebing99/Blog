#include <iostream>
#include <string>

class Phone
{
public:
    Phone() {}
    virtual ~Phone() {}
    virtual void ShowDecorate() = 0;
};

class iPhone : public Phone
{
public:
    iPhone(std::string name)
        : m_name(name) {}
    ~iPhone() {}
    void ShowDecorate()
    {
        std::cout << "Name: " << m_name << std::endl;
    }

private:
    std::string m_name;

};

class NokiaPhone : public Phone
{
public:
    NokiaPhone(std::string name)
        : m_name(name)
    {
    }
    ~NokiaPhone()
    {
    }
    void ShowDecorate()
    {
        std::cout << "Name: " << m_name << std::endl;
    }

private:
    std::string m_name;
};

class DecoratorPhone : public Phone
{
public:
    DecoratorPhone(Phone *phone)
        : m_phone(phone)
    {
    }
    virtual void ShowDecorate()
    {
        m_phone->ShowDecorate();
    }

private:
    Phone *m_phone;
};

class DecoratePhoneA : public DecoratorPhone
{
public:
    DecoratePhoneA(Phone *ph)
        : DecoratorPhone(ph)
    {
    }
    void ShowDecorate()
    {
        DecoratorPhone::ShowDecorate();
        AddDecorate();
    }

private:
    void AddDecorate()
    {
        std::cout << "Decorator: HiFi Audio System" << std::endl;
    }
};

class DecoratePhoneB : public DecoratorPhone
{
public:
    DecoratePhoneB(Phone *ph)
        : DecoratorPhone(ph)
    {
    }
    void ShowDecorate()
    {
        DecoratorPhone::ShowDecorate();
        AddDecorate();
    }

private:
    void AddDecorate()
    {
        std::cout << "Decorator: Duel Camera" << std::endl;
    }
};

int main()
{
    Phone *nokia = new NokiaPhone("Nokia N8");
    Phone *iphone = new iPhone("iPhone 4");
    Phone *dpa = new DecoratePhoneA(nokia);
    Phone *dpb = new DecoratePhoneB(iphone);

    nokia->ShowDecorate();
    dpa->ShowDecorate();
    dpb->ShowDecorate();

    delete nokia;
    nokia = nullptr;
    delete iphone;
    iphone = nullptr;
    delete dpa;
    dpa = nullptr;
    delete dpb;
    dpb = nullptr;

    return 0;
}
