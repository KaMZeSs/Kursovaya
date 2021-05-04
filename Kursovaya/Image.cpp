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

void Image::operator++(int)
{
	if (Content.size() >= 2)
	{
		int max = 0;
		for (int i = 0; i < Content.size(); i++)
		{
			if (Content[i].size() > max) max = Content[i].size();
		}
		for (int i = 1; i < Content.size() - 1; i++)
		{
			Content[i].erase(Content[i].begin());
			Content[i].erase(Content[i].end());
			Content[i].insert(Content[i].begin(), 149);
			Content[i].insert(Content[i].end(), 149);
		}
		Content.front().clear();
		Content.front().resize(max + 1, 149);
		Content.back().clear();
		Content.back().resize(max + 1, 149);
	}
	else
	{
		int len = Content.back().size();
		Content.back().clear();
		Content.back().resize(len, 149);
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