// SPDX-FileCopyrightText: 2023 Ondřej Surý
//
// SPDX-License-Identifier: WTFPL

#pragma once

#include <map>
#include <string>

#include "Rule.hh"

namespace TuringMachine
{

struct State {
	std::string name;
	std::map<Rule, State &> transitions;

	State(std::string n);

	bool operator==(const State &state) const;
};

std::ostream &operator<<(std::ostream &os, const State s);

}; // namespace TuringMachine
