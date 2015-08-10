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

\file Vec3d.cpp

Created on: Feb 18, 2015
\author     fkzey
*/
#include "Vec3d.hpp"

#include <cmath>
#include <cstdio>
#include <cstring>

#include "Quaterniond.hpp"
#include "Vec2d.hpp"

Vec3d::Vec3d( void )
{
  m_Values[ 0 ] = 0.0f;
  m_Values[ 1 ] = 0.0f;
  m_Values[ 2 ] = 0.0f;
}

Vec3d::Vec3d( const double value )
{
  m_Values[ 0 ] = value;
  m_Values[ 1 ] = value;
  m_Values[ 2 ] = value;
}

Vec3d::Vec3d( const Vec3d& other )
{
  m_Values[ 0 ] = other.m_Values[ 0 ];
  m_Values[ 1 ] = other.m_Values[ 1 ];
  m_Values[ 2 ] = other.m_Values[ 2 ];
}

Vec3d::Vec3d( const double x, const double y, const double z )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
  m_Values[ 2 ] = z;
}

Vec3d::~Vec3d( void ) { return; }

void
Vec3d::Set( const double& x, const double& y, const double& z )
{
  m_Values[ 0 ] = x;
  m_Values[ 1 ] = y;
  m_Values[ 2 ] = z;
}

void
Vec3d::X( const double& x )
{
  m_Values[ 0 ] = x;
}

void
Vec3d::Y( const double& y )
{
  m_Values[ 1 ] = y;
}

void
Vec3d::Z( const double& z )
{
  m_Values[ 2 ] = z;
}

double
Vec3d::LengthSq( void ) const
{
  return  m_Values[ 0 ] * m_Values[ 0 ] +
          m_Values[ 1 ] * m_Values[ 1 ] +
          m_Values[ 2 ] * m_Values[ 2 ];
}

double
Vec3d::Length( void ) const
{
  return sqrtf( LengthSq() );
}

double
Vec3d::Dot( const Vec3d& other ) const
{
  return  m_Values[ 0 ] * other.m_Values[ 0 ] +
          m_Values[ 1 ] * other.m_Values[ 1 ] +
          m_Values[ 2 ] * other.m_Values[ 2 ];
}

double
Vec3d::Max( void ) const
{
  return m_Values[ 0 ] > m_Values[ 1 ] ?
         ( m_Values[ 0 ] < m_Values[ 2 ] ?
           m_Values[ 2 ] : m_Values[ 0 ] ) :
         m_Values[ 1 ];
}

double
Vec3d::Min( void ) const
{
  return m_Values[ 0 ] < m_Values[ 1 ] ?
         ( m_Values[ 0 ] > m_Values[ 2 ] ?
           m_Values[ 2 ] : m_Values[ 0 ] ) :
         m_Values[ 1 ];
}

Vec3d
Vec3d::Clamp( const Vec3d& Min, const Vec3d& Max )
{
  Vec3d result;

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

Vec3d
Vec3d::Normalize( void ) const
{
  double length = Length();

  return (*this)/length;
}

Vec3d
Vec3d::Reflect( const Vec3d& normal ) const
{
  return (*this) - ( normal * ( Dot( normal ) * 2 ) );
}

Vec3d
Vec3d::Rotate( const Quaterniond& quaternion ) const
{
  Quaterniond conjugateQ = quaternion.Conjugate();
  Quaterniond w          = quaternion * ( *this ) * conjugateQ;

  return Vec3d( w.X(), w.Y(), w.Z() );
}

Vec3d
Vec3d::Rotate( const Vec3d& Axis, const double Angle ) const
{
  const double sinAngle = sinf( -Angle );
  const double cosAngle = cosf( -Angle );

  return  Cross( Axis * sinAngle ) +              //Rotation on local X
          ( ( *this ) * cosAngle) +               //Rotation on local Z
          Axis * Dot( Axis * ( 1 - cosAngle ) );  //Rotation on local Y
}

Vec3d
Vec3d::Cross( const Vec3d& vector ) const
{
  return Vec3d( m_Values[1] * vector.m_Values[2] - m_Values[2] * vector.m_Values[1],
                m_Values[2] * vector.m_Values[0] - m_Values[0] * vector.m_Values[2],
                m_Values[0] * vector.m_Values[1] - m_Values[1] * vector.m_Values[0] );
}

Vec3d
Vec3d::Lerp( const Vec3d& Destination, double LerpFactor ) const
{
  return ( Destination - ( *this ) ) * LerpFactor + ( *this );
}

Vec3d
Vec3d::Max( const Vec3d& vector ) const
{
  return Vec3d(
      m_Values[ 0 ] > vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] > vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ],
      m_Values[ 2 ] > vector.m_Values[ 2 ] ? m_Values[ 2 ] : vector.m_Values[ 2 ]
  );
}

