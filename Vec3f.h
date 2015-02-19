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

\file Vec3f.h

Created on: Feb 18, 2015
\author     fkzey
*/
#ifndef VEC3F_H_
#define VEC3F_H_

class Vec2f;
class Vec4f;

class Vec3f
{
public:
  Vec3f( void );
  Vec3f( const float value );
  Vec3f( const Vec3f& Vec3f );
  Vec3f( const float x, const float y, const float z );
  virtual
  ~Vec3f( void );

  void
  Set( const float& x, const float& y, const float& z );
  void
  X( const float& x );
  void
  Y( const float& y );
  void
  Z( const float& z );

  float
  LengthSq( void ) const;
  float
  Length( void ) const;
  float
  Dot( const Vec3f& other ) const;
  float
  Max( void ) const;
  float
  Min( void ) const;

  Vec3f
  Clamp( const Vec3f& Min, const Vec3f& Max );
  Vec3f
  Normalize( void ) const;
  Vec3f
  Reflect( const Vec3f& normal ) const;
  Vec3f
  Rotate( const Vec4f& quaternion ) const;
  Vec3f
  Rotate( const Vec3f& Axis, const float Angle ) const;
  Vec3f
  Cross( const Vec3f& vector ) const;
  Vec3f
  Lerp( const Vec3f& Destination, float LerpFactor ) const;
  Vec3f
  Max( const Vec3f& vector ) const;
  Vec3f
  Min( const Vec3f& vector ) const;

  Vec3f
  operator +( const float summand ) const;
  Vec3f
  operator +( const Vec3f& summand ) const;
  Vec3f
  operator -( const float subtrahend ) const;
  Vec3f
  operator -( const Vec3f& subtrahend ) const;
  Vec3f
  operator *( const float factor ) const;
  Vec3f
  operator *( const Vec3f& factor ) const;
  Vec3f
  operator /( const float dividend ) const;
  Vec3f&
  operator +=( const Vec3f& summand );
  Vec3f&
  operator +=( const float summand );
  Vec3f&
  operator -=( const Vec3f& subtrahend );
  Vec3f&
  operator -=( const float subtrahend );
  Vec3f&
  operator *=( const float factor );
  Vec3f&
  operator *=( const Vec3f& factor );
  Vec3f&
  operator /=( const float dividend );

  bool
  operator ==( const Vec3f& expr ) const;
  bool
  operator !=( const Vec3f& expr ) const;

  float&
  operator []( unsigned int i );
  float
  operator []( unsigned int i ) const;

  float
  X( void ) const;
  float
  Y( void ) const;
  float
  Z( void ) const;

  Vec2f
  XX( void ) const;
  Vec2f
  XY( void ) const;
  Vec2f
  XZ( void ) const;
  Vec2f
  YX( void ) const;
  Vec2f
  YY( void ) const;
  Vec2f
  YZ( void ) const;
  Vec2f
  ZX( void ) const;
  Vec2f
  ZY( void ) const;
  Vec2f
  ZZ( void ) const;

  Vec3f
  XXX( void ) const;
  Vec3f
  XXY( void ) const;
  Vec3f
  XXZ( void ) const;
  Vec3f
  XYX( void ) const;
  Vec3f
  XYY( void ) const;
  Vec3f
  XYZ( void ) const;
  Vec3f
  XZX( void ) const;
  Vec3f
  XZY( void ) const;
  Vec3f
  XZZ( void ) const;
  Vec3f
  YXX( void ) const;
  Vec3f
  YXY( void ) const;
  Vec3f
  YXZ( void ) const;
  Vec3f
  YYX( void ) const;
  Vec3f
  YYY( void ) const;
  Vec3f
  YYZ( void ) const;
  Vec3f
  YZX( void ) const;
  Vec3f
  YZY( void ) const;
  Vec3f
  YZZ( void ) const;
  Vec3f
  ZXX( void ) const;
  Vec3f
  ZXY( void ) const;
  Vec3f
  ZXZ( void ) const;
  Vec3f
  ZYX( void ) const;
  Vec3f
  ZYY( void ) const;
  Vec3f
  ZYZ( void ) const;
  Vec3f
  ZZX( void ) const;
  Vec3f
  ZZY( void ) const;
  Vec3f
  ZZZ( void ) const;

  void
  Print( void ) const;

  float*
  Values( void );

protected:
private:
  float m_Values[ 3 ];

};

#endif /* VEC3F_H_ */
