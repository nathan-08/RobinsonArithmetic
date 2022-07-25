#include "node.h"
using namespace std;

Node::Node(NodeType type, u8 value)
	: type(type), left(nullptr), right(nullptr), value(value) {}

Node::Node(NodeType type, Node* left, Node* right)
	: type(type), left(left), right(right)
{ }

Node::~Node() {
	if (left) delete left;
	if (right) delete right;
}

ostream& operator<<(ostream& os, Node& node) {
	switch (node.type) {
	case NODE_NEG:
		os << "!";
		break;
	case NODE_IMPL:
		os << "=>";
		break;
	case NODE_IFF:
		os << "<=>";
		break;
	case NODE_AND:
		os << "&";
		break;
	case NODE_OR:
		os << "|";
		break;

	case NODE_EQ:
		os << "=";
		break;
	case NODE_PLUS:
		os << "+";
		break;
	case NODE_MULT:
		os << "x";
		break;
	case NODE_S:
		os << "S";
		break;
	case NODE_ZERO:
		os << "0";
		break;
	default:
		os << "<UNKNOWN>";
	}
	return os;
}