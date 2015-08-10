/*
 This software is provided 'as-is', without any express or implied
 warranty.  In no event will the authors be held liable for any damages
 arisinfg from the use of this software.

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

 \file Mat4d.cpp

 Created on: Feb 19, 2015
 \author     fkzey
 */

#include "Mat4d.hpp"

#include "Vec2f.hpp"
#include "Vec3d.hpp"
#include "Quaterniond.hpp"
#include "../GeekMathConstants.hpp"

#include <cmath>
#include <cstdio>
#include <cstring>

static const unsigned int MATRIX_SIZE = sizeof( double ) * 16;

Mat4d::Mat4d( void )
{
  memset( m_Values, 0.0, MATRIX_SIZE );
}

Mat4d::Mat4d( const Mat4d& matrix )
{
  memcpy( m_Values, matrix.m_Values, MATRIX_SIZE );
}

Mat4d::~Mat4d( void ) { return; }

Mat4d&
Mat4d::Scale( const Vec3d& scale )
{
  return Scale( scale[ 0 ], scale[ 1 ], scale[ 2 ] );
}

Mat4d&
Mat4d::Scale( const double& x, const double& y, const double& z )
{
  m_Values[0][0] = x;    m_Values[0][1] = 0.0; m_Values[0][2] = 0.0; m_Values[0][3] = 0.0;
  m_Values[1][0] = 0.0; m_Values[1][1] = y;    m_Values[1][2] = 0.0; m_Values[1][3] = 0.0;
  m_Values[2][0] = 0.0; m_Values[2][1] = 0.0; m_Values[2][2] = z;    m_Values[2][3] = 0.0;
  m_Values[3][0] = 0.0; m_Values[3][1] = 0.0; m_Values[3][2] = 0.0; m_Values[3][3] = 1.0;

  return *this;
}

Mat4d&
Mat4d::Identity( void )
{
  memset( m_Values, 0.0, MATRIX_SIZE );

  m_Values[ 0 ][ 0 ] = 1.0;
  m_Values[ 1 ][ 1 ] = 1.0;
  m_Values[ 2 ][ 2 ] = 1.0;
  m_Values[ 3 ][ 3 ] = 1.0;

  return *this;
}

Mat4d&
Mat4d::Rotation( const Quaterniond& Quaterniond )
{
  Vec3d n = Vec3d(        2.0 * (Quaterniond.X() * Quaterniond.Z() - Quaterniond.W() * Quaterniond.Y()),
                          2.0 * (Quaterniond.Y() * Quaterniond.Z() + Quaterniond.W() * Quaterniond.X()),
                   1.0 - 2.0 * (Quaterniond.X() * Quaterniond.X() + Quaterniond.Y() * Quaterniond.Y()));

  Vec3d v = Vec3d(        2.0 * (Quaterniond.X() * Quaterniond.Y() + Quaterniond.W() * Quaterniond.Z()),
                   1.0 - 2.0 * (Quaterniond.X() * Quaterniond.X() + Quaterniond.Z() * Quaterniond.Z()),
                          2.0 * (Quaterniond.Y() * Quaterniond.Z() - Quaterniond.W() * Quaterniond.X()));

  Vec3d u = Vec3d( 1.0 - 2.0 * (Quaterniond.Y() * Quaterniond.Y() + Quaterniond.Z() * Quaterniond.Z()),
                          2.0 * (Quaterniond.X() * Quaterniond.Y() - Quaterniond.W() * Quaterniond.Z()),
                          2.0 * (Quaterniond.X() * Quaterniond.Z() + Quaterniond.W() * Quaterniond.Y()));

  return Rotation( n, v, u );
}

Mat4d&
Mat4d::Rotation( const Vec3d& forward, const Vec3d& up )
{
  Vec3d n = forward.Normalize();
  Vec3d u = Vec3d( up.Normalize() ).Cross( n );
  Vec3d v = n.Cross(u);

  m_Values[ 0 ][ 0 ] = u.X(); m_Values[ 0 ][ 1 ] = u.Y(); m_Values[ 0 ][ 2 ] = u.Z(); m_Values[ 0 ][ 3 ] = 0.0;
  m_Values[ 1 ][ 0 ] = v.X(); m_Values[ 1 ][ 1 ] = v.Y(); m_Values[ 1 ][ 2 ] = v.Z(); m_Values[ 1 ][ 3 ] = 0.0;
  m_Values[ 2 ][ 0 ] = n.X(); m_Values[ 2 ][ 1 ] = n.Y(); m_Values[ 2 ][ 2 ] = n.Z(); m_Values[ 2 ][ 3 ] = 0.0;
  m_Values[ 3 ][ 0 ] = 0.0;  m_Values[ 3 ][ 1 ] = 0.0;  m_Values[ 3 ][ 2 ] = 0.0;  m_Values[ 3 ][ 3 ] = 1.0;

  return *this;
}

