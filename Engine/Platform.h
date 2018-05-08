#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Graphics.h"

class Platform
{
public:
	Platform( const Vei2& pos );

	void Draw( Graphics& gfx ) const;

	void Move( const Vec2& amount );

	const Rect& GetRect() const;
public:
	static constexpr int Size = 32;
private:
	Vec2 pos;
	Rect hitbox;
	static const Surface spr;
};