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

  Classes classes;
  int semant_errors;
  std::map<Symbol,Class_>class_name_2_class_definition;
  std::map<Symbol,Symbol> class_name_2_parent_class_name;


    void install_basic_classes();

  ostream& error_stream;
  bool is_basic_class(Symbol class_name);
  bool is_hierarchy_graph_acyclic(Symbol class_name);

public:

  ClassTable(Classes);
  void register_methods_and_attrs();
  std::map<Symbol,method_class*> register_methods(class__class*class_definition);
  std::map<Symbol,attr_class*> register_attrs(class__class*class_definition);
  bool build_class_hierarchy_graph();
  bool is_class_hierarchy_graph_valid();
  int errors() { return semant_errors; }
  ostream& semant_error();
  ostream& semant_error(Class_ c);
  ostream& semant_error(Symbol filename, tree_node *t);

};




#endif

