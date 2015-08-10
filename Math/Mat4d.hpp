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

 \file Mat4d.h

 Created on: Feb 19, 2015
 \author     fkzey
 */

#ifndef MAT4D_H_
#define MAT4D_H_

class Vec3d;
class Quaterniond;

class Mat4d
{
public:
  Mat4d( void );
  Mat4d( const Mat4d& matrix );
  virtual
  ~Mat4d( void );

  Mat4d
  Scale( const Vec3d& );
  Mat4d
  Scale( const double&, const double&, const double& );
  Mat4d
  Identity( void );
  Mat4d
  Rotation( const Quaterniond& Quaterniond );
  Mat4d
  Rotation( const Vec3d& forward, const Vec3d& up );
  Mat4d
  Rotation( const double x, const double y, const double z );
  Mat4d
  Rotation( const Vec3d& n, const Vec3d& v, const Vec3d& u );
  Vec3d
  Transformation( const Vec3d& vector ) const;
  Quaterniond
  Transformation( const Quaterniond& vector ) const;
  Mat4d
  Inverse( void ) const;
  Mat4d
  Transpose( void ) const;
  Mat4d
  Translation( const Vec3d& );
  Mat4d
  Translation( const double&, const double&, const double& );
  Mat4d
  Perspective( const double FoV, const double Aspect, const double zNear, const double zFar );
  Mat4d
  Orthographic( const double Left, const double Right,
                const double Bottom, const double Top,
                const double zNear, const double zFar );

  Mat4d
  operator *( const Mat4d& ) const;

  Quaterniond
  operator *( const Quaterniond& ) const;

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
  double  m_Values[ 4 ][ 4 ];

};

#endif /* MAT4D_H_ */