Mat4d&
Mat4d::Rotation( const double x, const double y, const double z )
{
  Mat4d rx, ry, rz;

  rx.m_Values[0][0] = 1.0;     rx.m_Values[1][0] = 0.0     ; rx.m_Values[2][0] =  0.0     ; rx.m_Values[3][0] = 0.0;
  rx.m_Values[0][1] = 0.0;     rx.m_Values[1][1] = cosf( x ); rx.m_Values[2][1] = -sinf( x ); rx.m_Values[3][1] = 0.0;
  rx.m_Values[0][2] = 0.0;     rx.m_Values[1][2] = sinf( x ); rx.m_Values[2][2] =  cosf( x ); rx.m_Values[3][2] = 0.0;
  rx.m_Values[0][3] = 0.0;     rx.m_Values[1][3] = 0.0     ; rx.m_Values[2][3] =  0.0     ; rx.m_Values[3][3] = 1.0;

  ry.m_Values[0][0] = cosf( y ); ry.m_Values[1][0] = 0.0;     ry.m_Values[2][0] = -sinf( y ); ry.m_Values[3][0] = 0.0;
  ry.m_Values[0][1] = 0.0     ; ry.m_Values[1][1] = 1.0;     ry.m_Values[2][1] =  0.0     ; ry.m_Values[3][1] = 0.0;
  ry.m_Values[0][2] = sinf( y ); ry.m_Values[1][2] = 0.0;     ry.m_Values[2][2] =  cosf( y ); ry.m_Values[3][2] = 0.0;
  ry.m_Values[0][3] = 0.0     ; ry.m_Values[1][3] = 0.0;     ry.m_Values[2][3] =  0.0     ; ry.m_Values[3][3] = 1.0;

  rz.m_Values[0][0] = cosf( z ); rz.m_Values[1][0] = -sinf( z ); rz.m_Values[2][0] = 0.0;     rz.m_Values[3][0] = 0.0;
  rz.m_Values[0][1] = sinf( z ); rz.m_Values[1][1] =  cosf( z ); rz.m_Values[2][1] = 0.0;     rz.m_Values[3][1] = 0.0;
  rz.m_Values[0][2] = 0.0     ; rz.m_Values[1][2] =  0.0     ; rz.m_Values[2][2] = 1.0;     rz.m_Values[3][2] = 0.0;
  rz.m_Values[0][3] = 0.0     ; rz.m_Values[1][3] =  0.0     ; rz.m_Values[2][3] = 0.0;     rz.m_Values[3][3] = 1.0;

  *this = rz * ry * rx;

  return *this;
}

Mat4d&
Mat4d::Rotation( const Vec3d& n, const Vec3d& v, const Vec3d& u )
{
  m_Values[ 0 ][ 0 ] = u.X(); m_Values[ 0 ][ 1 ] = u.Y(); m_Values[ 0 ][ 2 ] = u.Z(); m_Values[ 0 ][ 3 ] = 0.0;
  m_Values[ 1 ][ 0 ] = v.X(); m_Values[ 1 ][ 1 ] = v.Y(); m_Values[ 1 ][ 2 ] = v.Z(); m_Values[ 1 ][ 3 ] = 0.0;
  m_Values[ 2 ][ 0 ] = n.X(); m_Values[ 2 ][ 1 ] = n.Y(); m_Values[ 2 ][ 2 ] = n.Z(); m_Values[ 2 ][ 3 ] = 0.0;
  m_Values[ 3 ][ 0 ] = 0.0;  m_Values[ 3 ][ 1 ] = 0.0;  m_Values[ 3 ][ 2 ] = 0.0;  m_Values[ 3 ][ 3 ] = 1.0;

  return *this;
}

