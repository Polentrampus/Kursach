#pragma once
#include "AreaShowText.h"

class InputArea : public AreaShowText
{
public:
	explicit InputArea(const Vector2f& AreaSize = Vector2f(0, 0)) : condition(false), length(0),
		AreaShowText(AreaSize) {
		text.setString('1');
	}
	void setCondition(bool Condition);
	void setLength(unsigned int Length) { length = Length; }
	void setString(const String& string) override;
	void addChar(char ch);
	unsigned int getLength() const { return length; }
	int get_int() const;
	bool getCondition() const { return condition; }


private:
	bool condition;
	unsigned int length;
};

