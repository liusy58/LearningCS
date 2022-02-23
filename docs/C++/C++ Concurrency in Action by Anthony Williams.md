### 2.1 启动线程


=== "launch_a_thread1.cpp"
```C++
void do_some_work();
std::thread my_thread(do_some_work);
```

=== "launch_a_thread2.cpp"
```C++
class background_task
{
public:
    void operator()() const
    {
        do_something();
        do_something_else();
    }
};
background_task f;
std::thread my_thread(f);
```

`launch_a_thread1.cpp`显示了直接将函数传递给thread的调用方式，`launch_a_thread2.cpp`显示了传递一个callable的类型的调用方式。

???+note "C++ vexing parse"
=== "test1.cpp"
```C++
std::thread my_thread(background_task());
```

这个并不是启动一个线程，这是声明一个函数，有一个参数，参数类型是 pointer-to-a-function-taking-no-parameters-and-returning-a-background_task-object

