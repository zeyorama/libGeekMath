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

 \file Quaterniond.cpp

 Created on: Mar 9, 2015
 \author     fkzey
 */

#include "Quaterniond.hpp"

#include <cmath>
#include <cstdio>
#include <cstring>

#include "Mat4d.hpp"
#include "Vec2d.hpp"
#include "Vec3d.hpp"

Quaterniond::Quaterniond( const Mat4d& matrix )
{
  const double trace = matrix[ 0 ][ 0 ] + matrix[ 1 ][ 1 ] + matrix[ 2 ][ 2 ];

  if      ( trace > 0 )
  {
    const double s = 0.5f / sqrtf( trace + 1.0f );

    m_Values[ 3 ] = 0.25f / s;
    m_Values[ 0 ] = ( matrix[ 1 ][ 2 ] - matrix[ 2 ][ 1 ] ) * s;
    m_Values[ 1 ] = ( matrix[ 2 ][ 0 ] - matrix[ 0 ][ 2 ] ) * s;
    m_Values[ 2 ] = ( matrix[ 0 ][ 1 ] - matrix[ 1 ][ 0 ] ) * s;
  }
  else if ( matrix[ 0 ][ 0 ] > matrix[ 1 ][ 1 ] && matrix[ 0 ][ 0 ] > matrix[ 2 ][ 2 ] )
  {
    const double s = 2.0f * sqrtf( 1.0f + matrix[ 0 ][ 0 ] - matrix[ 1 ][ 1 ] - matrix[ 2 ][ 2 ] );

    m_Values[ 3 ] = ( matrix[ 1 ][ 2 ] - matrix[ 2 ][ 1 ] ) / s;
    m_Values[ 0 ] = 0.25f * s;
    m_Values[ 1 ] = ( matrix[ 1 ][ 0 ] + matrix[ 0 ][ 1 ] ) / s;
    m_Values[ 2 ] = ( matrix[ 2 ][ 0 ] + matrix[ 0 ][ 2 ] ) / s;
  }
  else if ( matrix[ 1 ][ 1 ] > matrix[ 2 ][ 2 ])
  {
    const double s = 2.0f * sqrtf( 1.0f + matrix[ 1 ][ 1 ] - matrix[ 0 ][ 0 ] - matrix[ 2 ][ 2 ] );

    m_Values[ 3 ] = ( matrix[ 2 ][ 0 ] - matrix[ 0 ][ 2 ] ) / s;
    m_Values[ 0 ] = ( matrix[ 1 ][ 0 ] + matrix[ 0 ][ 1 ] ) / s;
    m_Values[ 1 ] = 0.25f * s;
    m_Values[ 2 ] = ( matrix[ 2 ][ 1 ] + matrix[ 1 ][ 2 ] ) / s;
  }
  else
  {
    const double s = 2.0f * sqrtf( 1.0f + matrix[ 2 ][ 2 ] - matrix[ 1 ][ 1 ] - matrix[ 0 ][ 0 ]);

    m_Values[ 3 ] = ( matrix[ 0 ][ 1 ] - matrix[ 1 ][ 0 ] ) / s;
    m_Values[ 0 ] = ( matrix[ 2 ][ 0 ] + matrix[ 0 ][ 2 ] ) / s;
    m_Values[ 1 ] = ( matrix[ 1 ][ 2 ] + matrix[ 2 ][ 1 ] ) / s;
    m_Values[ 2 ] = 0.25f * s;
  }

  const double length = Length();

  m_Values[ 3 ] = m_Values[ 3 ] / length;
  m_Values[ 0 ] = m_Values[ 0 ] / length;
  m_Values[ 1 ] = m_Values[ 1 ] / length;
  m_Values[ 2 ] = m_Values[ 2 ] / length;
}

Quaterniond::Quaterniond( const Vec2d& vector )
{
  m_Values[ 0 ] = vector.X();
  m_Values[ 1 ] = vector.Y();
  m_Values[ 2 ] = 0.0f;
  m_Values[ 3 ] = 1.0f;
}

Quaterniond::Quaterniond( const Vec3d& vector )
{
  m_Values[ 0 ] = vector.X();
  m_Values[ 1 ] = vector.Y();
  m_Values[ 2 ] = vector.Z();
  m_Values[ 3 ] = 1.0f;
}

Quaterniond::Quaterniond( const Quaterniond& vector )
{
  m_Values[ 0 ] = vector.m_Values[ 0 ];
  m_Values[ 1 ] = vector.m_Values[ 1 ];
  m_Values[ 2 ] = vector.m_Values[ 2 ];
  m_Values[ 3 ] = vector.m_Values[ 3 ];
}

