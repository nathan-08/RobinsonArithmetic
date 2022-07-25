#pragma once
// Inductive natural numbers
#include "types.h"

struct Value {
	virtual ~Value() = default;
};

struct Bool : public Value {
	bool value;
};

struct Nat : public Value {
	virtual ~Nat() = default;
	virtual Nat const* dec() const = 0;
	virtual Nat* copy() const = 0;

	static bool is_zero(Nat const*);
	static Nat* sum(Nat const*, Nat const*);
	static Nat* mul(Nat const*, Nat const*);
	static Nat* from_int(u8);
	static u16 to_int(Nat const*);
};

struct Zero : public Nat {
	Nat const* dec() const override;
	Nat* copy() const override;
};

struct Suc : public Nat {
	Nat* inner = nullptr;

	Suc(Nat*);
	~Suc();

	Nat const* dec() const override;
	Nat* copy() const override;
};
