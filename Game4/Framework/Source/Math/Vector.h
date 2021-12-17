#pragma once

namespace fw {

class vec2
{
public:
    vec2() { x = 0; y = 0; }
    vec2(float nx, float ny) { x = nx; y = ny; }

    static void Test();

    void Set(float nx, float ny) { x = nx; y = ny; }

    vec2 operator+(const vec2& o) const { return vec2( x + o.x, y + o.y ); }
    vec2 operator-(const vec2& o) const { return vec2( x - o.x, y - o.y ); }
    vec2 operator*(const vec2& o) const { return vec2( x * o.x, y * o.y ); }
    vec2 operator/(const vec2& o) const { return vec2( x / o.x, y / o.y ); }

    vec2 operator*(float o) const { return vec2( x * o, y * o ); }
    vec2 operator/(float o) const { return vec2( x / o, y / o ); }

    vec2& operator+=(const vec2& o) { x += o.x; y += o.y; return *this; }
    vec2& operator-=(const vec2& o) { x -= o.x; y -= o.y; return *this; }
    vec2& operator*=(const vec2& o) { x *= o.x; y *= o.y; return *this; }
    vec2& operator/=(const vec2& o) { x /= o.x; y /= o.y; return *this; }

    vec2 operator-() { return vec2(-x, -y); }

    bool operator==(const vec2& o) const { return (x == o.x && y == o.y); }
    bool operator!=(const vec2& o) const { return (x != o.x || y != o.y); }

    float Length() const
    {
        return sqrtf( x*x + y*y );
    }

    float DistanceTo(const vec2& o) const
    {
        return (*this - o).Length();
    }

    void Normalize()
    {
        if( x != 0 || y != 0 )
        {
            float len = Length();
            x /= len;
            y /= len;
        }
    }

    vec2 GetNormalized() const
    {
        if( x != 0 || y != 0 )
        {
            float len = Length();
            return *this / len;
        }

        return vec2(0,0);
    }

    float Dot(const vec2& o) const
    {
        return x*o.x + y*o.y;
    }

public:
    float x;
    float y;
};

inline vec2 operator*(float f, const vec2& v) { return vec2( v.x * f, v.y * f ); }
inline vec2 operator/(float f, const vec2& v) { return vec2( v.x / f, v.y / f ); }

class ivec2
{
public:
    ivec2() { x = 0; y = 0; }
    ivec2(int nx, int ny) { x = nx; y = ny; }

    void Set(int nx, int ny) { x = nx; y = ny; }

    ivec2 operator+(const ivec2& o) const { return ivec2( x + o.x, y + o.y ); }
    ivec2 operator-(const ivec2& o) const { return ivec2( x - o.x, y - o.y ); }
    //vec2 operator*(const vec2& o) const { return vec2( x * o.x, y * o.y ); }
    ivec2 operator/(const vec2& o) const { return ivec2( x / o.x, y / o.y ); }

    vec2 operator*(float o) const { return vec2( x * o, y * o ); }
    //vec2 operator/(float o) const { return vec2( x / o, y / o ); }

    ivec2& operator+=(const ivec2& o) { x += o.x; y += o.y; return *this; }
    ivec2& operator-=(const ivec2& o) { x -= o.x; y -= o.y; return *this; }
    //vec2& operator*=(const vec2& o) { x *= o.x; y *= o.y; return *this; }
    //vec2& operator/=(const vec2& o) { x /= o.x; y /= o.y; return *this; }

    //vec2 operator-() { return vec2(-x, -y); }

    bool operator==(const ivec2& o) const { return (x == o.x && y == o.y); }
    //bool operator!=(const vec2& o) const { return (x != o.x || y != o.y); }

public:
    int x;
    int y;

    float Length() const
    {
        return sqrtf(x * x + y * y);
    }

    void Normalize()
    {
        if (x != 0 || y != 0)
        {
            float len = Length();
            x /= len;
            y /= len;
        }
    }

};

} // namespace fw