Vec3d
Mat4d::Transformation( const Vec3d& vector ) const
{
  return ( Transformation( Quaterniond( vector ) ) ).XYZ();
}

Quaterniond
Mat4d::Transformation( const Quaterniond& vector ) const
{
  Quaterniond result( 0, 0, 0, 0 );

  for( unsigned int i = 0; i < 4; i++ )
    for( unsigned int j = 0; j < 4; j++ )
      result[ i ] += m_Values[ j ][ i ] * vector[ j ];

  return result;
}

Mat4d
Mat4d::Inverse( void ) const
{
  Mat4d result;

  double         inv[ 16 ], det;
  const double * m = *m_Values;

  inv[ 0 ] = m[ 5 ]  * m[ 10 ] * m[ 15 ] -
             m[ 5 ]  * m[ 11 ] * m[ 14 ] -
             m[ 9 ]  * m[ 6 ]  * m[ 15 ] +
             m[ 9 ]  * m[ 7 ]  * m[ 14 ] +
             m[ 13 ] * m[ 6 ]  * m[ 11 ] -
             m[ 13 ] * m[ 7 ]  * m[ 10 ];

  inv[ 4 ] = -m[ 4 ]  * m[ 10 ] * m[ 15 ] +
              m[ 4 ]  * m[ 11 ] * m[ 14 ] +
              m[ 8 ]  * m[ 6 ]  * m[ 15 ] -
              m[ 8 ]  * m[ 7 ]  * m[ 14 ] -
              m[ 12 ] * m[ 6 ]  * m[ 11 ] +
              m[ 12 ] * m[ 7 ]  * m[ 10 ];

  inv[ 8 ] = m[ 4 ]  * m[ 9 ] * m[ 15 ] -
             m[ 4 ]  * m[ 11 ] * m[ 13 ] -
             m[ 8 ]  * m[ 5 ] * m[ 15 ] +
             m[ 8 ]  * m[ 7 ] * m[ 13 ] +
             m[ 12 ] * m[ 5 ] * m[ 11 ] -
             m[ 12 ] * m[ 7 ] * m[ 9 ];

  inv[ 12 ] = -m[ 4 ]  * m[ 9 ] * m[ 14 ] +
               m[ 4 ]  * m[ 10 ] * m[ 13 ] +
               m[ 8 ]  * m[ 5 ] * m[ 14 ] -
               m[ 8 ]  * m[ 6 ] * m[ 13 ] -
               m[ 12 ] * m[ 5 ] * m[ 10 ] +
               m[ 12 ] * m[ 6 ] * m[ 9 ];

  inv[ 1 ] = -m[ 1 ]  * m[ 10 ] * m[ 15 ] +
              m[ 1 ]  * m[ 11 ] * m[ 14 ] +
              m[ 9 ]  * m[ 2 ] * m[ 15 ] -
              m[ 9 ]  * m[ 3 ] * m[ 14 ] -
              m[ 13 ] * m[ 2 ] * m[ 11 ] +
              m[ 13 ] * m[ 3 ] * m[ 10 ];

  inv[ 5 ] = m[ 0 ]  * m[ 10 ] * m[ 15 ] -
             m[ 0 ]  * m[ 11 ] * m[ 14 ] -
             m[ 8 ]  * m[ 2 ] * m[ 15 ] +
             m[ 8 ]  * m[ 3 ] * m[ 14 ] +
             m[ 12 ] * m[ 2 ] * m[ 11 ] -
             m[ 12 ] * m[ 3 ] * m[ 10 ];

  inv[ 9 ] = -m[ 0 ]  * m[ 9 ] * m[ 15 ] +
              m[ 0 ]  * m[ 11 ] * m[ 13 ] +
              m[ 8 ]  * m[ 1 ] * m[ 15 ] -
              m[ 8 ]  * m[ 3 ] * m[ 13 ] -
              m[ 12 ] * m[ 1 ] * m[ 11 ] +
              m[ 12 ] * m[ 3 ] * m[ 9 ];

  inv[ 13 ] = m[ 0 ]  * m[ 9 ] * m[ 14 ] -
              m[ 0 ]  * m[ 10 ] * m[ 13 ] -
              m[ 8 ]  * m[ 1 ] * m[ 14 ] +
              m[ 8 ]  * m[ 2 ] * m[ 13 ] +
              m[ 12 ] * m[ 1 ] * m[ 10 ] -
              m[ 12 ] * m[ 2 ] * m[ 9 ];

  inv[ 2 ] = m[ 1 ]  * m[ 6 ] * m[ 15 ] -
             m[ 1 ]  * m[ 7 ] * m[ 14 ] -
             m[ 5 ]  * m[ 2 ] * m[ 15 ] +
             m[ 5 ]  * m[ 3 ] * m[ 14 ] +
             m[ 13 ] * m[ 2 ] * m[ 7 ] -
             m[ 13 ] * m[ 3 ] * m[ 6 ];

  inv[ 6 ] = -m[ 0 ]  * m[ 6 ] * m[ 15 ] +
              m[ 0 ]  * m[ 7 ] * m[ 14 ] +
              m[ 4 ]  * m[ 2 ] * m[ 15 ] -
              m[ 4 ]  * m[ 3 ] * m[ 14 ] -
              m[ 12 ] * m[ 2 ] * m[ 7 ] +
              m[ 12 ] * m[ 3 ] * m[ 6 ];

  inv[ 10 ] = m[ 0 ]  * m[ 5 ] * m[ 15 ] -
              m[ 0 ]  * m[ 7 ] * m[ 13 ] -
              m[ 4 ]  * m[ 1 ] * m[ 15 ] +
              m[ 4 ]  * m[ 3 ] * m[ 13 ] +
              m[ 12 ] * m[ 1 ] * m[ 7 ] -
              m[ 12 ] * m[ 3 ] * m[ 5 ];

  inv[ 14 ] = -m[ 0 ]  * m[ 5 ] * m[ 14 ] +
               m[ 0 ]  * m[ 6 ] * m[ 13 ] +
               m[ 4 ]  * m[ 1 ] * m[ 14 ] -
               m[ 4 ]  * m[ 2 ] * m[ 13 ] -
               m[ 12 ] * m[ 1 ] * m[ 6 ] +
               m[ 12 ] * m[ 2 ] * m[ 5 ];

  inv[ 3 ] = -m[ 1 ] * m[ 6 ] * m[ 11 ] +
              m[ 1 ] * m[ 7 ] * m[ 10 ] +
              m[ 5 ] * m[ 2 ] * m[ 11 ] -
              m[ 5 ] * m[ 3 ] * m[ 10 ] -
              m[ 9 ] * m[ 2 ] * m[ 7 ] +
              m[ 9 ] * m[ 3 ] * m[ 6 ];

  inv[ 7 ] = m[ 0 ] * m[ 6 ] * m[ 11 ] -
             m[ 0 ] * m[ 7 ] * m[ 10 ] -
             m[ 4 ] * m[ 2 ] * m[ 11 ] +
             m[ 4 ] * m[ 3 ] * m[ 10 ] +
             m[ 8 ] * m[ 2 ] * m[ 7 ] -
             m[ 8 ] * m[ 3 ] * m[ 6 ];

  inv[ 11 ] = -m[ 0 ] * m[ 5 ] * m[ 11 ] +
               m[ 0 ] * m[ 7 ] * m[ 9 ] +
               m[ 4 ] * m[ 1 ] * m[ 11 ] -
               m[ 4 ] * m[ 3 ] * m[ 9 ] -
               m[ 8 ] * m[ 1 ] * m[ 7 ] +
               m[ 8 ] * m[ 3 ] * m[ 5 ];

  inv[ 15 ] = m[ 0 ] * m[ 5 ] * m[ 10 ] -
              m[ 0 ] * m[ 6 ] * m[ 9 ] -
              m[ 4 ] * m[ 1 ] * m[ 10 ] +
              m[ 4 ] * m[ 2 ] * m[ 9 ] +
              m[ 8 ] * m[ 1 ] * m[ 6 ] -
              m[ 8 ] * m[ 2 ] * m[ 5 ];

  det = m[ 0 ] * inv[ 0 ] + m[ 1 ] * inv[ 4 ] + m[ 2 ] * inv[ 8 ] + m[ 3 ] * inv[ 12 ];

  if ( det == 0 ) return *this;

  det = 1.0 / det;

  result.Set( 0, 0, inv[ 0 ]  * det );
  result.Set( 0, 1, inv[ 1 ]  * det );
  result.Set( 0, 2, inv[ 2 ]  * det );
  result.Set( 0, 3, inv[ 3 ]  * det );
  result.Set( 1, 0, inv[ 4 ]  * det );
  result.Set( 1, 1, inv[ 5 ]  * det );
  result.Set( 1, 2, inv[ 6 ]  * det );
  result.Set( 1, 3, inv[ 7 ]  * det );
  result.Set( 2, 0, inv[ 8 ]  * det );
  result.Set( 2, 1, inv[ 9 ]  * det );
  result.Set( 2, 2, inv[ 10 ] * det );
  result.Set( 2, 3, inv[ 11 ] * det );
  result.Set( 3, 0, inv[ 12 ] * det );
  result.Set( 3, 1, inv[ 13 ] * det );
  result.Set( 3, 2, inv[ 14 ] * det );
  result.Set( 3, 3, inv[ 15 ] * det );

  return result;
}

