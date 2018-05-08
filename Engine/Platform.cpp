#include "Platform.h"
#include "SpriteEffect.h"

const Surface Platform::spr = Surface( Size,Size,Colors::Gray );

Platform::Platform( const Vei2& pos )
	:
	pos( Vec2( pos ) ),
	hitbox( this->pos,float( Size ),float( Size ) )
{
}

void Platform::Draw( Graphics& gfx ) const
{
	// gfx.DrawRect( pos.x,pos.y,Size,Size,Colors::Gray );
	gfx.DrawSprite( int( pos.x ),int( pos.y ),
		spr,SpriteEffect::Copy() );

#if 0
	if( hitbox.IsContainedBy( Graphics::GetScreenRect()
		.GetExpanded( -2 ) ) )
	{
		gfx.DrawHitbox( hitbox );
	}
#endif
}

void Platform::Move( const Vec2& amount )
{
	pos += amount;

	hitbox.MoveTo( pos );
}

const Rect& Platform::GetRect() const
{
	return( hitbox );
}
