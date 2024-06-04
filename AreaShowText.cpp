#include "AreaShowText.h"

AreaShowText::AreaShowText(const Vector2f& AreaSize)
{
	area.setSize(AreaSize);
	area.setOrigin(AreaSize.x / 2, AreaSize.y / 2);
}

void AreaShowText::setPosition(float x, float y)
{
	area.setPosition(x, y);
	text.setPosition(x,y);

}

void AreaShowText::setString(const String& string)
{
	text.setPosition(area.getPosition());
	text.setString(string);
	text.setCharacterSize((unsigned int)area.getSize().y * 0.8);
	text.setOrigin(Vector2f((text.getLocalBounds().width) / 2,
		(text.getLocalBounds().height *1.5)));
}

void AreaShowText::draw(sf::RenderWindow& window)
{
	window.draw(area);
	window.draw(text);
};

void AreaShowText::setCellSpecifications(const Vector2f& CellSize, const Color& CellColor, const Vector2f& origin, float OutlineThickness,
	const Color& OutlineColor, float x, float y, bool Condition)
{
	area.setSize(CellSize);
	area.setFillColor(CellColor);
	area.setOrigin(origin);
	setOutlineThickness(OutlineThickness);
	setOutlineColor(OutlineColor);
	setPosition(x, y);
	condition = Condition;
}

void AreaShowText::setCondition(bool Condition)
{
	condition = Condition;
	if (condition)
		area.setFillColor(Color(136, 232, 18, 400)); // Зеленый
	else
		area.setFillColor(Color(255, 36, 4, 400)); // Красный
}
