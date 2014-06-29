{
    int n; int i;
    int a; int b; int c;
    {
        read n;
        if (n >= 1) then 
        {
            a = 1;
            write a
        };
        if (n >= 2) then 
        {
            b = 2;
            write b
        };
        i = 3;
        while (i <= n) do
        {
            c = a + b;
            write c;
            a = b;
            b = c;
            i = i + 1
        }
    }
}