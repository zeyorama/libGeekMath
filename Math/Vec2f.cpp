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

\file Vec2f.cpp

Created on: Feb 18, 2015
\author     fkzey
*/
#include "Vec2f.h"

#include <cmath>
#include <cstdio>
#include <cstring>

Vec2f::Vec2f( void )
{
  m_Values[ 0 ] = 0.0f;
  m_Values[ 1 ] = 0.0f;
}

Vec2f::Vec2f( const float value )
{
  m_Values[ 0 ] = value;
  m_Values[ 1 ] = value;
}

Vec2f::Vec2f( const Vec2f& other )
{
  m_Values[ 0 ] = other.m_Values[ 0 ];
  m_Values[ 1 ] = other.m_Values[ 1 ];
}

Vec2f::Vec2f( const float x, const float y )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
}

Vec2f::~Vec2f( void ) { return; }

void
Vec2f::Set( const float& x, const float& y )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
}

void
Vec2f::X( const float& x )
{
  m_Values[ 0 ] = x;
}

void
Vec2f::Y( const float& y )
{
  m_Values[ 1 ] = y;
}

float
Vec2f::LengthSq( void ) const
{
  return m_Values[ 0 ] * m_Values[ 0 ] + m_Values[ 1 ] * m_Values[ 1 ];
}

float
Vec2f::Length( void ) const
{
  return sqrtf( LengthSq() );
}

float
Vec2f::Dot( const Vec2f& other ) const
{
  return  m_Values[ 0 ] * other.m_Values[ 0 ] +
          m_Values[ 1 ] * other.m_Values[ 1 ];
}

float
Vec2f::Max( void ) const
{
  return m_Values[ 0 ] > m_Values[ 1 ] ? m_Values[ 0 ] : m_Values[ 1 ];
}

float
Vec2f::Min( void ) const
{
  return m_Values[ 0 ] < m_Values[ 1 ] ? m_Values[ 0 ] : m_Values[ 1 ];
}

Vec2f
Vec2f::Clamp( const Vec2f& Min, const Vec2f& Max )
{
  Vec2f result;

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

Vec2f
Vec2f::Normalize( void ) const
{
  float length = Length();

  return (*this)/length;
}

Vec2f
Vec2f::Reflect( const Vec2f& normal ) const
{
  return (*this) - ( normal * ( Dot( normal ) * 2 ) );
}

Vec2f
Vec2f::Lerp( const Vec2f& Destination, float LerpFactor ) const
{
  return ( Destination - ( *this ) ) * LerpFactor + ( *this );
}

Vec2f
Vec2f::Max( const Vec2f& vector ) const
{
  return Vec2f(
      m_Values[ 0 ] > vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] > vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ]
  );
}

Vec2f
Vec2f::Min( const Vec2f& vector ) const
{
  return Vec2f(
      m_Values[ 0 ] < vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] < vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ]
  );
}

Vec2f
Vec2f::operator +( const float summand ) const
{
  return Vec2f( m_Values[ 0 ] + summand, m_Values[ 1 ] + summand );
}

Vec2f
Vec2f::operator +( const Vec2f& summand ) const
{
  return Vec2f( m_Values[ 0 ] + summand.m_Values[ 0 ],
                m_Values[ 1 ] + summand.m_Values[ 1 ] );
}

Vec2f
Vec2f::operator -( const float subtrahend ) const
{
  return Vec2f( m_Values[ 0 ] - subtrahend, m_Values[ 1 ] - subtrahend );
}

Vec2f
Vec2f::operator -( const Vec2f& subtrahend ) const
{
  return Vec2f( m_Values[ 0 ] - subtrahend.m_Values[ 0 ],
                m_Values[ 1 ] - subtrahend.m_Values[ 1 ] );
}

Vec2f
Vec2f::operator *( const float factor ) const
{
  return Vec2f( m_Values[ 0 ] * factor, m_Values[ 1 ] * factor );
}

Vec2f
Vec2f::operator *( const Vec2f& factor ) const
{
  return Vec2f( m_Values[ 0 ] * factor.m_Values[ 0 ],
                m_Values[ 1 ] * factor.m_Values[ 1 ] );
}

Vec2f
Vec2f::operator /( const float dividend ) const
{
  if ( dividend == 0.0f ) return Vec2f();

  return Vec2f( m_Values[ 0 ] / dividend, m_Values[ 1 ] / dividend );
}

Vec2f&
Vec2f::operator +=( const float summand )
{
  m_Values[ 0 ] += summand;
  m_Values[ 1 ] += summand;

  return *this;
}

Vec2f&
Vec2f::operator +=( const Vec2f& summand )
{
  m_Values[ 0 ] += summand.m_Values[ 0 ];
  m_Values[ 1 ] += summand.m_Values[ 1 ];

  return *this;
}
Vec2f&
Vec2f::operator -=( const Vec2f& subtrahend )
{
  m_Values[ 0 ] -= subtrahend.m_Values[ 0 ];
  m_Values[ 1 ] -= subtrahend.m_Values[ 1 ];

  return *this;
}

Vec2f&
Vec2f::operator -=( const float subtrahend )
{
  m_Values[ 0 ] -= subtrahend;
  m_Values[ 1 ] -= subtrahend;

  return *this;
}

Vec2f&
Vec2f::operator *=( const float factor )
{
  m_Values[ 0 ] *= factor;
  m_Values[ 1 ] *= factor;

  return *this;
}

Vec2f&
Vec2f::operator *=( const Vec2f& factor )
{
  m_Values[ 0 ] *= factor.m_Values[ 0 ];
  m_Values[ 1 ] *= factor.m_Values[ 1 ];

  return *this;
}

Vec2f&
Vec2f::operator /=( const float dividend )
{
  if ( dividend == 0.0f ) return *this;

  m_Values[ 0 ] /= dividend;
  m_Values[ 1 ] /= dividend;

  return *this;
}

bool
Vec2f::operator ==( const Vec2f& expr ) const
{
  return  m_Values[ 0 ] == expr.m_Values[ 0 ] &&
          m_Values[ 1 ] == expr.m_Values[ 1 ];
}

bool
Vec2f::operator !=( const Vec2f& expr ) const
{
  return  m_Values[ 0 ] != expr.m_Values[ 0 ] ||
          m_Values[ 1 ] != expr.m_Values[ 1 ];
}

float&
Vec2f::operator []( unsigned int i )
{
  return m_Values[ i ];
}

float
Vec2f::operator []( unsigned int i ) const
{
  return m_Values[ i ];
}

float
Vec2f::X( void ) const
{
  return m_Values[ 0 ];
}

float
Vec2f::Y( void ) const
{
  return m_Values[ 1 ];
}

Vec2f
Vec2f::XX( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2f
Vec2f::XY( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 1 ] );
}

Vec2f
Vec2f::YX( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 0 ] );
}

Vec2f
Vec2f::YY( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 1 ] );
}

void
Vec2f::Print( void ) const
{
  printf( "( %f | %f )\n", m_Values[ 0 ], m_Values[ 1 ] );
}

const float*
Vec2f::Values( void ) const
{
  return m_Values;
}
