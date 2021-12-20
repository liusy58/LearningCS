## Understand `auto` type deduction

当一个变量使用`auto`进行声明的时候，`auto`扮演了模版中的`T`的角色，变量的类型说明符扮演了`ParamType`的角色。但是有一个不太一样，那就是当`auto`声明的变量使用花括号进行初始化的时候，`auto`类型推导推出的类型则为`std::initializer_list`，这种情况将在最后讨论。



我们将从下面几个方面来探讨`auto`作为类型说明符(`ParamType`)的变量声明的情况。

* 类型说明符是一个指针或者引用

```c++
int x = 23;
const auto & rx=x;             //  rx 的类型是const int&
```

* 类型说明符既不是指针也不是引用

```c++
auto x = 2;		// x 的类型是int
```

* 类型说明符是一个通用引用

```c++
auto x = 27;   
const auto cx = x;
auto&& uref1 = x;               //x是int左值，
                                //所以uref1类型为int&
auto&& uref2 = cx;              //cx是const int左值，
                                //所以uref2类型为const int&
auto&& uref3 = 27;              //27是int右值，
                                //所以uref3类型为int&&
```

> uniform initialization
>
> ```c++
> int x1{12};
> int x2 = {12};
> ```
>
> `C++11 `添加了用于支持统一初始化(uniform initilization)的语法`{}` 





