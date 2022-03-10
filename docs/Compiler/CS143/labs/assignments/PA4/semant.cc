

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "semant.h"
#include "utilities.h"


extern int semant_debug;
extern char *curr_filename;
ClassTable *classtable;
SymbolTable<Symbol,Symbol> *objects_table;
Symbol current_class_name;
Class_ current_class_definition;
std::map<Symbol,std::map<Symbol,method_class*>>class_name_2_methods;
std::map<Symbol,std::map<Symbol,attr_class*>>class_name_2_attrs;
std::map<Symbol, method_class*> current_class_methods;
std::map<Symbol, attr_class*> current_class_attrs;
//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
static Symbol 
    arg,
    arg2,
    Bool,
    concat,
    cool_abort,
    copy,
    Int,
    in_int,
    in_string,
    IO,
    length,
    Main,
    main_meth,
    No_class,
    No_type,
    Object,
    out_int,
    out_string,
    prim_slot,
    self,
    SELF_TYPE,
    Str,
    str_field,
    substr,
    type_name,
    val;
//
// Initializing the predefined symbols.
//
static void initialize_constants(void)
{
    arg         = idtable.add_string("arg");
    arg2        = idtable.add_string("arg2");
    Bool        = idtable.add_string("Bool");
    concat      = idtable.add_string("concat");
    cool_abort  = idtable.add_string("abort");
    copy        = idtable.add_string("copy");
    Int         = idtable.add_string("Int");
    in_int      = idtable.add_string("in_int");
    in_string   = idtable.add_string("in_string");
    IO          = idtable.add_string("IO");
    length      = idtable.add_string("length");
    Main        = idtable.add_string("Main");
    main_meth   = idtable.add_string("main");
    //   _no_class is a symbol that can't be the name of any 
    //   user-defined class.
    No_class    = idtable.add_string("_no_class");
    No_type     = idtable.add_string("_no_type");
    Object      = idtable.add_string("Object");
    out_int     = idtable.add_string("out_int");
    out_string  = idtable.add_string("out_string");
    prim_slot   = idtable.add_string("_prim_slot");
    self        = idtable.add_string("self");
    SELF_TYPE   = idtable.add_string("SELF_TYPE");
    Str         = idtable.add_string("String");
    str_field   = idtable.add_string("_str_field");
    substr      = idtable.add_string("substr");
    type_name   = idtable.add_string("type_name");
    val         = idtable.add_string("_val");
}

void type_check(Class_ class_definition);
Symbol type_check(method_class* method);
Symbol type_check(attr_class* attr);
Symbol type_check(Feature f);
void build_attribute_scopes(Class_ );


void raise_error() {
    cerr << "Compilation halted due to static semantic errors." << endl;
    exit(1);
}


ClassTable::ClassTable(Classes classes) : classes(classes), semant_errors(0) , error_stream(cerr) {

    /* Fill this in */
    install_basic_classes();

}

