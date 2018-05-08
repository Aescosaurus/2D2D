#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Rect.h"
#include "Surface.h"

class Bullet
{
public:
	Bullet( const Vec2& pos,const Vec2& target,float bloom );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	bool CheckHit( const Rect& box );
	void Kill();
	void Move( const Vec2& amount );

	bool WillDelete() const;
	const Vec2& GetPos();
	const Rect& GetRect();
private:
	static constexpr int size = 8;
	static constexpr float speed = 830.1f;
	static const Surface img;
	Vec2 pos;
	Vec2 vel;
	Rect hitbox;
	bool dead = false;
	static constexpr float lifetime = 0.8f;
	float timer = 0.0f;
};