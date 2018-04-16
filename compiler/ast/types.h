#ifndef __TYPES__
#define __TYPES__

#include <string>

using namespace std;

class Operator {
	public:
		enum Value {
			UNKNOWN,
			PLUS,
			MINUS,
			TIMES,
			DIVIDE,
			EQUAL,
			NOTEQUAL,
			LESSTHAN,
			LESSTHANEQ,
			GREATERTHAN,
			GREATERTHANEQ,
		};
		Value type;
		Operator(Value t = Operator::UNKNOWN) { type = t; }
		string toString() {
			switch (type) {
				case PLUS			: return "+";
				case MINUS			: return "-";
				case TIMES			: return "*";
				case DIVIDE			: return "/";
				case EQUAL	 		: return "==";
				case NOTEQUAL		: return "!=";
				case LESSTHAN		: return "<";
				case LESSTHANEQ 	: return "<=";
				case GREATERTHAN	: return ">";
				case GREATERTHANEQ	: return ">=";
			}
			return "UNKNOWN";
		}
};

class Scalar {
	public:
		enum Value {
			UNKNOWN,
			BYTE,
			NUMBER,
		};
		Value type;
		Scalar(Value t = Scalar::UNKNOWN) { type = t; }
		string toString() {
			switch (type) {
				case BYTE	: return "byte";
				case NUMBER : return "number";
			}
			return "UNKNOWN";
		}
};

class BaseType {		
	public:
		BaseType() { refs = 0; }
		BaseType(Scalar t, int r = 0) { type = t, refs = r; }
		Scalar type; 
		int refs;
		string toString() {
			return type.toString()+string(refs,'*');
		}
};
#endif