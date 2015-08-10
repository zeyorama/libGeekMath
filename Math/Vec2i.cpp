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

\file Vec2i.cpp

Created on: Feb 18, 2015
\author     fkzey
*/
#include "Vec2i.hpp"

#include <cmath>
#include <cstdio>
#include <cstring>

Vec2i::Vec2i( void )
{
  m_Values[ 0 ] = 0;
  m_Values[ 1 ] = 0;
}

Vec2i::Vec2i( const int value )
{
  m_Values[ 0 ] = value;
  m_Values[ 1 ] = value;
}

Vec2i::Vec2i( const Vec2i& other )
{
  m_Values[ 0 ] = other.m_Values[ 0 ];
  m_Values[ 1 ] = other.m_Values[ 1 ];
}

Vec2i::Vec2i( const int x, const int y )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
}

Vec2i::~Vec2i( void ) { return; }

void
Vec2i::Set( const int& x, const int& y )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
}

void
Vec2i::X( const int& x )
{
  m_Values[ 0 ] = x;
}

void
Vec2i::Y( const int& y )
{
  m_Values[ 1 ] = y;
}

int
Vec2i::LengthSq( void ) const
{
  return m_Values[ 0 ] * m_Values[ 0 ] + m_Values[ 1 ] * m_Values[ 1 ];
}

int
Vec2i::Length( void ) const
{
  return sqrtf( LengthSq() );
}

int
Vec2i::Dot( const Vec2i& other ) const
{
  return  m_Values[ 0 ] * other.m_Values[ 0 ] +
          m_Values[ 1 ] * other.m_Values[ 1 ];
}

int
Vec2i::Max( void ) const
{
  return m_Values[ 0 ] > m_Values[ 1 ] ? m_Values[ 0 ] : m_Values[ 1 ];
}

int
Vec2i::Min( void ) const
{
  return m_Values[ 0 ] < m_Values[ 1 ] ? m_Values[ 0 ] : m_Values[ 1 ];
}

Vec2i
Vec2i::Clamp( const Vec2i& Min, const Vec2i& Max )
{
  Vec2i result;

  if      ( m_Values[ 0 ] < Min.m_Values[ 0 ] )
    result.m_Values[ 0 ] = Min.m_Values[ 0 ];
  else if ( m_Values[ 0 ] > Max.m_Values[ 0 ] )
    result.m_Values[ 0 ] = Max.m_Values[ 0 ];
  else
    result.m_Values[ 0 ] = m_Values[ 0 ];

  if      ( m_Values[ 1 ] < Min.m_Values[ 1 ] )
    result.m_Values[ 1 ] = Min.m_Values[ 1 ];
  else if ( m_Values[ 1 ] > Max.m_Values[ 1 ] )
    result.m_Values[ 1 ] = Max.m_Values[ 1 ];
  else
    result.m_Values[ 1 ] = m_Values[ 1 ];

  return result;
}

Vec2i
Vec2i::Normalize( void ) const
{
  float length = Length();

  return (*this)/length;
}

Vec2i
Vec2i::Max( const Vec2i& vector ) const
{
  return Vec2i(
      m_Values[ 0 ] > vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] > vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ]
  );
}

Vec2i
Vec2i::Min( const Vec2i& vector ) const
{
  return Vec2i(
      m_Values[ 0 ] < vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] < vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ]
  );
}

Vec2i
Vec2i::operator +( const int summand ) const
{
  return Vec2i( m_Values[ 0 ] + summand, m_Values[ 1 ] + summand );
}

Vec2i
Vec2i::operator +( const Vec2i& summand ) const
{
  return Vec2i( m_Values[ 0 ] + summand.m_Values[ 0 ],
                m_Values[ 1 ] + summand.m_Values[ 1 ] );
}

Vec2i
Vec2i::operator -( const int subtrahend ) const
{
  return Vec2i( m_Values[ 0 ] - subtrahend, m_Values[ 1 ] - subtrahend );
}

Vec2i
Vec2i::operator -( const Vec2i& subtrahend ) const
{
  return Vec2i( m_Values[ 0 ] - subtrahend.m_Values[ 0 ],
                m_Values[ 1 ] - subtrahend.m_Values[ 1 ] );
}

