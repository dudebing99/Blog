#include <iostream>
#include <string>

class Phone
{
  public:
    Phone() {}
    virtual ~Phone() {}
    virtual void ShowDecorate() {}
};

class iPhone : public Phone //具体手机类
{
  private:
    std::string name;

  public:
    iPhone(std::string _name)
        : name(_name) {}
    ~iPhone() {}
    void ShowDecorate()
    {
        std::cout << "手机: " << name << std::endl;
    }
};

class NokiaPhone : public Phone
{
  private:
    std::string name;

  public:
    NokiaPhone(std::string _name)
        : name(_name)
    {
    }
    ~NokiaPhone()
    {
    }
    void ShowDecorate()
    {
        std::cout << "手机: " << name << std::endl;
    }
};

class DecoratorPhone : public Phone
{
  private:
    Phone *m_phone; //要装饰的手机
  public:
    DecoratorPhone(Phone *phone)
        : m_phone(phone)
    {
    }
    virtual void ShowDecorate()
    {
        m_phone->ShowDecorate();
    }
};

//具体的装饰 A
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
        std::cout << "增加挂件" << std::endl;
    }
};

//具体的装饰 B
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
        std::cout << "屏幕贴膜" << std::endl;
    }
};

int main()
{
    Phone *ph = new NokiaPhone("1050");
    Phone *dpa = new DecoratePhoneA(ph); //增加挂件
    Phone *dpb = new DecoratePhoneB(ph); //增加贴膜

    ph->ShowDecorate();
    dpa->ShowDecorate();
    dpb->ShowDecorate();

    delete ph;
    delete dpa;
    delete dpb;

    return 0;
}