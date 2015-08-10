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

 \file Vec4d.cpp

 Created on: Feb 19, 2015
 \author     fkzey
 */

#include "Vec4d.hpp"

#include <cmath>
#include <cstdio>
#include <cstring>

#include "Vec2d.hpp"
#include "Vec3d.hpp"

Vec4d::Vec4d( const Vec2d& vector )
{
  m_Values[ 0 ] = vector.X();
  m_Values[ 1 ] = vector.Y();
  m_Values[ 2 ] = 0.0f;
  m_Values[ 3 ] = 1.0f;
}

Vec4d::Vec4d( const Vec3d& vector )
{
  m_Values[ 0 ] = vector.X();
  m_Values[ 1 ] = vector.Y();
  m_Values[ 2 ] = vector.Z();
  m_Values[ 3 ] = 1.0f;
}

Vec4d::Vec4d( const Vec4d& vector )
{
  m_Values[ 0 ] = vector.m_Values[ 0 ];
  m_Values[ 1 ] = vector.m_Values[ 1 ];
  m_Values[ 2 ] = vector.m_Values[ 2 ];
  m_Values[ 3 ] = vector.m_Values[ 3 ];
}

Vec4d::Vec4d( const float x, const float y, const float z, const float w )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
  m_Values[ 2 ] = z;
  m_Values[ 3 ] = w;
}

Vec4d::~Vec4d( void ) { return; }

void
Vec4d::Set( const float& x, const float& y, const float& z, const float& w )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
  m_Values[ 2 ] = z;
  m_Values[ 3 ] = w;
}

void
Vec4d::X( const float& x )
{
  m_Values[ 0 ] = x;
}

void
Vec4d::Y( const float& y )
{
  m_Values[ 1 ] = y;
}

void
Vec4d::Z( const float& z )
{
  m_Values[ 2 ] = z;
}

void
Vec4d::W( const float& w )
{
  m_Values[ 3 ] = w;
}

float
Vec4d::Length( void ) const
{
  return sqrtf( LengthSq() );
}

float
Vec4d::LengthSq( void ) const
{
  return  m_Values[ 0 ] * m_Values[ 0 ] +
          m_Values[ 1 ] * m_Values[ 1 ] +
          m_Values[ 2 ] * m_Values[ 2 ] +
          m_Values[ 3 ] * m_Values[ 3 ];
}

float
Vec4d::Dot( const Vec4d& other ) const
{
  return  m_Values[ 0 ] * other.m_Values[ 0 ] +
          m_Values[ 1 ] * other.m_Values[ 1 ] +
          m_Values[ 2 ] * other.m_Values[ 2 ] +
          m_Values[ 3 ] * other.m_Values[ 3 ];
}

float
Vec4d::Max( void ) const
{
  return m_Values[ 0 ] > m_Values[ 1 ] ?
         ( m_Values[ 0 ] < m_Values[ 2 ] ?
           ( m_Values[ 2 ] < m_Values[ 3 ] ?
             m_Values[ 3 ] : m_Values[ 2 ] )
           : m_Values[ 0 ] ) :
         m_Values[ 1 ];
}

float
Vec4d::Min( void ) const
{
  return m_Values[ 0 ] < m_Values[ 1 ] ?
         ( m_Values[ 0 ] > m_Values[ 2 ] ?
           ( m_Values[ 2 ] > m_Values[ 3 ] ?
             m_Values[ 3 ] : m_Values[ 2 ] )
           : m_Values[ 0 ] ) :
         m_Values[ 1 ];
}

Vec4d
Vec4d::Clamp( const Vec4d& Min, const Vec4d& Max )
{
  Vec4d result;

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

Vec4d
Vec4d::Normalize( void ) const
{
  return (*this)/Length();
}

Vec4d
Vec4d::Reflect( const Vec4d& normal ) const
{
  return (*this) - ( normal * ( Dot( normal ) * 2 ) );
}

Vec4d
Vec4d::Lerp( const Vec4d& Destination, const float LerpFactor ) const
{
  return ( Destination - ( *this ) ) * LerpFactor + ( *this );
}

Vec4d
Vec4d::NLerp( const Vec4d& Destination, const float LerpFactor, const bool shortestPath ) const
{
  Vec4d correctedDest( Destination );

  if ( shortestPath && Dot( Destination ) < 0 )
    correctedDest = Destination * -1;

  return Lerp( correctedDest, LerpFactor ).Normalize();
}

#define SLERP_EPSILON 1e3

Vec4d
Vec4d::SLerp( const Vec4d& Destination, const float LerpFactor, const bool shortestPath ) const
{
  Vec4d correctedDest( Destination );
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

  return Vec4d( (*this) * src + correctedDest * dest );
}

Vec4d
Vec4d::Max( const Vec4d& vector ) const
{
  return Vec4d(
      m_Values[ 0 ] > vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] > vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ],
      m_Values[ 2 ] > vector.m_Values[ 2 ] ? m_Values[ 2 ] : vector.m_Values[ 2 ],
      m_Values[ 3 ] > vector.m_Values[ 3 ] ? m_Values[ 3 ] : vector.m_Values[ 3 ]
  );
}

