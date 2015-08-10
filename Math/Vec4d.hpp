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

 \file Vec4d.h

 Created on: Feb 19, 2015
 \author     fkzey
 */
#ifndef VEC4D_H_
#define VEC4D_H_

class Vec2d;
class Vec3d;

class Vec4d
{
public:
  Vec4d( const Vec2d& vector );
  Vec4d( const Vec3d& vector );
  Vec4d( const Vec4d& vector );
  Vec4d( const float x = 0.0f, const float y = 0.0f, const float z = 0.0f, const float w = 1.0f );
  virtual
  ~Vec4d( void );

  void
  Set( const float& x, const float& y, const float& z, const float& w );
  void
  X( const float& x );
  void
  Y( const float& y );
  void
  Z( const float& z );
  void
  W( const float& w );

  float
  Length( void ) const;
  float
  LengthSq( void ) const;
  float
  Dot( const Vec4d& other ) const;
  float
  Max( void ) const;
  float
  Min( void ) const;

  Vec4d
  Clamp( const Vec4d& Min, const Vec4d& Max );
  Vec4d
  Normalize( void ) const;
  Vec4d
  Reflect( const Vec4d& normal ) const;
  Vec4d
  Lerp( const Vec4d& Destination, const float LerpFactor ) const;
  Vec4d
  NLerp( const Vec4d& Destination, const float LerpFactor, const bool shortestPath ) const;
  Vec4d
  SLerp( const Vec4d& Destination, const float LerpFactor, const bool shortestPath ) const;
  Vec4d
  Max( const Vec4d& vector ) const;
  Vec4d
  Min( const Vec4d& vector ) const;

  Vec4d
  operator +( const float summand ) const;
  Vec4d
  operator +( const Vec4d& summand ) const;
  Vec4d
  operator -( const float subtrahend ) const;
  Vec4d
  operator -( const Vec4d& subtrahend ) const;
  Vec4d
  operator *( const float factor ) const;
  Vec4d
  operator *( const Vec4d& factor ) const;
  Vec4d
  operator /( const float dividend ) const;
  Vec4d&
  operator +=( const Vec4d& summand );
  Vec4d&
  operator +=( const float summand );
  Vec4d&
  operator -=( const Vec4d& subtrahend );
  Vec4d&
  operator -=( const float subtrahend );
  Vec4d&
  operator *=( const float factor );
  Vec4d&
  operator *=( const Vec4d& factor );
  Vec4d&
  operator /=( const float dividend );

  bool
  operator ==( const Vec4d& expr ) const;
  bool
  operator !=( const Vec4d& expr ) const;

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
  float
  W( void ) const;

  Vec2d
  XX( void ) const;
  Vec2d
  XY( void ) const;
  Vec2d
  XZ( void ) const;
  Vec2d
  XW( void ) const;
  Vec2d
  YX( void ) const;
  Vec2d
  YY( void ) const;
  Vec2d
  YZ( void ) const;
  Vec2d
  YW( void ) const;
  Vec2d
  ZX( void ) const;
  Vec2d
  ZY( void ) const;
  Vec2d
  ZZ( void ) const;
  Vec2d
  ZW( void ) const;
  Vec2d
  WX( void ) const;
  Vec2d
  WY( void ) const;
  Vec2d
  WZ( void ) const;
  Vec2d
  WW( void ) const;

  Vec3d
  XXX( void ) const;
  Vec3d
  XXY( void ) const;
  Vec3d
  XXZ( void ) const;
  Vec3d
  XXW( void ) const;
  Vec3d
  XYX( void ) const;
  Vec3d
  XYY( void ) const;
  Vec3d
  XYZ( void ) const;
  Vec3d
  XYW( void ) const;
  Vec3d
  XZX( void ) const;
  Vec3d
  XZY( void ) const;
  Vec3d
  XZZ( void ) const;
  Vec3d
  XZW( void ) const;
  Vec3d
  XWX( void ) const;
  Vec3d
  XWY( void ) const;
  Vec3d
  XWZ( void ) const;
  Vec3d
  XWW( void ) const;
  Vec3d
  YXX( void ) const;
  Vec3d
  YXY( void ) const;
  Vec3d
  YXZ( void ) const;
  Vec3d
  YXW( void ) const;
  Vec3d
  YYX( void ) const;
  Vec3d
  YYY( void ) const;
  Vec3d
  YYZ( void ) const;
  Vec3d
  YYW( void ) const;
  Vec3d
  YZX( void ) const;
  Vec3d
  YZY( void ) const;
  Vec3d
  YZZ( void ) const;
  Vec3d
  YZW( void ) const;
  Vec3d
  YWX( void ) const;
  Vec3d
  YWY( void ) const;
  Vec3d
  YWZ( void ) const;
  Vec3d
  YWW( void ) const;
  Vec3d
  ZXX( void ) const;
  Vec3d
  ZXY( void ) const;
  Vec3d
  ZXZ( void ) const;
  Vec3d
  ZXW( void ) const;
  Vec3d
  ZYX( void ) const;
  Vec3d
  ZYY( void ) const;
  Vec3d
  ZYZ( void ) const;
  Vec3d
  ZYW( void ) const;
  Vec3d
  ZZX( void ) const;
  Vec3d
  ZZY( void ) const;
  Vec3d
  ZZZ( void ) const;
  Vec3d
  ZZW( void ) const;
  Vec3d
  ZWX( void ) const;
  Vec3d
  ZWY( void ) const;
  Vec3d
  ZWZ( void ) const;
  Vec3d
  ZWW( void ) const;
  Vec3d
  WXX( void ) const;
  Vec3d
  WXY( void ) const;
  Vec3d
  WXZ( void ) const;
  Vec3d
  WXW( void ) const;
  Vec3d
  WYX( void ) const;
  Vec3d
  WYY( void ) const;
  Vec3d
  WYZ( void ) const;
  Vec3d
  WYW( void ) const;
  Vec3d
  WZX( void ) const;
  Vec3d
  WZY( void ) const;
  Vec3d
  WZZ( void ) const;
  Vec3d
  WZW( void ) const;
  Vec3d
  WWX( void ) const;
  Vec3d
  WWY( void ) const;
  Vec3d
  WWZ( void ) const;
  Vec3d
  WWW( void ) const;

  void
  Print( void ) const;

  const float*
  Values( void ) const;

protected:
private:
  float m_Values[ 4 ];
};

#endif /* VEC4D_H_ */
