#pragma once

#include "..\\math\math.h"
#include "..\\core\assert.h"
#include <windows.h>

struct color {
public:
	float r, g, b;
	color() { }
	color(float r, float g, float b) : r(r), g(g), b(b) { }
	void set(float r, float g, float b) { }

	float operator [] (size_t index) const { }
	float& operator [] (size_t index) { }

	// relational operator
	bool operator == (const color& c) const { }
	bool operator != (const color& c) const { }

	// assignment operator
	color& operator += (const color & c) { }
	color& operator -= (const color & c) { }
	color& operator *= (const color & c) { }
	color& operator /= (const color & c) { }
	color& operator += (float s) { }
	color& operator -= (float s) { }
	color& operator *= (float s) { }
	color& operator /= (float s) { }

	// arithmetic operator
	color operator + (const color& c) const { }
	color operator - (const color& c) const { }
	color operator * (const color& c) const { }
	color operator / (const color& c) const { }
	color operator + (float s) const { }
	color operator - (float s) const { }
	color operator * (float s) const { }
	color operator / (float s) const { }

	operator COLORREF() const {
		BYTE _r = static_cast<BYTE>(math::clamp01(r) * 255.0f);
		BYTE _g = static_cast<BYTE>(math::clamp01(g) * 255.0f);
		BYTE _b = static_cast<BYTE>(math::clamp01(b) * 255.0f);
		return RGB(_r, _g, _b);
	}

	static const color red;
	static const color green;
	static const color blue;
	static const color white;
	static const color orange;
	static const color yellow;
	static const color magenta;
	static const color cyan;
};