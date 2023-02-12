#pragma once

class Sequence {
private: 
	int size;
	int* arr;

public:
	Sequence(const int N);
	Sequence(const int N, int*);
	Sequence(const Sequence&);

	int* getSequence();
	int getSize() { return this->size; }
	void printSequence();

	~Sequence();
};


Sequence getResSequence(Sequence);
int changeNum(int&);