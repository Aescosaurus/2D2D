#include "Bullet.h"
#include "SpriteEffect.h"
#include "Random.h"

const Surface Bullet::img = { size,size,Colors::Cyan };

Bullet::Bullet( const Vec2& pos,const Vec2& target,float bloom )
	:
	pos( pos ),
	vel( Vec2::GetVecFromAngle( ( target - pos ).GetNormalized()
		.GetAngle() + Random::RangeF( -bloom,bloom ) ) ),
	hitbox( pos,float( size ),float( size ) )
{}

void Bullet::Update( float dt )
{
	pos += vel * speed * dt;

	hitbox.MoveTo( pos -
		Vec2( float( size ) / 2.0f ) );

	timer += dt;
}

void Bullet::Draw( Graphics& gfx ) const
{
	const Vei2 drawPos = Vei2( pos -
		Vec2( float( size ) / 2.0f ) );
	// const Vei2 drawPos = Vei2( pos );
	// const Vei2 drawPos2 = drawPos +
	// 	Vei2( vel * float( size ) * 2.0f );

	gfx.DrawSprite( drawPos.x,drawPos.y,
		img,SpriteEffect::Copy() );
	// if( Graphics::GetScreenRect().ContainsPoint( drawPos ) &&
	// 	Graphics::GetScreenRect().ContainsPoint( drawPos2 ) )
	// {
	// 	gfx.DrawLine( drawPos.x,drawPos.y,
	// 		drawPos2.x,drawPos2.y,
	// 		Colors::Yellow );
	// }

#if !NDEBUG
	if( hitbox.IsContainedBy( Graphics::GetScreenRect() ) )
	{
		gfx.DrawHitbox( hitbox );
	}
#endif
}

bool Bullet::CheckHit( const Rect& box )
{
	if( hitbox.IsOverlappingWith( box ) )
	{
		dead = true;

		// Maybe spawn particles or something here.

		return true;
	}
	else return false;
}

void Bullet::Kill()
{
	dead = true;
}

void Bullet::Move( const Vec2& amount )
{
	pos += amount;
}

bool Bullet::WillDelete() const
{
	return( !hitbox.IsContainedBy( Graphics
		::GetScreenRect() ) || dead || timer >= lifetime );
}

const Vec2& Bullet::GetPos()
{
	return( pos );
}

const Rect& Bullet::GetRect()
{
	return( hitbox );
}
