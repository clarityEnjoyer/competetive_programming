#ifndef GEO_H
#define GEO_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

using ll = long long;

struct Point {
  ll x, y;

  Point(ll x = 0, ll y = 0) : x(x), y(y) {}

  Point operator-(const Point& other) const {
    return Point(x - other.x, y - other.y);
  }

  ll Cross(const Point& other) const {
    return x * other.y - y * other.x;
  }

  bool operator<(const Point& other) const {
    return x == other.x ? y < other.y : x < other.x;
  }

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

// I/O Operators for speed debugging
istream& operator>>(istream& is, Point& p) {
  return is >> p.x >> p.y;
}
ostream& operator<<(ostream& os, const Point& p) {
  return os << "(" << p.x << " " << p.y << ")";
}

// > 0: Left turn (CCW), < 0: Right turn (CW), 0: Collinear
ll Orient(const Point& a, const Point& b, const Point& c) {
  return (b - a).Cross(c - a);
}

int Sgn(ll x) {
  return (x > 0) - (x < 0);
}

// 1D check for bounding box intersection
bool OnSegment1D(ll a, ll b, ll c, ll d) {
  if (a > b) swap(a, b);
  if (c > d) swap(c, d);
  return max(a, c) <= min(b, d);
}

// Segment Intersection Check
bool Intersect(Point a, Point b, Point c, Point d) {
  ll s1 = Orient(a, b, c);
  ll s2 = Orient(a, b, d);
  if (s1 == 0 && s2 == 0) {
    return OnSegment1D(a.x, b.x, c.x, d.x) && OnSegment1D(a.y, b.y, c.y, d.y);
  }
  ll s3 = Orient(c, d, a);
  ll s4 = Orient(c, d, b);
  return Sgn(s1) * Sgn(s2) <= 0 && Sgn(s3) * Sgn(s4) <= 0;
}

// Monotone Chain Algorithm
// Returns Convex Hull in CCW order.
// "phase" loop obsługująca górną i dolną otoczkę w jednym kodzie.
vector<Point> ConvexHull(vector<Point> pts) {
  sort(pts.begin(), pts.end());
  // Usuwamy duplikaty, by algorytm był stabilny przy nakładających się punktach
  pts.erase(unique(pts.begin(), pts.end()), pts.end());

  vector<Point> hull;
  hull.reserve(pts.size());

  for (int phase = 0; phase < 2; ++phase) {
    auto start = hull.size();
    for (const auto& p : pts) {
      while (hull.size() >= start + 2 && 
             Orient(hull[hull.size() - 2], hull.back(), p) <= 0) {
        hull.pop_back();
      }
      hull.push_back(p);
    }
    hull.pop_back(); // Remove the last point (duplicate of start of next phase)
    
    // Trick: Reverse points to build the lower hull in the second pass
    if (phase == 0) reverse(pts.begin(), pts.end());
  }
  
  if (hull.empty() && !pts.empty()) return {pts[0]};
  return hull;
}

// Area using Shoelace formula (returns 2 * Area)
ll PolygonArea2(const vector<Point>& poly) {
  ll area = 0;
  int n = poly.size();
  for (int i = 0; i < n; ++i) {
    area += poly[i].Cross(poly[(i + 1) % n]);
  }
  return abs(area);
}

#endif // GEO_H
