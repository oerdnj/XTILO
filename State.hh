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

	// Iterator for the transitions map
	struct Iterator {
		using iterator_category = std::input_iterator_tag;
		using value_type = std::pair<const Rule, State &>;
		using difference_type = std::ptrdiff_t;
		using pointer = value_type *;
		using reference = value_type &;

		// Iterator constructor
		Iterator(std::map<Rule, State &>::iterator iter) : iter(iter) {}

		// Iterator operations
		Iterator &operator++()
		{
			++iter;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		reference operator*() const { return *iter; }

		pointer operator->() { return &(*iter); }

		bool operator==(const Iterator &other) const
		{
			return iter == other.iter;
		}

		bool operator!=(const Iterator &other) const
		{
			return !(*this == other);
		}

	      private:
		std::map<Rule, State &>::iterator iter;
	};

	// Functions to get begin and end iterators for transitions
	Iterator begin() { return Iterator(transitions.begin()); }

	Iterator end() { return Iterator(transitions.end()); }
};

std::ostream &operator<<(std::ostream &os, const State s);

}; // namespace TuringMachine
