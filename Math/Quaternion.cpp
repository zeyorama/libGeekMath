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

 \file Quaternion.cpp

 Created on: Mar 9, 2015
 \author     fkzey
 */

#include "Quaternion.h"

#include "Vec2f.h"
#include "Vec3f.h"
#include "Mat4f.h"

#include <cmath>
#include <cstdio>
#include <cstring>

Quaternion::Quaternion( const Mat4f& matrix )
{
  const float trace = matrix[ 0 ][ 0 ] + matrix[ 1 ][ 1 ] + matrix[ 2 ][ 2 ];

  if      ( trace > 0 )
  {
    const float s = 0.5f / sqrtf( trace + 1.0f );

    m_Values[ 3 ] = 0.25f / s;
    m_Values[ 0 ] = ( matrix[ 1 ][ 2 ] - matrix[ 2 ][ 1 ] ) * s;
    m_Values[ 1 ] = ( matrix[ 2 ][ 0 ] - matrix[ 0 ][ 2 ] ) * s;
    m_Values[ 2 ] = ( matrix[ 0 ][ 1 ] - matrix[ 1 ][ 0 ] ) * s;
  }
  else if ( matrix[ 0 ][ 0 ] > matrix[ 1 ][ 1 ] && matrix[ 0 ][ 0 ] > matrix[ 2 ][ 2 ] )
  {
    const float s = 2.0f * sqrtf( 1.0f + matrix[ 0 ][ 0 ] - matrix[ 1 ][ 1 ] - matrix[ 2 ][ 2 ] );

    m_Values[ 3 ] = ( matrix[ 1 ][ 2 ] - matrix[ 2 ][ 1 ] ) / s;
    m_Values[ 0 ] = 0.25f * s;
    m_Values[ 1 ] = ( matrix[ 1 ][ 0 ] + matrix[ 0 ][ 1 ] ) / s;
    m_Values[ 2 ] = ( matrix[ 2 ][ 0 ] + matrix[ 0 ][ 2 ] ) / s;
  }
  else if ( matrix[ 1 ][ 1 ] > matrix[ 2 ][ 2 ])
  {
    const float s = 2.0f * sqrtf( 1.0f + matrix[ 1 ][ 1 ] - matrix[ 0 ][ 0 ] - matrix[ 2 ][ 2 ] );

    m_Values[ 3 ] = ( matrix[ 2 ][ 0 ] - matrix[ 0 ][ 2 ] ) / s;
    m_Values[ 0 ] = ( matrix[ 1 ][ 0 ] + matrix[ 0 ][ 1 ] ) / s;
    m_Values[ 1 ] = 0.25f * s;
    m_Values[ 2 ] = ( matrix[ 2 ][ 1 ] + matrix[ 1 ][ 2 ] ) / s;
  }
  else
  {
    const float s = 2.0f * sqrtf( 1.0f + matrix[ 2 ][ 2 ] - matrix[ 1 ][ 1 ] - matrix[ 0 ][ 0 ]);

    m_Values[ 3 ] = ( matrix[ 0 ][ 1 ] - matrix[ 1 ][ 0 ] ) / s;
    m_Values[ 0 ] = ( matrix[ 2 ][ 0 ] + matrix[ 0 ][ 2 ] ) / s;
    m_Values[ 1 ] = ( matrix[ 1 ][ 2 ] + matrix[ 2 ][ 1 ] ) / s;
    m_Values[ 2 ] = 0.25f * s;
  }

  const float length = Length();

  m_Values[ 3 ] = m_Values[ 3 ] / length;
  m_Values[ 0 ] = m_Values[ 0 ] / length;
  m_Values[ 1 ] = m_Values[ 1 ] / length;
  m_Values[ 2 ] = m_Values[ 2 ] / length;
}

Quaternion::Quaternion( const Vec2f& vector )
{
  m_Values[ 0 ] = vector.X();
  m_Values[ 1 ] = vector.Y();
  m_Values[ 2 ] = 0.0f;
  m_Values[ 3 ] = 1.0f;
}

