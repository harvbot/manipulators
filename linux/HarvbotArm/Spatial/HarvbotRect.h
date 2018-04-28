#pragma once
struct HarvbotRect
{
	HarvbotRect() {};
	HarvbotRect(int _x, int _y, int _width, int _height) {
		x = _x;
		y = _y;
		width = _width;
		height = _height;
	};

	int x;
	int y;
	int width;
	int height;

	bool isEmpty()
	{
		return width == 0 && height == 0;
	}

	void empty()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}
};

