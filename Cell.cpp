#include "Cell.h"

void Cell::setCellSpecifications(const Vector2f& CellSize, const Color& CellColor, float OutlineThickness,
	const Color& OutlineColor, const Vector2f& CoordsOrigin, float x, float y, bool Condition)
{
	setSize(CellSize);
	setFillColor(CellColor);
	setOutlineThickness(OutlineThickness);
	setOutlineColor(OutlineColor);
	setOrigin(CoordsOrigin);
	setPosition(x, y);
	condition = Condition;
}

void Cell::setCondition(bool Condition)
{
	condition = Condition;
	if (condition)
		setFillColor(Color(136, 232, 18, 400)); // Зеленый
	else
		setFillColor(Color(255, 36, 4, 400)); // Красный
}
