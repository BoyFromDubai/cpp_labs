#include "sequence.h"
#include <random>
#include <iostream>


Sequence::Sequence(const int N) {
	std::srand((unsigned)std::time(NULL));
	
	size = N;
	arr = new int[N];

	for (size_t i = 0; i < N; i++)
		arr[i] = std::rand();
}

Sequence::Sequence(const int N, int* arr) {
	size = N;
	this->arr = new int[N];
	std::copy(arr, arr + N, this->arr);
}


Sequence::Sequence(const Sequence& obj): 
	arr(obj.size ? new int[obj.size] : nullptr), 
	size(obj.size)
{
	std::copy(obj.arr, obj.arr + size, arr);
}

Sequence::~Sequence() {
	delete[] arr;
}

int* Sequence::getSequence() {
	int* tmp = new int[size];
	std::copy(arr, arr + size, tmp);

	return tmp;
}

void Sequence::printSequence() {
	for (size_t i = 0; i < size; i++)
		std::cout << arr[i] << "\t";

	std::cout << std::endl;
}


Sequence getResSequence(Sequence sequence) {
	int seq_size = sequence.getSize();
	int res_seq_size = seq_size * 2;
	int* seq = sequence.getSequence();
	int* tmp_seq = sequence.getSequence();
	int* seq_2_step = new int[seq_size];
	int* res = new int[res_seq_size];

	for (size_t i = 0; i < seq_size; i++) {
		size_t cur_max_num = 0;
		size_t cur_max_num_pos = i;

		for (size_t j = i; j < seq_size; j++) {
			size_t cur_num = changeNum(tmp_seq[j]);
			
			if (cur_num > cur_max_num) {
				cur_max_num = cur_num;
				cur_max_num_pos = j;
			}
		}

		if (i == 0)
			std::copy(tmp_seq, tmp_seq + seq_size, seq_2_step);

		res[i] = seq[cur_max_num_pos];

		int tmp_elem = seq[cur_max_num_pos];
		seq[cur_max_num_pos] = seq[i];
		seq[i] = tmp_elem;
		std::copy(seq, seq + seq_size, tmp_seq);
	}

	delete[] seq;
	delete[] tmp_seq;

	for (size_t i = 0; i < seq_size; i++) {
		for (size_t j = i; j < seq_size; j++) {
			if (seq_2_step[i] > seq_2_step[j]) {
				int tmp = seq_2_step[i];
				seq_2_step[i] = seq_2_step[j];
				seq_2_step[j] = tmp;
			}
		}

		res[seq_size + i] = seq_2_step[i];
	}

	delete[] seq_2_step;

	Sequence res_seq(res_seq_size, res);

	delete[] res;

	return res_seq;
}

int changeNum(int& num) {
	size_t count = 0;
	int tmp = num;
	int res = 0;

	while (tmp != 0) {
		int digit = tmp % 10;
		tmp = tmp / 10;
		res += count == 0 ? ++digit % 10 : (++digit % 10) * (std::pow(10, count));
		count++;
	}

	num = res;

	return count;
}

