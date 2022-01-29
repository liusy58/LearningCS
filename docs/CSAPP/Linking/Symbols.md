### 符号和符号表

=== "ELF符号表中的条目"
    ```C
    typedef struct { 
        int   name;      /* String table offset */ 
        char  type:4,    /* Function or data (4 bits) */ 
        binding:4; /* Local or global (4 bits) */ 
        char  reserved;  /* Unused */  
        short section;   /* Section header index */
        long  value;     /* Section offset or absolute address */ 
        long  size;      /* Object size in bytes */ 
    } Elf64_Symbol;     
    ```





| Name      | Description          |
| --------- | -------------------- |
| `name`    | 字符串表中的字节偏移 |
| `value`   | 符号的地址           |
| `size`    | 目标的大小           |
| `type`    | 要么是数据要么是函数 |
| `binding` | 本地还是全局？       |
|           |                      |
|           |                      |



注意，有三个伪节，只有可重定位文件中才有的：

* `ABS`：表示不该被重定位的符号
* `UNDEF`：代表未定义的符号
* `COMMON`：表示还未被分配位置的未初始化的数据条目



???+note "`COMMON` vs. `.bss`"

    `COMMON`：未初始化的全局变量

    `.bss`：未初始化的静态变量以及初始化为0的全局或者静态变量。


