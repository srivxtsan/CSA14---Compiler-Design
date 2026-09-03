import re
from flask import Flask, request, jsonify, render_template

app = Flask(__name__)

# =====================================================================
# 1. AST REPRESENTATION
# =====================================================================

class Node:
    def __str__(self):
        return self.to_string(outer=True)

    def to_string(self, outer=True):
        raise NotImplementedError()

class Atom(Node):
    def __init__(self, name):
        self.name = name.strip()

    def __repr__(self):
        return self.name

    def __eq__(self, other):
        return isinstance(other, Atom) and self.name == other.name

    def __hash__(self):
        return hash(self.name)

    def to_string(self, outer=True):
        return self.name

class Neg(Node):
    def __init__(self, expr):
        self.expr = expr

    def __repr__(self):
        return f"~{self.expr}"

    def __eq__(self, other):
        return isinstance(other, Neg) and self.expr == other.expr

    def __hash__(self):
        return hash(("~", self.expr))

    def to_string(self, outer=True):
        if isinstance(self.expr, (Atom, Neg)):
            return f"~{self.expr.to_string(outer=False)}"
        return f"~({self.expr.to_string(outer=False)})"

class Impl(Node):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __repr__(self):
        return f"({self.left} -> {self.right})"

    def __eq__(self, other):
        return isinstance(other, Impl) and self.left == other.left and self.right == other.right

    def __hash__(self):
        return hash(("->", self.left, self.right))

    def to_string(self, outer=True):
        s = f"{self.left.to_string(outer=False)} -> {self.right.to_string(outer=False)}"
        return s if outer else f"({s})"

class Conj(Node):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __repr__(self):
        return f"({self.left} ^ {self.right})"

    def __eq__(self, other):
        return isinstance(other, Conj) and self.left == other.left and self.right == other.right

    def __hash__(self):
        return hash(("^", self.left, self.right))

    def to_string(self, outer=True):
        s = f"{self.left.to_string(outer=False)} ^ {self.right.to_string(outer=False)}"
        return s if outer else f"({s})"

class Disj(Node):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __repr__(self):
        return f"({self.left} v {self.right})"

    def __eq__(self, other):
        return isinstance(other, Disj) and self.left == other.left and self.right == other.right

    def __hash__(self):
        return hash(("v", self.left, self.right))

    def to_string(self, outer=True):
        s = f"{self.left.to_string(outer=False)} v {self.right.to_string(outer=False)}"
        return s if outer else f"({s})"

# =====================================================================
# 2. LOGIC PARSER
# =====================================================================

def tokenize(s):
    # Match operators: "->", "^", "v", "~", parents, and variables/atoms
    token_pattern = re.compile(r'(->|~|\^|v|\(|\)|[a-zA-Z_][a-zA-Z0-9_]*)')
    return [t for t in token_pattern.findall(s) if t.strip()]

class Parser:
    def __init__(self, tokens):
        self.tokens = tokens
        self.pos = 0

    def peek(self):
        if self.pos < len(self.tokens):
            return self.tokens[self.pos]
        return None

    def match(self, expected):
        if self.peek() == expected:
            self.pos += 1
            return True
        return False

    def consume(self):
        t = self.peek()
        if t is not None:
            self.pos += 1
        return t

    def parse_expr(self):
        return self.parse_impl()

    def parse_impl(self):
        left = self.parse_disj()
        if self.peek() == "->":
            self.consume()  # Consume "->"
            right = self.parse_impl()  # Right-associative
            return Impl(left, right)
        return left

    def parse_disj(self):
        left = self.parse_conj()
        while self.peek() == "v":
            self.consume()
            right = self.parse_conj()
            left = Disj(left, right)
        return left

    def parse_conj(self):
        left = self.parse_neg()
        while self.peek() == "^":
            self.consume()
            right = self.parse_neg()
            left = Conj(left, right)
        return left

    def parse_neg(self):
        if self.match("~"):
            return Neg(self.parse_neg())
        return self.parse_primary()

    def parse_primary(self):
        token = self.peek()
        if token == "(":
            self.consume()
            expr = self.parse_expr()
            if not self.match(")"):
                raise ValueError("Expected matching closing parenthesis ')'")
            return expr
        elif token and token.isalnum() and token not in ("v"):  # "v" is treated as OR operator
            self.consume()
            return Atom(token)
        else:
            raise ValueError(f"Unexpected token: {token}")

def parse(s):
    tokens = tokenize(s)
    if not tokens:
        raise ValueError("Empty logical expression.")
    parser = Parser(tokens)
    res = parser.parse_expr()
    if parser.peek() is not None:
        raise ValueError(f"Extra characters at end of statement: {' '.join(parser.tokens[parser.pos:])}")
    return res

# =====================================================================
# 3. BACKWARD CHAINING LOGIC SOLVER
# =====================================================================

