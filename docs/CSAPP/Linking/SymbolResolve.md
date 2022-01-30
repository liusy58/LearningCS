### 符号解析

#### 链接器如何解析多重定义的全局符号

函数和已初始化的全局变量是强符号，未初始化的全局变量是弱符号。



???+note "Linux链接器处理多重定义符号名的规则"

    * 不允许有多个同名的强符号
    * 如果有一个强符号和多个弱符号同名，那么选择强符号。
    * 如果有多个弱符号同名，那么从这些弱符号中任意选择一个。



=== "foo.c"

    ```C
    #include<stdio.h>
    void f(void);
    
    int y = 12345;
    int x = 12345;
    
    int main(){
        f();
        printf("x = 0x%x y = 0x%x \n",x,y);
        return 0;
    }
    ```

=== "bar.c"

    ```C
    double x;
    void f(){
        x = -0.0;
    }
    ```



=== "run by `gcc -0g  foo.c bar.c & ./a.out`"

    ```bash
    
    ```

#### 与静态库链接

???+note "静态库"

    将所有相关的目标模块大宝成为一个单独的文件，称为静态库，它可以用作链接器的输入。

???+note "为什么需要静态库？"

    1. 如果让编译器辨别出对标准函数的调用直接生成相应的代码的话，会极大的增加编译器的复杂度，而且每次增加、删除或者修改库函数就需要一个新的编译器版本。
    
    2. 如果将所有的标准C函数都放在一个单独的可重定位目标模板中，会对磁盘造成极大的浪费。
    
    3. 如果为每个标准函数创建一个独立的可重定位文件，那么程序员需要显式链接合适的目标模块到可执行文件中，这是一个容易出错并且耗时的过程。



???+note "如何创建一个静态库？"

    === "addvec.c"
    
    ```C
    int addcnt = 0;
    
    void addvec(int *x, int *y,
            int *z, int n) 
    {
        int i;
    
        addcnt++;
    
        for (i = 0; i < n; i++)
        z[i] = x[i] + y[i];
    }
    ```



    === "multvec.c"
    
    ```C
    int multcnt = 0;
    
    void multvec(int *x, int *y, 
            int *z, int n) 
    {
        int i;
    
        multcnt++;
    
        for (i = 0; i < n; i++)
        z[i] = x[i] * y[i];
    }
    ```
    
    === "command"
    
    ```bash
    gcc -c addvec.c multvec.c
    ar rcs libvector.a addvec.o multvec.o
    ```

???+note "如何使用上面创建的库呢？"

    === "main.c"
    
    ```C
    #include <stdio.h>
    #include "vector.h"
    
    int x[2] = {1, 2};
    int y[2] = {3, 4};
    int z[2];
    
    int main() 
    {
        addvec(x, y, z, 2);
        printf("z = [%d %d]\n", z[0], z[1]);
        return 0;
    }
    ```
    
    === "command1"
    
    ```bash
    gcc -c main.c 
    gcc -static -o main main.o ./libvector.a
    ```
    
    === "command2"
    
    ```bash
    gcc -c main.c 
    gcc -static -o main main.o -L. -lvector
    // -lvector 参数是 libvector.a 的缩写, -L. 参数告诉链接器在当前目录下查找 libvector.a。
    ```



#### 链接器如何使用静态库来解析引用

在符号解析阶段，链接器从左到右按照它们在编译器驱动程序命令行上出现的顺序来扫描可重定位目标文件和存档文件。在这次扫描中，链接器维护一个可重定位目标文件的集合E，一个未解析的符号集合U，以及一个在前面输入文件中已定义的符号集合D。

* 对于命令行上的每个输入文件 f, 链接器会判断 f 是一个目标文件还是一个存档文件。如果 f 是一个目标文件,那么链接器把 f 添加到 E, 修改 U 和 D 来反映 f 中的符号定义和引用,并继续下一个输入文件。
* 如果 f 是一个存档文件,那么链接器就尝试匹配 U 中未解析的符号和由存档文件成员定义的符号。如果某个存档文件成员 m, 定义了一个符号来解析 U 中的一个引用,那么就将 m 加到 E 中,并且链接器修改 U 和 D 来反映 m 中的符号定义和引用。对存档文件中所有的成员目标文件都依次进行这个过程,直到 U 和 D 都不再发生变化。此时,任何不包含在 E 中的成员目标文件都简单地被丢弃,而链接器将继续处理下一个输入文件。
* 如果当链接器完成对命令行上输入文件的扫描后, U 是非空的,那么链接器就会输出一个错误并终止。否则,它会合并和重定位 E 中的目标文件,构建输出的可执行文件。

???+note "解释下面出错的原因"

    === "command"
    
    ```bash
    gcc -static ./libvector.a main.c
    ```
    
    在处理 libvector.a 时, U 是空的,所以没有 libvector.a 中的成员目标文件会添加到 E 中。因此,对 addvec 的引用是绝不会被解析的,所以链接器会产生一条错误信息并终止。



???+example "一些例子"

    一般来说我们将库放到命令行的结尾，a 和 b 表示当前目录中的目标模块或者静态库,而 a -> b 表示 a 依赖于 b, 也就是说 b 定义了一个被 a 引用的符号。对于下面每种场景,请给出最小的命令行(即一个含有最少数量的目标文件和库参数的命令),使得静态链接器能解析所有的符号引用。

    === "`p.o -> libx.a`"

    ```bash
    gcc p.o libx.a
    ```

    === "`p.o -> libx.a -> liby.a`"

    ```bash
    gcc p.o libx.a liby.a
    ```



    === "`p.o->libx.a->liby.a && liby.a -> libx.a->p.o` "

    ```bash
    gcc p.o libx.a liby.a liby.a
    ```



