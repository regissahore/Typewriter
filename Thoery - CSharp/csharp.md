# Gammar

## Hello world!

    using System;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                Console.WriteLine("Hello world!");
                Console.ReadLine();
            }
        }
    }

## Types

### 内置类型 Built-in Types

<table>
    <tr><th>Type</th><th>Keyword</th></tr>
    <tr><td>整数</td><td>byte sbyte char int uint long ulong short ushort</td></tr>
    <tr><td>小数</td><td>decimal double float</td></tr>
    <tr><td>布尔型</td><td>bool</td></tr>
    <tr><td>字符串</td><td>string</td></tr>
    <tr><td>起源</td><td>object</td></tr>
</table>

初值问题：

    using System;

    namespace Code
    {
        class Program
        {
            static int a;
            static bool b;
            static decimal c;
            static string d;

            static void Main(string[] args)
            {
                Console.WriteLine(a);
                Console.WriteLine(b);
                Console.WriteLine(c);
                Console.WriteLine(d);
                Console.ReadLine();
            }
        }
    }

在C#中，初值一直为0。但需要*注意*的是，在一般的程序设计中，尽量不要使用不赋初值的变量，这会增大程序出错的可能性，而且C#对于函数内局部变量也不允许不赋初值。

### 自定义类型 Custom Types

# Common
