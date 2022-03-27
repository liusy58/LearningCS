#include <assert.h>
#include <stdio.h>
#include "emit.h"
#include "cool-tree.h"
#include "symtab.h"

#include<string>
#include<map>
#include<vector>

enum Basicness     {Basic, NotBasic};
#define TRUE 1
#define FALSE 0

class CgenClassTable;
typedef CgenClassTable *CgenClassTableP;

class CgenNode;
typedef CgenNode *CgenNodeP;

class CgenClassTable : public SymbolTable<Symbol,CgenNode> {
private:
   int tag_index = 0;
   List<CgenNode> *nds;
   ostream& str;
   int stringclasstag;
   int intclasstag;
   int boolclasstag;



// The following methods emit code for
// constants and global declarations.

   void code_global_data();
   void code_global_text();
   void code_bools(int);
   void code_select_gc();
   void code_constants();
   void code_class_nameTab();
   void code_class_objTab();
   void code_class_dispTab_and_protObj();
   void code_class_dispTab(CgenNode*node);
   void code_class_protObj(CgenNode*node);

// The following creates an inheritance graph from
// a list of classes.  The graph is implemented as
// a tree of `CgenNode', and class names are placed
// in the base class symbol table.

   void install_basic_classes();
   void install_class(CgenNodeP nd);
   void install_classes(Classes cs);
   void build_inheritance_tree();
   void set_relations(CgenNodeP nd);
public:
   CgenClassTable(Classes, ostream& str);
   void code();
   CgenNodeP root();

   void decide_object_layouts();
   std::vector<Symbol>& decide_object_layout(CgenNode*node);
   void decide_method_patch_tables();
   std::map<Symbol,Symbol> decide_method_patch_table(CgenNode*node);
};


class CgenNode : public class__class {
    friend CgenClassTable;
private: 
   CgenNodeP parentnd;                        // Parent of class
   List<CgenNode> *children;                  // Children of class
   Basicness basic_status;                    // `Basic' if class is basic
                                              // `NotBasic' otherwise
   std::map<Symbol,int> attrs_2_index;
   std::vector<Symbol> object_layout;
   int object_size;
   int class_tag;
   bool initialized = false;
   bool patch_table_initialized = false;

   std::map<Symbol,Symbol> method_to_declared_class;

public:

   CgenNode(Class_ c,
            Basicness bstatus,
            CgenClassTableP class_table);

   void add_child(CgenNodeP child);
   List<CgenNode> *get_children() { return children; }
   void set_parentnd(CgenNodeP p);
   CgenNodeP get_parentnd() { return parentnd; }
   int basic() { return (basic_status == Basic); }

   bool is_initialized(){ return initialized;}
   std::vector<Symbol>& get_object_layout(){ return object_layout;}
   void set_initialized(){ initialized = true;}
};

class BoolConst 
{
 private: 
  int val;
 public:
  BoolConst(int);
  void code_def(ostream&, int boolclasstag);
  void code_ref(ostream&) const;
};

