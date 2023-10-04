// SPDX-FileCopyrightText: 2023 Ondřej Surý
//
// SPDX-License-Identifier: WTFPL

#pragma once

#include <map>
#include <string>
#include <vector>

#include <unistd.h>

#include "State.hh"

namespace TuringMachine
{

class TuringMachine
{
	std::string tape;
	std::map<std::string, State> states;
	std::vector<char> input_alphabet;
	std::vector<char> tape_alphabet;
	State *q_0;

	State &getState(std::string name);

      public:
	TuringMachine(std::string tape_, std::string filename);

	void displayTape(State &state, size_t idx);
	void displayStates();

	void processTape(void);

      private:
	void adjustTape(size_t &idx);
	void applyRule(size_t &idx, State &state, char &head_symbol,
		       const Rule &rule, const State &next);

	bool processSymbol(size_t &idx, State &state);

}; // class TuringMachine

} // namespace TuringMachine
