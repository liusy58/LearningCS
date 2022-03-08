#ifndef SEMANT_H_
#define SEMANT_H_

#include <assert.h>
#include <iostream>  
#include "cool-tree.h"
#include "stringtab.h"
#include "symtab.h"
#include "list.h"

#include <map>

#define TRUE 1
#define FALSE 0

class ClassTable;
typedef ClassTable *ClassTableP;

// This is a structure that may be used to contain the semantic
// information such as the inheritance graph.  You may use it or not as
// you like: it is only here to provide a container for the supplied
// methods.

class ClassTable {
private:

  std::map<Symbol,Class__class*> name2class_definition;
  std::map<Symbol,Symbol> name2parent_name;
  std::map<Symbol,method_class*>classname2methods;

  int semant_errors;
  void install_basic_classes();

  ostream& error_stream;

public:

    bool install_custom_classes(Classes classes);
    bool build_inheritance_graph();
    bool is_inheritance_graph_valid();
    bool is_inheritance_graph_acyclic(Symbol name);
    bool is_basic_class(Symbol name);
    bool is_type_defined(Symbol name);
    ClassTable(Classes);
    void register_methods();
    void register_class_and_its_methods(Class__class* );
    std::map<Symbol,method_class*> get_class_methods(Class__class*class_defnition);
  int errors() { return semant_errors; }
  ostream& semant_error();
  ostream& semant_error(Class_ c);
  ostream& semant_error(Symbol filename, tree_node *t);
};


#endif

