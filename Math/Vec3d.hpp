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

\file Vec3d.h

Created on: Feb 18, 2015
\author     fkzey
*/
#ifndef VEC3D_H_
#define VEC3D_H_

class Vec2d;
class Quaterniond;

class Vec3d
{
public:
  Vec3d( void );
  Vec3d( const double value );
  Vec3d( const Vec3d& );
  Vec3d( const double x, const double y, const double z );
  virtual
  ~Vec3d( void );

  void
  Set( const double& x, const double& y, const double& z );
  void
  X( const double& x );
  void
  Y( const double& y );
  void
  Z( const double& z );

  double
  LengthSq( void ) const;
  double
  Length( void ) const;
  double
  Dot( const Vec3d& other ) const;
  double
  Max( void ) const;
  double
  Min( void ) const;

  Vec3d
  Clamp( const Vec3d& Min, const Vec3d& Max );
  Vec3d
  Normalize( void ) const;
  Vec3d
  Reflect( const Vec3d& normal ) const;
  Vec3d
  Rotate( const Quaterniond& Quaterniond ) const;
  Vec3d
  Rotate( const Vec3d& Axis, const double Angle ) const;
  Vec3d
  Cross( const Vec3d& vector ) const;
  Vec3d
  Lerp( const Vec3d& Destination, double LerpFactor ) const;
  Vec3d
  Max( const Vec3d& vector ) const;
  Vec3d
  Min( const Vec3d& vector ) const;

  Vec3d
  operator +( const double summand ) const;
  Vec3d
  operator +( const Vec3d& summand ) const;
  Vec3d
  operator -( const double subtrahend ) const;
  Vec3d
  operator -( const Vec3d& subtrahend ) const;
  Vec3d
  operator *( const double factor ) const;
  Vec3d
  operator *( const Vec3d& factor ) const;
  Vec3d
  operator /( const double dividend ) const;
  Vec3d&
  operator +=( const Vec3d& summand );
  Vec3d&
  operator +=( const double summand );
  Vec3d&
  operator -=( const Vec3d& subtrahend );
  Vec3d&
  operator -=( const double subtrahend );
  Vec3d&
  operator *=( const double factor );
  Vec3d&
  operator *=( const Vec3d& factor );
  Vec3d&
  operator /=( const double dividend );

  bool
  operator ==( const Vec3d& expr ) const;
  bool
  operator !=( const Vec3d& expr ) const;

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

  Vec2d
  XX( void ) const;
  Vec2d
  XY( void ) const;
  Vec2d
  XZ( void ) const;
  Vec2d
  YX( void ) const;
  Vec2d
  YY( void ) const;
  Vec2d
  YZ( void ) const;
  Vec2d
  ZX( void ) const;
  Vec2d
  ZY( void ) const;
  Vec2d
  ZZ( void ) const;

  Vec3d
  XXX( void ) const;
  Vec3d
  XXY( void ) const;
  Vec3d
  XXZ( void ) const;
  Vec3d
  XYX( void ) const;
  Vec3d
  XYY( void ) const;
  Vec3d
  XYZ( void ) const;
  Vec3d
  XZX( void ) const;
  Vec3d
  XZY( void ) const;
  Vec3d
  XZZ( void ) const;
  Vec3d
  YXX( void ) const;
  Vec3d
  YXY( void ) const;
  Vec3d
  YXZ( void ) const;
  Vec3d
  YYX( void ) const;
  Vec3d
  YYY( void ) const;
  Vec3d
  YYZ( void ) const;
  Vec3d
  YZX( void ) const;
  Vec3d
  YZY( void ) const;
  Vec3d
  YZZ( void ) const;
  Vec3d
  ZXX( void ) const;
  Vec3d
  ZXY( void ) const;
  Vec3d
  ZXZ( void ) const;
  Vec3d
  ZYX( void ) const;
  Vec3d
  ZYY( void ) const;
  Vec3d
  ZYZ( void ) const;
  Vec3d
  ZZX( void ) const;
  Vec3d
  ZZY( void ) const;
  Vec3d
  ZZZ( void ) const;

  void
  Print( void ) const;

  const double*
  Values( void ) const;

protected:
private:
  double m_Values[ 4 ];

};

#endif /* VEC3D_H_ */