Quaternion::Quaternion( const Vec3f& vector )
{
  m_Values[ 0 ] = vector.X();
  m_Values[ 1 ] = vector.Y();
  m_Values[ 2 ] = vector.Z();
  m_Values[ 3 ] = 1.0f;
}

Quaternion::Quaternion( const Quaternion& vector )
{
  m_Values[ 0 ] = vector.m_Values[ 0 ];
  m_Values[ 1 ] = vector.m_Values[ 1 ];
  m_Values[ 2 ] = vector.m_Values[ 2 ];
  m_Values[ 3 ] = vector.m_Values[ 3 ];
}

Quaternion::Quaternion( const Vec3f& Axis, const float Angle )
{
  float sinHalfAngle = sinf( Angle / 2 );
  float cosHalfAngle = cosf( Angle / 2 );

  m_Values[0] = Axis.X() * sinHalfAngle;
  m_Values[1] = Axis.Y() * sinHalfAngle;
  m_Values[2] = Axis.Z() * sinHalfAngle;
  m_Values[3] = cosHalfAngle;
}

Quaternion::Quaternion( const float x, const float y, const float z, const float w )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
  m_Values[ 2 ] = z;
  m_Values[ 3 ] = w;
}

Quaternion::~Quaternion( void ) { return; }

void
Quaternion::Set( const float& x, const float& y, const float& z, const float& w )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
  m_Values[ 2 ] = z;
  m_Values[ 3 ] = w;
}

void
Quaternion::X( const float& x )
{
  m_Values[ 0 ] = x;
}

void
Quaternion::Y( const float& y )
{
  m_Values[ 1 ] = y;
}

void
Quaternion::Z( const float& z )
{
  m_Values[ 2 ] = z;
}

void
Quaternion::W( const float& w )
{
  m_Values[ 3 ] = w;
}

float
Quaternion::Length( void ) const
{
  return sqrtf( LengthSq() );
}

float
Quaternion::LengthSq( void ) const
{
  return  m_Values[ 0 ] * m_Values[ 0 ] +
          m_Values[ 1 ] * m_Values[ 1 ] +
          m_Values[ 2 ] * m_Values[ 2 ] +
          m_Values[ 3 ] * m_Values[ 3 ];
}

float
Quaternion::Dot( const Quaternion& other ) const
{
  return  m_Values[ 0 ] * other.m_Values[ 0 ] +
          m_Values[ 1 ] * other.m_Values[ 1 ] +
          m_Values[ 2 ] * other.m_Values[ 2 ] +
          m_Values[ 3 ] * other.m_Values[ 3 ];
}

float
Quaternion::Max( void ) const
{
  return m_Values[ 0 ] > m_Values[ 1 ] ?
         ( m_Values[ 0 ] < m_Values[ 2 ] ?
           ( m_Values[ 2 ] < m_Values[ 3 ] ?
             m_Values[ 3 ] : m_Values[ 2 ] )
           : m_Values[ 0 ] ) :
         m_Values[ 1 ];
}

float
Quaternion::Min( void ) const
{
  return m_Values[ 0 ] < m_Values[ 1 ] ?
         ( m_Values[ 0 ] > m_Values[ 2 ] ?
           ( m_Values[ 2 ] > m_Values[ 3 ] ?
             m_Values[ 3 ] : m_Values[ 2 ] )
           : m_Values[ 0 ] ) :
         m_Values[ 1 ];
}

