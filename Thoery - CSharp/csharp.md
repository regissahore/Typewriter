# 语法

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

## 类型 Types

### 内置类型 Built-in Types

<table>
    <tr><th>Type</th><th>Keyword</th></tr>
    <tr><td>整数</td><td>byte sbyte char int uint long ulong short ushort</td></tr>
    <tr><td>小数</td><td>decimal double float</td></tr>
    <tr><td>布尔型</td><td>bool</td></tr>
    <tr><td>字符串</td><td>string</td></tr>
    <tr><td>起源</td><td>object</td></tr>
</table>

#### 初值问题：

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

在C#中，初值一直为0。但需要**注意**的是，在一般的程序设计中，尽量不要使用不赋初值的变量，这会增大程序出错的可能性，而且C#对于函数内局部变量也不允许不赋初值。

#### decimal提供了一个精度更高的小数，有28到29位的有效数字，但因此它的范围更小。

    using System;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                decimal m = 123.4m;
                Console.WriteLine(m);
                Console.ReadLine();
            }
        }
    }

#### object是一切类型的起源，可以被赋予任何值。

    using System;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                object o = 123.4m;
                Console.WriteLine(o);
                o = "object";
                Console.WriteLine(o);
                Console.ReadLine();
            }
        }
    }

#### 判断变量的类型：

    using System;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                object o = 123.4m;
                if (o.GetType() == typeof(decimal))
                {
                    Console.WriteLine("Decimal Test 1");
                }
                if (o is decimal)
                {
                    Console.WriteLine("Decimal Test 2");
                }
                Console.ReadLine();
            }
        }
    }

#### 空值（不建议使用）：

    using System;

    namespace Code
    {
        class Program
        {
            static int? val;

            static void Main(string[] args)
            {
                if (val == null)
                {
                    Console.WriteLine("Null test");
                }
                Console.ReadLine();
            }
        }
    }

#### 类型转换：

    using System;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                float a = 5.5f;
                int b = (int)a;
                object c = b as object;
                Console.WriteLine(c);
                Console.ReadLine();
            }
        }
    }

### 自定义类型 Custom Types

#### 结构体 struct

    using System;

    namespace Code
    {
        class Program
        {
            public struct Rect
            {
                public double left, top;
                public double width, height;
                public Rect(double left, double top, double right, double bottom)
                {
                    this.left = left;
                    this.top = top;
                    this.width = right - left;
                    this.height = bottom - top;
                }
                public override string ToString()
                {
                    return left + " " + top + " " + width + " " + height;
                }
            }
            static void Main(string[] args)
            {
                Rect rect = new Rect(10, 10, 100, 100);
                Console.WriteLine(rect.ToString());
                Console.ReadLine();
            }
        }
    }

默认为private。
结构体不能继承，所以不能用protected关键字。
重写父类函数必须加上override关键字。

#### 类 class

    using System;

    namespace Code
    {
        class Program
        {
            public class Rect : Object
            {
                protected double left, top;
                private double width, height;
                public Rect(double left, double top, double right, double bottom)
                {
                    this.left = left;
                    this.top = top;
                    this.width = right - left;
                    this.height = bottom - top;
                }
                public override string ToString()
                {
                    return left + " " + top + " " + width + " " + height;
                }
            }
            static void Main(string[] args)
            {
                Rect rect = new Rect(10, 10, 100, 100);
                Console.WriteLine(rect.ToString());
                Console.ReadLine();
            }
        }
    }

#### 接口 interface

    using System;

    namespace Code
    {
        class Program
        {
            interface IHungry
            {
                void hungry();
            }

            class Hungry : IHungry
            {
                public void hungry()
                {
                    Console.WriteLine("Hungry");
                }
            }
            static void Main(string[] args)
            {
                Hungry hungry = new Hungry();
                hungry.hungry();
                Console.ReadLine();
            }
        }
    }

接口只保存声明，不能用public等修饰。
类的实现中不需要override关键字。

#### 枚举 enum

    using System;

    namespace Code
    {
        class Program
        {
            enum Days : byte
            {
                Sat = 1, Sun, Mon, Tue, Wed, Thu, Fri
            };

            static void Main(string[] args)
            {
                Console.WriteLine(Days.Sat);
                Console.WriteLine((byte)Days.Sun);
                Console.ReadLine();
            }
        }
    }

枚举类型可以使用除了char外的任何整数。

