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
#include <iostream>
#include "framepanel.h"

using namespace std;


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

	    //  setXSize(vinfo.xres_virtual-10);
	    //  setYSize(vinfo.yres_virtual-10);
	     setXSize(1300);
	     setYSize(700);
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

#endif
