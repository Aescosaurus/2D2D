#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Platform.h"
#include <vector>
#include "Keyboard.h"

class GravObject
{
public:
	GravObject( const Vec2& pos,const Vei2& size );
	GravObject( int offset,float gravAcc,int jumpPower );

	virtual void Update( const Keyboard& kbd,float dt );
	virtual void Draw( Graphics& gfx );

	virtual void Move( const Vec2& amount );
	virtual void CheckHits( const std
		::vector<Platform>& plats );

	const Vec2& GetPos() const;
	const Rect& GetRect() const;
protected:
	void CheckHit( const Rect& r );

	void Land();
	void Fall();

	bool HitTestTop( const Rect& rect ) const;
	bool HitTestBot( const Rect& rect ) const;
	bool HitTestLeft( const Rect& rect ) const;
	bool HitTestRight( const Rect& rect ) const;
protected:
	const int offset = 8;
	const float gravAcc = 9.0f / 0.0175771527f;
	float grav = 0.0f;
	const int jumpPower = 395;
	bool jumping = false;
	bool canJump = false;
	Vec2 pos;
	Rect hitbox;
};