Mat4d
Mat4d::Transpose( void ) const
{
  Mat4d result;

  result.m_Values[ 0 ][ 1 ] = m_Values[ 1 ][ 0 ];
  result.m_Values[ 0 ][ 2 ] = m_Values[ 2 ][ 0 ];
  result.m_Values[ 0 ][ 3 ] = m_Values[ 3 ][ 0 ];
  result.m_Values[ 1 ][ 0 ] = m_Values[ 0 ][ 1 ];
  result.m_Values[ 1 ][ 2 ] = m_Values[ 2 ][ 1 ];
  result.m_Values[ 1 ][ 3 ] = m_Values[ 3 ][ 1 ];
  result.m_Values[ 2 ][ 0 ] = m_Values[ 0 ][ 2 ];
  result.m_Values[ 2 ][ 1 ] = m_Values[ 1 ][ 2 ];
  result.m_Values[ 2 ][ 3 ] = m_Values[ 3 ][ 2 ];
  result.m_Values[ 3 ][ 0 ] = m_Values[ 0 ][ 3 ];
  result.m_Values[ 3 ][ 1 ] = m_Values[ 1 ][ 3 ];
  result.m_Values[ 3 ][ 2 ] = m_Values[ 2 ][ 3 ];

  return result;
}


Mat4d&
Mat4d::Translation( const double& x, const double& y, const double& z )
{
  m_Values[ 0 ][ 0 ] = 1.0; m_Values[ 0 ][ 1 ] = 0.0; m_Values[ 0 ][ 2 ] = 0.0; m_Values[ 0 ][ 3 ] = x;
  m_Values[ 1 ][ 0 ] = 0.0; m_Values[ 1 ][ 1 ] = 1.0; m_Values[ 1 ][ 2 ] = 0.0; m_Values[ 1 ][ 3 ] = y;
  m_Values[ 2 ][ 0 ] = 0.0; m_Values[ 2 ][ 1 ] = 0.0; m_Values[ 2 ][ 2 ] = 1.0; m_Values[ 2 ][ 3 ] = z;
  m_Values[ 3 ][ 0 ] = 0.0; m_Values[ 3 ][ 1 ] = 0.0; m_Values[ 3 ][ 2 ] = 0.0; m_Values[ 3 ][ 3 ] = 1.0;

  return *this;
}