Vec3d
Vec3d::Min( const Vec3d& vector ) const
{
  return Vec3d(
      m_Values[ 0 ] < vector.m_Values[ 0 ] ? m_Values[ 0 ] : vector.m_Values[ 0 ],
      m_Values[ 1 ] < vector.m_Values[ 1 ] ? m_Values[ 1 ] : vector.m_Values[ 1 ],
      m_Values[ 2 ] < vector.m_Values[ 2 ] ? m_Values[ 2 ] : vector.m_Values[ 2 ]
  );
}

Vec3d
Vec3d::operator +( const double summand ) const
{
  return Vec3d( m_Values[ 0 ] + summand,
                m_Values[ 1 ] + summand,
                m_Values[ 2 ] + summand );
}

Vec3d
Vec3d::operator +( const Vec3d& summand ) const
{
  return Vec3d( m_Values[ 0 ] + summand.m_Values[ 0 ],
                m_Values[ 1 ] + summand.m_Values[ 1 ],
                m_Values[ 2 ] + summand.m_Values[ 2 ] );
}

Vec3d
Vec3d::operator -( const double subtrahend ) const
{
  return Vec3d( m_Values[ 0 ] - subtrahend,
                m_Values[ 1 ] - subtrahend,
                m_Values[ 2 ] - subtrahend );
}

Vec3d
Vec3d::operator -( const Vec3d& subtrahend ) const
{
  return Vec3d( m_Values[ 0 ] - subtrahend.m_Values[ 0 ],
                m_Values[ 1 ] - subtrahend.m_Values[ 1 ],
                m_Values[ 2 ] - subtrahend.m_Values[ 2 ] );
}

Vec3d
Vec3d::operator *( const double factor ) const
{
  return Vec3d( m_Values[ 0 ] * factor,
                m_Values[ 1 ] * factor,
                m_Values[ 2 ] * factor );
}

Vec3d
Vec3d::operator *( const Vec3d& factor ) const
{
  return Vec3d( m_Values[ 0 ] * factor.m_Values[ 0 ],
                m_Values[ 1 ] * factor.m_Values[ 1 ],
                m_Values[ 2 ] * factor.m_Values[ 2 ] );
}

Vec3d
Vec3d::operator /( const double dividend ) const
{
  if ( dividend == 0.0f ) return Vec3d();

  return Vec3d( m_Values[ 0 ] / dividend,
                m_Values[ 1 ] / dividend,
                m_Values[ 2 ] / dividend );
}

Vec3d&
Vec3d::operator +=( const double summand )
{
  m_Values[ 0 ] += summand;
  m_Values[ 1 ] += summand;
  m_Values[ 2 ] += summand;

  return *this;
}

Vec3d&
Vec3d::operator +=( const Vec3d& summand )
{
  m_Values[ 0 ] += summand.m_Values[ 0 ];
  m_Values[ 1 ] += summand.m_Values[ 1 ];
  m_Values[ 2 ] += summand.m_Values[ 2 ];

  return *this;
}
Vec3d&
Vec3d::operator -=( const Vec3d& subtrahend )
{
  m_Values[ 0 ] -= subtrahend.m_Values[ 0 ];
  m_Values[ 1 ] -= subtrahend.m_Values[ 1 ];
  m_Values[ 2 ] -= subtrahend.m_Values[ 2 ];

  return *this;
}

Vec3d&
Vec3d::operator -=( const double subtrahend )
{
  m_Values[ 0 ] -= subtrahend;
  m_Values[ 1 ] -= subtrahend;
  m_Values[ 2 ] -= subtrahend;

  return *this;
}

Vec3d&
Vec3d::operator *=( const double factor )
{
  m_Values[ 0 ] *= factor;
  m_Values[ 1 ] *= factor;
  m_Values[ 2 ] *= factor;

  return *this;
}

