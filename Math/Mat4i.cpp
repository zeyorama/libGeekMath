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

 \file Mat4i.cpp

 Created on: Feb 19, 2015
 \author     fkzey
 */

#include "Mat4i.hpp"

#include <cstdio>
#include <cstring>

static const unsigned int MATRIX_SIZE = sizeof( int ) * 16;

Mat4i::Mat4i( void )
{
  memset( m_Values, 0, MATRIX_SIZE );
}

Mat4i::Mat4i( const Mat4i& matrix )
{
  memcpy( m_Values, matrix.m_Values, MATRIX_SIZE );
}

Mat4i::~Mat4i( void ) { return; }

Mat4i
Mat4i::Identity( void )
{
  memset( m_Values, 0, MATRIX_SIZE );

  m_Values[ 0 ][ 0 ] = 1;
  m_Values[ 1 ][ 1 ] = 1;
  m_Values[ 2 ][ 2 ] = 1;
  m_Values[ 3 ][ 3 ] = 1;

  return *this;
}

Mat4i
Mat4i::Translation( const int& x, const int& y, const int& z )
{
  Identity();

  m_Values[ 0 ][ 3 ] = x;
  m_Values[ 1 ][ 3 ] = y;
  m_Values[ 2 ][ 3 ] = z;

  return *this;
}

Mat4i
Mat4i::Inverse( void ) const
{
  Mat4i result;

  int         inv[ 16 ], det;
  const int * m = *m_Values;

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

Mat4i
Mat4i::Transpose( void ) const
{
  Mat4i result;

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

Mat4i
Mat4i::operator *( const Mat4i& factor ) const
{
  Mat4i result;

  for ( unsigned int row = 0 ; row < 4 ; row++ )
    for ( unsigned int col = 0 ; col < 4; col++ )
      result.m_Values[ row ][ col ] = m_Values[ row ][ 0 ] * factor.m_Values[ 0 ][ col ] +
                                      m_Values[ row ][ 1 ] * factor.m_Values[ 1 ][ col ] +
                                      m_Values[ row ][ 2 ] * factor.m_Values[ 2 ][ col ] +
                                      m_Values[ row ][ 3 ] * factor.m_Values[ 3 ][ col ];

  return result;
}

Mat4i&
Mat4i::operator *=( const Mat4i& factor )
{
  Mat4i result;

  for ( unsigned int row = 0 ; row < 4 ; row++ )
    for ( unsigned int col = 0 ; col < 4; col++ )
      result.m_Values[ row ][ col ] = m_Values[ row ][ 0 ] * factor.m_Values[ 0 ][ col ] +
                                      m_Values[ row ][ 1 ] * factor.m_Values[ 1 ][ col ] +
                                      m_Values[ row ][ 2 ] * factor.m_Values[ 2 ][ col ] +
                                      m_Values[ row ][ 3 ] * factor.m_Values[ 3 ][ col ];

  memcpy( m_Values, result.m_Values, MATRIX_SIZE );

  return *this;
}

int*
Mat4i::operator []( unsigned int row )
{
  return m_Values[ row ];
}

const int*
Mat4i::operator []( unsigned int row ) const
{
  return m_Values[ row ];
}

const int*
Mat4i::Values( void ) const
{
  return *m_Values;
}

void
Mat4i::Set( const unsigned int row, const unsigned int col, const int& value )
{
  m_Values[ row ][ col ] = value;
}

void
Mat4i::Print( void ) const
{
  printf( "( %i | %i | %i | %i )\n", m_Values[ 0 ][ 0 ], m_Values[ 0 ][ 1 ], m_Values[ 0 ][ 2 ], m_Values[ 0 ][ 3 ] );
  printf( "( %i | %i | %i | %i )\n", m_Values[ 1 ][ 0 ], m_Values[ 1 ][ 1 ], m_Values[ 1 ][ 2 ], m_Values[ 1 ][ 3 ] );
  printf( "( %i | %i | %i | %i )\n", m_Values[ 2 ][ 0 ], m_Values[ 2 ][ 1 ], m_Values[ 2 ][ 2 ], m_Values[ 2 ][ 3 ] );
  printf( "( %i | %i | %i | %i )\n", m_Values[ 3 ][ 0 ], m_Values[ 3 ][ 1 ], m_Values[ 3 ][ 2 ], m_Values[ 3 ][ 3 ] );
}