Quaterniond::Quaterniond( const Vec3d& Axis, const double Angle )
{
  double sinHalfAngle = sinf( Angle / 2 );
  double cosHalfAngle = cosf( Angle / 2 );

  m_Values[0] = Axis.X() * sinHalfAngle;
  m_Values[1] = Axis.Y() * sinHalfAngle;
  m_Values[2] = Axis.Z() * sinHalfAngle;
  m_Values[3] = cosHalfAngle;
}

Quaterniond::Quaterniond( const double x, const double y, const double z, const double w )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
  m_Values[ 2 ] = z;
  m_Values[ 3 ] = w;
}

Quaterniond::~Quaterniond( void ) { return; }

void
Quaterniond::Set( const double& x, const double& y, const double& z, const double& w )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
  m_Values[ 2 ] = z;
  m_Values[ 3 ] = w;
}

void
Quaterniond::X( const double& x )
{
  m_Values[ 0 ] = x;
}

void
Quaterniond::Y( const double& y )
{
  m_Values[ 1 ] = y;
}

void
Quaterniond::Z( const double& z )
{
  m_Values[ 2 ] = z;
}

void
Quaterniond::W( const double& w )
{
  m_Values[ 3 ] = w;
}

double
Quaterniond::Length( void ) const
{
  return sqrtf( LengthSq() );
}

double
Quaterniond::LengthSq( void ) const
{
  return  m_Values[ 0 ] * m_Values[ 0 ] +
          m_Values[ 1 ] * m_Values[ 1 ] +
          m_Values[ 2 ] * m_Values[ 2 ] +
          m_Values[ 3 ] * m_Values[ 3 ];
}

double
Quaterniond::Dot( const Quaterniond& other ) const
{
  return  m_Values[ 0 ] * other.m_Values[ 0 ] +
          m_Values[ 1 ] * other.m_Values[ 1 ] +
          m_Values[ 2 ] * other.m_Values[ 2 ] +
          m_Values[ 3 ] * other.m_Values[ 3 ];
}

double
Quaterniond::Max( void ) const
{
  return m_Values[ 0 ] > m_Values[ 1 ] ?
         ( m_Values[ 0 ] < m_Values[ 2 ] ?
           ( m_Values[ 2 ] < m_Values[ 3 ] ?
             m_Values[ 3 ] : m_Values[ 2 ] )
           : m_Values[ 0 ] ) :
         m_Values[ 1 ];
}

double
Quaterniond::Min( void ) const
{
  return m_Values[ 0 ] < m_Values[ 1 ] ?
         ( m_Values[ 0 ] > m_Values[ 2 ] ?
           ( m_Values[ 2 ] > m_Values[ 3 ] ?
             m_Values[ 3 ] : m_Values[ 2 ] )
           : m_Values[ 0 ] ) :
         m_Values[ 1 ];
}

