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

\file Vec2d.h

Created on: Feb 18, 2015
\author     fkzey
*/
#ifndef VEC2D_H_
#define VEC2D_H_

class Vec2d
{
public:
  Vec2d( void );
  Vec2d( const double value );
  Vec2d( const Vec2d& Vec2d );
  Vec2d( const double x, const double y );
  virtual
  ~Vec2d( void );

  double
  LengthSq( void ) const;
  double
  Length( void ) const;
  double
  Dot( const Vec2d& other ) const;
  double
  Max( void ) const;
  double
  Min( void ) const;

  void
  Set( const double& x, const double& y );
  void
  X( const double& x );
  void
  Y( const double& y );

  Vec2d
  Clamp( const Vec2d& Min, const Vec2d& Max );
  Vec2d
  Normalize( void ) const;
  Vec2d
  Reflect( const Vec2d& normal ) const;
  Vec2d
  Lerp( const Vec2d& Destination, double LerpFactor ) const;
  Vec2d
  Max( const Vec2d& vector ) const;
  Vec2d
  Min( const Vec2d& vector ) const;

  Vec2d
  operator +( const double summand ) const;
  Vec2d
  operator +( const Vec2d& summand ) const;
  Vec2d
  operator -( const double subtrahend ) const;
  Vec2d
  operator -( const Vec2d& subtrahend ) const;
  Vec2d
  operator *( const double factor ) const;
  Vec2d
  operator *( const Vec2d& factor ) const;
  Vec2d
  operator /( const double dividend ) const;
  Vec2d&
  operator +=( const Vec2d& summand );
  Vec2d&
  operator +=( const double summand );
  Vec2d&
  operator -=( const Vec2d& subtrahend );
  Vec2d&
  operator -=( const double subtrahend );
  Vec2d&
  operator *=( const double factor );
  Vec2d&
  operator *=( const Vec2d& factor );
  Vec2d&
  operator /=( const double dividend );

  bool
  operator ==( const Vec2d& expr ) const;
  bool
  operator !=( const Vec2d& expr ) const;

  double&
  operator []( unsigned int i );
  double
  operator []( unsigned int i ) const;

  double
  X( void ) const;
  double
  Y( void ) const;

  Vec2d
  XX( void ) const;
  Vec2d
  XY( void ) const;
  Vec2d
  YX( void ) const;
  Vec2d
  YY( void ) const;

  void
  Print( void ) const;

  const double*
  Values( void ) const;

protected:
private:
  double m_Values[ 4 ];

};

#endif /* VEC2D_H_ */
