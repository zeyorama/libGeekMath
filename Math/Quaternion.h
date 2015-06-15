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

 \file Quaternion.h

 Created on: Mar 9, 2015
 \author     fkzey
 */

#ifndef LIBGEEKMATH_QUATERNION_H_
#define LIBGEEKMATH_QUATERNION_H_

class Mat4f;
class Vec2f;
class Vec3f;
class Vec4f;

class Quaternion
{
public:
  Quaternion( const Mat4f& matrix );
  Quaternion( const Vec2f& vector );
  Quaternion( const Vec3f& vector );
  Quaternion( const Quaternion& vector );
  Quaternion( const Vec3f& Axis, const float Angle );
  Quaternion( const float x = 0.0f, const float y = 0.0f, const float z = 0.0f, const float w = 1.0f );
  virtual
  ~Quaternion( void );

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
  Dot( const Quaternion& other ) const;
  float
  Max( void ) const;
  float
  Min( void ) const;

  Vec3f
  Forward( void ) const;
  Vec3f
  Backward( void ) const;
  Vec3f
  Left( void ) const;
  Vec3f
  Right( void ) const;
  Vec3f
  Up( void ) const;
  Vec3f
  Down( void ) const;

  Quaternion
  Clamp( const Quaternion& Min, const Quaternion& Max );
  Quaternion
  Conjugate( void ) const;
  Quaternion
  Normalize( void ) const;
  Quaternion
  Reflect( const Quaternion& normal ) const;
  Quaternion
  Lerp( const Quaternion& Destination, const float LerpFactor ) const;
  Quaternion
  NLerp( const Quaternion& Destination, const float LerpFactor, const bool shortestPath ) const;
  Quaternion
  SLerp( const Quaternion& Destination, const float LerpFactor, const bool shortestPath ) const;
  Quaternion
  Max( const Quaternion& vector ) const;
  Quaternion
  Min( const Quaternion& vector ) const;

  Mat4f
  RotationMatrix( void ) const;

  Quaternion
  operator +( const float summand ) const;
  Quaternion
  operator +( const Quaternion& summand ) const;
  Quaternion
  operator -( const float subtrahend ) const;
  Quaternion
  operator -( const Quaternion& subtrahend ) const;
  Quaternion
  operator *( const float factor ) const;
  Quaternion
  operator *( const Vec3f& factor ) const;
  Quaternion
  operator *( const Quaternion& factor ) const;
  Quaternion
  operator /( const float dividend ) const;
  Quaternion&
  operator +=( const Quaternion& summand );
  Quaternion&
  operator +=( const float summand );
  Quaternion&
  operator -=( const Quaternion& subtrahend );
  Quaternion&
  operator -=( const float subtrahend );
  Quaternion&
  operator *=( const float factor );
  Quaternion&
  operator *=( const Vec3f& factor );
  Quaternion&
  operator *=( const Quaternion& factor );
  Quaternion&
  operator /=( const float dividend );

  bool
  operator ==( const Quaternion& expr ) const;
  bool
  operator !=( const Quaternion& expr ) const;

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

  Vec2f
  XX( void ) const;
  Vec2f
  XY( void ) const;
  Vec2f
  XZ( void ) const;
  Vec2f
  XW( void ) const;
  Vec2f
  YX( void ) const;
  Vec2f
  YY( void ) const;
  Vec2f
  YZ( void ) const;
  Vec2f
  YW( void ) const;
  Vec2f
  ZX( void ) const;
  Vec2f
  ZY( void ) const;
  Vec2f
  ZZ( void ) const;
  Vec2f
  ZW( void ) const;
  Vec2f
  WX( void ) const;
  Vec2f
  WY( void ) const;
  Vec2f
  WZ( void ) const;
  Vec2f
  WW( void ) const;

  Vec3f
  XXX( void ) const;
  Vec3f
  XXY( void ) const;
  Vec3f
  XXZ( void ) const;
  Vec3f
  XXW( void ) const;
  Vec3f
  XYX( void ) const;
  Vec3f
  XYY( void ) const;
  Vec3f
  XYZ( void ) const;
  Vec3f
  XYW( void ) const;
  Vec3f
  XZX( void ) const;
  Vec3f
  XZY( void ) const;
  Vec3f
  XZZ( void ) const;
  Vec3f
  XZW( void ) const;
  Vec3f
  XWX( void ) const;
  Vec3f
  XWY( void ) const;
  Vec3f
  XWZ( void ) const;
  Vec3f
  XWW( void ) const;
  Vec3f
  YXX( void ) const;
  Vec3f
  YXY( void ) const;
  Vec3f
  YXZ( void ) const;
  Vec3f
  YXW( void ) const;
  Vec3f
  YYX( void ) const;
  Vec3f
  YYY( void ) const;
  Vec3f
  YYZ( void ) const;
  Vec3f
  YYW( void ) const;
  Vec3f
  YZX( void ) const;
  Vec3f
  YZY( void ) const;
  Vec3f
  YZZ( void ) const;
  Vec3f
  YZW( void ) const;
  Vec3f
  YWX( void ) const;
  Vec3f
  YWY( void ) const;
  Vec3f
  YWZ( void ) const;
  Vec3f
  YWW( void ) const;
  Vec3f
  ZXX( void ) const;
  Vec3f
  ZXY( void ) const;
  Vec3f
  ZXZ( void ) const;
  Vec3f
  ZXW( void ) const;
  Vec3f
  ZYX( void ) const;
  Vec3f
  ZYY( void ) const;
  Vec3f
  ZYZ( void ) const;
  Vec3f
  ZYW( void ) const;
  Vec3f
  ZZX( void ) const;
  Vec3f
  ZZY( void ) const;
  Vec3f
  ZZZ( void ) const;
  Vec3f
  ZZW( void ) const;
  Vec3f
  ZWX( void ) const;
  Vec3f
  ZWY( void ) const;
  Vec3f
  ZWZ( void ) const;
  Vec3f
  ZWW( void ) const;
  Vec3f
  WXX( void ) const;
  Vec3f
  WXY( void ) const;
  Vec3f
  WXZ( void ) const;
  Vec3f
  WXW( void ) const;
  Vec3f
  WYX( void ) const;
  Vec3f
  WYY( void ) const;
  Vec3f
  WYZ( void ) const;
  Vec3f
  WYW( void ) const;
  Vec3f
  WZX( void ) const;
  Vec3f
  WZY( void ) const;
  Vec3f
  WZZ( void ) const;
  Vec3f
  WZW( void ) const;
  Vec3f
  WWX( void ) const;
  Vec3f
  WWY( void ) const;
  Vec3f
  WWZ( void ) const;
  Vec3f
  WWW( void ) const;

  void
  Print( void ) const;

  const float*
  Values( void ) const;

protected:
private:
  float m_Values[ 4 ];
};

#endif /* LIBGEEKMATH_QUATERNION_H_ */
