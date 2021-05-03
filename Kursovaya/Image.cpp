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

bool Image::SetDimensions()
{
	int w = 0, h = 0;
	string Path;
	ifstream Doc(Path);
	string str;
	if (!Doc.is_open()) return false;
	while (!Doc.eof())
	{
		getline(Doc, str);
		int temp = str.length();
		if (temp > w) w = temp;
		h++;
	}
	return true;
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