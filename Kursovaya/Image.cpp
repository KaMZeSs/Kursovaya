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
	int w = 0, h = 0;
	string Path;
	ifstream Doc(Path);
	string str;
	if (!Doc.is_open())
	{
		cout << "Файл не открыт" << endl;
		system("pause");
		exit(-1);
	}
	while (!Doc.eof())
	{
		getline(Doc, str);
		int temp = str.length();
		if (temp > w) w = temp;
		h++;
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
		int temp = v[i].length();
		temp > maxlength ? maxlength = temp : temp = 0;
	}
	string str;
	str.resize(maxlength + 2, 95);
	v.insert(v.begin(), str);
	v.push_back(str);
	return v;
}