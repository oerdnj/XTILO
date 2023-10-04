// SPDX-FileCopyrightText: 2023 Ondřej Surý
//
// SPDX-License-Identifier: WTFPL

#include <map>
#include <string>

#include "Rule.hh"
#include "State.hh"

namespace TuringMachine
{

State::State(std::string n) : name(n) {}

bool State::operator==(const State &state) const { return name == state.name; }

std::ostream &operator<<(std::ostream &os, const State s)
{
	os << s.name;
	return os;
}

}; // namespace TuringMachine
