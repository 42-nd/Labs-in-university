#include "closest_pair.h"
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <iostream>

using namespace std;

double dist(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

std::pair<Point, Point> closest_pair_full_search(const std::vector<Point> &points) {

	double min_distance = 100000000.0;//there may be errors with insufficient value at the beginning!!!
	auto result = std::make_pair(Point(), Point());
	for (size_t i = 0; i < points.size(); ++i) {
		for (size_t j = i + 1; j < points.size(); ++j) {
            double distance = dist(points[i], points[j]);

			if (distance < min_distance) {
				min_distance = distance;
				result = make_pair(points[i], points[j]);
			}
		}
	}
	
	return result;
}

std::pair<Point, Point> closest_pair_between(std::vector<Point>& PLeft, std::vector<Point>& PRight, double d) {
    std::vector<Point> PStripe;
    double Xm = (PLeft.back().x + PRight.front().x) / 2.0;

    for (const Point& p : PRight) {
        if (abs(p.x - Xm) <= d) {
            PStripe.push_back(p);
        }
    }

    for (const Point& p : PLeft) {
        if (abs(p.x - Xm) < d) {
            PStripe.push_back(p);
        }
    }
    std::sort(PStripe.begin(), PStripe.end(), []( Point& a,  Point& b) {
        return a.y < b.y;
        });
    
    
    std::pair<Point, Point> closest_pair;

    closest_pair = closest_pair_full_search(PStripe);
    //for (size_t i = 0; i < PStripe.size(); ++i) {
    //    for (size_t j = i + 1; j < PStripe.size() && (PStripe[j].y - PStripe[i].y) < min_distance; ++j) {
    //        double distance = dist(PStripe[i], PStripe[j]);
    //        if (distance < min_distance) {
    //            min_distance = distance;
    //            closest_pair = std::make_pair(PStripe[i], PStripe[j]);
    //        }
    //    }
    //}
    return closest_pair;
}

std::pair<Point, Point> closest_pair(const std::vector<Point>& points) {
    if (points.size() < 2) {
        throw invalid_argument("Not enough points");
    }

    if (points.size() <= 3) {
        return closest_pair_full_search(points);
    }


    std::vector<Point> sorted_points = points;
    std::sort(sorted_points.begin(), sorted_points.end(), [](const Point& a, const Point& b) {
        return a.x < b.x;
        });


    
    size_t middle = points.size() / 2;
    std::vector<Point> PLeft(sorted_points.begin(), sorted_points.begin() + middle);
    std::vector<Point> PRight(sorted_points.begin() + middle, sorted_points.end());

    
    std::pair<Point, Point> pl = closest_pair(PLeft);
    std::pair<Point, Point> pr = closest_pair(PRight);

    
    double d = std::min(dist(pl.first, pl.second), dist(pr.first, pr.second));

    std::pair<Point, Point> pb = closest_pair_between(PLeft, PRight, d);
    
    if (dist(pl.first, pl.second) <= dist(pr.first, pr.second) && dist(pl.first, pl.second) <= dist(pb.first, pb.second)) {
        return pl;
    }
    else if (dist(pr.first, pr.second) <= dist(pl.first, pl.second) && dist(pr.first, pr.second) <= dist(pb.first, pb.second)) {
        return pr;
    }
    else {
        return pb;
    }
}
    

