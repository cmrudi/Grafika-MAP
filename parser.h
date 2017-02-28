// class parser
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "line.h"

using namespace std;


class Parser {
public :
	void parse (string filename){
		const string divider = "==";

		ifstream input_file(filename.c_str());

		Point p;
		string line;
		vector<Point> point_shape;
		string c;
		int a, count;
		count = 1;

		points.clear();

		if (input_file.is_open()) {
			while ( input_file.good() ) {
				while (input_file >> c) {
					if (!c.compare(divider)) {
						points.push_back(point_shape);
						point_shape.clear();
					} else {
						stringstream(c) >> a;
						if (count == 1) {
							p.setX(a);
							count = 2;
						} else {
							p.setY(a);
							count = 1;
							point_shape.push_back(p);
						}
					}
				}
			}
		}
		input_file.close();
	}
	void parseAdi (string filename){
		ifstream input_file(filename.c_str());

		Point p;
		string line;
		vector<Point> point_shape;
		int a, nPoint;
		nPoint = 0;

		points.clear();

		if (input_file.is_open()) {
			input_file >> nPoint;
			while ( input_file.good() ) {
				while (input_file >> a) {
					if (nPoint == 0) {
						nPoint = a;
						points.push_back(point_shape);
						point_shape.clear();
					} else {
						nPoint--;
						p.setX(a);
						input_file >> a;
						p.setY(a);
						point_shape.push_back(p);
					}
				}
				points.push_back(point_shape);
				point_shape.clear();

			}
		}
		input_file.close();
	}
	void parseTree (string filename){
		ifstream input_file(filename.c_str());

		Point p;
		int a;

		if (input_file.is_open()) {
			while ( input_file.good() ) {
				while (input_file >> a) {
					p.setX(a);
					input_file >> a;
					p.setY(a);
					trees.push_back(p);
				}
			}
		}
		input_file.close();
	}
	vector< vector<Point> > getPoints (){
		return points;
	}
	vector<Point> getTrees (){
		return trees;
	}


private :
	vector< vector<Point> > points;
	vector<Point> trees;
};

#endif