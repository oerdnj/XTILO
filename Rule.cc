// SPDX-FileCopyrightText: 2023 Ondřej Surý
//
// SPDX-License-Identifier: WTFPL

#include "Direction.hh"
#include <cstdint>

#include "Rule.hh"

namespace TuringMachine
{

Rule::Rule(char r, char w, Direction d)
    : read_symbol(r), write_symbol(w), direction(d)
{
}

Rule::Rule(char r, char w, char d) : read_symbol(r), write_symbol(w)
{
	switch (d) {
	case 'r':
	case 'R':
		direction = Direction::RIGHT;
		break;
	case 'l':
	case 'L':
		direction = Direction::LEFT;
		break;
	case 'n':
	case 'N':
	case 's':
	case '*':
		direction = Direction::STAY;
		break;
	default:
		throw;
	}
}

bool Rule::operator==(const Rule &rule) const
{
	return (read_symbol == rule.read_symbol &&
		write_symbol == rule.write_symbol &&
		direction == rule.direction);
}

std::ostream &operator<<(std::ostream &os, const Rule rule)
{
	os << rule.read_symbol << " " << rule.write_symbol << " "
	   << rule.direction;
	return os;
}

bool operator<(const Rule &a, const Rule &b)
{
	return a.read_symbol < b.read_symbol;
}
}; // namespace TuringMachine
