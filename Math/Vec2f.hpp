/*
This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

\file Vec2f.h

Created on: Feb 18, 2015
\author     fkzey
*/
#ifndef VEC2F_H_
#define VEC2F_H_

class Vec2f
{
public:
  Vec2f( void );
  Vec2f( const float value );
  Vec2f( const Vec2f& vec2f );
  Vec2f( const float x, const float y );
  virtual
  ~Vec2f( void );

  float
  LengthSq( void ) const;
  float
  Length( void ) const;
  float
  Dot( const Vec2f& other ) const;
  float
  Max( void ) const;
  float
  Min( void ) const;

  void
  Set( const float& x, const float& y );
  void
  X( const float& x );
  void
  Y( const float& y );

  Vec2f
  Clamp( const Vec2f& Min, const Vec2f& Max );
  Vec2f
  Normalize( void ) const;
  Vec2f
  Reflect( const Vec2f& normal ) const;
  Vec2f
  Lerp( const Vec2f& Destination, float LerpFactor ) const;
  Vec2f
  Max( const Vec2f& vector ) const;
  Vec2f
  Min( const Vec2f& vector ) const;

  Vec2f
  operator +( const float summand ) const;
  Vec2f
  operator +( const Vec2f& summand ) const;
  Vec2f
  operator -( const float subtrahend ) const;
  Vec2f
  operator -( const Vec2f& subtrahend ) const;
  Vec2f
  operator *( const float factor ) const;
  Vec2f
  operator *( const Vec2f& factor ) const;
  Vec2f
  operator /( const float dividend ) const;
  Vec2f&
  operator +=( const Vec2f& summand );
  Vec2f&
  operator +=( const float summand );
  Vec2f&
  operator -=( const Vec2f& subtrahend );
  Vec2f&
  operator -=( const float subtrahend );
  Vec2f&
  operator *=( const float factor );
  Vec2f&
  operator *=( const Vec2f& factor );
  Vec2f&
  operator /=( const float dividend );

  bool
  operator ==( const Vec2f& expr ) const;
  bool
  operator !=( const Vec2f& expr ) const;

  float&
  operator []( unsigned int i );
  float
  operator []( unsigned int i ) const;

  float
  X( void ) const;
  float
  Y( void ) const;

  Vec2f
  XX( void ) const;
  Vec2f
  XY( void ) const;
  Vec2f
  YX( void ) const;
  Vec2f
  YY( void ) const;

  void
  Print( void ) const;

  const float*
  Values( void ) const;

protected:
private:
  float m_Values[ 4 ];

};

#endif /* VEC2F_H_ */
