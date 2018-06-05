// 2017_tidyNumber.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

int main()
{
	std::string if_name = "B-small-practice.in";
	std::string of_name = "B-small-practice.txt";

	std::ifstream input_file(if_name, std::ifstream::in);
	std::ofstream output_file(of_name, std::ofstream::out);

	if (input_file.is_open() && output_file.is_open()) {
		int case_num;
		
		input_file >> case_num;

		for (int i = 0; i < case_num; i++) {
			std::string number;

			input_file >> number;
			
			for (int j = 0; j < number.size() - 1; j++) {
				if (number[j] > number[j + 1]) {
					number[j]--;
					for (int k = j + 1; k < number.size(); k++) {
						number[k] = '9';
					}

					for (int k = j - 1; k >= 0; k--) {
						if (number[k] > number[k + 1]) {
							number[k]--;
							number[k + 1] = '9';
						}
					}
				}
			}

			if (number[0] == '0') {
				number.erase(0, 1);
			}

			output_file << "Case #" << i + 1 << ": " << number << std::endl;
		}

		input_file.close();
		output_file.close();
	}

    return 0;
}

