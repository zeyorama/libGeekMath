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

\file Vec2i.h

Created on: Feb 18, 2015
\author     fkzey
*/
#ifndef VEC2F_H_
#define VEC2F_H_

class Vec2i
{
public:
  Vec2i( void );
  Vec2i( const int value );
  Vec2i( const Vec2i& Vec2i );
  Vec2i( const int x, const int y );
  virtual
  ~Vec2i( void );

  int
  LengthSq( void ) const;
  int
  Length( void ) const;
  int
  Dot( const Vec2i& other ) const;
  int
  Max( void ) const;
  int
  Min( void ) const;

  void
  Set( const int& x, const int& y );
  void
  X( const int& x );
  void
  Y( const int& y );

  Vec2i
  Clamp( const Vec2i& Min, const Vec2i& Max );
  Vec2i
  Normalize( void ) const;
  Vec2i
  Max( const Vec2i& vector ) const;
  Vec2i
  Min( const Vec2i& vector ) const;

  Vec2i
  operator +( const int summand ) const;
  Vec2i
  operator +( const Vec2i& summand ) const;
  Vec2i
  operator -( const int subtrahend ) const;
  Vec2i
  operator -( const Vec2i& subtrahend ) const;
  Vec2i
  operator *( const int factor ) const;
  Vec2i
  operator *( const Vec2i& factor ) const;
  Vec2i
  operator /( const int dividend ) const;
  Vec2i
  operator /( const float dividend ) const;
  Vec2i&
  operator +=( const Vec2i& summand );
  Vec2i&
  operator +=( const int summand );
  Vec2i&
  operator -=( const Vec2i& subtrahend );
  Vec2i&
  operator -=( const int subtrahend );
  Vec2i&
  operator *=( const int factor );
  Vec2i&
  operator *=( const Vec2i& factor );
  Vec2i&
  operator /=( const int dividend );

  bool
  operator ==( const Vec2i& expr ) const;
  bool
  operator !=( const Vec2i& expr ) const;

  int&
  operator []( unsigned int i );
  int
  operator []( unsigned int i ) const;

  int
  X( void ) const;
  int
  Y( void ) const;

  Vec2i
  XX( void ) const;
  Vec2i
  XY( void ) const;
  Vec2i
  YX( void ) const;
  Vec2i
  YY( void ) const;

  void
  Print( void ) const;

  const int*
  Values( void ) const;

protected:
private:
  int m_Values[ 4 ];

};

#endif /* VEC2F_H_ */
