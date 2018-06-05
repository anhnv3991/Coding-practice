// 2017_oversizedPancakeFlipper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>


int main()
{
	std::string if_name = "A-large-practice.in";
	std::string of_name = "Large-practice.txt";
	std::ifstream input_file(if_name, std::ifstream::in);
	std::ofstream output_file(of_name, std::ofstream::out);

	if (input_file.is_open() && output_file.is_open()) {
		int case_num;

		input_file >> case_num;

		for (int i = 0; i < case_num; i++) {
			int min_flip = 0;
			bool ok = true;
			std::string cake_status;
			int flip_size;

			input_file >> cake_status;
			input_file >> flip_size;

			for (int j = 0; j < cake_status.size(); j++) {
				if (cake_status[j] == '-') {
					min_flip++;
					// Fliping
					int k;
					for (k = 0; k < flip_size && k + j < cake_status.size(); k++) {
						if (cake_status[j + k] == '-') {
							cake_status[j + k] = '+';
						}
						else {
							cake_status[j + k] = '-';
						}
					}

					if (j + k == cake_status.size() && k < flip_size) {
						ok = false;
					}
				}
			}

			if (ok) {
				output_file << "Case #" << i + 1 << ": " << min_flip << std::endl;
			}
			else {
				output_file << "Case #" << i + 1 << ": IMPOSSIBLE" << std::endl;
			}
		}

		input_file.close();
		output_file.close();
	}

    return 0;
}

