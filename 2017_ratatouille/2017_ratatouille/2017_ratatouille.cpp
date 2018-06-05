// 2017_ratatouille.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>

void ratatouille(std::string if_name, std::string of_name)
{
	std::ifstream in_file(if_name, std::ifstream::in);
	std::ofstream out_file(of_name, std::ofstream::out);

	if (in_file.is_open() && out_file.is_open()) {
		int case_num;

		in_file >> case_num;

		for (int i = 0; i < case_num; i++) {


			std::cout << "Case #" << i + 1 << ": " << std::endl;
		}

		in_file.close();
		out_file.close();
	}
}

int main()
{
    return 0;
}