class Solver:
    def __init__(self, initial_premises):
        # We simplify and decompose initial premises to break down conjunctions
        self.premises = []
        for prem in initial_premises:
            self.premises.extend(self.simplify_and_decompose(prem))
        self.logs = []
        self.step_counter = 0

    def log(self, depth, message):
        self.step_counter += 1
        self.logs.append({
            "step": self.step_counter,
            "depth": depth,
            "message": message
        })

    def negate(self, node):
        if isinstance(node, Neg):
            return node.expr
        return Neg(node)

    def simplify_and_decompose(self, formula):
        # Break down conjunctions: A ^ B -> [A, B]
        if isinstance(formula, Conj):
            return self.simplify_and_decompose(formula.left) + self.simplify_and_decompose(formula.right)
        
        # Double Negation elimination: ~~A -> A
        if isinstance(formula, Neg) and isinstance(formula.expr, Neg):
            return self.simplify_and_decompose(formula.expr.expr)
        
        # De Morgan's Law for Negated Disjunction: ~(A v B) -> ~A ^ ~B -> [~A, ~B]
        if isinstance(formula, Neg) and isinstance(formula.expr, Disj):
            left_neg = self.negate(formula.expr.left)
            right_neg = self.negate(formula.expr.right)
            return self.simplify_and_decompose(left_neg) + self.simplify_and_decompose(right_neg)
            
        # Negated Implication: ~(A -> B) -> A ^ ~B -> [A, ~B]
        if isinstance(formula, Neg) and isinstance(formula.expr, Impl):
            left = formula.expr.left
            right_neg = self.negate(formula.expr.right)
            return self.simplify_and_decompose(left) + self.simplify_and_decompose(right_neg)

        return [formula]

    def prove(self, goal, path=None, depth=0):
        if path is None:
            path = []

        goal_str = str(goal)
        self.log(depth, f"🔍 Goal check: Proving {goal_str}")

        # 1. Loop detection
        if goal in path:
            self.log(depth, f"⚠️ Infinite Loop detected for sub-goal {goal_str}. Backtracking...")
            return False, None

        # 2. Base Case: Goal matches a premise directly
        for idx, prem in enumerate(self.premises):
            if prem == goal:
                self.log(depth, f"✅ Goal {goal_str} matches Premise: '{str(prem)}'")
                proof = [{
                    "statement": goal_str,
                    "justification": f"Given Premise"
                }]
                return True, proof

        # 3. Conjunction Introduction: To prove A ^ B, prove A and prove B
        if isinstance(goal, Conj):
            self.log(depth, f"🌿 Goal is a conjunction. Attempting to prove components...")
            self.log(depth, f"➡️ Component 1: {str(goal.left)}")
            ok_left, proof_left = self.prove(goal.left, path + [goal], depth + 1)
            if ok_left:
                self.log(depth, f"➡️ Component 2: {str(goal.right)}")
                ok_right, proof_right = self.prove(goal.right, path + [goal], depth + 1)
                if ok_right:
                    self.log(depth, f"✅ Both components of conjunction proven: {goal_str}")
                    combined = proof_left + proof_right + [{
                        "statement": goal_str,
                        "justification": f"Conjunction Introduction on '{str(goal.left)}' and '{str(goal.right)}'"
                    }]
                    return True, combined
            self.log(depth, f"❌ Failed to prove conjunction: {goal_str}")
            return False, None

        # 4. Disjunction Introduction: To prove A v B, try proving A. If that fails, try proving B.
        if isinstance(goal, Disj):
            self.log(depth, f"🌿 Goal is a disjunction. Trying Left side: {str(goal.left)}")
            ok_left, proof_left = self.prove(goal.left, path + [goal], depth + 1)
            if ok_left:
                self.log(depth, f"✅ Proven Left side of disjunction: {str(goal.left)}")
                combined = proof_left + [{
                    "statement": goal_str,
                    "justification": f"Disjunction Introduction (Left) on '{str(goal.left)}'"
                }]
                return True, combined

            self.log(depth, f"🌿 Left failed. Trying Right side of disjunction: {str(goal.right)}")
            ok_right, proof_right = self.prove(goal.right, path + [goal], depth + 1)
            if ok_right:
                self.log(depth, f"✅ Proven Right side of disjunction: {str(goal.right)}")
                combined = proof_right + [{
                    "statement": goal_str,
                    "justification": f"Disjunction Introduction (Right) on '{str(goal.right)}'"
                }]
                return True, combined
            self.log(depth, f"❌ Failed to prove either side of disjunction: {goal_str}")
            return False, None

        # 5. Conditional Proof: To prove A -> B, assume A as premise and prove B
        if isinstance(goal, Impl):
            self.log(depth, f"🌿 Goal is an implication. Assuming antecedent '{str(goal.left)}' to prove consequent '{str(goal.right)}'")
            self.premises.append(goal.left)
            ok, proof_sub = self.prove(goal.right, path + [goal], depth + 1)
            self.premises.pop()  # Clean up temporary assumption
            if ok:
                self.log(depth, f"✅ Antecedent assumption '{str(goal.left)}' successfully led to consequent '{str(goal.right)}'")
                combined = proof_sub + [{
                    "statement": goal_str,
                    "justification": f"Conditional Proof (Assumed '{str(goal.left)}' -> Proved '{str(goal.right)}')"
                }]
                return True, combined
            self.log(depth, f"❌ Conditional proof failed for implication: {goal_str}")

        # 6. Apply Rules of Inference by scanning existing premises

        # --- Rule: Modus Ponens (MP) ---
        # Premise: A -> B. Goal: B. Sub-goal: A
        for prem in self.premises:
            if isinstance(prem, Impl) and prem.right == goal:
                self.log(depth, f"⚙️ Attempting Modus Ponens with Premise '{str(prem)}' to derive goal '{goal_str}'")
                ok, proof_sub = self.prove(prem.left, path + [goal], depth + 1)
                if ok:
                    self.log(depth, f"✅ Modus Ponens succeeded on '{str(prem)}'")
                    combined = proof_sub + [{
                        "statement": goal_str,
                        "justification": f"Modus Ponens on '{str(prem)}' using antecedent '{str(prem.left)}'"
                    }]
                    return True, combined
                self.log(depth, f"↩️ Modus Ponens failed on '{str(prem)}' - could not prove '{str(prem.left)}'. Backtracking...")

        # --- Rule: Modus Tollens (MT) ---
        # Premise: A -> B. Goal: ~A. Sub-goal: ~B
        for prem in self.premises:
            if isinstance(prem, Impl):
                neg_left = self.negate(prem.left)
                if neg_left == goal:
                    sub_goal = self.negate(prem.right)
                    self.log(depth, f"⚙️ Attempting Modus Tollens with Premise '{str(prem)}' to derive goal '{goal_str}'")
                    ok, proof_sub = self.prove(sub_goal, path + [goal], depth + 1)
                    if ok:
                        self.log(depth, f"✅ Modus Tollens succeeded on '{str(prem)}'")
                        combined = proof_sub + [{
                            "statement": goal_str,
                            "justification": f"Modus Tollens on '{str(prem)}' using negated consequent '{str(sub_goal)}'"
                        }]
                        return True, combined
                    self.log(depth, f"↩️ Modus Tollens failed on '{str(prem)}' - could not prove '{str(sub_goal)}'. Backtracking...")

        # --- Rule: Disjunctive Syllogism (DS) ---
        # Premise: A v B. Goal: A (Sub-goal: ~B) or Goal: B (Sub-goal: ~A)
        for prem in self.premises:
            if isinstance(prem, Disj):
                if prem.left == goal:
                    sub_goal = self.negate(prem.right)
                    self.log(depth, f"⚙️ Attempting Disjunctive Syllogism with Premise '{str(prem)}' to derive goal '{goal_str}'")
                    ok, proof_sub = self.prove(sub_goal, path + [goal], depth + 1)
                    if ok:
                        self.log(depth, f"✅ Disjunctive Syllogism succeeded on '{str(prem)}'")
                        combined = proof_sub + [{
                            "statement": goal_str,
                            "justification": f"Disjunctive Syllogism on '{str(prem)}' using negation '{str(sub_goal)}'"
                        }]
                        return True, combined
                    self.log(depth, f"↩️ Disjunctive Syllogism failed on '{str(prem)}' - could not prove '{str(sub_goal)}'. Backtracking...")
                elif prem.right == goal:
                    sub_goal = self.negate(prem.left)
                    self.log(depth, f"⚙️ Attempting Disjunctive Syllogism with Premise '{str(prem)}' to derive goal '{goal_str}'")
                    ok, proof_sub = self.prove(sub_goal, path + [goal], depth + 1)
                    if ok:
                        self.log(depth, f"✅ Disjunctive Syllogism succeeded on '{str(prem)}'")
                        combined = proof_sub + [{
                            "statement": goal_str,
                            "justification": f"Disjunctive Syllogism on '{str(prem)}' using negation '{str(sub_goal)}'"
                        }]
                        return True, combined
                    self.log(depth, f"↩️ Disjunctive Syllogism failed on '{str(prem)}' - could not prove '{str(sub_goal)}'. Backtracking...")

        # --- Rule: Hypothetical Syllogism (HS) ---
        # Premise: A -> B. Goal: A -> C. Sub-goal: B -> C
        # Or Premise: B -> C. Goal: A -> C. Sub-goal: A -> B
        if isinstance(goal, Impl):
            for prem in self.premises:
                if isinstance(prem, Impl) and prem.left == goal.left:
                    # Match A -> B. Need to prove B -> C.
                    sub_goal = Impl(prem.right, goal.right)
                    self.log(depth, f"⚙️ Attempting Hypothetical Syllogism with Premise '{str(prem)}' to prove '{goal_str}'")
                    ok, proof_sub = self.prove(sub_goal, path + [goal], depth + 1)
                    if ok:
                        self.log(depth, f"✅ Hypothetical Syllogism succeeded on '{str(prem)}'")
                        combined = proof_sub + [{
                            "statement": goal_str,
                            "justification": f"Hypothetical Syllogism on '{str(prem)}' and proven relation '{str(sub_goal)}'"
                        }]
                        return True, combined
                    self.log(depth, f"↩️ Hypothetical Syllogism failed with premise '{str(prem)}'. Backtracking...")
                elif isinstance(prem, Impl) and prem.right == goal.right:
                    # Match B -> C. Need to prove A -> B.
                    sub_goal = Impl(goal.left, prem.left)
                    self.log(depth, f"⚙️ Attempting Hypothetical Syllogism with Premise '{str(prem)}' to prove '{goal_str}'")
                    ok, proof_sub = self.prove(sub_goal, path + [goal], depth + 1)
                    if ok:
                        self.log(depth, f"✅ Hypothetical Syllogism succeeded on '{str(prem)}'")
                        combined = proof_sub + [{
                            "statement": goal_str,
                            "justification": f"Hypothetical Syllogism on '{str(prem)}' and proven relation '{str(sub_goal)}'"
                        }]
                        return True, combined
                    self.log(depth, f"↩️ Hypothetical Syllogism failed with premise '{str(prem)}'. Backtracking...")

        # --- Rule: Proof by Cases (Disjunction Elimination) ---
        # If we have A v B in premises, and want to prove goal G:
        # Prove A -> G and B -> G
        if not isinstance(goal, Impl):
            for prem in self.premises:
                if isinstance(prem, Disj):
                    case1 = Impl(prem.left, goal)
                    case2 = Impl(prem.right, goal)
                    self.log(depth, f"⚙️ Attempting Proof by Cases on Premise '{str(prem)}' to derive goal '{goal_str}'")
                    self.log(depth, f"➡️ Case 1: Prove '{str(case1)}'")
                    ok_1, proof_sub1 = self.prove(case1, path + [goal], depth + 1)
                    if ok_1:
                        self.log(depth, f"➡️ Case 2: Prove '{str(case2)}'")
                        ok_2, proof_sub2 = self.prove(case2, path + [goal], depth + 1)
                        if ok_2:
                            self.log(depth, f"✅ Proof by Cases succeeded on premise '{str(prem)}'")
                            combined = proof_sub1 + proof_sub2 + [{
                                "statement": goal_str,
                                "justification": f"Proof by Cases (Disjunction Elimination) on '{str(prem)}' with subproofs '{str(case1)}' & '{str(case2)}'"
                            }]
                            return True, combined
                    self.log(depth, f"↩️ Proof by Cases failed on premise '{str(prem)}'. Backtracking...")

        self.log(depth, f"❌ Failed to prove goal: {goal_str}")
        return False, None

