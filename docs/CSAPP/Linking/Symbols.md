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