Quaternion
Quaternion::Clamp( const Quaternion& Min, const Quaternion& Max )
{
  Quaternion result;

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

Quaternion
Quaternion::Conjugate( void ) const
{
  return Quaternion( -m_Values[ 0 ], -m_Values[ 1 ], -m_Values[ 2 ], m_Values[ 3 ] );
}

Quaternion
Quaternion::Normalize( void ) const
{
  return (*this)/Length();
}

Quaternion
Quaternion::Reflect( const Quaternion& normal ) const
{
  return (*this) - ( normal * ( Dot( normal ) * 2 ) );
}

Quaternion
Quaternion::Lerp( const Quaternion& Destination, const float LerpFactor ) const
{
  return ( Destination - ( *this ) ) * LerpFactor + ( *this );
}

Quaternion
Quaternion::NLerp( const Quaternion& Destination, const float LerpFactor, const bool shortestPath ) const
{
  Quaternion correctedDest( Destination );

  if ( shortestPath && Dot( Destination ) < 0 )
    correctedDest = Destination * -1;

  return Lerp( correctedDest, LerpFactor ).Normalize();
}

#define SLERP_EPSILON 1e3

Quaternion
Quaternion::SLerp( const Quaternion& Destination, const float LerpFactor, const bool shortestPath ) const
{
  Quaternion correctedDest( Destination );
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

  return Quaternion( (*this) * src + correctedDest * dest );
}

Vec3f
Quaternion::Forward( void ) const
{
  return Vec3f( 0, 0,  1 ).Rotate( *this );
}

Vec3f
Quaternion::Backward( void ) const
{
  return Vec3f( 0, 0, -1 ).Rotate( *this );
}

Vec3f
Quaternion::Left( void ) const
{
  return Vec3f( -1, 0, 0 ).Rotate( *this );
}

Vec3f
Quaternion::Right( void ) const
{
  return Vec3f(  1, 0, 0 ).Rotate( *this );
}

Vec3f
Quaternion::Up( void ) const
{
  return Vec3f( 0,  1, 0 ).Rotate( *this );
}

Vec3f
Quaternion::Down( void ) const
{
  return Vec3f( 0, -1, 0 ).Rotate( *this );
}

Quaternion
Quaternion::Max( const Quaternion& vector ) const
{
  return Quaternion(
      m_Values[ 0 ] > vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] > vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ],
      m_Values[ 2 ] > vector.m_Values[ 2 ] ? m_Values[ 2 ] : vector.m_Values[ 2 ],
      m_Values[ 3 ] > vector.m_Values[ 3 ] ? m_Values[ 3 ] : vector.m_Values[ 3 ]
  );
}

Quaternion
Quaternion::Min( const Quaternion& vector ) const
{
  return Quaternion(
      m_Values[ 0 ] < vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] < vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ],
      m_Values[ 2 ] < vector.m_Values[ 2 ] ? m_Values[ 2 ] : vector.m_Values[ 2 ],
      m_Values[ 3 ] < vector.m_Values[ 3 ] ? m_Values[ 3 ] : vector.m_Values[ 3 ]
  );
}

Mat4f
Quaternion::RotationMatrix( void ) const
{
  return Mat4f().Rotation( *this );
}

Quaternion
Quaternion::operator +( const float summand ) const
{
  return Quaternion(
    m_Values[ 0 ] + summand,
    m_Values[ 1 ] + summand,
    m_Values[ 2 ] + summand,
    m_Values[ 3 ] + summand
  );
}

Quaternion
Quaternion::operator +( const Quaternion& summand ) const
{
  return Quaternion(
    m_Values[ 0 ] + summand.m_Values[ 0 ],
    m_Values[ 1 ] + summand.m_Values[ 1 ],
    m_Values[ 2 ] + summand.m_Values[ 2 ],
    m_Values[ 3 ] + summand.m_Values[ 3 ]
  );
}

Quaternion
Quaternion::operator -( const float subtrahend ) const
{
  return Quaternion(
    m_Values[ 0 ] - subtrahend,
    m_Values[ 1 ] - subtrahend,
    m_Values[ 2 ] - subtrahend,
    m_Values[ 3 ] - subtrahend
  );
}

Quaternion
Quaternion::operator -( const Quaternion& subtrahend ) const
{
  return Quaternion(
    m_Values[ 0 ] - subtrahend.m_Values[ 0 ],
    m_Values[ 1 ] - subtrahend.m_Values[ 1 ],
    m_Values[ 2 ] - subtrahend.m_Values[ 2 ],
    m_Values[ 3 ] - subtrahend.m_Values[ 3 ]
  );
}

Quaternion
Quaternion::operator *( const float factor ) const
{
  return Quaternion(
    m_Values[ 0 ] * factor,
    m_Values[ 1 ] * factor,
    m_Values[ 2 ] * factor,
    m_Values[ 3 ] * factor
  );
}

