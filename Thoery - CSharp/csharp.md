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

## 数组与容器

### 数组

#### 一维数组

    int[] array = new int[10];

**注意**：数组中的元素并未初始化，如果非内置类型需要初始化。

#### 高维数组

    int[,] array1 = new int[10, 10];
    int[][] array2 = new int[10][];

### 容器

容器类需要添加引用：

    using System.Collections;
    using System.Collections.Generic;

#### List

    using System;
    using System.Collections.Generic;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                List<string> array = new List<string>();
                array.Add("what");
                array.Add("the");
                array.Add("the");
                array.Remove("the");
                array.RemoveAt(0);
                foreach (var str in array)
                {
                    Console.WriteLine(str);
                }
                Console.ReadLine();
            }
        }
    }

#### Array

    using System;
    using System.Collections;
    using System.Collections.Generic;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                ArrayList array = new ArrayList();
                array.Add("what");
                array.Add(1);
                array.RemoveRange(0, 2);
                foreach (var i in array)
                {
                    Console.WriteLine(i);
                }
                Console.ReadLine();
            }
        }
    }

#### Dictionary

    using System;
    using System.Collections;
    using System.Collections.Generic;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                Dictionary<int, string> dict = new Dictionary<int, string>();
                dict[3] = "what";
                dict.Add(5, "world");
                dict.Remove(3);
                foreach (var i in dict)
                {
                    Console.WriteLine(i.Key + " " + i.Value);
                }
                Console.ReadLine();
            }
        }
    }

#### Queue

    using System;
    using System.Collections;
    using System.Collections.Generic;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                Queue queue = new Queue();
                queue.Enqueue(1);
                queue.Enqueue("2");
                while (queue.Count != 0)
                {
                    Console.WriteLine(queue.Peek());
                    queue.Dequeue();
                }
                Console.ReadLine();
            }
        }
    }

#### Stack

    using System;
    using System.Collections;
    using System.Collections.Generic;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                Stack stack = new Stack();
                stack.Push(1);
                stack.Push("2");
                while (stack.Count != 0)
                {
                    Console.WriteLine(stack.Peek());
                    stack.Pop();
                }
                Console.ReadLine();
            }
        }
    }

#### SortedList

    using System;
    using System.Collections;
    using System.Collections.Generic;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                SortedList<int, string> list = new SortedList<int, string>();
                list.Add(5, "what");
                list.Add(3, "the");
                foreach (var i in list)
                {
                    Console.WriteLine(i.Key + " " + i.Value);
                }
                Console.ReadLine();
            }
        }
    }


## 异常

### 处理异常

    using System;

    namespace Code
    {
        class Program
        {

            static void Main(string[] args)
            {
                try
                {
                    Console.WriteLine("Try");
                    int i = 0;
                    int j = 5 / i;
                }
                catch(Exception e)
                {
                    Console.WriteLine("Catch " + e.ToString());
                }
                finally
                {
                    Console.WriteLine("Finally");
                }
                Console.ReadLine();
            }
        }
    }

### 抛出异常

    using System;

    namespace Code
    {
        class Program
        {

            static void Main(string[] args)
            {
                int i = 0;
                if (i == 0)
                {
                    Exception e = new Exception();
                    throw e;
                }
                Console.ReadLine();
            }
        }
    }

## 面向对象

### 封装 Encapsulation

    namespace
    using

### 继承 Inheritance

结构不支持继承，但可以实现接口。

#### 抽象方法

##### virtual

    using System;

    namespace Code
    {
        class Program
        {
            class A
            {
                public virtual void func()
                {
                    Console.WriteLine("A");
                }
            }

            class B : A
            {
                public override void func()
                {
                    base.func();
                    Console.WriteLine("B");
                }
            }
            static void Main(string[] args)
            {
                B b = new B();
                b.func();
                Console.ReadLine();
            }
        }
    }

##### abstract

    using System;

    namespace Code
    {
        class Program
        {
            abstract class A
            {
                public abstract void func();
            }

            class B : A
            {
                public override void func()
                {
                    Console.WriteLine("B");
                }
            }
            static void Main(string[] args)
            {
                B b = new B();
                b.func();
                Console.ReadLine();
            }
        }
    }

#### sealed

禁止继续继承。

    class A {}
    sealed class B : A {}

### 多态 Polymorphism

#### operator

    using System;

    namespace Code
    {
        class Program
        {
            class Point
            {
                private int _u, _v;

                public int U
                {
                    get{return this._u;}
                    set{this._u = value;}
                }

                public int V
                {
                    get{return this._v;}
                    set{this._v = value;}
                }
                public Point()
                {
                    U = 0;
                    V = 0;
                }


                public Point(int u, int v)
                {
                    U = u;
                    V = v;
                }

                public void output()
                {
                    Console.WriteLine(U + " " + V);
                }

                public static Point operator +(Point a, Point b)
                {
                    Point c = new Point();
                    c.U = a.U + b.U;
                    c.V = a.V + b.V;
                    return c;
                }
            }
            static void Main(string[] args)
            {
                Point a = new Point(3, 4);
                Point b = new Point(5, 6);
                Point c = a + b;
                a.output();
                b.output();
                c.output();
                Console.ReadLine();
            }
        }
    }

#### explicit

利用等号赋值时，必须强制转换类型。

    public static explicit operator Point(int a)
    {
        Point c = new Point();
        c.U = a;
        c.V = a;
        return c;
    }

