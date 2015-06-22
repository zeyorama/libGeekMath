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

 \file Vec4f.cpp

 Created on: Feb 19, 2015
 \author     fkzey
 */

#include "Vec4f.hpp"

#include <cmath>
#include <cstdio>
#include <cstring>

#include "Mat4f.hpp"
#include "Vec2f.hpp"
#include "Vec3f.hpp"

Vec4f::Vec4f( const Vec2f& vector )
{
  m_Values[ 0 ] = vector.X();
  m_Values[ 1 ] = vector.Y();
  m_Values[ 2 ] = 0.0f;
  m_Values[ 3 ] = 1.0f;
}

Vec4f::Vec4f( const Vec3f& vector )
{
  m_Values[ 0 ] = vector.X();
  m_Values[ 1 ] = vector.Y();
  m_Values[ 2 ] = vector.Z();
  m_Values[ 3 ] = 1.0f;
}

Vec4f::Vec4f( const Vec4f& vector )
{
  m_Values[ 0 ] = vector.m_Values[ 0 ];
  m_Values[ 1 ] = vector.m_Values[ 1 ];
  m_Values[ 2 ] = vector.m_Values[ 2 ];
  m_Values[ 3 ] = vector.m_Values[ 3 ];
}

Vec4f::Vec4f( const float x, const float y, const float z, const float w )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
  m_Values[ 2 ] = z;
  m_Values[ 3 ] = w;
}

Vec4f::~Vec4f( void ) { return; }

void
Vec4f::Set( const float& x, const float& y, const float& z, const float& w )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
  m_Values[ 2 ] = z;
  m_Values[ 3 ] = w;
}

void
Vec4f::X( const float& x )
{
  m_Values[ 0 ] = x;
}

void
Vec4f::Y( const float& y )
{
  m_Values[ 1 ] = y;
}

void
Vec4f::Z( const float& z )
{
  m_Values[ 2 ] = z;
}

void
Vec4f::W( const float& w )
{
  m_Values[ 3 ] = w;
}

float
Vec4f::Length( void ) const
{
  return sqrtf( LengthSq() );
}

float
Vec4f::LengthSq( void ) const
{
  return  m_Values[ 0 ] * m_Values[ 0 ] +
          m_Values[ 1 ] * m_Values[ 1 ] +
          m_Values[ 2 ] * m_Values[ 2 ] +
          m_Values[ 3 ] * m_Values[ 3 ];
}

float
Vec4f::Dot( const Vec4f& other ) const
{
  return  m_Values[ 0 ] * other.m_Values[ 0 ] +
          m_Values[ 1 ] * other.m_Values[ 1 ] +
          m_Values[ 2 ] * other.m_Values[ 2 ] +
          m_Values[ 3 ] * other.m_Values[ 3 ];
}

float
Vec4f::Max( void ) const
{
  return m_Values[ 0 ] > m_Values[ 1 ] ?
         ( m_Values[ 0 ] < m_Values[ 2 ] ?
           ( m_Values[ 2 ] < m_Values[ 3 ] ?
             m_Values[ 3 ] : m_Values[ 2 ] )
           : m_Values[ 0 ] ) :
         m_Values[ 1 ];
}

float
Vec4f::Min( void ) const
{
  return m_Values[ 0 ] < m_Values[ 1 ] ?
         ( m_Values[ 0 ] > m_Values[ 2 ] ?
           ( m_Values[ 2 ] > m_Values[ 3 ] ?
             m_Values[ 3 ] : m_Values[ 2 ] )
           : m_Values[ 0 ] ) :
         m_Values[ 1 ];
}

Vec4f
Vec4f::Clamp( const Vec4f& Min, const Vec4f& Max )
{
  Vec4f result;

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

  if      ( m_Values[ 3 ] < Min.m_Values[ 3 ] )
    result.m_Values[ 3 ] = Min.m_Values[ 3 ];
  else if ( m_Values[ 3 ] > Max.m_Values[ 3 ] )
    result.m_Values[ 3 ] = Max.m_Values[ 3 ];
  else
    result.m_Values[ 3 ] = m_Values[ 3 ];

  return result;
}

