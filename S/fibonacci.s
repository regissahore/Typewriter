{
    int n; int i;
    int a; int b; int c;
    {
        read n;
        if (n >= 1) then 
        {
            i = 1;
            write i
        };
        if (n >= 2) then 
        {
            i = 2;
            write i
        };
        i = 3;
        a = 1;
        b = 2;
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