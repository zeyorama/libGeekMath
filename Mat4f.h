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

 \file Mat4f.h

 Created on: Feb 19, 2015
 \author     fkzey
 */

#ifndef MAT4F_H_
#define MAT4F_H_

class Vec3f;
class Vec4f;

class Mat4f
{
public:
  Mat4f( void );
  Mat4f( const Mat4f& matrix );
  virtual
  ~Mat4f( void );

  Mat4f
  Scale( const Vec3f& scale );
  Mat4f
  Identity( void );
  Mat4f
  Rotation( const Vec4f& quaternion );
  Mat4f
  Rotation( const Vec3f& forward, const Vec3f& up );
  Mat4f
  Rotation( const float x, const float y, const float z );
  Mat4f
  Rotation( const Vec3f& n, const Vec3f& v, const Vec3f& u );
  Mat4f
  Transpose( void ) const;
  Mat4f
  Translation( const Vec3f& translation );

  Mat4f
  operator *( const Mat4f& factor ) const;

  Mat4f&
  operator *=( const Mat4f& factor );

  float*
  operator []( unsigned int row );
  const float*
  operator []( unsigned int row ) const;

  float*
  Values( void );

  void
  Set( const unsigned int row, const unsigned int col, const float value );
  void
  Print( void ) const;

protected:
private:
  float m_Values[ 4 ][ 4 ];

};

#endif /* MAT4F_H_ */
