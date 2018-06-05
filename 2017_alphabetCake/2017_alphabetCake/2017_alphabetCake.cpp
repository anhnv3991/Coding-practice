// 2017_alphabetCake.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

class Cake {
public:

	typedef struct {
		int top, bottom;
		int left, right;
		int val;
	} Rect;

	Cake() {}

	Cake(int width, int height) {
		width_ = width;
		height_ = height;

		cake_ = std::string(width_ * height_, '?');
	}

	void setInitPiece(int row, int col, int val) {
		if (val == '?')
			return;

		Rect new_piece;

		new_piece.top = new_piece.bottom = row;
		new_piece.left = new_piece.right = col;
		new_piece.val = val;

		pieces_.push_back(new_piece);

		cake_[row * width_ + col] = val;
	}

	void cutCake() {
		for (int i = 0; i < pieces_.size(); i++) {

			while (expandLeft(pieces_[i])) {}
			while (expandRight(pieces_[i])) {}
			while (expandUp(pieces_[i])) {}
			while (expandDown(pieces_[i])) {}
		}
	}

	bool expandLeft(Rect &piece) {
		if (piece.left == 0)
			return false;

		for (int i = piece.top; i <= piece.bottom; i++) {
			// Row i, col left - 1
			int cell_val = cake_[i * width_ + piece.left - 1];

			if (cell_val != '?' && cell_val != piece.val) {
				return false;
			}
		}

		piece.left--;

		for (int i = piece.top; i <= piece.bottom; i++) {
			cake_[i * width_ + piece.left] = piece.val;
		}

		return true;
	}

	bool expandRight(Rect &piece) {
		if (piece.right == width_ - 1)
			return false;

		for (int i = piece.top; i <= piece.bottom; i++) {
			int cell_val = cake_[i * width_ + piece.right + 1];

			if (cell_val != '?' && cell_val != piece.val) {
				return false;
			}
		}

		piece.right++;

		for (int i = piece.top; i <= piece.bottom; i++) {
			cake_[i * width_ + piece.right] = piece.val;
		}

		return true;
	}

	bool expandUp(Rect &piece) {
		if (piece.top == 0) 
			return false;
		
		for (int i = piece.left; i <= piece.right; i++) {
			int cell_val = cake_[(piece.top - 1) * width_ + i];

			if (cell_val != '?' && cell_val != piece.val) {
				return false;
			}
		}

		piece.top--;

		for (int i = piece.left; i <= piece.right; i++) {
			cake_[piece.top * width_ + i] = piece.val;
		}

		return true;
	}

	bool expandDown(Rect &piece) {
		if (piece.bottom == height_ - 1)
			return false;

		for (int i = piece.left; i <= piece.right; i++) {
			int cell_val = cake_[(piece.bottom + 1) * width_ + i];

			if (cell_val != '?' && cell_val != piece.val) {
				return false;
			}
		}

		piece.bottom++;

		for (int i = piece.left; i <= piece.right; i++) {
			cake_[piece.bottom * width_ + i] = piece.val;
		}

		return true;
	}

	std::string printOut() {
		std::ostringstream  output;

		for (int i = 0; i < height_; i++) {
			for (int j = 0; j < width_; j++) {
				output << cake_[i * width_ + j];
			}
			output << std::endl;
		}

		return output.str();
	}


private:
	std::string cake_;
	std::vector<Rect> pieces_;
	int width_, height_;
};

void alphabetCake(std::string if_name, std::string of_name)
{
	std::ifstream in_file(if_name, std::ifstream::in);
	std::ofstream out_file(of_name, std::ofstream::out);

	if (in_file.is_open() && out_file.is_open()) {
		int case_num;

		in_file >> case_num;

		for (int i = 0; i < case_num; i++) {
			int width, height;

			in_file >> height >> width;

			Cake new_cake(width, height);

			std::string cake_line;

			for (int row = 0; row < height; row++) {
				in_file >> cake_line;

				for (int col = 0; col < width; col++) {
					new_cake.setInitPiece(row, col, cake_line[col]);
				}
			}

			new_cake.cutCake();

			out_file << "Case #" << i + 1 << ":" << std::endl;
			out_file << new_cake.printOut();

		}

		in_file.close();
		out_file.close();
	}
}

int main()
{
	alphabetCake("A-small-practice.in", "A-small-practice-out.txt");
	alphabetCake("A-large-practice.in", "A-large-practice-out.txt");

    return 0;
}

