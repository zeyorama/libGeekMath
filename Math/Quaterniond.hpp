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

 \file Quaterniond.h

 Created on: Mar 9, 2015
 \author     fkzey
 */

#ifndef LIBGEEKMATH_QUATERNIOND_H_
#define LIBGEEKMATH_QUATERNIOND_H_

class Vec2d;
class Vec3d;
class Vec4d;
class Mat4d;

class Quaterniond
{
public:
  Quaterniond( const Mat4d& matrix );
  Quaterniond( const Vec2d& vector );
  Quaterniond( const Vec3d& vector );
  Quaterniond( const Quaterniond& vector );
  Quaterniond( const Vec3d& Axis, const double Angle );
  Quaterniond( const double x = 0.0f, const double y = 0.0f, const double z = 0.0f, const double w = 1.0f );
  virtual
  ~Quaterniond( void );

  void
  Set( const double& x, const double& y, const double& z, const double& w );
  void
  X( const double& x );
  void
  Y( const double& y );
  void
  Z( const double& z );
  void
  W( const double& w );

  double
  Length( void ) const;
  double
  LengthSq( void ) const;
  double
  Dot( const Quaterniond& other ) const;
  double
  Max( void ) const;
  double
  Min( void ) const;

  Vec3d
  Forward( void ) const;
  Vec3d
  Backward( void ) const;
  Vec3d
  Left( void ) const;
  Vec3d
  Right( void ) const;
  Vec3d
  Up( void ) const;
  Vec3d
  Down( void ) const;

  Quaterniond
  Clamp( const Quaterniond& Min, const Quaterniond& Max );
  Quaterniond
  Conjugate( void ) const;
  Quaterniond
  Normalize( void ) const;
  Quaterniond
  Reflect( const Quaterniond& normal ) const;
  Quaterniond
  Lerp( const Quaterniond& Destination, const double LerpFactor ) const;
  Quaterniond
  NLerp( const Quaterniond& Destination, const double LerpFactor, const bool shortestPath ) const;
  Quaterniond
  SLerp( const Quaterniond& Destination, const double LerpFactor, const bool shortestPath ) const;
  Quaterniond
  Max( const Quaterniond& vector ) const;
  Quaterniond
  Min( const Quaterniond& vector ) const;

  Mat4d
  RotationMatrix( void ) const;

  Quaterniond
  operator +( const double summand ) const;
  Quaterniond
  operator +( const Quaterniond& summand ) const;
  Quaterniond
  operator -( const double subtrahend ) const;
  Quaterniond
  operator -( const Quaterniond& subtrahend ) const;
  Quaterniond
  operator *( const double factor ) const;
  Quaterniond
  operator *( const Vec3d& factor ) const;
  Quaterniond
  operator *( const Quaterniond& factor ) const;
  Quaterniond
  operator /( const double dividend ) const;
  Quaterniond&
  operator +=( const Quaterniond& summand );
  Quaterniond&
  operator +=( const double summand );
  Quaterniond&
  operator -=( const Quaterniond& subtrahend );
  Quaterniond&
  operator -=( const double subtrahend );
  Quaterniond&
  operator *=( const double factor );
  Quaterniond&
  operator *=( const Vec3d& factor );
  Quaterniond&
  operator *=( const Quaterniond& factor );
  Quaterniond&
  operator /=( const double dividend );

  bool
  operator ==( const Quaterniond& expr ) const;
  bool
  operator !=( const Quaterniond& expr ) const;

  double&
  operator []( unsigned int i );
  double
  operator []( unsigned int i ) const;

  double
  X( void ) const;
  double
  Y( void ) const;
  double
  Z( void ) const;
  double
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

  const double*
  Values( void ) const;

protected:
private:
  double m_Values[ 4 ];
};

#endif /* LIBGEEKMATH_QUATERNIOND_H_ */
