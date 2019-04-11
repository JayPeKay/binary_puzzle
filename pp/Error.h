#pragma once

class Error {
public:
	int row = -1;
	int column = -1;

	bool ruleOneIsColumn;
	bool ruleTwoIsColumn;

	bool unmodifiableField = false;
	bool ruleOne = false;
	bool ruleTwo = false;
	bool ruleThree = false;

	Error();
	~Error();

	bool operator ==(bool x);

private:

};