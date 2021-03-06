/*
* INF 110 - Trabalho prático 03
* Author: Lenilson Nascimento, Raphael Carmo
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>

#include <pnme/defs.h>

namespace filters
{
	int sobelY[3][3] =
	{
		{ -1, -2, -1 },
		{  0,  0,  0 },
		{  1,  2,  1 }
	};

	int sobelX[3][3] =
	{
		{ -1, 0, 1 },
		{ -2, 0, 2 },
		{ -1, 0, 1 }
	};

	int focus[3][3] =
	{
		{  0, -1,  0 },
		{ -1,  5, -1 },
		{  0, -1,  0 }
	};

	int gaussian[3][3] =
	{
		{ 1, 2, 1, },
		{ 2, 4, 2, },
		{ 1, 2, 1, }
	};

	int laplace[3][3] =
	{
		{  0, -1,  0 },
		{ -1,  4, -1 },
		{  0, -1,  0 }
	};

	int box[3][3] =
	{
		{ 1, 1, 1 },
		{ 1, 1, 1 },
		{ 1, 1, 1 }
	};
}

void lighten(
	unsigned char *pixels,
	int width,
	int height,
	int mod
)
{
	for(int y = 0; y < height * width; y ++)
	{
		pixels[y] = CLAMP(pixels[y] + mod, 0, 255);
	}
}

void greyscale(
	unsigned char *r,
	unsigned char *g,
	unsigned char *b,
	int width,
	int height
)
{
	for(int n = 0; n < width * height; n ++)
	{
		r[n] = g[n] = b[n] = (r[n] * 0.2126f + 0.7152 * g[n] + 0.0722 * b[n]);
	}
}

void mirror(
	unsigned char *pixels,
	int width,
	int height
)
{
	for(int y = 0; y < height; y ++)
	{
		for(int x = 0; x < width / 2; x ++)
		{
			std::swap(pixels[y * width + x], pixels[y * width + width - x - 1]);
		}
	}
}

void negative(
	unsigned char *pixels,
	int width,
	int height
)
{
	for(int x = 0; x < width; x ++)
	{
		for(int y = 0; y < height; y ++)
		{
			pixels[y * width + x] = (255 - pixels[y * width + x]);
		}
	}
}

int filterLine(
	unsigned char *line,
	int x,
	int width,
	int f[3]
)
{
	int j = line[x] * f[1];

	if(x >= 1)
	{
		j += line[x - 1] * f[0];
	}

	if(x < width - 1)
	{
		j += line[x + 1] * f[2];
	}

	return j;
}

int convolve(
	unsigned char *in,
	int x,
	int y,
	int width,
	int height,
	int f[3][3]
)
{
	int j = filterLine(in + y * width, x, width, f[1]);

	if(y >= 1)
	{
		j += filterLine(in + (y - 1) * width, x, width, f[0]);
	}

	if(y < height - 1)
	{
		j += filterLine(in + (y + 1) * width, x, width, f[2]);
	}

	return j;
}

void sobel(
	unsigned char *in,
	int width,
	int height
)
{
	unsigned char *out = new unsigned char[width * height];

	for(int y = 0; y < height; y ++)
	{
		for(int x = 0; x < width; x ++)
		{
			int convX = 1.f / 8 * convolve(in, x, y, width, height, filters::sobelX);
			int convY = 1.f / 8 * convolve(in, x, y, width, height, filters::sobelY);

			out[y * width + x] = (int) CLAMP(sqrt(convX * convX + convY * convY), 0, 255);
		}
	}

	std::memcpy(in, out, width * height);
	delete[] out;
}

void pixelate(
	unsigned char *in,
	int width,
	int height,
	int radius
)
{
	if(radius < 1)
	{
		return;
	}

	unsigned char *out = new unsigned char[width * height];

	for(int y = 0; y < height - 1; )
	{
		for(int x = 0; x < width - 1; )
		{
			for(int z = y; z < std::min(height, y + radius); z ++)
			{
				for(int w = x; w < std::min(width, x + radius); w ++)
				{
					out[z * width + w] = CLAMP(
							convolve(
								in, x + 1, y + 1, width, height, filters::box
							) / 8.f,
						0, 255);
				}
			}

			x += radius;
		}

		y += radius;
	}

	std::memcpy(in, out, width * height);
	delete[] out;
}

void filter(
	unsigned char *in,
	int width,
	int height,
	int f[3][3],
	float norm
)
{
	unsigned char *out = new unsigned char[width * height];

	for(int y = 0; y < height; y ++)
	{
		for(int x = 0; x < width; x ++)
		{
			int conv = convolve(in, x, y, width, height, f);
			out[y * width + x] = (unsigned char) CLAMP(conv * norm, 0, 255);
		}
	}

	std::memcpy(in, out, width * height);
	delete[] out;
}
