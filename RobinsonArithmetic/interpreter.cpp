#include "interpreter.h"
#include "nat.h"
using namespace std;

Interpreter::Interpreter(Node* n) {
	Value* v = visit(n);
	Nat* num = dynamic_cast<Nat*>(v);
	if (num) {
		cout << "evaluation: " << Nat::to_int(num) << endl;
	}
	else {
		Bool* b = dynamic_cast<Bool*>(v);
		if (!b) {
			cout << "cast failed" << endl;
		}
		else {
			cout << "evaluation (bool): " << b->value << endl;
		}
	}
	delete v;
}

Value* Interpreter::visit(Node* n) {
	if (!n) return nullptr;
	Value* left = visit(n->left);
	Value* right = visit(n->right);
	Value* result = nullptr;
	switch (n->type) {
	case NODE_ZERO:
		result = new Zero();
		break;
	case NODE_S:
		// HERE IS THE ISSUE (builds new nat out of 
		// previous nodes)
		result = new Suc(dynamic_cast<Nat*>(right)->copy());
		break;
	case NODE_PLUS:
		result = Nat::sum(
			dynamic_cast<Nat*>(left),
			dynamic_cast<Nat*>(right));
		break;
	case NODE_MULT:
		result = Nat::mul(
			dynamic_cast<Nat*>(left),
			dynamic_cast<Nat*>(right));
		break;
	case NODE_EQ:
	{
		bool bool_result = Nat::eq(
			dynamic_cast<Nat*>(left),
			dynamic_cast<Nat*>(right));
		delete left;
		delete right;
		return new Bool(bool_result);
	}
	default:
		cout << "~didn't plan for this" << endl;
	}
	delete left;
	delete right;
	return result;
}

