#ifndef SEABATTLE_VECTOR2D_H
#define SEABATTLE_VECTOR2D_H

#include <nlohmann/json.hpp>
#include <algorithm>
using json = nlohmann::json;

class point2d
{
public:
    int x;
    int y;

    point2d() : x(0), y(0) {}
    point2d(int x, int y) : x(x), y(y) {}
    point2d(std::pair<int, int> coordinates) : x(coordinates.first), y(coordinates.second) {}
    point2d(const point2d &point)
    {
        x = point.x;
        y = point.y;
    }
    point2d(const json &data)
    {
        x = data.at("x");
        y = data.at("y");
    }

    point2d &operator=(const point2d &point)
    {
        if (this != &point)
        {
            x = point.x;
            y = point.y;
        }
        return *this;
    }
    point2d &operator=(point2d &&point)
    {
        if (this != &point)
        {
            x = std::move(point.x);
            y = std::move(point.y);
        }
        return *this;
    }

    point2d operator+(point2d v) const { return point2d(x + v.x, y + v.y); }
    point2d operator-(point2d v) const { return point2d(x - v.x, y - v.y); }
    point2d operator/(int det) const { return point2d(x / det, y / det); }
    point2d operator*(int k) const { return point2d(x * k, y * k); }

    void operator+=(point2d v)
    {
        x += v.x;
        y += v.y;
    }
    void operator-=(point2d v)
    {
        x -= v.x;
        y -= v.y;
    }

    json toJson()
    {
        json data;
        data["x"] = x;
        data["y"] = y;
        return data;
    }
};

class box2d
{
public:
    point2d min_point;
    point2d max_point;

    box2d() : min_point(), max_point() {}
    box2d(point2d min_point, point2d max_point) : min_point(min_point), max_point(max_point) {}
    box2d(const box2d &box)
    {
        min_point = box.min_point;
        max_point = box.max_point;
    }
    box2d(box2d &&box)
    {
        min_point = std::move(box.min_point);
        max_point = std::move(box.max_point);
    }
    box2d(const json &data) : min_point(data.at("min_point")), max_point(data.at("max_point")) {}

    box2d &operator=(const box2d &box)
    {
        if (this != &box)
        {
            min_point = box.min_point;
            max_point = box.max_point;
        }
        return *this;
    }

    box2d &operator=(box2d &&box)
    {
        if (this != &box)
        {
            min_point = std::move(box.min_point);
            max_point = std::move(box.max_point);
        }
        return *this;
    }

    bool contains(point2d point) const
    {
        return point.x >= min_point.x &&
               point.y >= min_point.y &&
               point.x <= max_point.x &&
               point.y <= max_point.y;
    }

    bool contains(box2d box) const
    {
        return contains(box.min_point) && contains(box.max_point);
    }

    bool intersects(box2d box) const
    {
        return (box.max_point.x >= min_point.x) && (max_point.x >= box.min_point.x) &&
               (box.max_point.y >= min_point.y) && (max_point.y >= box.min_point.y);
    }

    json toJson()
    {
        json data;
        data["min_point"] = min_point.toJson();
        data["max_point"] = max_point.toJson();
        return data;
    }
};

#endif