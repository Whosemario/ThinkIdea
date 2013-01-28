
#ifndef VEC3F_H
#define VEC3F_H


class Vec3f{
public:
	Vec3f();
	Vec3f(float x,float y,float z);
	Vec3f(const Vec3f& other);

	Vec3f& operator=(const Vec3f& other);
	float & operator[](int index);
	float operator[](int index) const;

	Vec3f operator*(float scale) const;
	Vec3f operator/(float scale) const;
	Vec3f operator+(const Vec3f& other) const;
	Vec3f operator-(const Vec3f& other) const;
	Vec3f operator-() const;

	const Vec3f &operator*=(float scale);
	const Vec3f &operator/=(float scale);
	const Vec3f &operator+=(const Vec3f& other);
	const Vec3f &operator-=(const Vec3f& other);

	float magnitude() const;
	float magnitudeSquared() const;
	Vec3f normalized() const;
	float dot(const Vec3f& other) const;
	Vec3f cross(const Vec3f& other) const;

private:
	float v[3];
};

Vec3f operator*(float scale, const Vec3f &v);
std::ostream &operator<<(std::ostream &output, const Vec3f &v);

#endif