void ClassTable::install_basic_classes() {

    // The tree package uses these globals to annotate the classes built below.
   // curr_lineno  = 0;
    Symbol filename = stringtable.add_string("<basic class>");
    
    // The following demonstrates how to create dummy parse trees to
    // refer to basic Cool classes.  There's no need for method
    // bodies -- these are already built into the runtime system.
    
    // IMPORTANT: The results of the following expressions are
    // stored in local variables.  You will want to do something
    // with those variables at the end of this method to make this
    // code meaningful.

    // 
    // The Object class has no parent class. Its methods are
    //        abort() : Object    aborts the program
    //        type_name() : Str   returns a string representation of class name
    //        copy() : SELF_TYPE  returns a copy of the object
    //
    // There is no need for method bodies in the basic classes---these
    // are already built in to the runtime system.

    Class_ Object_class =
	class_(Object, 
	       No_class,
	       append_Features(
			       append_Features(
					       single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
					       single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
			       single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
	       filename);

    // 
    // The IO class inherits from Object. Its methods are
    //        out_string(Str) : SELF_TYPE       writes a string to the output
    //        out_int(Int) : SELF_TYPE            "    an int    "  "     "
    //        in_string() : Str                 reads a string from the input
    //        in_int() : Int                      "   an int     "  "     "
    //
    Class_ IO_class = 
	class_(IO, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       single_Features(method(out_string, single_Formals(formal(arg, Str)),
										      SELF_TYPE, no_expr())),
							       single_Features(method(out_int, single_Formals(formal(arg, Int)),
										      SELF_TYPE, no_expr()))),
					       single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
			       single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
	       filename);  

    //
    // The Int class has no methods and only a single attribute, the
    // "val" for the integer. 
    //
    Class_ Int_class =
	class_(Int, 
	       Object,
	       single_Features(attr(val, prim_slot, no_expr())),
	       filename);

    //
    // Bool also has only the "val" slot.
    //
    Class_ Bool_class =
	class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())),filename);

    //
    // The class Str has a number of slots and operations:
    //       val                                  the length of the string
    //       str_field                            the string itself
    //       length() : Int                       returns length of the string
    //       concat(arg: Str) : Str               performs string concatenation
    //       substr(arg: Int, arg2: Int): Str     substring selection
    //       
    Class_ Str_class =
	class_(Str, 
	       Object,
	       append_Features(
			       append_Features(
					       append_Features(
							       append_Features(
									       single_Features(attr(val, Int, no_expr())),
									       single_Features(attr(str_field, prim_slot, no_expr()))),
							       single_Features(method(length, nil_Formals(), Int, no_expr()))),
					       single_Features(method(concat, 
								      single_Formals(formal(arg, Str)),
								      Str, 
								      no_expr()))),
			       single_Features(method(substr, 
						      append_Formals(single_Formals(formal(arg, Int)), 
								     single_Formals(formal(arg2, Int))),
						      Str, 
						      no_expr()))),
	       filename);


    this->class_name_2_class_definition[Object] = Object_class;
    this->class_name_2_class_definition[Str] = Str_class;
    this->class_name_2_class_definition[Bool] = Bool_class;
    this->class_name_2_class_definition[Int] = Int_class;
    this->class_name_2_class_definition[IO] = IO_class;

}

////////////////////////////////////////////////////////////////////
//
// semant_error is an overloaded function for reporting errors
// during semantic analysis.  There are three versions:
//
//    ostream& ClassTable::semant_error()                
//
//    ostream& ClassTable::semant_error(Class_ c)
//       print line number and filename for `c'
//
//    ostream& ClassTable::semant_error(Symbol filename, tree_node *t)  
//       print a line number and filename
//
///////////////////////////////////////////////////////////////////

ostream& ClassTable::semant_error(Class_ c)
{                                                             
    return semant_error(c->get_filename(),c);
}    

ostream& ClassTable::semant_error(Symbol filename, tree_node *t)
{
    error_stream << filename << ":" << t->get_line_number() << ": ";
    return semant_error();
}

ostream& ClassTable::semant_error()                  
{                                                 
    semant_errors++;                            
    return error_stream;
} 



/*   This is the entry point to the semantic checker.

     Your checker should do the following two things:

     1) Check that the program is semantically correct
     2) Decorate the abstract syntax tree with type information
        by setting the `type' field in each Expression node.
        (see `tree.h')

     You are free to first do 1), make sure you catch all semantic
     errors. Part 2) can be done in a second stage, when you want
     to build mycoolc.
 */
void program_class::semant()
{
    initialize_constants();

    /* ClassTable constructor may do some semantic analysis */
    classtable = new ClassTable(classes);

    if(!classtable->build_class_hierarchy_graph()){
        raise_error();
    }

    if(!classtable->is_class_hierarchy_graph_valid()){
        raise_error();
    }

    classtable->register_methods_and_attrs();

    if(classtable->errors()){
        raise_error();
    }

    for(int i = classes->first(); classes->more(i); i = classes->next(i)) {
        auto class_definition = classes->nth(i);
        type_check(class_definition);
    }




    /* some semantic analysis code may go here */



    if (classtable->errors()) {
	cerr << "Compilation halted due to static semantic errors." << endl;
	exit(1);
    }
}



