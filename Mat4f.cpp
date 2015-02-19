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

 \file Mat4f.cpp

 Created on: Feb 19, 2015
 \author     fkzey
 */

#include "Mat4f.h"

#include "Vec2f.h"
#include "Vec3f.h"
#include "Vec4f.h"

#include <cstdio>

Mat4f::Mat4f( void )
{
  for ( int i = 0; i < 4; i++ )
    for ( int j = 0; j < 4; j++ )
      m_Values[ i ][ j ] = 0.0f;
}

Mat4f::~Mat4f( void ) { return; }

Mat4f
Mat4f::Scale( const Vec3f& scale )
{
  m_Values[ 0 ][ 0 ] = scale.X();
  m_Values[ 1 ][ 1 ] = scale.Y();
  m_Values[ 2 ][ 2 ] = scale.Z();
  m_Values[ 3 ][ 3 ] = 1.0f;

  return *this;
}

Mat4f
Mat4f::Identity( void )
{
  m_Values[ 0 ][ 0 ] = 1.0f;
  m_Values[ 1 ][ 1 ] = 1.0f;
  m_Values[ 2 ][ 2 ] = 1.0f;
  m_Values[ 3 ][ 3 ] = 1.0f;

  return *this;
}

Mat4f
Mat4f::Transpose( void ) const
{
  Mat4f t;

  for (int j = 0; j < 4; j++)
    for (int i = 0; i < 4; i++)
      t.m_Values[i][j] = m_Values[j][i];

  return t;
}

Mat4f
Mat4f::Translation( const Vec3f& translation )
{
  m_Values[ 0 ][ 3 ] = translation.X();
  m_Values[ 1 ][ 3 ] = translation.Y();
  m_Values[ 2 ][ 3 ] = translation.Z();
  m_Values[ 3 ][ 3 ] = 1.0f;

  return *this;
}

float*
Mat4f::Values( void )
{
  return *m_Values;
}

void
Mat4f::Set( const unsigned int row, const unsigned int col, const float value )
{
  m_Values[ row ][ col ] = value;
}

void
Mat4f::Print( void ) const
{
  puts( "Matrix 4x4 float:" );
  printf( "( %f | %f | %f | %f )\n", m_Values[ 0 ][ 0 ], m_Values[ 0 ][ 1 ], m_Values[ 0 ][ 2 ], m_Values[ 0 ][ 3 ] );
  printf( "( %f | %f | %f | %f )\n", m_Values[ 1 ][ 0 ], m_Values[ 1 ][ 1 ], m_Values[ 1 ][ 2 ], m_Values[ 1 ][ 3 ] );
  printf( "( %f | %f | %f | %f )\n", m_Values[ 2 ][ 0 ], m_Values[ 2 ][ 1 ], m_Values[ 2 ][ 2 ], m_Values[ 2 ][ 3 ] );
  printf( "( %f | %f | %f | %f )\n", m_Values[ 3 ][ 0 ], m_Values[ 3 ][ 1 ], m_Values[ 3 ][ 2 ], m_Values[ 3 ][ 3 ] );
}