Vec4f
Vec4f::Normalize( void ) const
{
  return (*this)/Length();
}

Vec4f
Vec4f::Reflect( const Vec4f& normal ) const
{
  return (*this) - ( normal * ( Dot( normal ) * 2 ) );
}

Vec4f
Vec4f::Lerp( const Vec4f& Destination, const float LerpFactor ) const
{
  return ( Destination - ( *this ) ) * LerpFactor + ( *this );
}

Vec4f
Vec4f::NLerp( const Vec4f& Destination, const float LerpFactor, const bool shortestPath ) const
{
  Vec4f correctedDest( Destination );

  if ( shortestPath && Dot( Destination ) < 0 )
    correctedDest = Destination * -1;

  return Lerp( correctedDest, LerpFactor ).Normalize();
}

#define SLERP_EPSILON 1e3

Vec4f
Vec4f::SLerp( const Vec4f& Destination, const float LerpFactor, const bool shortestPath ) const
{
  Vec4f correctedDest( Destination );
  float cos = Dot( Destination );

  if ( shortestPath && cos < 0 )
  {
    cos           *= -1;
    correctedDest  = Destination * -1;
  }

  if ( fabs( cos ) > ( 1 - SLERP_EPSILON ) )
    return NLerp( correctedDest, LerpFactor, false );

  float sin    = sqrtf( 1.f - cos * cos );
  float angle  = atan2f( sin, cos );
  float invSin = 1.f / sin;

  float src  = sinf( ( 1.f - LerpFactor ) * angle ) * invSin;
  float dest = sinf( LerpFactor * angle ) * invSin;

  return Vec4f( (*this) * src + correctedDest * dest );
}

Vec4f
Vec4f::Max( const Vec4f& vector ) const
{
  return Vec4f(
      m_Values[ 0 ] > vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] > vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ],
      m_Values[ 2 ] > vector.m_Values[ 2 ] ? m_Values[ 2 ] : vector.m_Values[ 2 ],
      m_Values[ 3 ] > vector.m_Values[ 3 ] ? m_Values[ 3 ] : vector.m_Values[ 3 ]
  );
}

Vec4f
Vec4f::Min( const Vec4f& vector ) const
{
  return Vec4f(
      m_Values[ 0 ] < vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] < vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ],
      m_Values[ 2 ] < vector.m_Values[ 2 ] ? m_Values[ 2 ] : vector.m_Values[ 2 ],
      m_Values[ 3 ] < vector.m_Values[ 3 ] ? m_Values[ 3 ] : vector.m_Values[ 3 ]
  );
}

Vec4f
Vec4f::operator +( const float summand ) const
{
  return Vec4f(
    m_Values[ 0 ] + summand,
    m_Values[ 1 ] + summand,
    m_Values[ 2 ] + summand,
    m_Values[ 3 ] + summand
  );
}

Vec4f
Vec4f::operator +( const Vec4f& summand ) const
{
  return Vec4f(
    m_Values[ 0 ] + summand.m_Values[ 0 ],
    m_Values[ 1 ] + summand.m_Values[ 1 ],
    m_Values[ 2 ] + summand.m_Values[ 2 ],
    m_Values[ 3 ] + summand.m_Values[ 3 ]
  );
}

Vec4f
Vec4f::operator -( const float subtrahend ) const
{
  return Vec4f(
    m_Values[ 0 ] - subtrahend,
    m_Values[ 1 ] - subtrahend,
    m_Values[ 2 ] - subtrahend,
    m_Values[ 3 ] - subtrahend
  );
}

