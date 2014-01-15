# �﷨

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

## ���� Types

### �������� Built-in Types

<table>
    <tr><th>Type</th><th>Keyword</th></tr>
    <tr><td>����</td><td>byte sbyte char int uint long ulong short ushort</td></tr>
    <tr><td>С��</td><td>decimal double float</td></tr>
    <tr><td>������</td><td>bool</td></tr>
    <tr><td>�ַ���</td><td>string</td></tr>
    <tr><td>��Դ</td><td>object</td></tr>
</table>

#### ��ֵ���⣺

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

��C#�У���ֵһֱΪ0������Ҫ**ע��**���ǣ���һ��ĳ�������У�������Ҫʹ�ò�����ֵ�ı������������������Ŀ����ԣ�����C#���ں����ھֲ�����Ҳ����������ֵ��

#### decimal�ṩ��һ�����ȸ��ߵ�С������28��29λ����Ч���֣���������ķ�Χ��С��

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

#### object��һ�����͵���Դ�����Ա������κ�ֵ��

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

#### �жϱ��������ͣ�

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

#### ��ֵ��������ʹ�ã���

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

#### ����ת����

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

### �Զ������� Custom Types

#### �ṹ�� struct

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

Ĭ��Ϊprivate��
�ṹ�岻�ܼ̳У����Բ�����protected�ؼ��֡�
��д���ຯ���������override�ؼ��֡�

#### �� class

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

#### �ӿ� interface

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

�ӿ�ֻ����������������public�����Ρ�
���ʵ���в���Ҫoverride�ؼ��֡�

#### ö�� enum

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

ö�����Ϳ���ʹ�ó���char����κ�������

### ��ʽ����

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

### ��������

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

### ��������

    List<string> strings = new List<string>();

### ����

    const int i = 5;

### ��ֵ������

* �������ͺͽṹ�崫ֵ�����������á�
* ref��out�ؼ��ִ����á�

#### ����

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

#### ����ֵ

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

#### ref��out

ͨ����˵��ref��Ҫ�ں������ʼ����out��ζ���ں����ڳ�ʼ����

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

## �߼���ѭ��

### �߼�

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

switch���Խ��ַ�����ÿ��case�������break��

### ѭ��

#### for��foreach

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

#### ����

    goto
    continue
    break

## ����������

### ����

#### һά����

    int[] array = new int[10];

**ע��**�������е�Ԫ�ز�δ��ʼ�������������������Ҫ��ʼ����

#### ��ά����

    int[,] array1 = new int[10, 10];
    int[][] array2 = new int[10][];

### ����

��������Ҫ������ã�

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


## �쳣

### �����쳣

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

### �׳��쳣

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

## �������

### ��װ Encapsulation

    namespace
    using

### �̳� Inheritance

�ṹ��֧�ּ̳У�������ʵ�ֽӿڡ�

#### ���󷽷�

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

### ��̬ Polymorphism

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

���õȺŸ�ֵʱ������ǿ��ת�����͡�

    public static explicit operator Point(int a)
    {
        Point c = new Point();
        c.U = a;
        c.V = a;
        return c;
    }

#### implicit

���õȺŸ�ֵʱ������ǿ��ת�����͡�

    public static implicit operator Point(int a)
    {
        Point c = new Point();
        c.U = a;
        c.V = a;
        return c;
    }

#### ��������

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

# ������

## ע��

    /// <summary>
    /// �ӷ����㡣
    /// </summary>
    /// <param name="a">������</param>
    /// <param name="b">����</param>
    /// <returns>��</returns>
    int add(int a, int b)
    {
        return a + b;
    }

## ����

### ����

* ����Ӧ��������
* �ӿ�����I��Ϊǰ׺
* �쳣��Exception��Ϊǰ׺

# ������

## �ļ��Ķ�д

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


## ͼ��Ķ�д

����̨����Ĭ��û������System.Drawing����Ҫ�Լ��ֶ���ӡ�

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


# ��δ�ᵽ�Ĺؼ���
event
explicit
base
extern
operator
fixed
params
checked
unchecked
readonly
unsafe
implicit
default
sealed
volatile
delegate
internal
sizeof
lock
stackalloc
