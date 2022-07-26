#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <time.h>
const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green   = TGAColor(0, 255,   0,   255);

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

void triangle(Vec2i *v, const int width, const int height,TGAImage &image, TGAColor color)
{
	/*
	int x0 = (v[0].x + 1.) * width / 2.;
	int y0 = (v[0].y + 1.) * height / 2.;
	int x1 = (v[1].x + 1.) * width / 2.;
	int y1 = (v[1].y + 1.) * height / 2.;
	int x2 = (v[2].x + 1.) * width / 2.;
	int y2 = (v[2].y + 1.) * height / 2.;
	*/
	//line_6(x0,y0,x1,y1,image,color);
	//line_6(x1,y1,x2,y2,image,color);
	//line_6(x2,y2,x0,y0,image,color);
	line_6(v[0].x,v[0].y,v[1].x,v[1].y,image,color);
	line_6(v[1].x,v[1].y,v[2].x,v[2].y,image,color);
	line_6(v[2].x,v[2].y,v[0].x,v[0].y,image,color);

}
#if 0
int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	//image.set(52, 41, red);
	clock_t start, finish;
	start = clock();
	//line_4(10, 20, 100, 100, image, red);
	line_6(13, 20, 80, 40, image, white); 
	line_6(20, 13, 40, 80, image, red); 
	line_6(80, 40, 13, 20, image, red);
	finish = clock();
	double duration = (double)(finish - start) / 1000;
	std::cout << "draw time: " << duration << "ms"<< std::endl;
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}
#endif
#if 0
int main(int argc, char** argv) {
    /*if (2==argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("obj/african_head.obj");
    }*/
	Model *model = NULL;
	model = new Model("obj/african_head.obj");
	const int width  = 800;
	const int height = 800;

    TGAImage image(width, height, TGAImage::RGB);
    // 循环模型里的所有三角形
	for (int i = 0; i < model->nfaces(); i++) {
	std::vector<int> face = model->face(i);

		// 循环三角形三个顶点，每两个顶点连一条线
		for (int j = 0; j < 3; j++) {
			Vec3f v0 = model->vert(face[j]);
			Vec3f v1 = model->vert(face[(j + 1) % 3]);
			
			// 因为模型空间取值范围是 [-1, 1]^3，我们要把模型坐标平移到屏幕坐标中
			// 下面 (point + 1) * width(height) / 2 的操作学名为视口变换（Viewport Transformation）
			int x0 = (v0.x + 1.) * width / 2.;
			int y0 = (v0.y + 1.) * height / 2.;
			int x1 = (v1.x + 1.) * width / 2.;
			int y1 = (v1.y + 1.) * height / 2.;
			
			// 画线
			line_6(x0, y0, x1, y1, image, white);
		}
	}
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}
#endif
int main(int argc, char** argv) {
	const int width  = 200;
	const int height = 200;
	TGAImage image(width, height, TGAImage::RGB);
	Vec2i v[3] = {Vec2i(20, 30), Vec2i(80, 90), Vec2i(40, 120)};
	triangle(v, width, height, image, red);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
	return 0;
}