Vec4f
Vec4f::operator -( const Vec4f& subtrahend ) const
{
  return Vec4f(
    m_Values[ 0 ] - subtrahend.m_Values[ 0 ],
    m_Values[ 1 ] - subtrahend.m_Values[ 1 ],
    m_Values[ 2 ] - subtrahend.m_Values[ 2 ],
    m_Values[ 3 ] - subtrahend.m_Values[ 3 ]
  );
}

Vec4f
Vec4f::operator *( const float factor ) const
{
  return Vec4f(
    m_Values[ 0 ] * factor,
    m_Values[ 1 ] * factor,
    m_Values[ 2 ] * factor,
    m_Values[ 3 ] * factor
  );
}

Vec4f
Vec4f::operator *( const Vec4f& factor ) const
{
  return Vec4f(
    m_Values[ 0 ] * factor.m_Values[ 0 ],
    m_Values[ 1 ] * factor.m_Values[ 1 ],
    m_Values[ 2 ] * factor.m_Values[ 2 ],
    m_Values[ 3 ] * factor.m_Values[ 3 ]
  );
}

Vec4f
Vec4f::operator /( const float dividend ) const
{
  if ( dividend == 0.0f ) return Vec4f();

  return Vec4f(
    m_Values[ 0 ] / dividend,
    m_Values[ 1 ] / dividend,
    m_Values[ 2 ] / dividend,
    m_Values[ 3 ] / dividend
  );
}

Vec4f&
Vec4f::operator +=( const Vec4f& summand )
{
  m_Values[ 0 ] += summand.m_Values[ 0 ];
  m_Values[ 1 ] += summand.m_Values[ 1 ];
  m_Values[ 2 ] += summand.m_Values[ 2 ];
  m_Values[ 3 ] += summand.m_Values[ 3 ];

  return *this;
}

Vec4f&
Vec4f::operator +=( const float summand )
{
  m_Values[ 0 ] += summand;
  m_Values[ 1 ] += summand;
  m_Values[ 2 ] += summand;
  m_Values[ 3 ] += summand;

  return *this;
}

Vec4f&
Vec4f::operator -=( const Vec4f& subtrahend )
{
  m_Values[ 0 ] -= subtrahend.m_Values[ 0 ];
  m_Values[ 1 ] -= subtrahend.m_Values[ 1 ];
  m_Values[ 2 ] -= subtrahend.m_Values[ 2 ];
  m_Values[ 3 ] -= subtrahend.m_Values[ 3 ];

  return *this;
}

Vec4f&
Vec4f::operator -=( const float subtrahend )
{
  m_Values[ 0 ] -= subtrahend;
  m_Values[ 1 ] -= subtrahend;
  m_Values[ 2 ] -= subtrahend;
  m_Values[ 3 ] -= subtrahend;

  return *this;
}

Vec4f&
Vec4f::operator *=( const float factor )
{
  m_Values[ 0 ] *= factor;
  m_Values[ 1 ] *= factor;
  m_Values[ 2 ] *= factor;
  m_Values[ 3 ] *= factor;

  return *this;
}

Vec4f&
Vec4f::operator *=( const Vec4f& factor )
{
  m_Values[ 0 ] *= factor.m_Values[ 0 ];
  m_Values[ 1 ] *= factor.m_Values[ 1 ];
  m_Values[ 2 ] *= factor.m_Values[ 2 ];
  m_Values[ 3 ] *= factor.m_Values[ 3 ];

  return *this;
}

Vec4f&
Vec4f::operator /=( const float dividend )
{
  if ( dividend == 0.0f ) return *this;

  m_Values[ 0 ] /= dividend;
  m_Values[ 1 ] /= dividend;
  m_Values[ 2 ] /= dividend;
  m_Values[ 3 ] /= dividend;

  return *this;
}

bool
Vec4f::operator ==( const Vec4f& expr ) const
{
  return  m_Values[ 0 ] == expr.m_Values[ 0 ] &&
          m_Values[ 1 ] == expr.m_Values[ 1 ] &&
          m_Values[ 2 ] == expr.m_Values[ 2 ] &&
          m_Values[ 3 ] == expr.m_Values[ 3 ];
}

