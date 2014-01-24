#include <cstdio>

char s[4096];

int main()
{
    freopen("geometry.cpp", "r", stdin);
    freopen("script.cpp", "w", stdout);
    while (gets(s))
    {
        for (int i = 0; s[i]; ++i)
        {
            if (s[i] == '"') {
                printf("\\");
            } else if (s[i] == '\'') {
                printf("\\");
            } else if (s[i] == '\\') {
                printf("\\");
            }
            printf("%c", s[i]);
        }
        printf(" \\n");
    }
    return 0;
}