Quaterniond
Quaterniond::Clamp( const Quaterniond& Min, const Quaterniond& Max )
{
  Quaterniond result;

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

Quaterniond
Quaterniond::Conjugate( void ) const
{
  return Quaterniond( -m_Values[ 0 ], -m_Values[ 1 ], -m_Values[ 2 ], m_Values[ 3 ] );
}

Quaterniond
Quaterniond::Normalize( void ) const
{
  return (*this)/Length();
}

Quaterniond
Quaterniond::Reflect( const Quaterniond& normal ) const
{
  return (*this) - ( normal * ( Dot( normal ) * 2 ) );
}

Quaterniond
Quaterniond::Lerp( const Quaterniond& Destination, const double LerpFactor ) const
{
  return ( Destination - ( *this ) ) * LerpFactor + ( *this );
}

Quaterniond
Quaterniond::NLerp( const Quaterniond& Destination, const double LerpFactor, const bool shortestPath ) const
{
  Quaterniond correctedDest( Destination );

  if ( shortestPath && Dot( Destination ) < 0 )
    correctedDest = Destination * -1;

  return Lerp( correctedDest, LerpFactor ).Normalize();
}

#define SLERP_EPSILON 1e3

Quaterniond
Quaterniond::SLerp( const Quaterniond& Destination, const double LerpFactor, const bool shortestPath ) const
{
  Quaterniond correctedDest( Destination );
  double cos = Dot( Destination );

  if ( shortestPath && cos < 0 )
  {
    cos           *= -1;
    correctedDest  = Destination * -1;
  }

  if ( fabs( cos ) > ( 1 - SLERP_EPSILON ) )
    return NLerp( correctedDest, LerpFactor, false );

  double sin    = sqrtf( 1.f - cos * cos );
  double angle  = atan2f( sin, cos );
  double invSin = 1.f / sin;

  double src  = sinf( ( 1.f - LerpFactor ) * angle ) * invSin;
  double dest = sinf( LerpFactor * angle ) * invSin;

  return Quaterniond( (*this) * src + correctedDest * dest );
}

Vec3d
Quaterniond::Forward( void ) const
{
  return Vec3d( 0, 0,  1 ).Rotate( *this );
}

Vec3d
Quaterniond::Backward( void ) const
{
  return Vec3d( 0, 0, -1 ).Rotate( *this );
}

Vec3d
Quaterniond::Left( void ) const
{
  return Vec3d( -1, 0, 0 ).Rotate( *this );
}

Vec3d
Quaterniond::Right( void ) const
{
  return Vec3d(  1, 0, 0 ).Rotate( *this );
}

Vec3d
Quaterniond::Up( void ) const
{
  return Vec3d( 0,  1, 0 ).Rotate( *this );
}

Vec3d
Quaterniond::Down( void ) const
{
  return Vec3d( 0, -1, 0 ).Rotate( *this );
}

Quaterniond
Quaterniond::Max( const Quaterniond& vector ) const
{
  return Quaterniond(
      m_Values[ 0 ] > vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] > vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ],
      m_Values[ 2 ] > vector.m_Values[ 2 ] ? m_Values[ 2 ] : vector.m_Values[ 2 ],
      m_Values[ 3 ] > vector.m_Values[ 3 ] ? m_Values[ 3 ] : vector.m_Values[ 3 ]
  );
}

Quaterniond
Quaterniond::Min( const Quaterniond& vector ) const
{
  return Quaterniond(
      m_Values[ 0 ] < vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] < vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ],
      m_Values[ 2 ] < vector.m_Values[ 2 ] ? m_Values[ 2 ] : vector.m_Values[ 2 ],
      m_Values[ 3 ] < vector.m_Values[ 3 ] ? m_Values[ 3 ] : vector.m_Values[ 3 ]
  );
}

Mat4d
Quaterniond::RotationMatrix( void ) const
{
  return Mat4d().Rotation( *this );
}

Quaterniond
Quaterniond::operator +( const double summand ) const
{
  return Quaterniond(
    m_Values[ 0 ] + summand,
    m_Values[ 1 ] + summand,
    m_Values[ 2 ] + summand,
    m_Values[ 3 ] + summand
  );
}

Quaterniond
Quaterniond::operator +( const Quaterniond& summand ) const
{
  return Quaterniond(
    m_Values[ 0 ] + summand.m_Values[ 0 ],
    m_Values[ 1 ] + summand.m_Values[ 1 ],
    m_Values[ 2 ] + summand.m_Values[ 2 ],
    m_Values[ 3 ] + summand.m_Values[ 3 ]
  );
}

Quaterniond
Quaterniond::operator -( const double subtrahend ) const
{
  return Quaterniond(
    m_Values[ 0 ] - subtrahend,
    m_Values[ 1 ] - subtrahend,
    m_Values[ 2 ] - subtrahend,
    m_Values[ 3 ] - subtrahend
  );
}

Quaterniond
Quaterniond::operator -( const Quaterniond& subtrahend ) const
{
  return Quaterniond(
    m_Values[ 0 ] - subtrahend.m_Values[ 0 ],
    m_Values[ 1 ] - subtrahend.m_Values[ 1 ],
    m_Values[ 2 ] - subtrahend.m_Values[ 2 ],
    m_Values[ 3 ] - subtrahend.m_Values[ 3 ]
  );
}

Quaterniond
Quaterniond::operator *( const double factor ) const
{
  return Quaterniond(
    m_Values[ 0 ] * factor,
    m_Values[ 1 ] * factor,
    m_Values[ 2 ] * factor,
    m_Values[ 3 ] * factor
  );
}

Quaterniond
Quaterniond::operator *( const Vec3d& factor ) const
{
  return Quaterniond(
     (m_Values[3] * factor[0]) + (m_Values[1] * factor[2]) - (m_Values[2] * factor[1]),
     (m_Values[3] * factor[1]) + (m_Values[2] * factor[0]) - (m_Values[0] * factor[2]),
     (m_Values[3] * factor[2]) + (m_Values[0] * factor[1]) - (m_Values[1] * factor[0]),
    -(m_Values[0] * factor[0]) - (m_Values[1] * factor[1]) - (m_Values[2] * factor[2])
  );
}