bool ClassTable::is_basic_class(Symbol class_name){
    return (class_name == Object)
            || (class_name == Int)
            || (class_name == Str)
            || (class_name == Bool)
            || (class_name == IO);

}



// check class redefinition

bool ClassTable::build_class_hierarchy_graph(){
    for(int i = classes->first(); classes->more(i); i = classes->next(i))
    {
        auto class_definition = classes->nth(i);
        auto class_name = class_definition->get_name();
        if(class_name_2_class_definition.count(class_name)){
            // TODO: error handling
            return false;
        }
        auto parent_class_name = class_definition->get_parent();
        class_name_2_class_definition[class_name] = class_definition;
        class_name_2_parent_class_name[class_name] = parent_class_name;
    }
    return true;
}



// check wrong cases
//              1. when parent class is not defined
//              2. when the hierarchy_graph is acyclic.




bool ClassTable::is_class_hierarchy_graph_valid() {
    for(auto &[class_name,class_definition]:class_name_2_class_definition){
        auto parent_class_name = class_definition->get_parent();
        if(!class_name_2_class_definition.count(parent_class_name)){
            // TODO: handle error
            return false;
        }
        if(!is_hierarchy_graph_acyclic(class_name)){
            // TODO
            return false;
        }
    }
    return true;
}




bool ClassTable::is_hierarchy_graph_acyclic(Symbol class_name){
    Symbol fast = class_name;
    Symbol slow = class_name;
    while(fast != Object){
        fast = class_name_2_parent_class_name[fast];
        if(fast == Object){
            return true;
        }
        fast = class_name_2_parent_class_name[fast];
        slow = class_name_2_parent_class_name[slow];
        if(fast == slow){
            return false;
        }
    }
    return true;
}


std::map<Symbol,method_class*> ClassTable::register_methods(class__class*class_definition) {
    std::map<Symbol,method_class*> method_name_2_method;
    auto features = class_definition->get_features();
    for(int i = features->first(); features->more(i); i = features->next(i)) {
        auto feature = features->nth(i);
        if(feature->is_method()){
            auto method = dynamic_cast<method_class*>(feature);
            auto method_name = method->get_name();
            if(method_name_2_method.count(method_name)){
                // TODO:: handle error
                semant_error();
            }
            method_name_2_method[method_name] = method;
        }
    }
    return method_name_2_method;
}

std::map<Symbol,attr_class*> ClassTable::register_attrs(class__class*class_definition){
    std::map<Symbol,attr_class*> name_2_attr;
    auto features = class_definition->get_features();
    for(int i = features->first(); features->more(i); i = features->next(i)) {
        auto feature = features->nth(i);
        if(!feature->is_method()){
            auto attr = dynamic_cast<attr_class*>(feature);
            auto name = attr->get_name();
            if(name_2_attr.count(name)){
                // TODO:: handle error
                semant_error();
            }
            name_2_attr[name] = attr;
        }
    }
    return name_2_attr;
}

void ClassTable::register_methods_and_attrs() {
    for(auto &[class_name,class_def]:class_name_2_class_definition){
        auto class_definition = dynamic_cast<class__class *>(class_def);
        class_name_2_methods[class_name] = register_methods(class_definition);
        class_name_2_attrs[class_name] = register_attrs(class_definition);
    }
}


void type_check(Class_ class_definition){
    current_class_name = class_definition->get_name();
    current_class_definition = class_definition;
    current_class_attrs = class_name_2_attrs[current_class_name];
    current_class_methods = class_name_2_methods[current_class_name];

    objects_table = new SymbolTable<Symbol,Symbol>();
    objects_table->enterscope();
    objects_table->addid(self,&current_class_name);

    build_attribute_scopes(current_class_definition);
}

void build_attribute_scopes(Class_ class_definition){
    objects_table->enterscope();

    auto attrs = class_name_2_attrs[class_definition->get_name()];
    for(auto &[attr_name,attr_definition] : attrs){
        objects_table->addid(attr_name,)
    }
}