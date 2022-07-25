#pragma once
#include "parser.h"
#include "nat.h"

class Interpreter {
	Value* visit(Node*);
public:
	Interpreter(Node*);
};

