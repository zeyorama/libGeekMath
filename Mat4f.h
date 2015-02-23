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

enum ZeyoMatrixType
{
  EMPTY,
  IDENTITY,
  SCALE,
  TRANSLATION,
  ROTATION,
  PERSPECTIVE,
  ORTHOGRAPHIC
};

struct ZeyoPerspectiveMatrix
{
  float FieldOfView;
  float Aspect;
  float zNear;
  float zFar;
};

struct ZeyoOrtographicMatrix
{
  float Top;
  float Bottom;
  float Left;
  float Right;
  float zNear;
  float zFar;
};

struct ZeyoMatrixSetting
{
  ZeyoMatrixType  Type;
  union
  {
    ZeyoPerspectiveMatrix Perspective;
    ZeyoOrtographicMatrix Orthographic;

    unsigned int          Empty;
  } Setting;
};

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
  Vec3f
  Transform( const Vec3f& vector );
  Vec4f
  Transform( const Vec4f& vector );
  Mat4f
  Transpose( void ) const;
  Mat4f
  Translation( const Vec3f& translation );
  Mat4f
  Perspective( const float FoV, const float Aspect, const float zNear, const float zFar );
  Mat4f
  Orthographic( const float Left, const float Right,
                const float Bottom, const float Top,
                const float zNear, const float zFar );

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
  float             m_Values[ 4 ][ 4 ];
  ZeyoMatrixSetting m_Setting;

};

#endif /* MAT4F_H_ */
