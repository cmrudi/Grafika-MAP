#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <map>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <vector>

class Point
{
public:
	Point() : x(0), y(0){}

	Point(int ax, int ay){
		x = ax;
		y = ay;
	}

	Point(const Point& p){
		(*this).x = p.x;
		(*this).y = p.y;
	}

	Point& operator=(const Point &p){
		x = p.x;
		y = p.y;
		return *this;
	}

	bool operator==(const Point &p){
        if((*this).x == p.x){
            if((*this).y == p.y){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
	}

	bool operator!=(const Point &p){
        if(*this == p){
            return false;
        }else{
            return true;
        }
	}

	int getX(){
		return x;
	}

	int getY(){
		return y;
	}

	void setX(int ax){
		x = ax;
	}

	void setY(int ay){
		y = ay;
	}

	void Move(int dx, int dy){
		(*this).x += dx;
		(*this).y += dy;
	}

	void rotateP(double degrees, const Point& center = Point()){
        double rad = degrees * 3.14/180;
        (*this).x = center.x + ((*this).x-center.x)*cos(rad) - ((*this).y - center.y)*sin(rad);
        (*this).y = center.y + ((*this).x-center.x)*sin(rad) + ((*this).y-center.y)*cos(rad);
	}

	void Scale(float sx, float sy,const Point& center = Point()){
		(*this).x = center.x + floor((float)((*this).x-center.x)*sx);
		(*this).y = center.y + floor((float)((*this).y-center.y)*sy);
	}

	// void ScaleClip(float sx, float sy, int x1, int x2)

	void printPoint(){
		std::cout << x << " " << y << " ";
	}

private:
	int x;
	int y;

};

class Color
{
public:
	Color() : r(0), g(0), b(0), a(0) {}

	Color(char r, char g, char b)
	{
		(*this).r = r;
		(*this).g = g;
		(*this).b = b;
		(*this).a = 0;
    }

	Color(char r, char g, char b, char a)
	{
		(*this).r = r;
		(*this).g = g;
		(*this).b = b;
		(*this).a = a;
	}

	Color(const Color& c){
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
	}

	Color& operator=(const Color& c){
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;

        return *this;
	}

	char getR()
	{
		return r;
	}

	char getB()
	{
		return b;
	}

	char getG()
	{
		return g;
	}

	char getA()
	{
		return a;
	}

	void setR(char c)
	{
		(*this).r = c;
	}

	void setG(char c)
	{
		(*this).g = c;
	}

	void setB(char c)
	{
		(*this).b = c;
	}

	void setA(char c)
	{
		(*this).a = c;
	}

	static const Color WHITE, BLUE, RED, GREEN, BLACK;

private:
	char r;
	char g;
	char b;
	char a;
};


class Frame
{
public:
	virtual void set(Color c, Point& p) = 0;
	virtual void set(char r, char g, char b, Point& p) = 0;
	virtual void set(char r, char g, char b, int x, int y) = 0;
	virtual Color get(Point& p) = 0;
	virtual Color get(int x, int y) = 0;
    virtual int getXSize() = 0;
	virtual int getYSize() = 0;

};

class FramePanel : public Frame
{
public:
    FramePanel(){
        sizex = sizey = 0;
        xmin = ymin = 0;
        EmptyFrame();
    }

    FramePanel(int x, int y){
    	xmin = ymin = 0;
        setXSize(x);
        setYSize(y);
        EmptyFrame();
    }

    FramePanel(int x, int y, int xmin, int ymin){
    	(*this).xmin = xmin;
    	(*this).ymin = ymin;
    	setXSize(x);
    	setYSize(y);
    	EmptyFrame(); 
    }

    FramePanel(FramePanel& _f){
        sizex = _f.sizex;
        sizey = _f.sizey;
        xmin = ymin = 0;
        for(int i = 0; i<_f.sizex;i++){
            for(int j = 0; j<_f.sizey;j++){
                M[i][j] = _f.M[i][j];
            }
        }
    }


    FramePanel& operator= (FramePanel& _f){
        M.clear();
        sizex = _f.sizex;
        sizey = _f.sizey;
        for(int i = 0; i<_f.sizex;i++){
            for(int j = 0; j<_f.sizey;j++){
                M[i][j] = _f.M[i][j];
            }
        }
        return *this;
    }

    void set(Color c, Point& p){
        M[p.getX()][p.getY()] = c;
    }

     void set(Color c, int x, int y){
        M[x][y] = c;
    }

    void set(char r, char g, char b, Point& p){
        M[p.getX()][p.getY()] = Color(r,g,b);
    }

    void set(char r, char g, char b, int x, int y){
        M[x][y] = Color(r,g,b);
    }

    Color get(Point& p){
        return M[p.getX()][p.getY()];
    }

    Color get(int x, int y){
        return M[x][y];
    }

    int getXSize(){
        return sizex;
    }

    int getYSize(){
        return sizey;
    }

    void setXSize(int x){
        sizex = x;
        M.resize(sizex);
    }

    void setYSize(int y){
        sizey = y;
        for(unsigned int i = 0; i<M.size(); i++){
            M[i].resize(sizey);
        }
    }

    int getXMin(){
    	return xmin;
    }

    int getYMin(){
    	return ymin;
    }

    void setXMin(int x){
    	xmin = x;
    }

    void setYMin(int y){
    	ymin = y;
    }

	void EmptyFrame(){
		for(int i = 0; i < sizex; i++){
			for(int j = 0; j<sizey; j++){
				M[i][j] = Color::BLACK;
				if(i == 0 || i == sizex-1 || j == 0 || j == sizey-1){
					M[i][j] = Color::WHITE;
				}
			}
		}
	}



private:
    std::vector<std::vector<Color> > M;
    int sizex, sizey;
    int xmin, ymin;
};


class Framebuffer : public FramePanel
{
public:
	Framebuffer() : FramePanel(){
        if((*this).fbp == NULL){
            init();
        }
	}

	~Framebuffer(){
        munmap(fbp, screensize);
        close(fbfd);
	}

	void init(){
		// Open the file for reading and writing
	     fbfd = open("/dev/fb0", O_RDWR);
	     if (fbfd == -1) {
	         perror("Error: cannot open framebuffer device");
	         exit(1);
	     }
	     printf("The framebuffer device was opened successfully.\n");

	     // Get fixed screen information
	     if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
	         perror("Error reading fixed information");
	         exit(2);
	     }

	     // Get variable screen information
	     if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
	         perror("Error reading variable information");
	         exit(3);
	     }

	     // Figure out the size of the screen in bytes
	     screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

	     setXSize(vinfo.xres_virtual-10);
	     setYSize(vinfo.yres_virtual-10);
	     EmptyFrame();


	     // Map the device to memory
	     fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
	                        fbfd, 0);
	     if ((intptr_t)fbp == -1) {
	         perror("Error: failed to map framebuffer device to memory");
	         exit(4);
	     }
	     printf("The framebuffer device was mapped to memory successfully.\n");
	}

	void setColor(Color c, Point& p){

        setColor(c.getR(), c.getG(), c.getB(), p.getX(), p.getY());
	}

	void setColor(Color c, int x, int y){
        setColor(c.getR(), c.getG(), c.getB(), x,y);
	}

    void setColor(char r, char g, char b, Point& p){
        setColor(r, g, b, p.getX(), p.getY());
    }

    void setColor(char r, char g, char b, int x, int y){
        if(x <= 0 || x >= getXSize() || y <=0 || y >= getYSize()){
            return;
        }

        int location = getLocation(x, y);
		if (vinfo.bits_per_pixel == 32) {
			*(fbp + location + 0) = b;
			*(fbp + location + 1) = g;
			*(fbp + location + 2) = r;
			*(fbp + location + 3) = 0;
		}
		else if (vinfo.bits_per_pixel == 16) {
			unsigned short int t = (r >> 3) << 11 | (g >> 2) << 5 | (b >> 3);
			*((unsigned short int*)(fbp + location)) = t;
		}
		else {
			printf("Unknown bpp format: %d bpp\n", vinfo.bits_per_pixel);
		}
    }


    Color getColor(int x, int y){
        return get(x, y);
    }

    Color getColor(Point& p){
        return get(p);
    }

    void EmptyScreen(){
        for(int i = 0; i< getXSize(); i++){
            for(int j = 0; j< getYSize(); j++){
                setColor(-1,-1,-1,i,j);
            }
        }
    }

    void Draw(){
    	int xsize = getXSize();
    	int ysize = getYSize();
    	for(int i = 0; i< xsize; i++){
    		for(int j = 0; j<ysize; j++){
    			setColor(get(i, j), i, j);
    		}
    	}
    }
    void drawFrame(FramePanel& f){
    	int xsize = f.getXSize();
    	int ysize = f.getYSize();
    	int xmin = f.getXMin();
    	int ymin = f.getYMin();
		for(int i = 0; i < xsize;i++){
			for(int j = 0; j<ysize; j++){
				set(f.get(i, j), i+xmin, j+ymin);
			}
		}  
    }

    


private:

    int getLocation(int x, int y) {
		return (x + vinfo.xoffset) * (vinfo.bits_per_pixel / 8)
				+ (y + vinfo.yoffset) * finfo.line_length;
	}

	int fbfd;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	char *fbp;
	long int screensize;
};

const Color Color::RED = Color(255,0,0);
const Color Color::WHITE = Color(255,255,255);
const Color Color::BLACK = Color();
const Color Color::GREEN = Color(0,255,0);
const Color Color::BLUE = Color(0,0,255);

#endif
/*reference to https://github.com/azaky/grafika/*/
