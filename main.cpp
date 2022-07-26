#include "tgaimage.h"
#include <iostream>
#include <time.h>
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line_final(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color) { 
#if 0
    int dx = x2-x1; 
    int dy = y2-y1;
    bool steep = false; 
    if (std::abs(x1-x2)<std::abs(y1-y2)) { 
        std::swap(x1, y1); 
        std::swap(x2, y2); 
        steep = true; 
    } 
    if (x1>x2) { 
        std::swap(x1, x2); 
        std::swap(y1, y2); 
    } 
	int eps = 0; 
 
    int deps = std::abs(dy)*2; 
    
    int y = y1; 
    for (int x=x1; x<=x2; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        eps += deps; 
        if (eps > dx) { 
            y += (y2>y1?1:-1); 
            eps -= dx*2; 
        } 
    } 
#else
    bool steep = false; 
    if (std::abs(x1-x2)<std::abs(y1-y2)) { 
        std::swap(x1, y1); 
        std::swap(x2, y2); 
        steep = true; 
    } 
    if (x1>x2) { 
        std::swap(x1, x2); 
        std::swap(y1, y2); 
    } 
    int dx = x2-x1; 
    int dy = y2-y1; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y1; 
    for (int x=x1; x<=x2; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y2>y1?1:-1); 
            error2 -= dx*2; 
        } 
    } 
#endif
} 

void line(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color) { 
    bool steep = false; 
    if (std::abs(x1-x2)<std::abs(y1-y2)) { // if the line is steep, we transpose the image 
        std::swap(x1, y1); 
        std::swap(x2, y2); 
        steep = true; 
    } 
    if (x1>x2) { // make it left−to−right 
        std::swap(x1, x2); 
        std::swap(y1, y2); 
    } 
    for (int x=x1; x<=x2; x++) { 
        float t = (x-x1)/(float)(x2-x1); 
        int y = y1*(1.-t) + y2*t; 
        if (steep) { 
            image.set(y, x, color); // if transposed, de−transpose 
        } else { 
            image.set(x, y, color); 
        } 
    } 
}
void line1(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    for (int x=x0; x<=x1; x++) { 
        float t = (x-x0)/(float)(x1-x0); 
        int y = y0*(1.-t) + y1*t; 
        image.set(x, y, color); 
    } 
}





void line_1(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color)
{
	float dl = 0.01;
	int x, y;
	int dx = x2 - x1;
	int dy = y2 - y1;
	for(float t = 0; t < 1.0; t+=dl)
	{
		x = t*dx + x1;
		y = t*dy + y1;
		image.set(x, y, color);
	}
	
}

//error
void line_2(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color)
{
	//float dl = 0.01;
	int x, y;
	y = y1;
	for(x = x1; x <= x2; x++)
	{
		image.set(x, y, color);
		//float t = (y2 - y1) / (float)(x2 - x1);
		y = y + (y2 - y1) / (x2 - x1);
	}
}
void line_3(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color)
{
	//float dl = 0.01;
	int x, y;
	int dx = x2 - x1;
	int dy = y2 - y1;
	float step;
	float dlx, dly;
	if(std::abs(dx) >= std::abs(dy)) {
		step = std::abs(dx);
	} else {
		step = std::abs(dy);
	}

	dlx = dx / step;
	dly = dy / step;

	x = x1;
	y = y1;
	for(int i = 0; i < step; i++)
	{
		image.set(x, y, color);
		x = x + dlx;
		y = y + dly;
	}
}

void line_4(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color)
{
	int x, y;
	int dx = x2 - x1;
	int dy = y2 - y1;
	int enps = 0;
	y = y1;
	bool steep = false;
	if(std::abs(dx) < std::abs(dy)) {
		std::swap(x1, y1);
		std::swap(x2, y2);
		steep = true;
	}
	if(x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	dx = x2 - x1;
	dy = y2 - y1;
	for(x = x1; x <= x2; x++)
	{
		if(steep == false) {
			image.set(x, y, color);
		} else {
			image.set(y, x, color);
		}
		enps += dy;
		if((enps * 2) > dx)
		{
			y++;
			enps -= dx;
		}
	}
}

void line_5(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color)
{
	int x, y;
	int dx = x2 - x1;
	int dy = y2 - y1;
	bool steep = false;
	if(std::abs(dx) < std::abs(dy)) {
		std::swap(x1, y1);
		std::swap(x2, y2);
		steep = true;
	}
	if(x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	for(x = x1; x <= x2; x++)
	{
		float t = (x - x1) / (float)(x2 - x1);		//	!(x2 - x1)
		y = (y2 - y1) * t + y1;
		//y = y1 * (1.0 - t) + y2 * t;
		if (steep) { 
            image.set(y, x, color); // if transposed, de−transpose 
        } else { 
            image.set(x, y, color); 
        } 
	}
}

void line_6(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color)
{
	int x, y;
	bool steep = false;
	if(std::abs(x2 - x1) < std::abs(y2 - y1)) {
	//if (std::abs(x1-x2)<std::abs(y1-y2)) { 
		std::swap(x1, y1);
		std::swap(x2, y2);
		steep = true;
	}
	if(x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	int dx = x2 - x1;
	int dy = y2 - y1;
	int eps = 0;
	int deps = std::abs(dy) * 2;
	y = y1;
	for(x = x1; x <= x2; x++)
	{
		//float t = (x - x1) / (float)(x2 - x1);		//	!(x2 - x1)
		//y = (y2 - y1) * t + y1;
		//y = y1 * (1.0 - t) + y2 * t;
		if (steep) { 
            image.set(y, x, color); // if transposed, de−transpose 
        } else { 
            image.set(x, y, color); 
        }
		eps += deps;
		// 这里用位运算 <<1 代替 *2
		if(eps > dx)  {
			y += (y2>y1?1:-1);
			eps -= dx * 2;
		} 
	}
}


int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	//image.set(52, 41, red);
	clock_t start, finish;
	start = clock();
	//line_4(10, 20, 100, 100, image, red);
	line_4(13, 20, 80, 40, image, white); 
	line_4(20, 13, 40, 80, image, red); 
	line_4(80, 40, 13, 20, image, red);
	finish = clock();
	double duration = (double)(finish - start) / 1000;
	std::cout << "draw time: " << duration << "ms"<< std::endl;
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

