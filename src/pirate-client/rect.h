#ifndef RECT_H
#define RECT_H

#include <string>
#include <sstream>
#include <SDL.h>
#include "json/json.h"
#include "vectors.h"

///A rectangle
/**
*  Describes a rectangle, can use ints, floats or doubles
*  to represent its values
*/
template<class T>
class Rect {
public:
	Rect() : pos(0, 0), w(0), h(0) {
	}
	/**
	*  Construct the rect and set its properties
	*  @param pX The x position
	*  @param pY The y position
	*  @param pW The width
	*  @param pH The height
	*/
	Rect(T pX, T pY, T pW, T pH) : pos(pX, pY), w(pW), h(pH) {
	}
	/**
	*  Construct the rect and set its properties
	*  @param pPos The position, as a vector
	*  @param pW The width
	*  @param pH The height
	*/
	Rect(Vector2<T> pPos, T pW, T pH){
		Set(pPos, pW, pH);
	}
	/**
	*  Set the rect's properties
	*  @param val The Json::Value containing x, y, w, h
	*/
	Rect(Json::Value val){
		Load(val);
	}
	/**
	*  Set the rect's properties
	*  @param pX The x position
	*  @param pY The y position
	*  @param pW The width
	*  @param pH The height
	*/
	void Set(T pX, T pY, T pW, T pH){
		pos.x = pX;
		pos.y = pY;
		w = pW;
		h = pH;
	}
	/**
	*  Set the rect's properties
	*  @param pPos The position, as a vector
	*  @param pW The width
	*  @param pH The height
	*/
	void Set(Vector2<T> pPos, T pW, T pH){
		pos = pPos;
		w = pW;
		h = pH;
	}
	/**
	*  Save the box's properties to a Json::Value and return it
	*  @return Json::Value containing the box's properties
	*/
	Json::Value Save() const {
		Json::Value val;
		val["x"] = pos.x;
		val["y"] = pos.y;
		val["w"] = w;
		val["h"] = h;
		return val;
	}
	/**
	*  Load the box's properties from a Json::Value
	*  @param val The Json::Value containing the properties to load
	*/
	void Load(Json::Value val){
		Set(val["x"].asInt(), val["y"].asInt(),
			val["w"].asInt(), val["h"].asInt());
	}

	//check collision
	bool collide(const Rect<float> &a){
		if (a.pos.y + a.h <= pos.y)
			return false;
		if (a.pos.y >= pos.y + h)
			return false;
		if (a.pos.x + a.w <= pos.x)
			return false;
		if (a.pos.x >= pos.x + w)
			return false;

		return true;
	}

	bool collide(const Vector2f &p){
		if ((p.x > pos.x && p.x < pos.x + w) && (p.y > pos.y && p.y < pos.y + h))	
			return true;
		return false;
}

	///Operators
    bool operator == (Rect<T> r) const {
        return (pos.x == r.pos.x && pos.y == r.pos.y 
            && w == r.w && h == r.h);
    }
	Rect<T>& operator += (Vector2f vec){
		this->pos += vec;
		return *this;
	}
	Rect<T> operator + (const Vector2f v) const{
		return Rect<T>(pos.x + v.x, pos.y + v.y, w, h);
	}
	Rect<T> operator - (const Vector2f v) const{
		return Rect<T>(pos.x - v.x, pos.y - v.y, w, h);
	}
	///For conversions
	operator SDL_Rect() const{
		SDL_Rect rect;
		rect.x = pos.x;
		rect.y = pos.y;
		rect.w = w;
		rect.h = h;
		return rect;
	}
	operator Rect<float>() const {
		Rect<float> rect(pos, w, h);
		return rect;
	}
	operator Rect<int>() const {
		Rect<int> rect(pos, w, h);
		return rect;
	}
  operator std::string() const {
    std::stringstream s;
    s << "Rect: (" << (std::string)pos 
      << ", w: " << w << ", h: " << h << ")";
    return s.str();
  }

public:
	Vector2<T> pos;
	T w, h;
};

typedef Rect<int> Recti;
typedef Rect<float> Rectf;
typedef Rect<double> Rectd;

#endif
