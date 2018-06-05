// 2017_bathroomStalls.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define DEC_SIZE_ 20

class Decimal {
public:
	Decimal() {}

	Decimal(std::string input) {
		val = input;
		std::reverse(val.begin(), val.end());
	}

	Decimal(int input) {
		val = std::to_string(input);
		std::reverse(val.begin(), val.end());
	}

	bool isOdd() {
		return (val[0] - '0' % 2 != 0);
	}

	bool isEven() {
		return (val[0] - '0' % 2 == 0);
	}

	Decimal operator=(Decimal other) {
		val = other.val;

		return *this;
	}

	Decimal operator=(int other) {
		val = std::to_string(other);
		std::reverse(val.begin(), val.end());

		return *this;
	}

	Decimal operator+(int new_val) {
		int carry = 0;

		for (int i = 0; i < val.size() - 1; i++) {
			int tmp = val[i] - '0';

			tmp += new_val + carry;

			carry = tmp / 10;
			tmp = tmp % 10 + '0';

			val[i] = tmp;
		}

		if (carry > 0) {
			std::string attachment = std::to_string(carry);

			std::reverse(attachment.begin(), attachment.end());

			val.append(attachment);
		}

		return *this;
	}

	Decimal operator-(int new_val) {
		return (*this + (-new_val));
	}

	Decimal operator/(int divisor) {
		std::reverse(val.begin(), val.end());
		int carry = 0;

		std::string result;

		int i;

		for (i = 0; i + 5 < val.size() - 1; i += 5) {
			std::string sub_str = val.substr(i, i + 4);

			int tmp = std::stoi(sub_str) + carry * 100000;

			carry = tmp % divisor;
			tmp /= divisor;

			result.append(std::to_string(tmp));
		}

		std::string sub_str = val.substr(i);

		if (carry > 0) {
			sub_str.insert(0, std::to_string(carry));
		}

		int tmp = std::stoi(sub_str);

		carry = tmp % divisor;
		tmp /= divisor;

		result.append(std::to_string(tmp));

		val = result;
		std::reverse(val.begin(), val.end());

		return *this;
	}

	Decimal operator*=(int mult) {
		std::reverse(val.begin(), val.end());

		int carry = 0;

		for (int i = 0; i < val.size(); i++) {
			int tmp = val[i] - '0';

			tmp = tmp * mult + carry;

			carry = tmp / 10;
			tmp %= 10;
			
			val[i] = tmp + '0';
		}

		std::string appendix = std::to_string(carry);
		std::reverse(appendix.begin(), appendix.end());

		val.append(appendix);

		std::reverse(val.begin(), val.end());
	
		return *this;
	}

	bool operator<(Decimal other) {
		if (val.size() < other.val.size())
			return true;

		if (val.size() > other.val.size())
			return false;

		return (val < other.val);
	}

	Decimal operator*(int mult) {
		Decimal output;

		output.val = val;
		std::string &res = output.val;

		std::reverse(res.begin(), res.end());

		int carry = 0;

		for (int i = 0; i < res.size(); i++) {
			int tmp = res[i] - '0';

			tmp = tmp * mult + carry;

			carry = tmp / 10;
			tmp %= 10;

			res[i] = tmp + '0';
		}

		std::string appendix = std::to_string(carry);
		std::reverse(appendix.begin(), appendix.end());

		res.append(appendix);

		std::reverse(res.begin(), res.end());

		return output;
	}

	Decimal operator+(Decimal other) {
		int carry = 0;
		Decimal output(other.val);
		std::string &other_val = output.val;

		for (int i = 0; i < other_val.size() && i < val.size(); i++) {
			int tmp_val = val[i] - '0';
			int o_val = other_val[i] - '0';

			o_val += tmp_val + carry;

			carry = o_val / 10;
			tmp_val %= 10;

			other_val[i] = tmp_val + '0';
		}

		if (carry > 0) {
			if (carry < )
		}
	}

	std::string getVal() {
		std::string output = val;
		std::reverse(output.begin(), output.end());

		return output;
	}

private:
	std::string val;
};

bool bathroomStalls(std::string if_name, std::string of_name)
{
	std::ifstream input_file(if_name, std::ifstream::in);
	std::ofstream output_file(of_name, std::ofstream::out);

	if (input_file.is_open() && output_file.is_open()) {
		int case_num;

		input_file >> case_num;

		for (int i = 0; i < case_num; i++) {
			std::string stall, user;
			
			input_file >> stall;
			input_file >> user;

			Decimal stall_num(stall), user_num(user);

			std::cout << "Stall num = " << stall << " size of stall_num = " << sizeof(long int) << std::endl;

			Decimal big_num, small_num;
			Decimal big_val, small_val;
			Decimal node_num = 2;

			big_num = 1;
			small_num = 0;
			big_val = stall_num;
			small_val = 0;
			
			while (node_num - 1 < user_num) {
				node_num *= 2;
				bool check_big = big_val.isOdd();
				bool check_small = small_val.isOdd();
				
				//4 cases
				if (!check_big && !check_small) {
					//2k + 1 & 2k + 1: new_big = new_small = k
					big_val = small_val = big_val / 2;
					big_num = small_num = big_num + small_num;
				}
				else if (!check_big && check_small) {
					//2k + 1 & 2k
					big_val = big_val / 2;
					small_val = big_val - 1;
					big_num = big_num * 2 + small_num;
				}
				else if (check_big && !check_small) {
					//2k & 2k - 1
					big_val = big_val / 2;
					small_val = big_val - 1;
					small_num = small_num * 2 + big_num;
				}
				else {
					//2k & 2k
					big_val = big_val / 2;
					small_val = big_val - 1;
					small_num = big_num = big_num + small_num;
				}				
			}
			
			Decimal remain_user_num = user_num - node_num / 2 + 1;
			Decimal max, min;

			if (remain_user_num > big_num) {
				if (small_val % 2 == 0) {
					max = small_val / 2;
					min = max - 1;
				}
				else {
					max = min = small_val / 2;
				}
			}
			else {
				if (big_val % 2 == 0) {
					max = big_val / 2;
					min = max - 1;
				}
				else {
					max = min = big_val / 2;
				}
			}


			output_file << "Case #" << i + 1 << ": " << max << " " << min << std::endl;
		}

		input_file.close();
		output_file.close();

		return true;
	}

	return false;
}

int main()
{
	bathroomStalls("C-small-practice-1.in", "C-small-practice-1.txt");
	std::cout << "End of first" << std::endl;
	getchar();
	bathroomStalls("C-small-practice-2.in", "C-small-practice-2.txt");
	std::cout << "End of Second" << std::endl;
	getchar();
	bathroomStalls("C-large-practice.in", "C-large-practice.txt");
	std::cout << "End of thirds" << std::endl;
	getchar();
	getchar();

	
	return 0;
}

