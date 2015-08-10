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

 \file Mat3d.hpp

 Created on: Jun 22, 2015
 \author     fkzey
 */

#ifndef MATH_MAT3D_HPP_
#define MATH_MAT3D_HPP_

class Vec2d;
class Vec3d;

/*
 * GeekEngine::Mat3d
 */
class Mat3d
{
public:
  Mat3d( void );
  Mat3d( const Mat3d& );
  Mat3d( const Vec3d&, const Vec3d&, const Vec3d& );
  virtual
  ~Mat3d( void );

  Mat3d
  Identity( void );
  Mat3d
  Scale( const Vec2d& );
  Mat3d
  Scale( const double& x, const double& y );
  Mat3d
  RotateZ( const double& );
  Mat3d
  Translation( const Vec2d& );
  Mat3d
  Translation( const double& x, const double& y );
  Mat3d
  Inverse( void ) const;
  Mat3d
  Transpose( void ) const;

  Mat3d
  operator *( const Mat3d& factor ) const;
  Vec3d
  operator *( const Vec3d& ) const;

  Mat3d&
  operator *=( const Mat3d& factor );

  double*
  operator []( unsigned int row );
  const double*
  operator []( unsigned int row ) const;

  const double*
  Values( void ) const;

  void
  Set( const unsigned int row, const unsigned int col, const double& );
  void
  Print( void ) const;

protected:
private:
  double m_Values[ 3 ][ 3 ];

};

#endif /* MATH_MAT3D_HPP_ */