Mat4d&
Mat4d::Translation( const Vec3d& t )
{
  return Translation( t[ 0 ], t[ 1 ], t[ 2 ] );
}

double cotf( double value )
{
  return tanf( M_PI_2 - value );
}

Mat4d&
Mat4d::Perspective( const double FoV, const double Aspect, const double zNear, const double zFar )
{
  const double f   = cotf( DEG2RAD( FoV ) / 2.0 );
  const double tz  = -( zFar - zNear ) / ( zNear - zFar );
  const double z   = ( 2.0 * zFar * zNear ) / ( zNear - zFar );

  m_Values[0][0] = f * Aspect;  m_Values[0][1] = 0.0; m_Values[0][2] =  0.0; m_Values[0][3] = 0.0;
  m_Values[1][0] = 0.0;        m_Values[1][1] = f;    m_Values[1][2] =  0.0; m_Values[1][3] = 0.0;
  m_Values[2][0] = 0.0;        m_Values[2][1] = 0.0; m_Values[2][2] =  tz;   m_Values[2][3] = z;
  m_Values[3][0] = 0.0;        m_Values[3][1] = 0.0; m_Values[3][2] = 1.0; m_Values[3][3] = 0.0;

  return *this;
}

Mat4d&
Mat4d::Orthographic( const double Left, const double Right,
                     const double Bottom, const double Top,
                     const double zNear, const double zFar )
{
  if ( zNear >= zFar ) throw "ERROR: zNear must be less than zFar.";

  const double width   = Right - Left;
  const double height  = Top - Bottom;
  const double depth   = zFar - zNear;

  m_Values[0][0] = 2.0 / width; m_Values[0][1] = 0.0;          m_Values[0][2] =  0.0;         m_Values[0][3] = -( ( Right + Left ) / width );
  m_Values[1][0] = 0.0;         m_Values[1][1] = 2.0 / height; m_Values[1][2] =  0.0;         m_Values[1][3] = -( ( Top + Bottom ) / height );
  m_Values[2][0] = 0.0;         m_Values[2][1] = 0.0;          m_Values[2][2] = -2.0 / depth; m_Values[2][3] = -( ( zFar + zNear ) / depth );
  m_Values[3][0] = 0.0;         m_Values[3][1] = 0.0;          m_Values[3][2] =  0.0;         m_Values[3][3] =  1.0;

  return *this;
}

