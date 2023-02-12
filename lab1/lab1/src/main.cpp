#include <iostream>
#include "sequence.h"

int main() {
	const int N = 5;
	Sequence sequence(N);
	sequence.printSequence();

	Sequence res_seq = getResSequence(sequence);
	res_seq.printSequence();

	return 0;
}