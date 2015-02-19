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

\file Vec3f.cpp

Created on: Feb 18, 2015
\author     fkzey
*/
#include "Vec3f.h"

#include "Vec2f.h"
#include "Vec4f.h"

#include <cmath>
#include <cstdio>

Vec3f::Vec3f( void )
{
  m_Values[ 0 ] = 0.0f;
  m_Values[ 1 ] = 0.0f;
  m_Values[ 2 ] = 0.0f;
}

Vec3f::Vec3f( const float value )
{
  m_Values[ 0 ] = value;
  m_Values[ 1 ] = value;
  m_Values[ 2 ] = value;
}

Vec3f::Vec3f( const Vec3f& other )
{
  m_Values[ 0 ] = other.m_Values[ 0 ];
  m_Values[ 1 ] = other.m_Values[ 1 ];
  m_Values[ 2 ] = other.m_Values[ 2 ];
}

Vec3f::Vec3f( const float x, const float y, const float z )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
  m_Values[ 2 ] = z;
}

Vec3f::~Vec3f( void ) { return; }

void
Vec3f::Set( const float& x, const float& y, const float& z )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
  m_Values[ 2 ] = z;
}

void
Vec3f::X( const float& x )
{
  m_Values[ 0 ] = x;
}

void
Vec3f::Y( const float& y )
{
  m_Values[ 1 ] = y;
}

void
Vec3f::Z( const float& z )
{
  m_Values[ 2 ] = z;
}

float
Vec3f::LengthSq( void ) const
{
  return  m_Values[ 0 ] * m_Values[ 0 ] +
          m_Values[ 1 ] * m_Values[ 1 ] +
          m_Values[ 2 ] * m_Values[ 2 ];
}

float
Vec3f::Length( void ) const
{
  return sqrtf( LengthSq() );
}

float
Vec3f::Dot( const Vec3f& other ) const
{
  return  m_Values[ 0 ] * other.m_Values[ 0 ] +
          m_Values[ 1 ] * other.m_Values[ 1 ] +
          m_Values[ 2 ] * other.m_Values[ 2 ];
}

float
Vec3f::Max( void ) const
{
  return m_Values[ 0 ] > m_Values[ 1 ] ?
         ( m_Values[ 0 ] < m_Values[ 2 ] ?
           m_Values[ 2 ] : m_Values[ 0 ] ) :
         m_Values[ 1 ];
}

float
Vec3f::Min( void ) const
{
  return m_Values[ 0 ] < m_Values[ 1 ] ?
         ( m_Values[ 0 ] > m_Values[ 2 ] ?
           m_Values[ 2 ] : m_Values[ 0 ] ) :
         m_Values[ 1 ];
}

Vec3f
Vec3f::Clamp( const Vec3f& Min, const Vec3f& Max )
{
  Vec3f result;

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

  if      ( m_Values[ 2 ] < Min.m_Values[ 2 ] )
    result.m_Values[ 2 ] = Min.m_Values[ 2 ];
  else if ( m_Values[ 2 ] > Max.m_Values[ 2 ] )
    result.m_Values[ 2 ] = Max.m_Values[ 2 ];
  else
    result.m_Values[ 2 ] = m_Values[ 2 ];

  return result;
}

Vec3f
Vec3f::Normalize( void ) const
{
  float length = Length();

  return (*this)/length;
}

Vec3f
Vec3f::Reflect( const Vec3f& normal ) const
{
  return (*this) - ( normal * ( Dot( normal ) * 2 ) );
}

Vec3f
Vec3f::Rotate( const Vec4f& quaternion ) const
{
  Vec4f conjugateQ = quaternion.Conjugate();
  Vec4f w          = quaternion * ( *this ) * conjugateQ;

  return Vec3f( w.X(), w.Y(), w.Z() );
}

Vec3f
Vec3f::Rotate( const Vec3f& Axis, const float Angle ) const
{
  const float sinAngle = sinf( -Angle );
  const float cosAngle = cosf( -Angle );

  return  Cross( Axis * sinAngle ) +              //Rotation on local X
          ( ( *this ) * cosAngle) +               //Rotation on local Z
          Axis * Dot( Axis * ( 1 - cosAngle ) );  //Rotation on local Y
}