Quaterniond
Quaterniond::operator *( const Quaterniond& factor ) const
{
  return Quaterniond(
    m_Values[ 0 ] * factor.m_Values[ 3 ] + m_Values[ 3 ] * factor.m_Values[ 0 ] + m_Values[ 1 ] * factor.m_Values[ 2 ] - m_Values[ 2 ] * factor.m_Values[ 1 ],
    m_Values[ 1 ] * factor.m_Values[ 3 ] + m_Values[ 3 ] * factor.m_Values[ 1 ] + m_Values[ 2 ] * factor.m_Values[ 0 ] - m_Values[ 0 ] * factor.m_Values[ 2 ],
    m_Values[ 2 ] * factor.m_Values[ 3 ] + m_Values[ 3 ] * factor.m_Values[ 2 ] + m_Values[ 0 ] * factor.m_Values[ 1 ] - m_Values[ 1 ] * factor.m_Values[ 0 ],
    m_Values[ 3 ] * factor.m_Values[ 3 ] - m_Values[ 0 ] * factor.m_Values[ 0 ] - m_Values[ 1 ] * factor.m_Values[ 1 ] - m_Values[ 2 ] * factor.m_Values[ 2 ]
  );
}

Quaterniond
Quaterniond::operator /( const double dividend ) const
{
  if ( dividend == 0.0f ) return Quaterniond();

  return Quaterniond(
    m_Values[ 0 ] / dividend,
    m_Values[ 1 ] / dividend,
    m_Values[ 2 ] / dividend,
    m_Values[ 3 ] / dividend
  );
}

Quaterniond&
Quaterniond::operator +=( const Quaterniond& summand )
{
  m_Values[ 0 ] += summand.m_Values[ 0 ];
  m_Values[ 1 ] += summand.m_Values[ 1 ];
  m_Values[ 2 ] += summand.m_Values[ 2 ];
  m_Values[ 3 ] += summand.m_Values[ 3 ];

  return *this;
}

Quaterniond&
Quaterniond::operator +=( const double summand )
{
  m_Values[ 0 ] += summand;
  m_Values[ 1 ] += summand;
  m_Values[ 2 ] += summand;
  m_Values[ 3 ] += summand;

  return *this;
}

Quaterniond&
Quaterniond::operator -=( const Quaterniond& subtrahend )
{
  m_Values[ 0 ] -= subtrahend.m_Values[ 0 ];
  m_Values[ 1 ] -= subtrahend.m_Values[ 1 ];
  m_Values[ 2 ] -= subtrahend.m_Values[ 2 ];
  m_Values[ 3 ] -= subtrahend.m_Values[ 3 ];

  return *this;
}

Quaterniond&
Quaterniond::operator -=( const double subtrahend )
{
  m_Values[ 0 ] -= subtrahend;
  m_Values[ 1 ] -= subtrahend;
  m_Values[ 2 ] -= subtrahend;
  m_Values[ 3 ] -= subtrahend;

  return *this;
}

Quaterniond&
Quaterniond::operator *=( const double factor )
{
  m_Values[ 0 ] *= factor;
  m_Values[ 1 ] *= factor;
  m_Values[ 2 ] *= factor;
  m_Values[ 3 ] *= factor;

  return *this;
}

Quaterniond&
Quaterniond::operator *=( const Vec3d& factor )
{
  Quaterniond vec = (*this) * factor;

  memcpy( m_Values, vec.m_Values, sizeof( double ) * 4 );

  return *this;
}

Quaterniond&
Quaterniond::operator *=( const Quaterniond& factor )
{
  m_Values[ 0 ] *= factor.m_Values[ 0 ];
  m_Values[ 1 ] *= factor.m_Values[ 1 ];
  m_Values[ 2 ] *= factor.m_Values[ 2 ];
  m_Values[ 3 ] *= factor.m_Values[ 3 ];

  return *this;
}

Quaterniond&
Quaterniond::operator /=( const double dividend )
{
  if ( dividend == 0.0f ) return *this;

  m_Values[ 0 ] /= dividend;
  m_Values[ 1 ] /= dividend;
  m_Values[ 2 ] /= dividend;
  m_Values[ 3 ] /= dividend;

  return *this;
}

