

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "semant.h"
#include "utilities.h"
#include "cool-tree.h"

extern int semant_debug;
extern char *curr_filename;

ClassTable *classtable;
void raise_error() {
    cerr << "Compilation halted due to static semantic errors." << endl;
    exit(1);
}
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



ClassTable::ClassTable(Classes classes) :classes(classes), semant_errors(0) , error_stream(cerr) {

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
    this->class_name_2_class_definition[Int] = Int_class;
    this->class_name_2_class_definition[Str] = Str_class;
    this->class_name_2_class_definition[IO] = IO_class;
    this->class_name_2_class_definition[Bool] = Bool_class;



    // this is not right in fact
    this->class_name_2_class_definition[SELF_TYPE] = Object_class;

    this->class_name_2_parent_class_name[Int] = Object;
    this->class_name_2_parent_class_name[Str] = Object;
    this->class_name_2_parent_class_name[IO] = Object;
    this->class_name_2_parent_class_name[Bool] = Object;
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

    classtable->install_custom_classes();

    classtable->build_class_hierarchy();

    classtable->verify_class_hierarchy();
    /* some semantic analysis code may go here */

    if(classtable->errors()){
        raise_error();
    }
    classtable->build_method_and_attr_table();

    classtable->check_classes();


    if (classtable->errors()) {
        cerr << "Compilation halted due to static semantic errors." << endl;
        exit(1);
    }
}

void ClassTable::install_custom_classes(){
    for(int i = classes->first(); classes->more(i); i = classes->next(i)) {
        auto class_definition = classes->nth(i);
        auto class_name = class_definition->get_name();
        if(is_basic_class(class_name)){
            semant_error(class_definition)
                    << "Redefinition of basic class "
                    << class_name->get_string()
                    << ".\n";
            raise_error();
        }
        if(class_name_2_class_definition.count(class_name)){
            semant_error(class_definition)
                            << "Class "
                            << class_name->get_string()
                            << " was previously defined.\n";
            raise_error();
        }
        class_name_2_class_definition[class_name] = class_definition;
    }
}

void ClassTable::build_class_hierarchy() {
    for(int i = classes->first(); classes->more(i); i = classes->next(i)){
        auto class_definition = classes->nth(i);
        auto class_name = class_definition->get_name();
        auto parent_class_name = class_definition->get_parent();

        if(!class_name_2_class_definition.count(parent_class_name)){
            semant_error(class_definition)
                    << "Class "
                    << class_name->get_string()
                    << " inherits from an undefined class "
                    << parent_class_name->get_string()
                    << ".\n";
            raise_error();
        }
        if(is_class_cannot_inherited(parent_class_name)){
            semant_error(class_definition)
                    << "Class "
                    << class_name->get_string()
                    << " cannot inherit class "
                    << parent_class_name->get_string()
                    << ".\n";
            raise_error();
        }
        class_name_2_parent_class_name[class_name] = parent_class_name;
    }
}




void ClassTable::verify_class_hierarchy(){
    if(!class_name_2_class_definition.count(Main)){
        semant_error() << "Class Main is not defined.\n";
        raise_error();
    }
    for(int i = classes->first(); classes->more(i); i = classes->next(i)){
        auto class_definition = classes->nth(i);
        auto class_name = class_definition->get_name();
        auto parent_class_name = class_name_2_parent_class_name[class_name];
        if(!is_hierarchy_graph_acyclic(class_name)){
            semant_error(class_definition)
                    << "Class "
                    << class_name->get_string()
                    << ", or an ancestor of "
                    << parent_class_name->get_string()
                    << ", is involved in an inheritance cycle.\n";
        }
    }
}


bool ClassTable::is_class_cannot_inherited(Symbol class_name) {
    return (class_name == Int)
           ||(class_name == Str)
           ||(class_name == Bool)
           ||(class_name == SELF_TYPE);

}

bool ClassTable::is_basic_class(Symbol class_name) {
    return (class_name == Int)
           ||(class_name == Str)
           ||(class_name == Bool)
           ||(class_name == Object)
           ||(class_name == IO)
           ||(class_name == SELF_TYPE);

}

