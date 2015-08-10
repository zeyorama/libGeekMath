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

 \file Mat3f.hpp

 Created on: Jun 22, 2015
 \author     fkzey
 */

#ifndef MATH_MAT3F_HPP_
#define MATH_MAT3F_HPP_

class Vec2f;
class Vec3f;

/*
 * GeekEngine::Mat3f
 */
class Mat3f
{
public:
  Mat3f( void );
  Mat3f( const Mat3f& );
  Mat3f( const Vec3f&, const Vec3f&, const Vec3f& );
  virtual
  ~Mat3f( void );

  Mat3f&
  Identity( void );
  Mat3f&
  Scale( const Vec2f& );
  Mat3f&
  Scale( const float& x, const float& y );
  Mat3f&
  RotateZ( const float& );
  Mat3f&
  Translation( const Vec2f& );
  Mat3f&
  Translation( const float& x, const float& y );
  Mat3f
  Inverse( void ) const;
  Mat3f
  Transpose( void ) const;

  Mat3f
  operator *( const Mat3f& factor ) const;
  Vec3f
  operator *( const Vec3f& ) const;

  Mat3f&
  operator *=( const Mat3f& factor );

  float*
  operator []( unsigned int row );
  const float*
  operator []( unsigned int row ) const;

  const float*
  Values( void ) const;

  void
  Set( const unsigned int row, const unsigned int col, const float& );
  void
  Print( void ) const;

protected:
private:
  float m_Values[ 3 ][ 3 ];

};

#endif /* MATH_MAT3F_HPP_ */
