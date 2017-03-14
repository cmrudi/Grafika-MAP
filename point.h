#ifndef POINT_H
#define POINT_H

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
		double rad_angle = degrees * 3.14 / 180;
		// printf("%f\n",rad_angle);
		//translate to origin
		double dx = this->x - center.x;
		double dy = this->y - center.y;
		// printf("%f %f\n", dx,dy);
		//rotate point
		double new_dx = (dx) * cos(rad_angle) - (dy) * sin(rad_angle);
		double new_dy = (dx) * sin(rad_angle) + (dy) * cos(rad_angle);
		// printf("%f %f\n", dx,dy);

		this->x = (int)round(new_dx) + center.x;
		this->y = (int)round(new_dy) + center.y;
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

#endif // POINT_H