Vec2i
Vec2i::operator *( const int factor ) const
{
  return Vec2i( m_Values[ 0 ] * factor, m_Values[ 1 ] * factor );
}

Vec2i
Vec2i::operator *( const Vec2i& factor ) const
{
  return Vec2i( m_Values[ 0 ] * factor.m_Values[ 0 ],
                m_Values[ 1 ] * factor.m_Values[ 1 ] );
}

Vec2i
Vec2i::operator /( const int dividend ) const
{
  if ( dividend == 0 ) return Vec2i();

  return Vec2i( m_Values[ 0 ] / dividend, m_Values[ 1 ] / dividend );
}

Vec2i
Vec2i::operator /( const float dividend ) const
{
  if ( dividend == 0.0f ) return Vec2i();

  return Vec2i( (float)m_Values[ 0 ] / dividend, (float)m_Values[ 1 ] / dividend );
}

Vec2i&
Vec2i::operator +=( const int summand )
{
  m_Values[ 0 ] += summand;
  m_Values[ 1 ] += summand;

  return *this;
}

Vec2i&
Vec2i::operator +=( const Vec2i& summand )
{
  m_Values[ 0 ] += summand.m_Values[ 0 ];
  m_Values[ 1 ] += summand.m_Values[ 1 ];

  return *this;
}
Vec2i&
Vec2i::operator -=( const Vec2i& subtrahend )
{
  m_Values[ 0 ] -= subtrahend.m_Values[ 0 ];
  m_Values[ 1 ] -= subtrahend.m_Values[ 1 ];

  return *this;
}

Vec2i&
Vec2i::operator -=( const int subtrahend )
{
  m_Values[ 0 ] -= subtrahend;
  m_Values[ 1 ] -= subtrahend;

  return *this;
}

Vec2i&
Vec2i::operator *=( const int factor )
{
  m_Values[ 0 ] *= factor;
  m_Values[ 1 ] *= factor;

  return *this;
}

Vec2i&
Vec2i::operator *=( const Vec2i& factor )
{
  m_Values[ 0 ] *= factor.m_Values[ 0 ];
  m_Values[ 1 ] *= factor.m_Values[ 1 ];

  return *this;
}

Vec2i&
Vec2i::operator /=( const int dividend )
{
  if ( dividend == 0 ) return *this;

  m_Values[ 0 ] /= dividend;
  m_Values[ 1 ] /= dividend;

  return *this;
}

bool
Vec2i::operator ==( const Vec2i& expr ) const
{
  return  m_Values[ 0 ] == expr.m_Values[ 0 ] &&
          m_Values[ 1 ] == expr.m_Values[ 1 ];
}

bool
Vec2i::operator !=( const Vec2i& expr ) const
{
  return  m_Values[ 0 ] != expr.m_Values[ 0 ] ||
          m_Values[ 1 ] != expr.m_Values[ 1 ];
}

int&
Vec2i::operator []( unsigned int i )
{
  return m_Values[ i ];
}

int
Vec2i::operator []( unsigned int i ) const
{
  return m_Values[ i ];
}

int
Vec2i::X( void ) const
{
  return m_Values[ 0 ];
}

int
Vec2i::Y( void ) const
{
  return m_Values[ 1 ];
}

Vec2i
Vec2i::XX( void ) const
{
  return Vec2i( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2i
Vec2i::XY( void ) const
{
  return Vec2i( m_Values[ 0 ], m_Values[ 1 ] );
}

Vec2i
Vec2i::YX( void ) const
{
  return Vec2i( m_Values[ 1 ], m_Values[ 0 ] );
}

Vec2i
Vec2i::YY( void ) const
{
  return Vec2i( m_Values[ 1 ], m_Values[ 1 ] );
}

void
Vec2i::Print( void ) const
{
  printf( "( %i | %i )\n", m_Values[ 0 ], m_Values[ 1 ] );
}

const int*
Vec2i::Values( void ) const
{
  return m_Values;
}
