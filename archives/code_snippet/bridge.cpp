#include <iostream>
#include <string>

class USB
{
public:
    USB() {}
    virtual ~USB() {}

public:
    virtual void Transfer() = 0;
};

// USB 2.0
class USB20 : public USB
{
public:
    USB20() {}
    ~USB20() {}

public:
    void Transfer()
    {
        std::cout << "Transfer by USB 2.0" << std::endl;
    }
};

// USB 3.0
class USB30 : public USB
{
public:
    USB30() {}
    ~USB30() {}

public:
    void Transfer()
    {
        std::cout << "Transfer by USB 3.0, faster" << std::endl;
    }
};

class PC
{
public:
    PC() {}
    virtual ~PC() {}

public:
    virtual void Transfer(USB *usb) = 0;
};

class DellPC : public PC
{
public:
    DellPC() {}
    ~DellPC() {}

public:
    void Transfer(USB *usb)
    {
        std::cout << "Dell PC, try to transfer data by USB device" << std::endl;
        usb->Transfer();
    }
};


int main()
{
    USB *usb20 = new USB20();
    USB *usb30 = new USB30();

    PC *pc = new DellPC();

    pc->Transfer(usb20);
    pc->Transfer(usb30);

    delete usb20;
    usb20 = nullptr;
    delete usb30;
    usb30 = nullptr;
    delete pc;
    pc = nullptr;

    return 0;
}



