1. first we need to install `bison`

```bash
sudo apt-get install -y bison
```

2. GNU bison
   GNU Bison, commonly known as Bison, is a parser generator that is part of the GNU Project. Bison reads a specification in the BNF notation (a context-free language),warns about any parsing ambiguities, and generates a parser that reads sequences of tokens and decides whether the sequence conforms to the syntax specified by the grammar.


3.

4. class hierarchy

* tree_node
  * Program_class //typedef Program_class *Program; 
    * program_class
  * Case_class //typedef Case_class *Case;
    * branch_class
  * Class__class //typedef Class__class *Class_; //typedef list_node<Class_>* Classes
    * class__class
  * Expression_class //typedef Expression_class *Expression;
    * assign_class
    * block_class
    * bool_const_class
    * comp_class
    * conn_class
    * dispatch_class
    * divide_class
    * eq_class
    * int_const_class
    * isvoid_class
    * leq_class
    * let_class
    * loop_class
    * lt_class
    * mul_class
    * neg_class
    * new__class
    * no_expr_class
    * object_class
    * plus_class
    * static_dispatch_class
    * string_const_class
    * sub_class
    * typecase_class
  * Feature_class // typedef Feature_class *Feature;
    * attr_class
    * methopd_class
  * Formal_class // typedef Formal_class *Formal;
    * formal_class

* Entry
  * IdEntry
  * IntEntry
  * StringEntry