### 隐式类型

    using System;

    namespace Code
    {
        class Program
        {

            static void Main(string[] args)
            {
                var i = "what";
                Console.WriteLine(i);
                Console.ReadLine();
            }
        }
    }

### 匿名类型

    using System;

    namespace Code
    {
        class Program
        {

            static void Main(string[] args)
            {
                var i = new { u = 1, v = "c"};
                Console.WriteLine(i.u);
                Console.WriteLine(i.v);
                Console.ReadLine();
            }
        }
    }

### 泛型类型

    List<string> strings = new List<string>();

### 常量

    const int i = 5;

### 传值和引用

* 内置类型和结构体传值，其它传引用。
* ref和out关键字传引用。

#### 参数

    using System;

    namespace Code
    {
        class Program
        {
            struct Node
            {
                public int u;
                public int v;
            }

            class CNode
            {
                public int u;
                public int v;
            }

            static void function1(int a)
            {
                a = 1;
            }

            static void function2(string b)
            {
                b = "1";
            }
            static void function3(Node c)
            {
                c.u = c.v = 1;
            }
            static void function4(CNode d)
            {
                d.u = d.v = 1;
            }
            static void Main(string[] args)
            {
                int a = 0;
                function1(a);
                Console.WriteLine(a);
                string b = "0";
                function2(b);
                Console.WriteLine(b);
                Node c;
                c.u = c.v = 0;
                function3(c);
                Console.WriteLine(c.u + " " + c.v);
                CNode d = new CNode();
                function4(d);
                Console.WriteLine(d.u + " " + d.v);
                Console.ReadLine();
            }
        }
    }

#### 返回值

    using System;

    namespace Code
    {
        class Program
        {
            class Node
            {
                public class InsideNode
                {
                    public int u, v;
                }
                private InsideNode node = new InsideNode();

                public InsideNode getInsideNode()
                {
                    return node;
                }

                public void writeLine()
                {
                    Console.WriteLine(node.u + " " + node.v);
                }
            }

            static void Main(string[] args)
            {
                Node node = new Node();
                Node.InsideNode inside = node.getInsideNode();
                node.writeLine();
                inside.u = inside.v = 1;
                node.writeLine();
                Console.ReadLine();
            }
        }
    }

#### ref和out

通常来说，ref需要在函数外初始化，out意味着在函数内初始化。

    using System;

    namespace Code
    {
        class Program
        {
            static void function(ref int i, out int j)
            {
                i = 3;
                j = 4;
            }

            static void Main(string[] args)
            {
                int i = 0, j = 1;
                function(ref i, out j);
                Console.WriteLine(i + " " + j);
                Console.ReadLine();
            }
        }
    }

## 逻辑与循环

### 逻辑

#### if

    using System;

    namespace Code
    {
        class Program
        {

            static void Main(string[] args)
            {
                if (!false && (true || false))
                {
                    Console.WriteLine("Logic!");
                }
                else
                {
                    Console.WriteLine("Masaka!");
                }
                Console.ReadLine();
            }
        }
    }

#### switch

    using System;

    namespace Code
    {
        class Program
        {

            static void Main(string[] args)
            {
                string str = "div";
                switch (str)
                {
                    case "div":
                        Console.WriteLine("div");
                        break;
                    case "nav":
                        Console.WriteLine("nav");
                        break;
                    default:
                        Console.WriteLine("default");
                        break;
                }
                Console.ReadLine();
            }
        }
    }

switch可以接字符串，每个case后必须有break。

### 循环

#### for和foreach

    using System;

    namespace Code
    {
        class Program
        {

            static void Main(string[] args)
            {
                int[] array = new int[10];
                for (int i = 0; i < array.Length; ++i )
                {
                    array[i] = i;
                }
                foreach (int i in array)
                {
                    Console.Write(array[i]);
                }
                Console.ReadLine();
            }
        }
    }

#### while

    using System;

    namespace Code
    {
        class Program
        {

            static void Main(string[] args)
            {
                int[] array = new int[10];
                int i = 0;
                while (i < 10)
                {
                    array[i] = i;
                    ++i;
                }
                do
                {
                    i -= 1;
                    Console.Write(array[i]);
                }
                while (i > 0);
                Console.ReadLine();
            }
        }
    }

#### 跳出

    goto
    continue
    break

# 常用类

# 还未提到的关键字
abstract
event
explicit
switch
base
extern
operator
throw
finally
fixed
try
params
catch
checked
unchecked
readonly
unsafe
implicit
virtual
default
sealed
volatile
delegate
internal
sizeof
lock
stackalloc
