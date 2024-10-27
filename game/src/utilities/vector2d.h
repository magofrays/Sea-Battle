#include <bits/stdc++.h>
class point2d{
    public:
    int x; int y;

    point2d() : x(0), y(0) {}
    point2d(int x, int y) : x(x), y(y) {}
    point2d(std::pair<int, int> coordinates): x(coordinates.first), y(coordinates.second){}
    point2d(const point2d & point){
        x = point.x;
        y = point.y;
    }
    point2d & operator =(const point2d & point){
        if(this != &point){
            x = point.x;
            y = point.y;
        }
        return *this;}
    point2d & operator =(point2d && point){
        if(this != &point){
            x = std::move(point.x);
            y = std::move(point.y);
        }
        return *this;}

    point2d operator+(point2d v) const { return point2d(x + v.x, y + v.y); }
    point2d operator-(point2d v) const { return point2d(x - v.x, y - v.y); }
    point2d operator/(int det)  const { return point2d(x / det, y / det); }
    point2d operator*(int k)  const { return point2d(x * k, y * k); }
    
    void operator+=(point2d v) { x += v.x; y += v.y; }
    void operator-=(point2d v) { x -= v.x; y -= v.y; }
};

class box2d{
    public:
    point2d min_point;
    point2d max_point;

    box2d() : min_point(), max_point() {}
    box2d(point2d min_point, point2d max_point) : min_point(min_point), max_point(max_point) {}
    box2d(const box2d & box){
        min_point = box.min_point;
        max_point = box.max_point;}
    box2d(box2d && box){
        min_point = std::move(box.min_point);
        max_point = std::move(box.max_point);}
    box2d & operator = (const box2d & box){
        if(this != &box){
            min_point = box.min_point;
            max_point = box.max_point;
        }
        return *this;}
    box2d & operator = (box2d && box){
        if(this != &box){
            min_point = std::move(min_point);
            max_point = std::move(max_point);
        }
        return *this;}


    bool contains(point2d point) const
        {
            return point.x >= min_point.x &&
                   point.y >= min_point.y &&
                   point.x <  max_point.x &&
                   point.y <  max_point.y;
        }
    
    bool contains(box2d box) const
        {
            return box.min_point.x >= min_point.x &&
                   box.min_point.y >= min_point.y &&
                   box.max_point.x <= max_point.x &&
                   box.max_point.y <= max_point.y;
        }

    bool intersects(box2d box) const
        {
            return (box.max_point.x > min_point.x) && (max_point.x > box.min_point.x) &&
                   (box.max_point.y > min_point.y) && (max_point.y > box.min_point.y);
        }

    box2d intersection(box2d box) const //founds area that belongs to both areas
        {
            box2d res = box2d(
                point2d(std::max(min_point.x, box.min_point.x), std::max(min_point.y, box.min_point.y)),
                point2d(std::min(max_point.x, box.max_point.x), std::min(max_point.y, box.max_point.y))
            );

            if (res.max_point.x < res.min_point.x || res.max_point.y < res.min_point.y)
                return box2d();
            return res;
        }
};