Vec4d
Vec4d::Min( const Vec4d& vector ) const
{
  return Vec4d(
      m_Values[ 0 ] < vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] < vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ],
      m_Values[ 2 ] < vector.m_Values[ 2 ] ? m_Values[ 2 ] : vector.m_Values[ 2 ],
      m_Values[ 3 ] < vector.m_Values[ 3 ] ? m_Values[ 3 ] : vector.m_Values[ 3 ]
  );
}

Vec4d
Vec4d::operator +( const float summand ) const
{
  return Vec4d(
    m_Values[ 0 ] + summand,
    m_Values[ 1 ] + summand,
    m_Values[ 2 ] + summand,
    m_Values[ 3 ] + summand
  );
}

Vec4d
Vec4d::operator +( const Vec4d& summand ) const
{
  return Vec4d(
    m_Values[ 0 ] + summand.m_Values[ 0 ],
    m_Values[ 1 ] + summand.m_Values[ 1 ],
    m_Values[ 2 ] + summand.m_Values[ 2 ],
    m_Values[ 3 ] + summand.m_Values[ 3 ]
  );
}

Vec4d
Vec4d::operator -( const float subtrahend ) const
{
  return Vec4d(
    m_Values[ 0 ] - subtrahend,
    m_Values[ 1 ] - subtrahend,
    m_Values[ 2 ] - subtrahend,
    m_Values[ 3 ] - subtrahend
  );
}

Vec4d
Vec4d::operator -( const Vec4d& subtrahend ) const
{
  return Vec4d(
    m_Values[ 0 ] - subtrahend.m_Values[ 0 ],
    m_Values[ 1 ] - subtrahend.m_Values[ 1 ],
    m_Values[ 2 ] - subtrahend.m_Values[ 2 ],
    m_Values[ 3 ] - subtrahend.m_Values[ 3 ]
  );
}

Vec4d
Vec4d::operator *( const float factor ) const
{
  return Vec4d(
    m_Values[ 0 ] * factor,
    m_Values[ 1 ] * factor,
    m_Values[ 2 ] * factor,
    m_Values[ 3 ] * factor
  );
}

Vec4d
Vec4d::operator *( const Vec4d& factor ) const
{
  return Vec4d(
    m_Values[ 0 ] * factor.m_Values[ 0 ],
    m_Values[ 1 ] * factor.m_Values[ 1 ],
    m_Values[ 2 ] * factor.m_Values[ 2 ],
    m_Values[ 3 ] * factor.m_Values[ 3 ]
  );
}

Vec4d
Vec4d::operator /( const float dividend ) const
{
  if ( dividend == 0.0f ) return Vec4d();

  return Vec4d(
    m_Values[ 0 ] / dividend,
    m_Values[ 1 ] / dividend,
    m_Values[ 2 ] / dividend,
    m_Values[ 3 ] / dividend
  );
}

Vec4d&
Vec4d::operator +=( const Vec4d& summand )
{
  m_Values[ 0 ] += summand.m_Values[ 0 ];
  m_Values[ 1 ] += summand.m_Values[ 1 ];
  m_Values[ 2 ] += summand.m_Values[ 2 ];
  m_Values[ 3 ] += summand.m_Values[ 3 ];

  return *this;
}

Vec4d&
Vec4d::operator +=( const float summand )
{
  m_Values[ 0 ] += summand;
  m_Values[ 1 ] += summand;
  m_Values[ 2 ] += summand;
  m_Values[ 3 ] += summand;

  return *this;
}

Vec4d&
Vec4d::operator -=( const Vec4d& subtrahend )
{
  m_Values[ 0 ] -= subtrahend.m_Values[ 0 ];
  m_Values[ 1 ] -= subtrahend.m_Values[ 1 ];
  m_Values[ 2 ] -= subtrahend.m_Values[ 2 ];
  m_Values[ 3 ] -= subtrahend.m_Values[ 3 ];

  return *this;
}

Vec4d&
Vec4d::operator -=( const float subtrahend )
{
  m_Values[ 0 ] -= subtrahend;
  m_Values[ 1 ] -= subtrahend;
  m_Values[ 2 ] -= subtrahend;
  m_Values[ 3 ] -= subtrahend;

  return *this;
}

Vec4d&
Vec4d::operator *=( const float factor )
{
  m_Values[ 0 ] *= factor;
  m_Values[ 1 ] *= factor;
  m_Values[ 2 ] *= factor;
  m_Values[ 3 ] *= factor;

  return *this;
}

