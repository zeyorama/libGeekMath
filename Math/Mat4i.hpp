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

 \file Mat4i.h

 Created on: Feb 19, 2015
 \author     fkzey
 */

#ifndef MAT4I_H_
#define MAT4I_H_

class Vec3f;
class Quaternion;

class Mat4i
{
public:
  Mat4i( void );
  Mat4i( const Mat4i& matrix );
  virtual
  ~Mat4i( void );

  Mat4i
  Identity( void );
  Mat4i
  Translation( const int& x, const int& y, const int& z );
  Mat4i
  Inverse( void ) const;
  Mat4i
  Transpose( void ) const;

  Mat4i
  operator *( const Mat4i& ) const;

  Mat4i&
  operator *=( const Mat4i& );

  int*
  operator []( unsigned int row );
  const int*
  operator []( unsigned int row ) const;

  const int*
  Values( void ) const;

  void
  Set( const unsigned int row, const unsigned int col, const int& );
  void
  Print( void ) const;

protected:
private:
  int m_Values[ 4 ][ 4 ];

};

#endif /* MAT4I_H_ */
