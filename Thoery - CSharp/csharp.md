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

在C#中，初值一直为0。但需要**注意**的是，在一般的程序设计中，尽量不要使用不赋初值的变量，这会增大程序出错的可能性，而且C#对于函数内局部变量也不允许不赋初值。

decimal提供了一个精度更高的小数，有28到29位的有效数字，但因此它的范围更小。

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

object是一切类型的起源，可以被赋予任何值。

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

判断变量的类型：

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

空值（不建议使用）：

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

类型转换：

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

# 常用类

# 还未提到的关键字
abstract
event
new
struct
as
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
private
foreach
protected
checked
goto
public
unchecked
class
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
namespace
