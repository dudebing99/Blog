#include <stdio.h>
#include <string.h>

// char *strtok(char *str, const char *delim);
// char *strtok_r(char *str, const char *delim, char **saveptr);

void Split()
{
    char str[] = "1, hello, world";
    char *ptr = strtok(str, ",");
    
    while (ptr != NULL)
    {
        printf("%s\n", ptr);
        ptr = strtok(NULL, ",");
    }
}

void Split2()
{
    char str[] = "2, hello, world";
    char *buf = NULL;
    char *ptr = strtok_r(str, ",", &buf);
    
    while (ptr != NULL)
    {
        printf("%s\n", ptr);
        ptr = strtok_r(NULL, ",", &buf);
    }
}

int main()
{
    Split();
    Split2();

    return 0;
}
