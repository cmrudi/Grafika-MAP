#ifndef COLOR_H
#define COLOR_H

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

	bool operator==(const Color &c){
        return (this->r == c.r && this->g == c.g && this->b == c.b);
	}

	bool operator!=(const Color &c){
        return !operator==(c);
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

const Color Color::RED = Color(255,0,0);
const Color Color::WHITE = Color(255,255,255);
const Color Color::BLACK = Color();
const Color Color::GREEN = Color(0,255,0);
const Color Color::BLUE = Color(0,0,255);

#endif // COLOR_H
