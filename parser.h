// class parser
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include "line.h"
#include "framebuffer.h"
using namespace std;


class Parser {
public :
	void parse (string filename);
	void parseAdi (string filename);
	void parseTree (string filename);
	vector< vector<Point> > getPoints ();
	vector<Point> getTrees ();


private :
	vector< vector<Point> > points;
	vector<Point> trees;
};

#endif