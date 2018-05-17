#include "GravObject.h"

GravObject::GravObject( const Vec2& pos,const Vei2& size )
	:
	pos( pos ),
	hitbox( pos,float( size.x ),float( size.y ) ),
	offset( size.x / 4 )
{
}

GravObject::GravObject( int offset,float gravAcc,int jumpPower )
	:
	offset( offset ),
	gravAcc( gravAcc ),
	jumpPower( jumpPower )
{
}

void GravObject::Update( const Keyboard& kbd,float dt )
{
	grav += gravAcc * dt;
	pos.y += grav * dt;

	if( kbd.KeyIsPressed( 'W' ) && canJump )
	{
		jumping = true;
		canJump = false;
	}

	if( jumping )
	{
		pos.y -= float( jumpPower ) * dt;
	}

	if( grav > float( jumpPower ) / 1.5f && jumping )
	{
		grav = 0.0f;
		jumping = false;
		canJump = false;
	}

	hitbox.MoveTo( pos );
}

void GravObject::Draw( Graphics& gfx )
{
	gfx.DrawRect( int( pos.x ),int( pos.y ),
		Platform::Size,Platform::Size,
		Colors::Magenta );
}

void GravObject::Move( const Vec2& amount )
{
	pos += amount;

	hitbox.MoveTo( pos );
}

void GravObject::CheckHits( const std
	::vector<Platform>& plats )
{
	for( const Platform& plat : plats )
	{
		CheckHit( plat.GetRect() );
	}
}

const Vec2& GravObject::GetPos() const
{
	return( pos );
}

const Rect& GravObject::GetRect() const
{
	return( hitbox );
}

void GravObject::CheckHit( const Rect& rect )
{
	if( HitTestBot( rect ) )
	{
		pos.y = rect.top - hitbox.GetHeight();
		Land();
	}
	if( HitTestTop( rect ) )
	{
		pos.y = rect.bottom;
		Fall();
	}

	if( HitTestLeft( rect ) )
	{
		pos.x = rect.right;
	}

	if( HitTestRight( rect ) )
	{
		pos.x = rect.left - hitbox.GetWidth();
	}
}

void GravObject::Land()
{
	grav = 0.0f;
	jumping = false;
	canJump = true;
}

void GravObject::Fall()
{
	jumping = false;
	grav = 0.0f;
}

bool GravObject::HitTestTop( const Rect& rect ) const
{
	return( pos.x + offset < rect.right &&
		pos.x + hitbox.GetWidth() - offset > rect.left &&
		pos.y < rect.bottom &&
		pos.y + offset > rect.top );
}

bool GravObject::HitTestBot( const Rect& rect ) const
{
	return( pos.x + offset < rect.right &&
		pos.x + hitbox.GetWidth() - offset > rect.left &&
		pos.y + hitbox.GetHeight() - offset < rect.bottom &&
		pos.y + hitbox.GetHeight() > rect.top );
}

bool GravObject::HitTestLeft( const Rect& rect ) const
{
	return( pos.x < rect.right &&
		pos.x + offset > rect.left &&
		pos.y + offset < rect.bottom &&
		pos.y + hitbox.GetHeight() - offset > rect.top );
}

bool GravObject::HitTestRight( const Rect& rect ) const
{
	return( pos.x + hitbox.GetWidth() - offset < rect.right &&
		pos.x + hitbox.GetWidth() > rect.left &&
		pos.y + offset < rect.bottom &&
		pos.y + hitbox.GetHeight() - offset > rect.top );
}
