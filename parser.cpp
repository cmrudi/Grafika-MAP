// class parser

#include <iostream>
#include <fstream>
#include <sstream>
#include "parser.h"
using namespace std;




vector< vector<Point> > Parser::getPoints () {
	return points;
}

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

void Parser::parseAdi (string filename) {
	const string divider = "==";

	ifstream input_file(filename.c_str());

	Point p;
	string line;
	vector<Point> point_shape;
	int a, count, nPoint;
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
					cout << " masuk sini " << endl;
				} else {
					nPoint--;
					p.setX(a);
					input_file >> a;
					p.setY(a);
					point_shape.push_back(p);

					cout << "x = " << p.getX() << " ";
					cout << "y = " << p.getY() << endl;
					cout << "nPoint = " << nPoint << endl;
					cout << point_shape.size() << endl;
				}
			}
			points.push_back(point_shape);
			point_shape.clear();

		}
	}
	input_file.close();
}


// int main () {
// 	Parser pars;
// 	Point p1, p2;
// 	pars.parseAdi("test2.txt");

// 	vector< vector<Point> > points = pars.getPoints();

// 	cout << points.size() << endl;
// 	cout << points[0].size() << endl;
// 	cout << points[1][2].getX() << endl;
// 	cout << points[1][2].getY() << endl;


// 	return 0;
// }