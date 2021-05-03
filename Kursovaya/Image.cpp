#pragma once
#include "Image.h"

Image::Image()
{
	width = 0;
	height = 0;
}

Image::~Image()
{

}

void Image::SetDimensions()
{
	height = Content.size();
	for (int i = 0; i < height; i++)
	{
		int temp = Content[i].length();
		if (width > temp)
		{
			width = temp;
		}
		temp = 0;
	}
}

int Image::GetWidth()
{
	return width;
}

int Image::GetHeight()
{
	return height;
}

vector<string> Image::Read()
{
	vector<string> v;
	char k = 95, l = 124;
	int maxlength = 0;
	for (int i = 0, max = this->Content.size(); i < max; i++)
	{
		string str = this->Content[i];
		str.insert(0, "|");
		v.push_back(str);
		int temp = str.length();
		temp > maxlength ? maxlength = temp : temp = 0;
	}
	for (int i = 0; i < v.size(); i++)
	{
		v[i].resize(maxlength, 32);
		v[i].push_back(124);
	}
	string str;
	str.resize(maxlength + 2, 95);
	v.insert(v.begin(), str);
	v.push_back(str);
	return v;
}