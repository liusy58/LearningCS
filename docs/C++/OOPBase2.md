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

