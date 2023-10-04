// SPDX-FileCopyrightText: 2023 Ondřej Surý
//
// SPDX-License-Identifier: WTFPL

#include <iostream>

#include "TuringMachine.hh"

int main(int argc, char **argv)
{
	if (argc < 3) {
		std::cerr << "usage: " << argv[0]
			  << " <tape> <file_with_recipe>\n";
		return 2;
	}

	TuringMachine::TuringMachine tm(argv[1], argv[2]);
	tm.processTape();

	std::cout << "\n";

	return 0;
}
