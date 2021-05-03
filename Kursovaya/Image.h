#pragma once
#include "File.h"

struct Square
{
	int X, Y, width, height;
};

class Image : public File
{
private:
	int width;
	int height;
public:
	Image();
	~Image();
	int GetWidth();
	int GetHeight();
	virtual vector<string> Read();
	void SetDimensions();
	Image operator << (Square*);
	virtual void operator --(int) {};
};