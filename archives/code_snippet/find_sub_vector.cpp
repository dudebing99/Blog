#include <iostream>  // std::cout
#include <algorithm> // std::find_end
#include <vector>    // std::vector

bool myfunction(int i, int j)
{
    return (i == j);
}

int main()
{
    int myints[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::vector<int> haystack(myints, myints + 10);

    int needle1[] = {1, 2, 3};

    // using default comparison:
    std::vector<int>::iterator it;
    it = std::find_end(haystack.begin(), haystack.end(), needle1, needle1 + 3);

    if (it != haystack.end())
        std::cout << "needle1 last found at position " << (it - haystack.begin()) << '\n';

    int needle2[] = {4, 5, 1};

    // using predicate comparison:
    it = std::find_end(haystack.begin(), haystack.end(), needle2, needle2 + 3, myfunction);

    if (it != haystack.end())
        std::cout << "needle2 last found at position " << (it - haystack.begin()) << '\n';

    std::vector<int> needle3{3, 4, 5};
    it = std::search(haystack.begin(), haystack.end(), needle3.begin(), needle3.end());
    if (it != haystack.end())
        std::cout << "needle3 first found at position " << (it - haystack.begin()) << '\n';

    return 0;
}

