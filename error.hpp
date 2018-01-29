#ifndef __ERROR_H__
#define __ERROR_H__

class Error {

public:
	enum Value {
		IllegalCharacter    = -1,
		UnterminatedComment = -2,
		UnterminatedString  = -3,
		FloatWithoutExpon	= -4,
	};
};

#endif