Vec3f
Vec3f::Cross( const Vec3f& vector ) const
{
  return Vec3f( m_Values[1] * vector.m_Values[2] - m_Values[2] * vector.m_Values[1],
                m_Values[2] * vector.m_Values[0] - m_Values[0] * vector.m_Values[2],
                m_Values[0] * vector.m_Values[1] - m_Values[1] * vector.m_Values[0] );
}

Vec3f
Vec3f::Lerp( const Vec3f& Destination, float LerpFactor ) const
{
  return ( Destination - ( *this ) ) * LerpFactor + ( *this );
}

Vec3f
Vec3f::Max( const Vec3f& vector ) const
{
  return Vec3f(
      m_Values[ 0 ] > vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] > vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ],
      m_Values[ 2 ] > vector.m_Values[ 2 ] ? m_Values[ 2 ] : vector.m_Values[ 2 ]
  );
}

Vec3f
Vec3f::Min( const Vec3f& vector ) const
{
  return Vec3f(
      m_Values[ 0 ] < vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] < vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ],
      m_Values[ 2 ] < vector.m_Values[ 2 ] ? m_Values[ 2 ] : vector.m_Values[ 2 ]
  );
}

Vec3f
Vec3f::operator +( const float summand ) const
{
  return Vec3f( m_Values[ 0 ] + summand,
                m_Values[ 1 ] + summand,
                m_Values[ 2 ] + summand );
}

Vec3f
Vec3f::operator +( const Vec3f& summand ) const
{
  return Vec3f( m_Values[ 0 ] + summand.m_Values[ 0 ],
                m_Values[ 1 ] + summand.m_Values[ 1 ],
                m_Values[ 2 ] + summand.m_Values[ 2 ] );
}

Vec3f
Vec3f::operator -( const float subtrahend ) const
{
  return Vec3f( m_Values[ 0 ] - subtrahend,
                m_Values[ 1 ] - subtrahend,
                m_Values[ 2 ] - subtrahend );
}

Vec3f
Vec3f::operator -( const Vec3f& subtrahend ) const
{
  return Vec3f( m_Values[ 0 ] - subtrahend.m_Values[ 0 ],
                m_Values[ 1 ] - subtrahend.m_Values[ 1 ],
                m_Values[ 2 ] - subtrahend.m_Values[ 2 ] );
}

Vec3f
Vec3f::operator *( const float factor ) const
{
  return Vec3f( m_Values[ 0 ] * factor,
                m_Values[ 1 ] * factor,
                m_Values[ 2 ] * factor );
}

Vec3f
Vec3f::operator *( const Vec3f& factor ) const
{
  return Vec3f( m_Values[ 0 ] * factor.m_Values[ 0 ],
                m_Values[ 1 ] * factor.m_Values[ 1 ],
                m_Values[ 2 ] * factor.m_Values[ 2 ] );
}

Vec3f
Vec3f::operator /( const float dividend ) const
{
  if ( dividend == 0.0f ) return Vec3f();

  return Vec3f( m_Values[ 0 ] / dividend,
                m_Values[ 1 ] / dividend,
                m_Values[ 2 ] / dividend );
}

Vec3f&
Vec3f::operator +=( const float summand )
{
  m_Values[ 0 ] += summand;
  m_Values[ 1 ] += summand;
  m_Values[ 2 ] += summand;

  return *this;
}

Vec3f&
Vec3f::operator +=( const Vec3f& summand )
{
  m_Values[ 0 ] += summand.m_Values[ 0 ];
  m_Values[ 1 ] += summand.m_Values[ 1 ];
  m_Values[ 2 ] += summand.m_Values[ 2 ];

  return *this;
}
Vec3f&
Vec3f::operator -=( const Vec3f& subtrahend )
{
  m_Values[ 0 ] -= subtrahend.m_Values[ 0 ];
  m_Values[ 1 ] -= subtrahend.m_Values[ 1 ];
  m_Values[ 2 ] -= subtrahend.m_Values[ 2 ];

  return *this;
}