bool
Quaterniond::operator ==( const Quaterniond& expr ) const
{
  return  m_Values[ 0 ] == expr.m_Values[ 0 ] &&
          m_Values[ 1 ] == expr.m_Values[ 1 ] &&
          m_Values[ 2 ] == expr.m_Values[ 2 ] &&
          m_Values[ 3 ] == expr.m_Values[ 3 ];
}

bool
Quaterniond::operator !=( const Quaterniond& expr ) const
{
  return  m_Values[ 0 ] != expr.m_Values[ 0 ] ||
          m_Values[ 1 ] != expr.m_Values[ 1 ] ||
          m_Values[ 2 ] != expr.m_Values[ 2 ] ||
          m_Values[ 3 ] != expr.m_Values[ 3 ];
}

double&
Quaterniond::operator []( unsigned int i )
{
  return m_Values[ i ];
}

double
Quaterniond::operator []( unsigned int i ) const
{
  return m_Values[ i ];
}

double
Quaterniond::X( void ) const
{
  return m_Values[ 0 ];
}

double
Quaterniond::Y( void ) const
{
  return m_Values[ 1 ];
}

double
Quaterniond::Z( void ) const
{
  return m_Values[ 2 ];
}
double
Quaterniond::W( void ) const
{
  return m_Values[ 3 ];
}

Vec2d
Quaterniond::XX( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2d
Quaterniond::XY( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2d
Quaterniond::XZ( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2d
Quaterniond::XW( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2d
Quaterniond::YX( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 0 ] );
}

Vec2d
Quaterniond::YY( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 1 ] );
}

Vec2d
Quaterniond::YZ( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 2 ] );
}

Vec2d
Quaterniond::YW( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 3 ] );
}

Vec2d
Quaterniond::ZX( void ) const
{
  return Vec2d( m_Values[ 2 ], m_Values[ 0 ] );
}

Vec2d
Quaterniond::ZY( void ) const
{
  return Vec2d( m_Values[ 2 ], m_Values[ 1 ] );
}

Vec2d
Quaterniond::ZZ( void ) const
{
  return Vec2d( m_Values[ 2 ], m_Values[ 2 ] );
}

Vec2d
Quaterniond::ZW( void ) const
{
  return Vec2d( m_Values[ 2 ], m_Values[ 3 ] );
}

Vec2d
Quaterniond::WX( void ) const
{
  return Vec2d( m_Values[ 3 ], m_Values[ 0 ] );
}

Vec2d
Quaterniond::WY( void ) const
{
  return Vec2d( m_Values[ 3 ], m_Values[ 1 ] );
}

Vec2d
Quaterniond::WZ( void ) const
{
  return Vec2d( m_Values[ 3 ], m_Values[ 2 ] );
}

Vec2d
Quaterniond::WW( void ) const
{
  return Vec2d( m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::XXX( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::XXY( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::XXZ( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::XXW( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::XYX( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::XYY( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::XYZ( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::XYW( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::XZX( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::XZY( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::XZZ( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::XZW( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::XWX( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::XWY( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::XWZ( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::XWW( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::YXX( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::YXY( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::YXZ( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::YXW( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::YYX( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::YYY( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::YYZ( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::YYW( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::YZX( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::YZY( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::YZZ( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::YZW( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::YWX( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::YWY( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::YWZ( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::YWW( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::ZXX( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::ZXY( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::ZXZ( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::ZXW( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::ZYX( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::ZYY( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::ZYZ( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::ZYW( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::ZZX( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::ZZY( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::ZZZ( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::ZZW( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::ZWX( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::ZWY( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::ZWZ( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::ZWW( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 3 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::WXX( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::WXY( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::WXZ( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::WXW( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 0 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::WYX( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::WYY( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::WYZ( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::WYW( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 1 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::WZX( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::WZY( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::WZZ( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::WZW( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 2 ], m_Values[ 3 ] );
}

Vec3d
Quaterniond::WWX( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 0 ] );
}

Vec3d
Quaterniond::WWY( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 1 ] );
}

Vec3d
Quaterniond::WWZ( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 2 ] );
}

Vec3d
Quaterniond::WWW( void ) const
{
  return Vec3d( m_Values[ 3 ], m_Values[ 3 ], m_Values[ 3 ] );
}

void
Quaterniond::Print( void ) const
{
  printf( "( %f | %f | %f | %f )\n", m_Values[ 0 ], m_Values[ 1 ], m_Values[ 2 ], m_Values[ 3 ] );
}

const double*
Quaterniond::Values( void ) const
{
  return m_Values;
}