Quaternion
Quaternion::operator *( const Vec3f& factor ) const
{
  return Quaternion(
     (m_Values[3] * factor[0]) + (m_Values[1] * factor[2]) - (m_Values[2] * factor[1]),
     (m_Values[3] * factor[1]) + (m_Values[2] * factor[0]) - (m_Values[0] * factor[2]),
     (m_Values[3] * factor[2]) + (m_Values[0] * factor[1]) - (m_Values[1] * factor[0]),
    -(m_Values[0] * factor[0]) - (m_Values[1] * factor[1]) - (m_Values[2] * factor[2])
  );
}

Quaternion
Quaternion::operator *( const Quaternion& factor ) const
{
  return Quaternion(
    m_Values[ 0 ] * factor.m_Values[ 0 ],
    m_Values[ 1 ] * factor.m_Values[ 1 ],
    m_Values[ 2 ] * factor.m_Values[ 2 ],
    m_Values[ 3 ] * factor.m_Values[ 3 ]
  );
}

Quaternion
Quaternion::operator /( const float dividend ) const
{
  if ( dividend == 0.0f ) return Quaternion();

  return Quaternion(
    m_Values[ 0 ] / dividend,
    m_Values[ 1 ] / dividend,
    m_Values[ 2 ] / dividend,
    m_Values[ 3 ] / dividend
  );
}

Quaternion&
Quaternion::operator +=( const Quaternion& summand )
{
  m_Values[ 0 ] += summand.m_Values[ 0 ];
  m_Values[ 1 ] += summand.m_Values[ 1 ];
  m_Values[ 2 ] += summand.m_Values[ 2 ];
  m_Values[ 3 ] += summand.m_Values[ 3 ];

  return *this;
}

Quaternion&
Quaternion::operator +=( const float summand )
{
  m_Values[ 0 ] += summand;
  m_Values[ 1 ] += summand;
  m_Values[ 2 ] += summand;
  m_Values[ 3 ] += summand;

  return *this;
}

Quaternion&
Quaternion::operator -=( const Quaternion& subtrahend )
{
  m_Values[ 0 ] -= subtrahend.m_Values[ 0 ];
  m_Values[ 1 ] -= subtrahend.m_Values[ 1 ];
  m_Values[ 2 ] -= subtrahend.m_Values[ 2 ];
  m_Values[ 3 ] -= subtrahend.m_Values[ 3 ];

  return *this;
}

Quaternion&
Quaternion::operator -=( const float subtrahend )
{
  m_Values[ 0 ] -= subtrahend;
  m_Values[ 1 ] -= subtrahend;
  m_Values[ 2 ] -= subtrahend;
  m_Values[ 3 ] -= subtrahend;

  return *this;
}

Quaternion&
Quaternion::operator *=( const float factor )
{
  m_Values[ 0 ] *= factor;
  m_Values[ 1 ] *= factor;
  m_Values[ 2 ] *= factor;
  m_Values[ 3 ] *= factor;

  return *this;
}

Quaternion&
Quaternion::operator *=( const Vec3f& factor )
{
  Quaternion vec = (*this) * factor;

  memcpy( m_Values, vec.m_Values, sizeof( float ) * 4 );

  return *this;
}

Quaternion&
Quaternion::operator *=( const Quaternion& factor )
{
  m_Values[ 0 ] *= factor.m_Values[ 0 ];
  m_Values[ 1 ] *= factor.m_Values[ 1 ];
  m_Values[ 2 ] *= factor.m_Values[ 2 ];
  m_Values[ 3 ] *= factor.m_Values[ 3 ];

  return *this;
}

Quaternion&
Quaternion::operator /=( const float dividend )
{
  if ( dividend == 0.0f ) return *this;

  m_Values[ 0 ] /= dividend;
  m_Values[ 1 ] /= dividend;
  m_Values[ 2 ] /= dividend;
  m_Values[ 3 ] /= dividend;

  return *this;
}

bool
Quaternion::operator ==( const Quaternion& expr ) const
{
  return  m_Values[ 0 ] == expr.m_Values[ 0 ] &&
          m_Values[ 1 ] == expr.m_Values[ 1 ] &&
          m_Values[ 2 ] == expr.m_Values[ 2 ] &&
          m_Values[ 3 ] == expr.m_Values[ 3 ];
}