Vec3d&
Vec3d::operator *=( const Vec3d& factor )
{
  m_Values[ 0 ] *= factor.m_Values[ 0 ];
  m_Values[ 1 ] *= factor.m_Values[ 1 ];
  m_Values[ 2 ] *= factor.m_Values[ 2 ];

  return *this;
}

Vec3d&
Vec3d::operator /=( const double dividend )
{
  if ( dividend == 0.0f ) return *this;

  m_Values[ 0 ] /= dividend;
  m_Values[ 1 ] /= dividend;
  m_Values[ 2 ] /= dividend;

  return *this;
}

bool
Vec3d::operator ==( const Vec3d& expr ) const
{
  return  m_Values[ 0 ] == expr.m_Values[ 0 ] &&
          m_Values[ 1 ] == expr.m_Values[ 1 ] &&
          m_Values[ 2 ] == expr.m_Values[ 2 ];
}

bool
Vec3d::operator !=( const Vec3d& expr ) const
{
  return  m_Values[ 0 ] != expr.m_Values[ 0 ] ||
          m_Values[ 1 ] != expr.m_Values[ 1 ] ||
          m_Values[ 2 ] != expr.m_Values[ 2 ];
}

double&
Vec3d::operator []( unsigned int i )
{
  return m_Values[ i ];
}

double
Vec3d::operator []( unsigned int i ) const
{
  return m_Values[ i ];
}

double
Vec3d::X( void ) const
{
  return m_Values[ 0 ];
}

double
Vec3d::Y( void ) const
{
  return m_Values[ 1 ];
}

double
Vec3d::Z( void ) const
{
  return m_Values[ 2 ];
}

Vec2d
Vec3d::XX( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 0 ] );
}

Vec2d
Vec3d::XY( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 1 ] );
}

Vec2d
Vec3d::XZ( void ) const
{
  return Vec2d( m_Values[ 0 ], m_Values[ 2 ] );
}

Vec2d
Vec3d::YX( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 0 ] );
}

Vec2d
Vec3d::YY( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 1 ] );
}

Vec2d
Vec3d::YZ( void ) const
{
  return Vec2d( m_Values[ 1 ], m_Values[ 2 ] );
}

Vec2d
Vec3d::ZX( void ) const
{
  return Vec2d( m_Values[ 2 ], m_Values[ 0 ] );
}

Vec2d
Vec3d::ZY( void ) const
{
  return Vec2d( m_Values[ 2 ], m_Values[ 1 ] );
}

Vec2d
Vec3d::ZZ( void ) const
{
  return Vec2d( m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3d
Vec3d::XXX( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3d
Vec3d::XXY( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3d
Vec3d::XXZ( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3d
Vec3d::XYX( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3d
Vec3d::XYY( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3d
Vec3d::XYZ( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3d
Vec3d::XZX( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3d
Vec3d::XZY( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3d
Vec3d::XZZ( void ) const
{
  return Vec3d( m_Values[ 0 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3d
Vec3d::YXX( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3d
Vec3d::YXY( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3d
Vec3d::YXZ( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3d
Vec3d::YYX( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3d
Vec3d::YYY( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3d
Vec3d::YYZ( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3d
Vec3d::YZX( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3d
Vec3d::YZY( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3d
Vec3d::YZZ( void ) const
{
  return Vec3d( m_Values[ 1 ], m_Values[ 2 ], m_Values[ 2 ] );
}

Vec3d
Vec3d::ZXX( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 0 ] );
}

Vec3d
Vec3d::ZXY( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 1 ] );
}

Vec3d
Vec3d::ZXZ( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 0 ], m_Values[ 2 ] );
}

Vec3d
Vec3d::ZYX( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 0 ] );
}

Vec3d
Vec3d::ZYY( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 1 ] );
}

Vec3d
Vec3d::ZYZ( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 1 ], m_Values[ 2 ] );
}

Vec3d
Vec3d::ZZX( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 0 ] );
}

Vec3d
Vec3d::ZZY( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 1 ] );
}

Vec3d
Vec3d::ZZZ( void ) const
{
  return Vec3d( m_Values[ 2 ], m_Values[ 2 ], m_Values[ 2 ] );
}

void
Vec3d::Print( void ) const
{
  printf( "( %f | %f | %f )\n", m_Values[ 0 ], m_Values[ 1 ], m_Values[ 2 ] );
}

const double*
Vec3d::Values( void ) const
{
  return m_Values;
}
