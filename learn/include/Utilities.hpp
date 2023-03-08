#pragma once

constexpr float PI      = 3.14159265f;
constexpr float DEG2RAD = 3.14159f / 180.0f;

//sf::Vector2f getGlobalPosition(sf::Vector2f localCoors, sf::Vector2f position, float rotation) {
//    float sinA = sin(rotation * DEG2RAD), cosA = cos(rotation * DEG2RAD);
//    sf::Vector2f l(localCoors.x * cosA - localCoors.y * sinA, localCoors.y * cosA + localCoors.x * sinA);
//    return position + l;
//}

template <typename T>
inline float PointToLine(sf::Vector2<T> point, sf::Vector2<T> line1, sf::Vector2<T> line2) {
	float h = line2.y - line1.y, s = line2.x - line1.x;
	return -((s * (point.y - line1.y) - h * (point.x - line1.x)) / sqrt(s * s + h * h));
}

template <typename T>
inline float DotProduct(sf::Vector2<T> v0, sf::Vector2<T> v1) {
	return v0.x * v1.x + v0.y * v1.y;
}

template <typename T> // Z coords of crossed vectors
inline float CrossProduct(sf::Vector2<T> v0, sf::Vector2<T> v1) {
	return v0.x * v1.y - v0.y * v1.x;
}

template <typename T>
inline float Distance(sf::Vector2<T> v0, sf::Vector2<T> v1) {
	return sqrtf((v0 - v1).x * (v0 - v1).x + (v0 - v1).y * (v0 - v1).y);
}

template <typename T>
inline float Length(sf::Vector2<T> v) {
	return sqrtf(v.x * v.x + v.y * v.y);
}

template <typename T>
static sf::Vector2<T> Normalize(sf::Vector2<T> v) {
	float length = Length(v);
	return length ? v / length : sf::Vector2<T>();
}

template <typename T>
static sf::Vector2<T> Rotate(sf::Vector2<T> point, sf::Vector2<T> center, float angle) {
	float r = angle * DEG2RAD;

	return sf::Vector2<T>
	{
		cosf(r)* (point.x - center.x) - sinf(r) * (point.y - center.y) + center.x,
		sinf(r)* (point.x - center.x) + cosf(r) * (point.y - center.y) + center.y
	};
}

template <typename T>
inline sf::Vector2<T> VecAbs(sf::Vector2<T> v) {
	return sf::Vector2<T>
	{
		v.x < T(0) ? -v.x : v.x,
			v.y < T(0) ? -v.y : v.y
	};
}

inline sf::Vector2f Lerp(sf::Vector2f x, sf::Vector2f y, float t) {
	return x * (1.0f - t) + y * t;
}

inline sf::Vector2f MousePos(const sf::RenderWindow& window = *(sf::RenderWindow*)nullptr) {
	return !&window ? (sf::Vector2f)sf::Mouse::getPosition() : window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

#ifdef DEBUG
template<typename ...T>
void Print(T&&... args) {
	(std::cout << ... << args);
}

#define LOG(...) Print(__VA_ARGS__)

#else

#define LOG(...)

#endif
