#include <iostream>
#include <chrono>
#include <functional>

using MilliSeconds = std::chrono::milliseconds;
using MicroSeconds = std::chrono::nanoseconds;
using NanoSeconds = std::chrono::nanoseconds;

template<typename TimeT = MilliSeconds>
struct Measure
{
    template<typename F, typename ...Args>
    typename TimeT::rep Execution(F func, Args&&... args)
    {
        auto start = std::chrono::system_clock::now();

        // Now call the function with all the parameters you need.
        func(std::forward<Args>(args)...);

        auto duration = std::chrono::duration_cast< TimeT>
            (std::chrono::system_clock::now() - start);

        return duration.count();
    }
};

class Dummy
{
public:
    Dummy() = default;
    ~Dummy() = default;

public:
    void Add()
    {
        double sum = 0.0;
        for (int i = 0; i < 8000000; ++ i)
        {
            sum += 1.01;
        }
    }
};

void Add()
{
    double sum = 0.0;
    for (int i = 0; i < 8000000; ++i)
    {
        sum += 1.01;
    }
}

int main()
{
    Measure<MilliSeconds> measure;

    std::cout << "1. call directly" << std::endl;
    std::cout << measure.Execution([&]() {
        double sum = 0.0;
        for (int i = 0; i < 8000000; ++i)
        {
            sum += 1.01;
        }
    }) << " ms" << std::endl;

    std::cout << "2. call member function" << std::endl;
    Dummy dummy;
    std::cout << measure.Execution(std::bind(&Dummy::Add, &dummy)) << " ms " << std::endl;

    std::cout << "3. call common function" << std::endl;
    std::cout << measure.Execution(Add) << " ms" << std::endl;

    return 0;
}