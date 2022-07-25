#include "nat.h"
#include <iostream>
#include <utility>
using namespace std;

// *** Zero *** //
Nat const* Zero::dec() const {
	return this;
}

Nat* Zero::copy() const {
	return new Zero();
}

// *** Suc *** //

Suc::Suc(Nat* n) : inner(n) {}

Nat const* Suc::dec() const {
	return inner;
}

Nat* Suc::copy() const {
	return new Suc(inner->copy());
}

Suc::~Suc() {
	delete inner;
}

// *** Nat *** //

bool Nat::is_zero(Nat const* a) {
	return dynamic_cast<Zero const*>(a) != nullptr;
}

Nat* Nat::sum(Nat const* a, Nat const* b) {
	Nat* c = b->copy();
	while (!is_zero(a)) {
		c = new Suc(c);
		a = a->dec();
	}
	return c;
}

Nat* Nat::mul(Nat const* a, Nat const* b) {
	Nat* c = new Zero();
	while (!is_zero(a)) {
		a = dynamic_cast<Suc const*>(a)->inner;
		// add b to c
		Nat const* bb = b;
		while (!is_zero(bb)) {
			bb = bb->dec();
			c = new Suc(c);
		}
	}
	return c;
}

Nat* Nat::from_int(u8 i) {
	Nat* n = new Zero();
	for (; i > 0; --i) {
		n = new Suc(n);
	}
	return n;
}

u16 Nat::to_int(Nat const* n) {
	u16 i = 0;
	for (; !is_zero(n); ++i) {
		n = n->dec();
	}
	return i;
}