Mat4d
Mat4d::operator *( const Mat4d& factor ) const
{
  Mat4d result;

  for ( unsigned int row = 0 ; row < 4 ; row++ )
    for ( unsigned int col = 0 ; col < 4; col++ )
      result.m_Values[ row ][ col ] = m_Values[ row ][ 0 ] * factor.m_Values[ 0 ][ col ] +
                                      m_Values[ row ][ 1 ] * factor.m_Values[ 1 ][ col ] +
                                      m_Values[ row ][ 2 ] * factor.m_Values[ 2 ][ col ] +
                                      m_Values[ row ][ 3 ] * factor.m_Values[ 3 ][ col ];

  return result;
}

Quaterniond
Mat4d::operator *( const Quaterniond& q ) const
{
  return Quaterniond(
    m_Values[0][0] * q.X() + m_Values[0][1] * q.Y() + m_Values[0][2] * q.Z() + m_Values[0][3] * q.W(),
    m_Values[1][0] * q.X() + m_Values[1][1] * q.Y() + m_Values[1][2] * q.Z() + m_Values[1][3] * q.W(),
    m_Values[2][0] * q.X() + m_Values[2][1] * q.Y() + m_Values[2][2] * q.Z() + m_Values[2][3] * q.W(),
    m_Values[3][0] * q.X() + m_Values[3][1] * q.Y() + m_Values[3][2] * q.Z() + m_Values[3][3] * q.W()
  );
}

double*
Mat4d::operator []( unsigned int row )
{
  return m_Values[ row ];
}

const double*
Mat4d::operator []( unsigned int row ) const
{
  return m_Values[ row ];
}

const double*
Mat4d::Values( void ) const
{
  return *m_Values;
}

void
Mat4d::Set( const unsigned int row, const unsigned int col, const double& value )
{
  m_Values[ row ][ col ] = value;
}

void
Mat4d::Print( void ) const
{
  printf( "( %f | %f | %f | %f )\n", m_Values[ 0 ][ 0 ], m_Values[ 0 ][ 1 ], m_Values[ 0 ][ 2 ], m_Values[ 0 ][ 3 ] );
  printf( "( %f | %f | %f | %f )\n", m_Values[ 1 ][ 0 ], m_Values[ 1 ][ 1 ], m_Values[ 1 ][ 2 ], m_Values[ 1 ][ 3 ] );
  printf( "( %f | %f | %f | %f )\n", m_Values[ 2 ][ 0 ], m_Values[ 2 ][ 1 ], m_Values[ 2 ][ 2 ], m_Values[ 2 ][ 3 ] );
  printf( "( %f | %f | %f | %f )\n", m_Values[ 3 ][ 0 ], m_Values[ 3 ][ 1 ], m_Values[ 3 ][ 2 ], m_Values[ 3 ][ 3 ] );
}
