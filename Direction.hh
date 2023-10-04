// SPDX-FileCopyrightText: 2023 Ondřej Surý
//
// SPDX-License-Identifier: WTFPL

#pragma once

#include <ostream>

namespace TuringMachine
{

enum class Direction {
	STAY,
	LEFT,
	RIGHT,
};

std::ostream &operator<<(std::ostream &os, const Direction d);

}; // namespace TuringMachine
