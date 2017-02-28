// class parser

#include <iostream>
#include <fstream>
#include <sstream>
#include "parser.h"
using namespace std;



void Parser::parse (string filename) {
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
					cout << "masuk sini" << endl;
					cout << points.size() << endl;
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

vector< vector<Point> > Parser::getPoints () {
	return points;
}


// int main () {
// 	Parser pars;
// 	Point p1, p2;
// 	pars.parse("test.txt");

// 	vector< vector<Point> > points = pars.getPoints();

// 	cout << points.size() << endl;
// 	cout << points[0][1].getX() << endl;
// 	cout << points[0][1].getY() << endl;


// 	return 0;
// }