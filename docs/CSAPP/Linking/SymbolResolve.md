### 符号解析

#### 链接器如何解析多重定义的全局符号

函数和已初始化的全局变量是强符号，未初始化的全局变量是弱符号。



Linux链接器处理多重定义符号名的规则

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

??? + note "如何使用上面创建的库呢？"

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
    ```