Vec3f&
Vec3f::operator -=( const float subtrahend )
{
  m_Values[ 0 ] -= subtrahend;
  m_Values[ 1 ] -= subtrahend;
  m_Values[ 2 ] -= subtrahend;

  return *this;
}

Vec3f&
Vec3f::operator *=( const float factor )
{
  m_Values[ 0 ] *= factor;
  m_Values[ 1 ] *= factor;
  m_Values[ 2 ] *= factor;

  return *this;
}

Vec3f&
Vec3f::operator *=( const Vec3f& factor )
{
  m_Values[ 0 ] *= factor.m_Values[ 0 ];
  m_Values[ 1 ] *= factor.m_Values[ 1 ];
  m_Values[ 2 ] *= factor.m_Values[ 2 ];

  return *this;
}

Vec3f&
Vec3f::operator /=( const float dividend )
{
  if ( dividend == 0.0f ) return *this;

  m_Values[ 0 ] /= dividend;
  m_Values[ 1 ] /= dividend;
  m_Values[ 2 ] /= dividend;

  return *this;
}

bool
Vec3f::operator ==( const Vec3f& expr ) const
{
  return  m_Values[ 0 ] == expr.m_Values[ 0 ] &&
          m_Values[ 1 ] == expr.m_Values[ 1 ] &&
          m_Values[ 2 ] == expr.m_Values[ 2 ];
}

bool
Vec3f::operator !=( const Vec3f& expr ) const
{
  return  m_Values[ 0 ] != expr.m_Values[ 0 ] ||
          m_Values[ 1 ] != expr.m_Values[ 1 ] ||
          m_Values[ 2 ] != expr.m_Values[ 2 ];
}

float&
Vec3f::operator []( unsigned int i )
{
  return m_Values[ i ];
}

float
Vec3f::operator []( unsigned int i ) const
{
  return m_Values[ i ];
}

float
Vec3f::X( void ) const
{
  return m_Values[ 0 ];
}

float
Vec3f::Y( void ) const
{
  return m_Values[ 1 ];
}

float
Vec3f::Z( void ) const
{
  return m_Values[ 2 ];
}

Vec2f
Vec3f::XX( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2f
Vec3f::XY( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 1 ] );
}

Vec2f
Vec3f::XZ( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 2 ] );
}

Vec2f
Vec3f::YX( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 0 ] );
}

Vec2f
Vec3f::YY( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 1 ] );
}

Vec2f
Vec3f::YZ( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 2 ] );
}

Vec2f
Vec3f::ZX( void ) const
{
  return Vec2f( m_Values[ 2 ], m_Values[ 0 ] );
}

Vec2f
Vec3f::ZY( void ) const
{
  return Vec2f( m_Values[ 2 ], m_Values[ 1 ] );
}

Vec2f
Vec3f::ZZ( void ) const
{
  return Vec2f( m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3f
Vec3f::XXX( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3f
Vec3f::XXY( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3f
Vec3f::XXZ( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3f
Vec3f::XYX( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3f
Vec3f::XYY( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3f
Vec3f::XYZ( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3f
Vec3f::XZX( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3f
Vec3f::XZY( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3f
Vec3f::XZZ( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3f
Vec3f::YXX( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3f
Vec3f::YXY( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3f
Vec3f::YXZ( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3f
Vec3f::YYX( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3f
Vec3f::YYY( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3f
Vec3f::YYZ( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3f
Vec3f::YZX( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3f
Vec3f::YZY( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3f
Vec3f::YZZ( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3f
Vec3f::ZXX( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3f
Vec3f::ZXY( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3f
Vec3f::ZXZ( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3f
Vec3f::ZYX( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3f
Vec3f::ZYY( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3f
Vec3f::ZYZ( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3f
Vec3f::ZZX( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3f
Vec3f::ZZY( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3f
Vec3f::ZZZ( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 2 ] );
}

void
Vec3f::Print( void ) const
{
  printf( "( %f | %f | %f )\n", m_Values[ 0 ], m_Values[ 1 ], m_Values[ 2 ] );
}

float*
Vec3f::Values( void )
{
  return m_Values;
}
