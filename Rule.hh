// SPDX-FileCopyrightText: 2023 Ondřej Surý
//
// SPDX-License-Identifier: WTFPL

#pragma once

#include <cstdint>
#include "Direction.hh"

namespace TuringMachine
{

struct Rule {
	uint8_t read_symbol, write_symbol;
	Direction direction;

	Rule(char r, char w, Direction d);
	Rule(char r, char w, char d);
	bool operator==(const Rule &rule) const;
};

std::ostream &operator<<(std::ostream &os, const Rule rule);

bool operator<(const Rule &a, const Rule &b);

}; // namespace TuringMachine
