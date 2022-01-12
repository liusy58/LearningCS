???+note "conversion function"
    Conversion function enables implicit conversion or explicit conversion from a class type to another type.

    There is an example of conversion function used in std:

    ```C++
    template <class Alloc>
    class vector<bool, Alloc>{
        public:
            typedef __bit_reference reference;
        protected:
            reference operator[](size_type n){
                return *(begin()+difference_type(n));
            }
    };
    struct __bit_reference {
        unsigned int*p;
        unsigned int mask;
        public:
            operator bool()const{return !(!(*p&mask));}
    };
    ```

???+note "pointer-like classes"
    There are 2 kinds of pointer-like classes: smart pointer and iterator.

    Smart pointer classes must override * and & operators. Iterator need override ++/-- apart from */&.

???+note "function-like classes"
    Function-like classes are those override `()` operator so their instances can behave like functions. An example is below:

    ```C++
    template <class T>
    struct less {
        bool operator() (const T&x,const T&y)const {return x < y;}
    }
    ```


???+note "template"
    ||example|
    |-|-|
    |class template||
    |function template||
    |member template|<img src="../img/member-template.png" alt="l" style="width:500px;"/>|
    

???+note "partial specialization"


???+note "template template parameter"
    <img src="../img/template template parameter.png" alt="l" style="width:500px;"/>

???+note "Static Binding VS. Dynamic Binding"
    Dynamic Binding: virtual function + pointer + upper cast (*(p->vptr[n]))(p)

    


