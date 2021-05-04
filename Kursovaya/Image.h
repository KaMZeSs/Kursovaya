#pragma once
#include "File.h"

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
	virtual void operator ++(int);
};