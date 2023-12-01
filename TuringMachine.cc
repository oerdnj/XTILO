// SPDX-FileCopyrightText: 2023 Ondřej Surý
//
// SPDX-License-Identifier: WTFPL

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Direction.hh"
#include "Rule.hh"
#include "State.hh"
#include "TuringMachine.hh"

namespace TuringMachine
{

TuringMachine::TuringMachine(std::string tape_, std::string filename)
    : tape(tape_), q_0(nullptr)
{
	std::ifstream ifs(filename, std::ios::in);
	std::string::size_type n;

	if (!ifs.is_open()) {
		throw std::invalid_argument(filename);
	}

	while ((n = tape.find_first_of(" ")) != std::string::npos) {
		tape[n] = '_';
	}

	std::string line;

	while (getline(ifs, line)) {
		n = line.find_first_of(";");
		if (n != std::string::npos) {
			line = line.substr(0, n);
		}

		n = line.find_last_not_of(" \t");
		if (n == std::string::npos) {
			continue;
		}

		if (n + 1 != line.size() - 1) {
			line = line.substr(0, n + 1);
		}

		std::istringstream iss(line);
		std::string present_state("");

		iss >> present_state;

		State &state = getState(present_state);

		if (q_0 == nullptr) {
			q_0 = &state;
		}

		std::string next_state;
		char read_symbol, write_symbol, direction;

		iss >> read_symbol >> write_symbol >> direction >> next_state;

		State &next = getState(next_state);

		Rule rule(read_symbol, write_symbol, direction);

		const auto [it, success] =
		    state.transitions.emplace(rule, next);

		assert(success);
	}

	ifs.close();

	if (q_0 == nullptr) {
		throw std::runtime_error("no states defined in " + filename);
	}
}

State &TuringMachine::getState(std::string name)
{
	if (auto search = states.find(name); search != states.end()) {
		return search->second;
	}

	const auto [it, success] = states.emplace(name, State(name));
	assert(success);

	return it->second;
}

void TuringMachine::displayTape(State &state, size_t idx)
{
	// Make sure the line is completely clean first
	std::cout << "\r";
	for (size_t i = 0; i < tape.size() + 5; i++) {
		std::cout << " ";
	}

	std::cout << "\r";

	std::cout << state << ":";

	std::cout << tape.substr(0, idx) << "[" << tape[idx] << "]";

	// Only print non-blanks at the end of the tape
	std::string::size_type n = tape.find_last_not_of("_");
	if (idx + 1 < n) {
		std::cout << tape.substr(idx + 1, n);
	}
	std::cout << std::flush;
	usleep(20000);
}

void TuringMachine::displayStates()
{
	for (auto state_it : states) {
		State &state = state_it.second;
		for (auto rule_it = state.begin(); rule_it != state.end();
		     ++rule_it) {
			const Rule &rule = rule_it->first;

			const State &next = rule_it->second;
			std::cout << state.name << " " << rule.read_symbol
				  << " " << rule.write_symbol << " "
				  << rule.direction << " " << next.name << "\n";
		}
	}
}

void TuringMachine::adjustTape(size_t &idx)
{
	if (idx == SIZE_MAX) {
		idx = 0;
		tape = "_" + tape;
	}
	if (idx == tape.size()) {
		tape = tape + "_";
	}
}

void TuringMachine::processTape(void)
{
	size_t idx = 0;
	State state = *q_0;

	displayTape(state, idx);

	while (true) {
		bool result = processSymbol(idx, state);
		adjustTape(idx);
		displayTape(state, idx);
		if (!result) {
			return;
		}

		if (state.name.substr(0, 3) == "halt") {
			return;
		}
	}
}

void TuringMachine::applyRule(size_t &idx, State &state, char &head_symbol,
			      const Rule &rule, const State &next)
{
	if (rule.write_symbol != '*') {
		head_symbol = rule.write_symbol;
	}

	switch (rule.direction) {
	case Direction::LEFT:
		idx--;
		break;
	case Direction::RIGHT:
		idx++;
		break;
	case Direction::STAY:
		break;
	}
	state = next;
}

bool TuringMachine::processSymbol(size_t &idx, State &state)
{
	char &head_symbol = tape[idx];

	for (auto &pair : state.transitions) {
		const Rule &rule = pair.first;
		const State &next = pair.second;

		if (rule.read_symbol == head_symbol) {
			applyRule(idx, state, head_symbol, rule, next);
			return true;
		}
	}

	/* The fallback rule must be last */
	for (auto &pair : state.transitions) {
		const Rule &rule = pair.first;
		const State &next = pair.second;

		if (rule.read_symbol == '*') {
			applyRule(idx, state, head_symbol, rule, next);
			return true;
		}
	}

	/* No matching state */
	return false;
}

}; // namespace TuringMachine
