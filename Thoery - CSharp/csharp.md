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

# ������

# ��δ�ᵽ�Ĺؼ���
abstract
event
new
struct
explicit
switch
base
extern
object
this
operator
throw
break
finally
out
fixed
override
try
case
params
catch
for
foreach
checked
goto
unchecked
if
readonly
unsafe
const
implicit
ref
continue
in
return
using
virtual
default
interface
sealed
volatile
delegate
internal
void
do
sizeof
while
lock
stackalloc
else
static
enum
