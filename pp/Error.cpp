#include "Error.h"

Error::Error() {}

Error::~Error() {}

bool Error::operator==(bool x) {
	if (!unmodifiableField && !ruleOne && !ruleTwo && !ruleThree)
		if (x) {
			return false;
		}
		else {
			return true;
		}
	else {
		if (!x) {
			return false;
		}
		else {
			return true;
		}
	}
}