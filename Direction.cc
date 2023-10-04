// SPDX-FileCopyrightText: 2023 Ondřej Surý
//
// SPDX-License-Identifier: WTFPL

#include <ostream>

#include "Direction.hh"

namespace TuringMachine
{

std::ostream &operator<<(std::ostream &os, const Direction d)
{
	switch (d) {
	case Direction::STAY:
		os << "*";
		break;
	case Direction::LEFT:
		os << "l";
		break;
	case Direction::RIGHT:
		os << "r";
		break;
	default:
		os.setstate(std::ios_base::failbit);
	}
	return os;
}

}; // namespace TuringMachine
