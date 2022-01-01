???+note "Understand the functional view of iterative algorithm"
    F(x) = x;   fixed point



???+note "The definitions of lattice and complete lattice"
    Given a poset (P, ⊑), ∀a, b ∈ P, if a ⊔ b and a ⊓ b exist, then(P, ⊑) is called a lattice. A poset is a lattice if every pair of its elements has a least upper bound and a greatest lower bound. 

    Given a lattice (P, ⊑), for arbitrary subset S of P, if ⊔S and ⊓S exist, then (P, ⊑) is called a complete lattice




???+note "How to summarize may and must analyses in lattices"



???+note "Understand the fixed-point theorem"
    <img src="../img/fixed-point.png" alt="l" style="width:500px;"/>


???+note "The relation between MOP and the solution produced by the iterative algorithm"
    MOP: F(x) ⊔ F(y)
    
    ours: F(x ⊔ y)




???+note "Constant propagation analysis"
    Given a variable x at program point p, determine whether x is guaranteed to hold a constant value at p



???+note "Worklist algorithm"


