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

\file Vec2d.cpp

Created on: Feb 18, 2015
\author     fkzey
*/
#include "Vec2d.hpp"

#include <cmath>
#include <cstdio>
#include <cstring>

Vec2d::Vec2d( void )
{
  m_Values[ 0 ] = 0.0f;
  m_Values[ 1 ] = 0.0f;
}

Vec2d::Vec2d( const double value )
{
  m_Values[ 0 ] = value;
  m_Values[ 1 ] = value;
}

Vec2d::Vec2d( const Vec2d& other )
{
  m_Values[ 0 ] = other.m_Values[ 0 ];
  m_Values[ 1 ] = other.m_Values[ 1 ];
}

Vec2d::Vec2d( const double x, const double y )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
}

Vec2d::~Vec2d( void ) { return; }

void
Vec2d::Set( const double& x, const double& y )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
}

void
Vec2d::X( const double& x )
{
  m_Values[ 0 ] = x;
}

void
Vec2d::Y( const double& y )
{
  m_Values[ 1 ] = y;
}

double
Vec2d::LengthSq( void ) const
{
  return m_Values[ 0 ] * m_Values[ 0 ] + m_Values[ 1 ] * m_Values[ 1 ];
}

double
Vec2d::Length( void ) const
{
  return sqrtf( LengthSq() );
}

double
Vec2d::Dot( const Vec2d& other ) const
{
  return  m_Values[ 0 ] * other.m_Values[ 0 ] +
          m_Values[ 1 ] * other.m_Values[ 1 ];
}

double
Vec2d::Max( void ) const
{
  return m_Values[ 0 ] > m_Values[ 1 ] ? m_Values[ 0 ] : m_Values[ 1 ];
}

double
Vec2d::Min( void ) const
{
  return m_Values[ 0 ] < m_Values[ 1 ] ? m_Values[ 0 ] : m_Values[ 1 ];
}

Vec2d
Vec2d::Clamp( const Vec2d& Min, const Vec2d& Max )
{
  Vec2d result;

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

Vec2d
Vec2d::Normalize( void ) const
{
  double length = Length();

  return (*this)/length;
}

Vec2d
Vec2d::Reflect( const Vec2d& normal ) const
{
  return (*this) - ( normal * ( Dot( normal ) * 2 ) );
}

Vec2d
Vec2d::Lerp( const Vec2d& Destination, double LerpFactor ) const
{
  return ( Destination - ( *this ) ) * LerpFactor + ( *this );
}

Vec2d
Vec2d::Max( const Vec2d& vector ) const
{
  return Vec2d(
      m_Values[ 0 ] > vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] > vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ]
  );
}

Vec2d
Vec2d::Min( const Vec2d& vector ) const
{
  return Vec2d(
      m_Values[ 0 ] < vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] < vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ]
  );
}

Vec2d
Vec2d::operator +( const double summand ) const
{
  return Vec2d( m_Values[ 0 ] + summand, m_Values[ 1 ] + summand );
}

Vec2d
Vec2d::operator +( const Vec2d& summand ) const
{
  return Vec2d( m_Values[ 0 ] + summand.m_Values[ 0 ],
                m_Values[ 1 ] + summand.m_Values[ 1 ] );
}

Vec2d
Vec2d::operator -( const double subtrahend ) const
{
  return Vec2d( m_Values[ 0 ] - subtrahend, m_Values[ 1 ] - subtrahend );
}

Vec2d
Vec2d::operator -( const Vec2d& subtrahend ) const
{
  return Vec2d( m_Values[ 0 ] - subtrahend.m_Values[ 0 ],
                m_Values[ 1 ] - subtrahend.m_Values[ 1 ] );
}

Vec2d
Vec2d::operator *( const double factor ) const
{
  return Vec2d( m_Values[ 0 ] * factor, m_Values[ 1 ] * factor );
}

Vec2d
Vec2d::operator *( const Vec2d& factor ) const
{
  return Vec2d( m_Values[ 0 ] * factor.m_Values[ 0 ],
                m_Values[ 1 ] * factor.m_Values[ 1 ] );
}

Vec2d
Vec2d::operator /( const double dividend ) const
{
  if ( dividend == 0.0f ) return Vec2d();

  return Vec2d( m_Values[ 0 ] / dividend, m_Values[ 1 ] / dividend );
}

Vec2d&
Vec2d::operator +=( const double summand )
{
  m_Values[ 0 ] += summand;
  m_Values[ 1 ] += summand;

  return *this;
}

Vec2d&
Vec2d::operator +=( const Vec2d& summand )
{
  m_Values[ 0 ] += summand.m_Values[ 0 ];
  m_Values[ 1 ] += summand.m_Values[ 1 ];

  return *this;
}
Vec2d&
Vec2d::operator -=( const Vec2d& subtrahend )
{
  m_Values[ 0 ] -= subtrahend.m_Values[ 0 ];
  m_Values[ 1 ] -= subtrahend.m_Values[ 1 ];

  return *this;
}

Vec2d&
Vec2d::operator -=( const double subtrahend )
{
  m_Values[ 0 ] -= subtrahend;
  m_Values[ 1 ] -= subtrahend;

  return *this;
}

Vec2d&
Vec2d::operator *=( const double factor )
{
  m_Values[ 0 ] *= factor;
  m_Values[ 1 ] *= factor;

  return *this;
}

Vec2d&
Vec2d::operator *=( const Vec2d& factor )
{
  m_Values[ 0 ] *= factor.m_Values[ 0 ];
  m_Values[ 1 ] *= factor.m_Values[ 1 ];

  return *this;
}

Vec2d&
Vec2d::operator /=( const double dividend )
{
  if ( dividend == 0.0f ) return *this;

  m_Values[ 0 ] /= dividend;
  m_Values[ 1 ] /= dividend;

  return *this;
}

bool
Vec2d::operator ==( const Vec2d& expr ) const
{
  return  m_Values[ 0 ] == expr.m_Values[ 0 ] &&
          m_Values[ 1 ] == expr.m_Values[ 1 ];
}

bool
Vec2d::operator !=( const Vec2d& expr ) const
{
  return  m_Values[ 0 ] != expr.m_Values[ 0 ] ||
          m_Values[ 1 ] != expr.m_Values[ 1 ];
}

double&
Vec2d::operator []( unsigned int i )
{
  return m_Values[ i ];
}

double
Vec2d::operator []( unsigned int i ) const
{
  return m_Values[ i ];
}

double
Vec2d::X( void ) const
{
  return m_Values[ 0 ];
}

double
Vec2d::Y( void ) const
{
  return m_Values[ 1 ];
}

Vec2d
Vec2d::XX( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2d
Vec2d::XY( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 1 ] );
}

Vec2d
Vec2d::YX( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 0 ] );
}

Vec2d
Vec2d::YY( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 1 ] );
}

void
Vec2d::Print( void ) const
{
  printf( "( %f | %f )\n", m_Values[ 0 ], m_Values[ 1 ] );
}

const double*
Vec2d::Values( void ) const
{
  return m_Values;
}
