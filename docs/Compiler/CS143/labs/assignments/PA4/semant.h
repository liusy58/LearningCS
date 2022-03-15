#ifndef SEMANT_H_
#define SEMANT_H_

#include <assert.h>
#include <iostream>  
#include "cool-tree.h"
#include "stringtab.h"
#include "symtab.h"
#include "list.h"
#include <set>
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



  void install_basic_classes();
  ostream& error_stream;
  static bool is_basic_class(Symbol class_name);
  bool is_hierarchy_graph_acyclic(Symbol class_name);
  static bool is_class_cannot_inherited(Symbol class_name);
  std::map<Symbol,method_class*>get_methods(Class__class*);
  std::map<Symbol,attr_class*>get_attrs(Class__class*);

  void check_class(Class__class*);
  void check_methods(Class__class*);
  void check_attrs(Class__class*);
  void check_method_override_restriction_satisfied(Class__class*current_class,method_class*method);
  void check_attr_satisfied(Class__class*,attr_class*);
  void add_attrs_to_objects_table();
  void check_attrs_type();
  void check_attr_type(attr_class*);

public:
  std::map<Symbol,Class_> class_name_2_class_definition;
  std::map<Symbol,Symbol> class_name_2_parent_class_name;
  std::map<Symbol,std::map<Symbol,method_class*>> class_name_2_methods;
  std::map<Symbol,std::map<Symbol,attr_class*>> class_name_2_attrs;


  Class_ cur_class;
  SymbolTable<Symbol,Symbol>*objects_table;
  ClassTable(Classes);
  void install_custom_classes();
  int errors() { return semant_errors; }
  ostream& semant_error();
  ostream& semant_error(Class_ c);
  ostream& semant_error(Symbol filename, tree_node *t);
  void build_class_hierarchy();
  void verify_class_hierarchy();
  void build_method_and_attr_table();
  void check_classes();
  // check A is subtype of B
  bool is_subtype(Symbol class_a_name, Symbol class_b_name);
  Symbol get_curr_class();

  Symbol least_common_ancestor(Symbol,Symbol);
  void check_methods_type();
  Symbol get_file_name(){return cur_class->get_filename();}

  bool is_basic_method(Symbol name);
  void check_method_no_self_type_parameter(method_class*);
};




#endif

