#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class AreaShowText
{
public:
	explicit AreaShowText(const Vector2f& AreaSize = Vector2f(0, 0));
	void setPosition(float x, float y);
	void setOrigin(const Vector2f& origin) { area.setOrigin(origin); }//задает центр точки привязки области отображения текста.
	void setAreaColor(const Color& color) { area.setFillColor(color); }//Устанавливает цвет заливки области отображения текста.
	void setOutlineThickness(float thickness) { area.setOutlineThickness(thickness); }//Устанавливает толщину контура (обводки) у области отображения текста.
	void setOutlineColor(const Color& color) { area.setOutlineColor(color); }//Задает цвет контура (обводки) области отображения текста.
	void setFont(const Font& font) { text.setFont(font); }//Устанавливает шрифт текста для отображения.
	virtual void setString(const String& string);
	void setTextColor(const Color& color) { text.setFillColor(color); }
	void setCellSpecifications(const Vector2f& CellSize, const Color& CellColor, const Vector2f& origin, float OutlineThickness,
		const Color& OutlineColor, float x, float y, bool Condition);
	void setCondition(bool Condition);
	bool getCondition() const { return condition; }
	const String& getString() const { return text.getString(); }//Возвращает строку текста, которая будет отображаться
	const Vector2f& getPosition() const { return area.getPosition(); }//Возвращает позицию области отображения текста.
	bool MousePressedArea(float x, float y) { return area.getGlobalBounds().contains(x, y); }//Проверяет, была ли область отображения текста нажата в указанных координатах x и y. Возвращает true, если область была нажата.
	void draw(sf::RenderWindow& window);
protected:
	std::string str;
	RectangleShape area;
	Text text;
	bool condition;
};

