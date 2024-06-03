#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class AreaShowText
{
public:
	explicit AreaShowText(const Vector2f& AreaSize = Vector2f(0, 0));
	void setPosition(float x, float y);
	void setOrigin(const Vector2f& origin) { area.setOrigin(origin); }//������ ����� ����� �������� ������� ����������� ������.
	void setAreaColor(const Color& color) { area.setFillColor(color); }//������������� ���� ������� ������� ����������� ������.
	void setOutlineThickness(float thickness) { area.setOutlineThickness(thickness); }//������������� ������� ������� (�������) � ������� ����������� ������.
	void setOutlineColor(const Color& color) { area.setOutlineColor(color); }//������ ���� ������� (�������) ������� ����������� ������.
	void setFont(const Font& font) { text.setFont(font); }//������������� ����� ������ ��� �����������.
	virtual void setString(const String& string);
	void setTextColor(const Color& color) { text.setFillColor(color); }
	void setCellSpecifications(const Vector2f& CellSize, const Color& CellColor, const Vector2f& origin, float OutlineThickness,
		const Color& OutlineColor, float x, float y, bool Condition);
	void setCondition(bool Condition);
	bool getCondition() const { return condition; }
	const String& getString() const { return text.getString(); }//���������� ������ ������, ������� ����� ������������
	const Vector2f& getPosition() const { return area.getPosition(); }//���������� ������� ������� ����������� ������.
	bool MousePressedArea(float x, float y) { return area.getGlobalBounds().contains(x, y); }//���������, ���� �� ������� ����������� ������ ������ � ��������� ����������� x � y. ���������� true, ���� ������� ���� ������.
	void draw(sf::RenderWindow& window);
protected:
	std::string str;
	RectangleShape area;
	Text text;
	bool condition;
};

