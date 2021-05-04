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
		if (width < temp)
		{
			width = temp;
		}
		temp = 0;
	}
}

void Image::operator--(int)
{
	if (Content.empty() || ( (Content.front() == Content.back()) && Content.back().size() == 0 )) 
		return;

	int max = 0;
	for (int i = 0; i < Content.size(); i++)
		if (Content[i].length() > max) max = Content[i].length();

	vector<int> v;
	for (int i = 0; i < Content.size(); i++)
		if (max == Content[i].length()) v.push_back(i);

	for (int i = 0; i < v.size(); i++)
	{
		Content.erase(Content.begin() + v[i]);
		for (int j = 0; j < v.size(); j++)
			v[j] -= 1;
	}
	Content.pop_back();
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
	str.resize(maxlength + 1, 45);
	v.insert(v.begin(), str);
	v.push_back(str);
	return v;
}