# 标题

在行首输入1~6个'#'对应着6阶标题。

    # H1
    ## H2
    ###### H6
	
对应的效果为：
# H1
## H2
###### H6


# 列表

列表支持星号、加号、减号和数字，在使用数字时，数字的内容不会影响输出的结果。

    * 杨
    * 教
    * 授

    6. 杨
    2. 教
    7. 授
	
对应的效果为：

* 杨
* 教
* 授

6. 杨
2. 教
7. 授

# 代码

在行首加上4个空格或1个制表符就可以加入代码，没有高亮显示。

    #include <cstdio>
    int main()
    {
        printf("Hello, Hentai Yang!");
        return 0;
    }

# 区块引用

    > Yang Jiaoshou is hentai。
    >
    > Friedrich Wilhelm Nietzsche

效果：

> Yang Jiaoshou is hentai。
>
> Friedrich Wilhelm Nietzsche

# 分隔线

一行中三个或以上的星号、减号、底线都可以构成分隔线。

    ***
    ----
    _____

***

----

_____

# 链接

使用方括号标记。

    [链接](https://github.com/CyberZHG/ZCoach)

效果如下：

[链接](https://github.com/CyberZHG/ZCoach)

# 强调

星号和底线可以用于强调，一次为斜体，两次为粗体。

    *强调*
    _强调_
    **强调**
    __强调__

*强调*

_强调_

**强调**

__强调__


# 图片

    ![Alt text](https://1.gravatar.com/avatar/b73cd8682e5a794a1cae7fc0e653b839?d=https%3A%2F%2Fidenticons.github.com%2F3c246ca8999e13ac2798a0c799958d47.png&r=x&s=440)

![Alt text](https://1.gravatar.com/avatar/b73cd8682e5a794a1cae7fc0e653b839?d=https%3A%2F%2Fidenticons.github.com%2F3c246ca8999e13ac2798a0c799958d47.png&r=x&s=440)

# 转义符号

使用\\进行转义，对于之前出现的特殊用途的符号都可以用\\写出来。