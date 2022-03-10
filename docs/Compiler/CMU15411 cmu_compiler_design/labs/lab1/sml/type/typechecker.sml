(* L1 Compiler
 * TypeChecker
 * Author: Alex Vaynberg <alv@andrew.cmu.edu>
 * Modified: Frank Pfenning <fp@cs.cmu.edu>
 *
 * Simple typechecker that is based on a unit Symbol.table
 * This is all that is needed since there is only an integer type present
 *) 

signature TYPE_CHECK =
sig
  (* prints error message and raises ErrorMsg.error if error found *)
  val typecheck : Ast.program -> unit
end;

structure TypeChecker :> TYPE_CHECK = 
struct
  structure A = Ast

  (* tc_exp : unit Symbol.table -> Ast.exp -> Mark.ext option -> unit *)
  fun tc_exp env (A.Var(id)) ext =
      (case Symbol.look env id
	of NONE => ( ErrorMsg.error ext ("undefined variable `" ^ Symbol.name id ^ "'") ;
		     raise ErrorMsg.Error )
         | SOME _ => ())
    | tc_exp env (A.ConstExp(c)) ext = ()
    | tc_exp env (A.OpExp(oper,es)) ext =
      (* Note: it is syntactically impossible in this language to
       * apply an operator to an incorrect number of arguments
       * so we only check each of the arguments
       *)
	List.app (fn e => tc_exp env e ext) es
    | tc_exp env (A.Marked(marked_exp)) ext =
        tc_exp env (Mark.data marked_exp) (Mark.ext marked_exp)

  (* tc_stms : unit Symbol.table -> Ast.program -> unit *)
  fun tc_stms env nil = ()
    | tc_stms env (A.Assign(id,e)::stms) =
        ( tc_exp env e NONE ;
	  tc_stms (Symbol.bind env (id, ())) stms )
    | tc_stms env (A.Return(e)::nil) =
        tc_exp env e NONE
    | tc_stms env (A.Return _ :: _) =
        ( ErrorMsg.error NONE ("`return' not last statement") ;
	  raise ErrorMsg.Error )

  fun typecheck prog = tc_stms Symbol.empty prog

end