bool ClassTable::is_hierarchy_graph_acyclic(Symbol class_name){
    Symbol fast = class_name;
    Symbol slow = class_name;
    while(fast != NULL && fast != Object){
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

void ClassTable::build_method_and_attr_table(){
    for(auto &[class_name,class_definition]:class_name_2_class_definition){
        class_name_2_methods[class_name] = get_methods(class_definition);
        class_name_2_attrs[class_name] = get_attrs(class_definition);
    }
}

std::map<Symbol,method_class*>ClassTable::get_methods(Class__class*class_definition){

    std::map<Symbol,method_class*> methods;
    if( class_definition == NULL){
        methods;
    }
    while(class_definition != NULL){
        auto features = class_definition->get_features();
        for(int i = features->first(); features->more(i); i = features->next(i)){
            auto feature = features->nth(i);
            if(!feature->is_method()){
                continue;
            }
            auto method = dynamic_cast<method_class*>(feature);
            if(methods.count(method->get_name())){
                continue;
            }
            methods[method->get_name()] = method;
        }
        if(class_definition->get_name() == Object){
            break;
        }
        class_definition = class_name_2_class_definition[class_name_2_parent_class_name[class_definition->get_name()]];
    }


    return methods;
}
std::map<Symbol,attr_class*>ClassTable::get_attrs(Class__class*class_definition){
    std::map<Symbol,attr_class*> attrs;
    auto features = class_definition->get_features();
    for(int i = features->first(); features->more(i); i = features->next(i)){
        auto feature = features->nth(i);
        if(feature->is_method()){
            continue;
        }
        auto attr = dynamic_cast<attr_class*>(feature);
        if(attr->get_name() == self){
            semant_error(class_definition->get_filename(),attr)
                << "'self' cannot be the name of an attribute.\n";
            raise_error();
        }
        attrs[attr->get_name()] = attr;
    }
    return attrs;
}

void ClassTable::check_classes() {
    for(auto &[class_name,class_definition]:class_name_2_class_definition){
        check_class(class_definition);
    }
}


void ClassTable::check_class(Class__class* class_definition) {
//    std::cout<<"Now check "<< class_definition->get_name()->get_string() << std::endl;
    cur_class = class_definition;
    objects_table = new SymbolTable<Symbol,Symbol>();
    objects_table->enterscope();
    objects_table->addid(self,&SELF_TYPE);

    check_methods(class_definition);
    check_attrs(class_definition);
    add_attrs_to_objects_table();
    check_attrs_type();

    check_methods_type();

}

void ClassTable::check_methods(Class__class* class_definition) {
    if(class_definition == NULL || class_definition->get_name() == Object){
        return;
    }
    auto methods = class_name_2_methods[class_definition->get_name()];
    auto parent_class_name = class_name_2_parent_class_name[class_definition->get_name()];
    auto parent_class = class_name_2_class_definition[parent_class_name];
    for(auto &[method_name,method_definition]:methods){
        check_method_no_self_type_parameter(method_definition);
        check_method_override_restriction_satisfied(parent_class,method_definition);
    }
}



void ClassTable::check_method_override_restriction_satisfied(Class__class*current_class,method_class*method){
    if( current_class == NULL){
        return ;
    }
    auto method_name = method->get_name();

    auto methods = class_name_2_methods[current_class->get_name()];
    auto parent_class_name = class_name_2_parent_class_name[current_class->get_name()];
    auto parent_class = class_name_2_class_definition[parent_class_name];
    if(!methods.count(method_name)){
        check_method_override_restriction_satisfied(parent_class,method);
    }else{
        auto method_curr = methods[method_name];
        auto formals = method->get_formals();
        auto curr_formals = method_curr->get_formals();
        if(formals->len() != curr_formals->len()){
            semant_error(get_file_name(),method)
            << "Incompatible number of formal parameters in redefined method "
            << method->get_name()->get_string()
            << ".\n";
            raise_error();
        }
        for(int i = formals->first(); formals->more(i); i = formals->next(i)){
            auto formal = formals->nth(i);
            auto curr_formal = curr_formals->nth(i);
            if(formal->get_type_decl() == SELF_TYPE){
                semant_error(get_file_name(),method)
                << "Formal parameter "
                <<  formal->get_name()
                << " cannot have type SELF_TYPE.\n";
            }
            if(formal->get_type_decl() != curr_formal->get_type_decl()){
                // TODO : error
                semant_error(get_file_name(),method)
                << "In redefined method "
                << method->get_name()->get_string()
                <<", parameter type "
                << formal->get_type_decl()->get_string()
                << " is different from original type "
                << curr_formal->get_type_decl()->get_string()
                << "\n";
            }
        }
        check_method_override_restriction_satisfied(parent_class,method);
    }

}


void ClassTable::check_attrs(Class__class* class_definition) {
    if(class_definition == NULL){
        return;
    }
    auto attrs = class_name_2_attrs[class_definition->get_name()];
    for(auto &[attr_name,attr]:attrs){
        auto parent_class_name = class_name_2_parent_class_name[class_definition->get_name()];
        auto parent_class = class_name_2_class_definition[parent_class_name];
        check_attr_satisfied(parent_class,attr);
    }
}

void ClassTable::check_attr_satisfied(Class__class*current_class,attr_class*attr){
    if(current_class == NULL || !class_name_2_attrs.count(current_class->get_name())){
        return;
    }

    auto attrs = class_name_2_attrs[current_class->get_name()];
    if(attrs.count(attr->get_name())){
        // TODO error
        semant_error(cur_class->get_filename(),attr)
        << "Attribute "
        << attr->get_name()->get_string()
        <<" is an attribute of an inherited class.\n";
        raise_error();
    }
    auto parent_class_name = class_name_2_parent_class_name[current_class->get_name()];
    auto parent_class = class_name_2_class_definition[parent_class_name];
    check_attr_satisfied(parent_class,attr);
}

void ClassTable::add_attrs_to_objects_table() {
    Class_ class_process = cur_class;
    while(class_process != NULL){
        auto attrs = class_name_2_attrs[class_process->get_name()];
        for(auto &[attr_name,attr_definition]:attrs){
            if(objects_table->lookup(attr_name)!=NULL){
                //TODO error handle
            }
            objects_table->addid(attr_name,new Symbol(attr_definition->get_type()));
        }
        class_process =class_name_2_class_definition[class_name_2_parent_class_name[class_process->get_name()]];
    }
}

void ClassTable::check_attrs_type() {
    auto attrs = class_name_2_attrs[cur_class->get_name()];
    for(auto &[attr_name,attr_definition]:attrs){
        attr_definition->check_type();
    }
}


// check A is subtype of B
bool ClassTable::is_subtype(Symbol class_a_name, Symbol class_b_name) {
    if(class_a_name == NULL || class_b_name == NULL){
        return false;
    }
    if( class_a_name == SELF_TYPE && class_b_name == SELF_TYPE ){
        return true;
    }

    if(class_a_name == SELF_TYPE){
        class_a_name = get_curr_class();
    }
    auto curr = class_a_name;
    while(curr!=NULL){
        if(curr == class_b_name){
            return true;
        }
        curr = class_name_2_parent_class_name[curr];
    }
    return false;
}


Symbol ClassTable::get_curr_class() {return cur_class->get_name();}

Symbol ClassTable::least_common_ancestor(Symbol class_a, Symbol class_b) {
    if(class_a == SELF_TYPE){
        class_a = classtable->get_curr_class();
    }
    while(class_a!=NULL){
        if(is_subtype(class_b,class_a)){
            return class_a;
        }
        class_a = class_name_2_parent_class_name[class_a];
    }
    return nullptr;
}

void ClassTable::check_methods_type() {

    auto methods = class_name_2_methods[cur_class->get_name()];
    for(auto &[method_name,method_definition]:methods){
        method_definition->check_type();
    }
}

bool ClassTable::is_basic_method(Symbol name) {
    return (name == copy) || (name == type_name)  || (name == cool_abort)
            || (name == out_string) || (name == out_int) || (name == in_int)||
            (name == in_string) || (name == length) || (name == concat)||
            (name == substr);
}

void ClassTable::check_method_no_self_type_parameter(method_class* method_definition) {
    auto formals = method_definition->get_formals();
    for(int i = formals->first(); formals->more(i); i = formals->next(i)) {
        auto formal = formals->nth(i);
        if (formal->get_type_decl() == SELF_TYPE) {
            classtable->semant_error(classtable->get_file_name(), method_definition)
                    << "Formal parameter "
                    << formal->get_name()
                    << " cannot have type SELF_TYPE.\n";
        }
        if(formal->get_name() == self){
            classtable->semant_error(classtable->get_file_name(), method_definition)
            << "'self' cannot be the name of a formal parameter.\n";
        }
    }
}


Symbol method_class::check_type(){
    if(classtable->is_basic_method(this->get_name())){
        return get_return_type();
    }
    if(!classtable->class_name_2_class_definition.count(this->get_return_type())){
        classtable->semant_error(classtable->cur_class->get_filename(),this)
                << "Undefined return type "
                << get_return_type()->get_string()
                << " in method "
                <<get_name()->get_string()
                << ".\n";
    }

    classtable->objects_table->enterscope();
    for(int i = formals->first(); formals->more(i); i = formals->next(i)){
        auto formal = formals->nth(i);
        if(classtable->objects_table->probe(formal->get_name())!=NULL){
            classtable->semant_error(classtable->cur_class->get_filename(),formal)
            << "Formal parameter "
            << formal->get_name()
            << " is multiply defined.\n";
        }else{
            classtable->objects_table->addid(formal->get_name(),new Symbol(formal->get_type_decl()));
        }
    }
    auto expr_type = expr->check_type();
    Symbol T0 = this->get_return_type();

    if(T0 != No_type && !classtable->is_subtype(expr_type,T0)){
        // TODO: error
       // Inferred return type Z of method h does not conform to declared return type B.
       classtable->semant_error(classtable->get_file_name(),this)
       << "Inferred return type "
       << expr_type->get_string()
       << " of method "
       << this->name
       << " does not conform to declared return type "
       << T0->get_string()
       <<".\n";

    }
    classtable->objects_table->exitscope();
    return T0;

}


Symbol attr_class::check_type() {
    if(dynamic_cast<no_expr_class*>(init) != NULL){
        return type_decl;
    }
    auto init_expr_type = init->check_type();
    if(!classtable->is_subtype(init_expr_type,type_decl)){
        // TODO error
    }
    return type_decl;
}



Symbol assign_class::check_type() {
    if(this->name == self){
        classtable->semant_error(classtable->get_file_name(),this)
        << "Cannot assign to 'self'.\n";
        raise_error();
    }
    type = expr->check_type();
    auto static_type = *classtable->objects_table->lookup(this->name);
    if(!classtable->is_subtype(type,static_type)){
        // TODO
        classtable->semant_error(classtable->cur_class->get_filename(),this)
        <<"Type "
        << type->get_string()
        << " of assigned expression does not conform to declared type "
        << static_type->get_string()
        <<" of identifier "
        << name->get_string()
        <<".\n";
        raise_error();
    }

    return static_type;
}


Symbol dispatch_class::check_type() {
    Symbol T0_;
    if(expr->check_type() == SELF_TYPE){
        T0_ = classtable->get_curr_class();
    }else{
        T0_ = expr->check_type();
    }
    if(!classtable->class_name_2_methods[T0_].count(name)){
        classtable->semant_error(classtable->cur_class->get_filename(),this)
        << "Dispatch to undefined method "
        << name->get_string()
        << ".\n";
        raise_error();
    }
    auto method = classtable->class_name_2_methods[T0_][name];
    auto formals = method->get_formals();
    if(formals->len() != actual->len()){
        // TODO: error
    }

    for(int i = formals->first(); formals->more(i); i = formals->next(i)){
        auto formal = formals->nth(i);
        auto expression = actual->nth(i);
        if(!classtable->is_subtype(expression->check_type(),formal->get_type_decl())){
            // error
            classtable->semant_error(classtable->cur_class->get_filename(),this)
            << "In call of method "
            << method->get_name()->get_string()
            << ", type "
            << (expression->check_type() == classtable->cur_class->get_name() ? "SELF_TYPE" : expression->check_type()->get_string())
            << " of parameter "
            << formal->get_name()->get_string()
            << " does not conform to declared type "
            << formal->get_type_decl()->get_string()
            << ".\n";
            raise_error();
        }
    }
    if(method->get_return_type() == SELF_TYPE){
        return type = expr->check_type();
    }
    return type = method->get_return_type();
}


Symbol static_dispatch_class::check_type() {
    auto T0 = expr->check_type();
    if(!classtable->is_subtype(T0 == SELF_TYPE? classtable->get_curr_class():T0,type_name)){
        // error
        classtable->semant_error(classtable->cur_class->get_filename(),this)
        << "Expression type "
        << T0->get_string()
        << " does not conform to declared static dispatch type "
        << type_name->get_string()
        << ".\n";
//        raise_error();
        return Object;
    }
    auto method  = classtable->class_name_2_methods[type_name][name];
    auto formals = method->get_formals();


    if(formals->len() != actual->len()){
        // TODO: error

    }
    for(int i = formals->first(); formals->more(i); i = formals->next(i)){
        auto formal = formals->nth(i);
        auto expression = actual->nth(i);
        if(!classtable->is_subtype(expression->check_type(),formal->get_type_decl())){
            // error
        }
    }

    if(method->get_return_type() == SELF_TYPE){
        return T0;
    }
    return type = method->get_return_type();

}


Symbol cond_class::check_type() {
    if(pred->check_type()!=Bool){
        // error
    }
    return type = classtable->least_common_ancestor(then_exp->check_type(),else_exp->check_type());
}

Symbol loop_class::check_type() {
    if(this->pred->check_type()!=Bool){
        // TODO error
        classtable->semant_error(classtable->cur_class->get_filename(),this)
        << "Loop condition does not have type Bool.\n";
        raise_error();
    }
    this->body->check_type();
    return type = Object;
}

Symbol typcase_class::check_type() {
    auto T0 = expr->check_type();
    Symbol ancestor = NULL;

    std::set<Symbol>branch_types;
    for(int i = cases->first(); cases->more(i); i = cases->next(i)){
        auto branch = cases->nth(i);
        if(branch_types.count(branch->get_type_decl())){
            classtable->semant_error(classtable->cur_class->get_filename(),this)
            << "Duplicate branch "
            << branch->get_type_decl()->get_string()
            <<" in case statement.\n";
            raise_error();
        }
        branch_types.insert(branch->get_type_decl());
        classtable->objects_table->enterscope();
        classtable->objects_table->addid(branch->get_name(),new Symbol(branch->get_type_decl()));
        auto T_ = branch->get_expr()->check_type();
        if(ancestor == NULL){
            ancestor = T_;
        }
        ancestor = classtable->least_common_ancestor(ancestor,T_);
    }
    return type = ancestor;
}

Symbol block_class::check_type() {
    auto index = body->len()-1;
    for(int i = body->first(); body->more(i); i = body->next(i)){
        auto expression = body->nth(i);
        expression->check_type();
    }
    auto last_expression = body->nth(index);
    return type = last_expression->check_type();
}

Symbol let_class::check_type() {
    if(this->identifier == self){
        classtable->semant_error(classtable->cur_class->get_filename(),this)
                << "'self' cannot be bound in a 'let' expression.\n";
        raise_error();
    }
    // no init
    if(dynamic_cast<no_expr_class*>(this->init)!=NULL){
        Symbol T0_ = type_decl;
//        if(T0_ == SELF_TYPE){
//            T0_ = classtable->cur_class->get_name();
//        }
        classtable->objects_table->enterscope();
        classtable->objects_table->addid(identifier,&T0_);
        auto T2 = body->check_type();
        classtable->objects_table->exitscope();
        return type = T2;
    }


    Symbol T0_ = type_decl;

    if(!classtable->is_subtype(init->check_type(),T0_)){
        // TODO error here
        classtable->semant_error(classtable->cur_class->get_filename(),this)
        << "Inferred type "
        << init->check_type()->get_string()
        << " of initialization of "
        << this->identifier->get_string()
        << " does not conform to identifier's declared type "
        << T0_->get_string()
        <<".\n";
    }
    classtable->objects_table->enterscope();
    classtable->objects_table->addid(identifier,&T0_);
    auto T2 = body->check_type();
    classtable->objects_table->exitscope();
    return type = T2;
}
Symbol plus_class::check_type() {
    if(e1->check_type()!=Int || e2->check_type()!=Int){
        // TODO error
        classtable->semant_error(classtable->cur_class->get_filename(),this)
        << "non-Int arguments: "
        << e1->check_type()->get_string()
        <<" + "
        << e2->check_type()->get_string()
        << "\n";
        raise_error();
    }
    return type = Int;
}

Symbol sub_class::check_type() {
    if(e1->check_type()!=Int || e2->check_type()!=Int){
        // TODO error
        classtable->semant_error(classtable->cur_class->get_filename(),this)
                << "non-Int arguments: "
                << e1->check_type()->get_string()
                <<" - "
                << e2->check_type()->get_string()
                << "\n";
        raise_error();
    }
    return type = Int;
}

Symbol mul_class::check_type() {
    if(e1->check_type()!=Int || e2->check_type()!=Int){
        // TODO error
        classtable->semant_error(classtable->cur_class->get_filename(),this)
                << "non-Int arguments: "
                << e1->check_type()->get_string()
                <<" * "
                << e2->check_type()->get_string()
                << "\n";
        raise_error();
    }
    return type = Int;
}

Symbol divide_class::check_type() {
    if(e1->check_type()!=Int || e2->check_type()!=Int){
        // TODO error
        classtable->semant_error(classtable->cur_class->get_filename(),this)
                << "non-Int arguments: "
                << e1->check_type()->get_string()
                <<" / "
                << e2->check_type()->get_string()
                << "\n";
        raise_error();
    }
    return type = Int;
}

Symbol neg_class::check_type() {
    if(this->e1->check_type()!=Int){
        // TODO error
    }
    return type = Int;
}

Symbol lt_class::check_type() {
    if(this->e1->check_type()!=Int || this->e2->check_type()!= Int){
        //TODO error
    }
    return type = Bool;
}
Symbol eq_class::check_type() {
    auto e1_type = e1->check_type();
    auto e2_type = e2->check_type();
    // Illegal comparison with a basic type.
    if(e1_type == Int && e2_type != Int){
        classtable->semant_error(classtable->cur_class->get_filename(), this)
        << "Illegal comparison with a basic type.\n";
        raise_error();
    }

    if(e1_type == Bool && e2_type != Bool){
        classtable->semant_error(classtable->cur_class->get_filename(), this)
                << "Illegal comparison with a basic type.\n";
        raise_error();
    }

    if(e1_type == Str && e2_type != Str){
        classtable->semant_error(classtable->cur_class->get_filename(), this)
                << "Illegal comparison with a basic type.\n";
        raise_error();
    }
    // TODO error here
    return type = Bool;
}

Symbol leq_class::check_type() {
    if(this->e1->check_type()!=Int || this->e2->check_type()!= Int){
        //TODO error
    }
    return type = Bool;
}
Symbol comp_class::check_type() {
    if(this->e1->check_type()!=Bool){
        // TODO error
    }
    return type = Bool;
}

Symbol int_const_class::check_type() {
    type = Int;
    return Int;
}
Symbol bool_const_class::check_type() {
    type = Bool;
    return Bool;
}
Symbol string_const_class::check_type() {
    type = Str;
    return Str;
}


Symbol new__class::check_type() {
//    if(type_name == SELF_TYPE){
//        return classtable->get_curr_class();
//    }
    if(!classtable->class_name_2_class_definition.count(this->type_name)){
        classtable->semant_error(classtable->get_file_name(),this)
        << "'new' used with undefined class "
        << type_name->get_string()
        << ".\n";
    }
    return type = type_name;
}

Symbol isvoid_class::check_type() {
    this->e1->check_type();
    return type = Bool;
}

Symbol no_expr_class::check_type() {
    return type = Object;
}

Symbol object_class::check_type() {
    if(classtable->objects_table->lookup(name) == NULL){
        classtable->semant_error(classtable->cur_class->get_filename(),this)
        << "Undeclared identifier "
        << name->get_string()
        << ".\n";
        raise_error();
    }
    return type = *classtable->objects_table->lookup(name);
}


