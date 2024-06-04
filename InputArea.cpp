#include "InputArea.h"

void InputArea::setCondition(bool Condition)
{
	condition = Condition;
	if (condition)
		area.setFillColor(Color(255, 255, 0)); // желтый
	else
		area.setFillColor(Color(255, 225, 0)); // черножопый
}

void InputArea::setString(const String& string)
{
	if (string.getSize() < length + 1 && string[0] > '0' && string[0] < 58)
	{
		for (int i = 1; i < string.getSize(); i++)
		{
			if (!(string[i] > 47 && string[i] < 58))
			{
				std::cout << "невероятная херь!!!" << '\n';
				return;
			}
		}
		text.setString(string);
		text.setCharacterSize(area.getSize().y);
		text.setOrigin(Vector2f((text.getLocalBounds().width) / 2,
			(text.getLocalBounds().height / 1.1)));
		text.setPosition(area.getPosition());
	}
	else std::cout << "input data error!!!" << '\n';
}

void InputArea::addChar(char ch)
{
	str = text.getString();
	if (ch == '0' && str.size() == 0)
		return;
	if (str.size() == 1 && str.data()[0] != 1)
		return;
	if (str.size() < length && ch != 8)
	{
		str += ch;
		text.setString(str);
	}
	else if (str.size() > 0 && ch == 8)
	{
		str.pop_back();
		text.setString(str);
	}
	text.setOrigin(Vector2f((text.getLocalBounds().width) / 2,
		(text.getLocalBounds().height / 1.5)));
	text.setPosition(area.getPosition());
}

int InputArea::get_int() const
{
	if (text.getString().getSize() > 0) return std::stoi((std::string)text.getString());
	return 1;
}
