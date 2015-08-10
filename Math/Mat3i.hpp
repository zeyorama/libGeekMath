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

 \file Mat3i.hpp

 Created on: Jun 22, 2015
 \author     fkzey
 */

#ifndef MATH_MAT3I_HPP_
#define MATH_MAT3I_HPP_

class Vec2i;

/*
 * GeekEngine::Mat3i
 */
class Mat3i
{
public:
  Mat3i( void );
  Mat3i( const Mat3i& );
  virtual
  ~Mat3i( void );

  Mat3i&
  Identity( void );
  Mat3i&
  Translation( const Vec2i& );
  Mat3i&
  Translation( const int& x, const int& y );
  Mat3i
  Inverse( void ) const;
  Mat3i
  Transpose( void ) const;

  Mat3i
  operator *( const Mat3i& factor ) const;

  Mat3i&
  operator *=( const Mat3i& factor );

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
  int m_Values[ 3 ][ 3 ];

};

#endif /* MATH_MAT3I_HPP_ */
