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