# Helper to remove duplicate proofs steps, preserving order
def clean_proof(proof_steps):
    if not proof_steps:
        return []
    seen = set()
    cleaned = []
    for step in proof_steps:
        stmt = step["statement"]
        if stmt not in seen:
            seen.add(stmt)
            cleaned.append(step)
    return cleaned

# =====================================================================
# 4. FLASK ENDPOINTS
# =====================================================================

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/analyze", methods=["POST"])
def analyze():
    data = request.get_json() or {}
    premises_raw = data.get("premises", [])
    conclusion_raw = data.get("conclusion", "")

    if not conclusion_raw.strip():
        return jsonify({"error": "Conclusion cannot be empty."}), 400

    try:
        # Parse conclusion
        conclusion = parse(conclusion_raw)
    except ValueError as e:
        return jsonify({"error": f"Error parsing conclusion: {str(e)}"}), 400

    parsed_premises = []
    for idx, prem_str in enumerate(premises_raw):
        if not prem_str.strip():
            continue
        try:
            parsed_premises.append(parse(prem_str))
        except ValueError as e:
            return jsonify({"error": f"Error parsing premise {idx + 1} ('{prem_str}'): {str(e)}"}), 400

    # Initialize solver and prove
    solver = Solver(parsed_premises)
    success, raw_proof = solver.prove(conclusion)
    
    proof = clean_proof(raw_proof) if success else []

    return jsonify({
        "success": success,
        "logs": solver.logs,
        "proof": proof
    })

if __name__ == "__main__":
    app.run(debug=True)