Vec4d&
Vec4d::operator *=( const Vec4d& factor )
{
  m_Values[ 0 ] *= factor.m_Values[ 0 ];
  m_Values[ 1 ] *= factor.m_Values[ 1 ];
  m_Values[ 2 ] *= factor.m_Values[ 2 ];
  m_Values[ 3 ] *= factor.m_Values[ 3 ];

  return *this;
}

Vec4d&
Vec4d::operator /=( const float dividend )
{
  if ( dividend == 0.0f ) return *this;

  m_Values[ 0 ] /= dividend;
  m_Values[ 1 ] /= dividend;
  m_Values[ 2 ] /= dividend;
  m_Values[ 3 ] /= dividend;

  return *this;
}

bool
Vec4d::operator ==( const Vec4d& expr ) const
{
  return  m_Values[ 0 ] == expr.m_Values[ 0 ] &&
          m_Values[ 1 ] == expr.m_Values[ 1 ] &&
          m_Values[ 2 ] == expr.m_Values[ 2 ] &&
          m_Values[ 3 ] == expr.m_Values[ 3 ];
}

bool
Vec4d::operator !=( const Vec4d& expr ) const
{
  return  m_Values[ 0 ] != expr.m_Values[ 0 ] ||
          m_Values[ 1 ] != expr.m_Values[ 1 ] ||
          m_Values[ 2 ] != expr.m_Values[ 2 ] ||
          m_Values[ 3 ] != expr.m_Values[ 3 ];
}

float&
Vec4d::operator []( unsigned int i )
{
  return m_Values[ i ];
}

float
Vec4d::operator []( unsigned int i ) const
{
  return m_Values[ i ];
}

float
Vec4d::X( void ) const
{
  return m_Values[ 0 ];
}

float
Vec4d::Y( void ) const
{
  return m_Values[ 1 ];
}

float
Vec4d::Z( void ) const
{
  return m_Values[ 2 ];
}
float
Vec4d::W( void ) const
{
  return m_Values[ 3 ];
}

Vec2d
Vec4d::XX( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2d
Vec4d::XY( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2d
Vec4d::XZ( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2d
Vec4d::XW( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2d
Vec4d::YX( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 0 ] );
}

Vec2d
Vec4d::YY( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 1 ] );
}

Vec2d
Vec4d::YZ( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 2 ] );
}

Vec2d
Vec4d::YW( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 3 ] );
}

Vec2d
Vec4d::ZX( void ) const
{
  return Vec2d( m_Values[ 2 ], m_Values[ 0 ] );
}

Vec2d
Vec4d::ZY( void ) const
{
  return Vec2d( m_Values[ 2 ], m_Values[ 1 ] );
}

Vec2d
Vec4d::ZZ( void ) const
{
  return Vec2d( m_Values[ 2 ], m_Values[ 2 ] );
}

Vec2d
Vec4d::ZW( void ) const
{
  return Vec2d( m_Values[ 2 ], m_Values[ 3 ] );
}

Vec2d
Vec4d::WX( void ) const
{
  return Vec2d( m_Values[ 3 ], m_Values[ 0 ] );
}

Vec2d
Vec4d::WY( void ) const
{
  return Vec2d( m_Values[ 3 ], m_Values[ 1 ] );
}

Vec2d
Vec4d::WZ( void ) const
{
  return Vec2d( m_Values[ 3 ], m_Values[ 2 ] );
}

Vec2d
Vec4d::WW( void ) const
{
  return Vec2d( m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::XXX( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::XXY( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::XXZ( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::XXW( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::XYX( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::XYY( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::XYZ( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::XYW( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::XZX( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::XZY( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::XZZ( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::XZW( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::XWX( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::XWY( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::XWZ( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::XWW( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::YXX( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::YXY( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::YXZ( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::YXW( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::YYX( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::YYY( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::YYZ( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::YYW( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::YZX( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::YZY( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::YZZ( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::YZW( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::YWX( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::YWY( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::YWZ( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::YWW( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::ZXX( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::ZXY( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::ZXZ( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::ZXW( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::ZYX( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::ZYY( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::ZYZ( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::ZYW( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::ZZX( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::ZZY( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::ZZZ( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::ZZW( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::ZWX( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::ZWY( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::ZWZ( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::ZWW( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::WXX( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::WXY( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::WXZ( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::WXW( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::WYX( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::WYY( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::WYZ( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::WYW( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::WZX( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::WZY( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::WZZ( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::WZW( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3d
Vec4d::WWX( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3d
Vec4d::WWY( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3d
Vec4d::WWZ( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3d
Vec4d::WWW( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 3 ] );
}

void
Vec4d::Print( void ) const
{
  printf( "( %f | %f | %f | %f )\n",
          m_Values[ 0 ], m_Values[ 1 ], m_Values[ 2 ], m_Values[ 3 ] );
}

const float*
Vec4d::Values( void ) const
{
  return m_Values;
}