#### implicit

利用等号赋值时，不须强制转换类型。

    public static implicit operator Point(int a)
    {
        Point c = new Point();
        c.U = a;
        c.V = a;
        return c;
    }

#### 函数重载

    using System;

    namespace Code
    {
        class Program
        {
            static void func(int x = 5)
            {
                Console.WriteLine(x);
            }
            static void func(string x)
            {
                Console.WriteLine(x);
            }
            static void Main(string[] args)
            {
                func();
                func(1);
                func("misaka");
                Console.ReadLine();
            }
        }
    }

## 事件

    using System;

    namespace Code
    {
        class Program
        {
            public class A
            {
                public delegate void handler(object sender, string str);
                public event handler aEvent;
                public void raise()
                {
                    aEvent(this, "test");
                }
            }

            static void write1(object sender, string str)
            {
                Console.WriteLine(str.ToLower());
            }

            static void write2(object sender, string str)
            {
                Console.WriteLine(str.ToUpper());
            }

            static void Main(string[] args)
            {
                A a = new A();
                a.aEvent += new A.handler(write1);
                a.aEvent += new A.handler(write2);
                a.raise();
                Console.ReadLine();
            }
        }
    }


## 其它关键字

### extern

定义外部实现的方法。

    [DllImport("avifil32.dll")]
    private static extern void AVIFileInit();

### internal

只有在同一程序集的文件中，内部类型或成员才是可访问的，常用于组件的开发。

    public class BaseClass
    {
        internal static int x = 0;
    }

### unsafe

不安全，涉及指针操作。

### fixed

禁止垃圾回收器重定位可移动的变量，只能出现在不安全的上下文中。

    unsafe static void TestMethod()
    {
        Point pt = new Point();
        fixed (int* p = &pt.x)
        {
            *p = 1;
        }

    }

### params

参数数目可变的函数。

    public static void UseParams2(params object[] list)

### checked

* 表达式为常数时，直接编译时警告。
* 表达式为非常数时，运行时抛出异常。

    checked(a + b)

### unchecked

* 表达式为常数时，无编译警告。
* 表达式为非常数时，无异常。

    unchecked(a + b)

### readonly

变量只读。

    public readonly int y = 5;

### volatile

可以由多个同时执行的线程修改。

    public volatile int i;

### sizeof

用于获取值类型的字节大小，其它类型只能在unsafe中使用。

### lock

获取给定对象的互斥锁。

    Object thisLock = new Object();
    lock (thisLock)
    {
    }

### stackalloc

在不安全代码中，用于分配内存块。

    int* fib = stackalloc int[100];

# 代码风格

## 注释

    /// <summary>
    /// 加法运算。
    /// </summary>
    /// <param name="a">被加数</param>
    /// <param name="b">加数</param>
    /// <returns>和</returns>
    int add(int a, int b)
    {
        return a + b;
    }

## 代码

### 命名

* 类名应该是名词
* 接口名以I作为前缀
* 异常以Exception作为前缀

# 常用类

## 随机数

    using System;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                Random random = new Random();
                Console.WriteLine(random.Next(100));
                Console.WriteLine(random.NextDouble());
                Console.ReadLine();
            }
        }
    }

## 日期与时间

    using System;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                DateTime date = DateTime.Now;
                Console.WriteLine(date.Year + "-" + date.Month + "-" + date.Day);
                Console.WriteLine(date.Hour + ":" + date.Minute + ":" + date.Second);
                Console.ReadLine();
            }
        }
    }

## 文件的读写

    using System;
    using System.IO;
    using System.Text;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                StreamWriter writer = new StreamWriter("text");
                writer.WriteLine("test");
                writer.Flush();
                writer.Close();
                StreamReader reader = new StreamReader("text");
                Console.WriteLine(reader.ReadLine());
                reader.Close();
                Console.ReadLine();
            }
        }
    }


## 图像的读写

控制台工程默认没有引用System.Drawing，需要自己手动添加。

    using System;
    using System.Drawing;

    namespace Code
    {
        class Program
        {
            static void Main(string[] args)
            {
                Bitmap bitmap = new Bitmap("test.jpg");
                for (int i = 0; i < bitmap.Width; ++i)
                {
                    for (int j = 0; j < bitmap.Height; ++j)
                    {
                        Color color = bitmap.GetPixel(i, j);
                        bitmap.SetPixel(i, j, Color.FromArgb(255 - color.R, 255 - color.G, 255 - color.B);
                    }
                }
                bitmap.Save("test.jpg");
                bitmap.Dispose();
            }
        }
    }

## 文件夹的遍历

    using System;
    using System.IO;

    namespace Code
    {
        class Program
        {
            static void print(string path)
            {
                DirectoryInfo dir = new DirectoryInfo(path);
                Console.WriteLine(dir.FullName);
                if (dir.Exists)
                {
                    DirectoryInfo[] dirInfo = dir.GetDirectories();
                    foreach (var d in dirInfo)
                    {
                        if (d.Name[0] != '$' && d.Name[0] != '.')
                        {
                            print(d.FullName);
                        }
                    }
                    FileInfo[] fileInfo = dir.GetFiles();
                    foreach (var f in fileInfo)
                    {
                        print(f.FullName);
                    }
                }
            }

            static void Main(string[] args)
            {
                print("F:\\ZCoach");
                Console.ReadLine();
            }
        }
    }