bool
Vec4f::operator !=( const Vec4f& expr ) const
{
  return  m_Values[ 0 ] != expr.m_Values[ 0 ] ||
          m_Values[ 1 ] != expr.m_Values[ 1 ] ||
          m_Values[ 2 ] != expr.m_Values[ 2 ] ||
          m_Values[ 3 ] != expr.m_Values[ 3 ];
}

float&
Vec4f::operator []( unsigned int i )
{
  return m_Values[ i ];
}

float
Vec4f::operator []( unsigned int i ) const
{
  return m_Values[ i ];
}

float
Vec4f::X( void ) const
{
  return m_Values[ 0 ];
}

float
Vec4f::Y( void ) const
{
  return m_Values[ 1 ];
}

float
Vec4f::Z( void ) const
{
  return m_Values[ 2 ];
}
float
Vec4f::W( void ) const
{
  return m_Values[ 3 ];
}

Vec2f
Vec4f::XX( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2f
Vec4f::XY( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2f
Vec4f::XZ( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2f
Vec4f::XW( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2f
Vec4f::YX( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 0 ] );
}

Vec2f
Vec4f::YY( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 1 ] );
}

Vec2f
Vec4f::YZ( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 2 ] );
}

Vec2f
Vec4f::YW( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 3 ] );
}

Vec2f
Vec4f::ZX( void ) const
{
  return Vec2f( m_Values[ 2 ], m_Values[ 0 ] );
}

Vec2f
Vec4f::ZY( void ) const
{
  return Vec2f( m_Values[ 2 ], m_Values[ 1 ] );
}

Vec2f
Vec4f::ZZ( void ) const
{
  return Vec2f( m_Values[ 2 ], m_Values[ 2 ] );
}

Vec2f
Vec4f::ZW( void ) const
{
  return Vec2f( m_Values[ 2 ], m_Values[ 3 ] );
}

Vec2f
Vec4f::WX( void ) const
{
  return Vec2f( m_Values[ 3 ], m_Values[ 0 ] );
}

Vec2f
Vec4f::WY( void ) const
{
  return Vec2f( m_Values[ 3 ], m_Values[ 1 ] );
}

Vec2f
Vec4f::WZ( void ) const
{
  return Vec2f( m_Values[ 3 ], m_Values[ 2 ] );
}

Vec2f
Vec4f::WW( void ) const
{
  return Vec2f( m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::XXX( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::XXY( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::XXZ( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::XXW( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::XYX( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::XYY( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::XYZ( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::XYW( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::XZX( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::XZY( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::XZZ( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::XZW( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::XWX( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::XWY( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::XWZ( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::XWW( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::YXX( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::YXY( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::YXZ( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::YXW( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::YYX( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::YYY( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::YYZ( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::YYW( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::YZX( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::YZY( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::YZZ( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::YZW( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::YWX( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::YWY( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::YWZ( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::YWW( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::ZXX( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::ZXY( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::ZXZ( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::ZXW( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::ZYX( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::ZYY( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::ZYZ( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::ZYW( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::ZZX( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::ZZY( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::ZZZ( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::ZZW( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::ZWX( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::ZWY( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::ZWZ( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::ZWW( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::WXX( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::WXY( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::WXZ( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::WXW( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::WYX( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::WYY( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::WYZ( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::WYW( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::WZX( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::WZY( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::WZZ( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::WZW( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3f
Vec4f::WWX( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3f
Vec4f::WWY( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3f
Vec4f::WWZ( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3f
Vec4f::WWW( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 3 ] );
}

void
Vec4f::Print( void ) const
{
  printf( "( %f | %f | %f | %f )\n",
          m_Values[ 0 ], m_Values[ 1 ], m_Values[ 2 ], m_Values[ 3 ] );
}

const float*
Vec4f::Values( void ) const
{
  return m_Values;
}