bool
Quaternion::operator !=( const Quaternion& expr ) const
{
  return  m_Values[ 0 ] != expr.m_Values[ 0 ] ||
          m_Values[ 1 ] != expr.m_Values[ 1 ] ||
          m_Values[ 2 ] != expr.m_Values[ 2 ] ||
          m_Values[ 3 ] != expr.m_Values[ 3 ];
}

float&
Quaternion::operator []( unsigned int i )
{
  return m_Values[ i ];
}

float
Quaternion::operator []( unsigned int i ) const
{
  return m_Values[ i ];
}

float
Quaternion::X( void ) const
{
  return m_Values[ 0 ];
}

float
Quaternion::Y( void ) const
{
  return m_Values[ 1 ];
}

float
Quaternion::Z( void ) const
{
  return m_Values[ 2 ];
}
float
Quaternion::W( void ) const
{
  return m_Values[ 3 ];
}

Vec2f
Quaternion::XX( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2f
Quaternion::XY( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2f
Quaternion::XZ( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2f
Quaternion::XW( void ) const
{
  return Vec2f( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2f
Quaternion::YX( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 0 ] );
}

Vec2f
Quaternion::YY( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 1 ] );
}

Vec2f
Quaternion::YZ( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 2 ] );
}

Vec2f
Quaternion::YW( void ) const
{
  return Vec2f( m_Values[ 1 ], m_Values[ 3 ] );
}

Vec2f
Quaternion::ZX( void ) const
{
  return Vec2f( m_Values[ 2 ], m_Values[ 0 ] );
}

Vec2f
Quaternion::ZY( void ) const
{
  return Vec2f( m_Values[ 2 ], m_Values[ 1 ] );
}

Vec2f
Quaternion::ZZ( void ) const
{
  return Vec2f( m_Values[ 2 ], m_Values[ 2 ] );
}

Vec2f
Quaternion::ZW( void ) const
{
  return Vec2f( m_Values[ 2 ], m_Values[ 3 ] );
}

Vec2f
Quaternion::WX( void ) const
{
  return Vec2f( m_Values[ 3 ], m_Values[ 0 ] );
}

Vec2f
Quaternion::WY( void ) const
{
  return Vec2f( m_Values[ 3 ], m_Values[ 1 ] );
}

Vec2f
Quaternion::WZ( void ) const
{
  return Vec2f( m_Values[ 3 ], m_Values[ 2 ] );
}

Vec2f
Quaternion::WW( void ) const
{
  return Vec2f( m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::XXX( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::XXY( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::XXZ( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::XXW( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::XYX( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::XYY( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::XYZ( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::XYW( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::XZX( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::XZY( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::XZZ( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::XZW( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::XWX( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::XWY( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::XWZ( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::XWW( void ) const
{
  return Vec3f( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::YXX( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::YXY( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::YXZ( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::YXW( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::YYX( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::YYY( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::YYZ( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::YYW( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::YZX( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::YZY( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::YZZ( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::YZW( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::YWX( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::YWY( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::YWZ( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::YWW( void ) const
{
  return Vec3f( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::ZXX( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::ZXY( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::ZXZ( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::ZXW( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::ZYX( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::ZYY( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::ZYZ( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::ZYW( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::ZZX( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::ZZY( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::ZZZ( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::ZZW( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::ZWX( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::ZWY( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::ZWZ( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::ZWW( void ) const
{
  return Vec3f( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::WXX( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::WXY( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::WXZ( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::WXW( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::WYX( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::WYY( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::WYZ( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::WYW( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::WZX( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::WZY( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::WZZ( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::WZW( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3f
Quaternion::WWX( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3f
Quaternion::WWY( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3f
Quaternion::WWZ( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3f
Quaternion::WWW( void ) const
{
  return Vec3f( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 3 ] );
}

void
Quaternion::Print( void ) const
{
  printf( "( %f | %f | %f | %f )\n",
          m_Values[ 0 ], m_Values[ 1 ], m_Values[ 2 ], m_Values[ 3 ] );
}

const float*
Quaternion::Values( void ) const
{
  return m_Values;
}
