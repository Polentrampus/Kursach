#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Cell : public sf::RectangleShape
{
public:
	explicit Cell(const Vector2f& CellSize = Vector2f(0, 0)) : condition(true), RectangleShape(CellSize) {}
	void setCellSpecifications(const Vector2f& CellSize, const Color& CellColor, float OutlineThickness,
		const Color& OutlineColor, const Vector2f& CoordsOrigin, float x, float y, bool Condition);
	bool getCondition() const { return condition; }
	void setCondition(bool Condition);
protected:
	bool condition;
};
