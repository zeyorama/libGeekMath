#include "Mat3d.hpp"

#include "Vec2f.hpp"
#include "Vec3f.hpp"

#include <cmath>
#include <cstdio>
#include <cstring>

static const unsigned int MATRIX_SIZE = sizeof( double ) * 9;

/* ************************************************** */
/* ************************************************** */
/* **************** CON-/DESTRUCTORS  *************** */
/* ************************************************** */
/* ************************************************** */
Mat3d::Mat3d( void )
{
  memset( m_Values, 0.0, MATRIX_SIZE );
}

Mat3d::Mat3d( const Mat3d& other )
{
  memcpy( m_Values, other.m_Values, MATRIX_SIZE );
}

Mat3d::Mat3d( const Vec3f& row1, const Vec3f& row2, const Vec3f& row3 )
{
  m_Values[ 0 ][ 0 ] = row1.X(); m_Values[ 0 ][ 1 ] = row1.Y(); m_Values[ 0 ][ 2 ] = row1.Z();
  m_Values[ 1 ][ 0 ] = row2.X(); m_Values[ 1 ][ 1 ] = row2.Y(); m_Values[ 1 ][ 2 ] = row2.Z();
  m_Values[ 2 ][ 0 ] = row3.X(); m_Values[ 2 ][ 1 ] = row3.Y(); m_Values[ 2 ][ 2 ] = row3.Z();
}

Mat3d::~Mat3d( void ) { return; }

/* ************************************************** */
/* ************************************************** */
/* ********************* PUBLIC  ******************** */
/* ************************************************** */
/* ************************************************** */
Mat3d&
Mat3d::Identity( void )
{
  memset( m_Values, 0.0, MATRIX_SIZE );

  m_Values[ 0 ][ 0 ] = 1.0;
  m_Values[ 1 ][ 1 ] = 1.0;
  m_Values[ 2 ][ 2 ] = 1.0;

  return *this;
}

Mat3d&
Mat3d::Scale( const Vec2f& s )
{
  return Scale( s.X(), s.Y() );
}

Mat3d&
Mat3d::Scale( const double& x, const double& y )
{
  Identity();

  m_Values[ 0 ][ 0 ] = x;
  m_Values[ 1 ][ 1 ] = y;

  return *this;
}

Mat3d&
Mat3d::RotateZ( const double& value )
{
  const double c = cosf( value );
  const double s = sinf( value );

  m_Values[ 0 ][ 0 ] =  c;
  m_Values[ 0 ][ 1 ] = -s;
  m_Values[ 1 ][ 0 ] =  s;
  m_Values[ 1 ][ 1 ] =  c;

  return *this;
}

Mat3d&
Mat3d::Translation( const Vec2f& t )
{
  return Translation( t.X(), t.Y() );
}

Mat3d&
Mat3d::Translation( const double& x, const double& y )
{
  Identity();

  m_Values[ 0 ][ 2 ] = x;
  m_Values[ 1 ][ 2 ] = y;

  return *this;
}

Mat3d
Mat3d::Inverse( void ) const
{
  Mat3d result;
  double determinant = m_Values[0][0] * ( m_Values[1][1] * m_Values[2][2] - m_Values[2][1] * m_Values[1][2] ) -
                      m_Values[0][1] * ( m_Values[1][0] * m_Values[2][2] - m_Values[1][2] * m_Values[2][0] ) +
                      m_Values[0][2] * ( m_Values[1][0] * m_Values[2][1] - m_Values[1][1] * m_Values[2][0] );

  if ( determinant == 0.0 ) return *this;

  double invdet = 1.0 / determinant;

  result.m_Values[0][0] =  ( m_Values[1][1] * m_Values[2][2] - m_Values[2][1] * m_Values[1][2] ) * invdet;
  result.m_Values[1][0] = -( m_Values[0][1] * m_Values[2][2] - m_Values[0][2] * m_Values[2][1] ) * invdet;
  result.m_Values[2][0] =  ( m_Values[0][1] * m_Values[1][2] - m_Values[0][2] * m_Values[1][1] ) * invdet;
  result.m_Values[0][1] = -( m_Values[1][0] * m_Values[2][2] - m_Values[1][2] * m_Values[2][0] ) * invdet;
  result.m_Values[1][1] =  ( m_Values[0][0] * m_Values[2][2] - m_Values[0][2] * m_Values[2][0] ) * invdet;
  result.m_Values[2][1] = -( m_Values[0][0] * m_Values[1][2] - m_Values[1][0] * m_Values[0][2] ) * invdet;
  result.m_Values[0][2] =  ( m_Values[1][0] * m_Values[2][1] - m_Values[2][0] * m_Values[1][1] ) * invdet;
  result.m_Values[1][2] = -( m_Values[0][0] * m_Values[2][1] - m_Values[2][0] * m_Values[0][1] ) * invdet;
  result.m_Values[2][2] =  ( m_Values[0][0] * m_Values[1][1] - m_Values[1][0] * m_Values[0][1] ) * invdet;

  return result;
}

Mat3d
Mat3d::Transpose( void ) const
{
  Mat3d result;

  result.m_Values[ 0 ][ 1 ] = m_Values[ 1 ][ 0 ];
  result.m_Values[ 0 ][ 2 ] = m_Values[ 2 ][ 0 ];
  result.m_Values[ 1 ][ 0 ] = m_Values[ 0 ][ 1 ];
  result.m_Values[ 1 ][ 2 ] = m_Values[ 2 ][ 1 ];
  result.m_Values[ 2 ][ 0 ] = m_Values[ 0 ][ 2 ];
  result.m_Values[ 2 ][ 1 ] = m_Values[ 1 ][ 2 ];

  return result;
}

Mat3d
Mat3d::operator *( const Mat3d& factor ) const
{
  Mat3d result;

  for ( unsigned int row = 0 ; row < 3 ; row++ )
    for ( unsigned int col = 0 ; col < 3; col++ )
      result.m_Values[ row ][ col ] = m_Values[ row ][ 0 ] * factor.m_Values[ 0 ][ col ] +
                                      m_Values[ row ][ 1 ] * factor.m_Values[ 1 ][ col ] +
                                      m_Values[ row ][ 2 ] * factor.m_Values[ 2 ][ col ];

  return result;
}

Vec3f
Mat3d::operator *( const Vec3f& v ) const
{
  Vec3f result;

  for ( unsigned int row = 0 ; row < 3 ; row++ )
    for ( unsigned int col = 0 ; col < 3; col++ )
      result[ row ] = m_Values[ row ][ 0 ] * v.X() +
                      m_Values[ row ][ 1 ] * v.Y() +
                      m_Values[ row ][ 2 ] * v.Z();

  return result;
}

Mat3d&
Mat3d::operator *=( const Mat3d& factor )
{
  Mat3d result;

  for ( unsigned int row = 0 ; row < 3 ; row++ )
    for ( unsigned int col = 0 ; col < 3; col++ )
      for( unsigned int trow = 0; trow < 3; trow++ )
        result.m_Values[ row ][ col ] += m_Values[ trow ][ col ] * factor.m_Values[ row ][ trow ];

  memcpy( m_Values, result.m_Values, MATRIX_SIZE );

  return *this;
}

double*
Mat3d::operator []( unsigned int row )
{
  return m_Values[ row ];
}

const double*
Mat3d::operator []( unsigned int row ) const
{
  return m_Values[ row ];
}

const double*
Mat3d::Values( void ) const
{
  return *m_Values;
}

void
Mat3d::Set( const unsigned int row, const unsigned int col, const double& value )
{
  m_Values[ row ][ col ] = value;
}

void
Mat3d::Print( void ) const
{
  printf( "( %f | %f | %f )", m_Values[ 0 ][ 0 ], m_Values[ 0 ][ 1 ], m_Values[ 0 ][ 2 ] );
  printf( "( %f | %f | %f )", m_Values[ 1 ][ 0 ], m_Values[ 1 ][ 1 ], m_Values[ 1 ][ 2 ] );
  printf( "( %f | %f | %f )", m_Values[ 2 ][ 0 ], m_Values[ 2 ][ 1 ], m_Values[ 2 ][ 2 ] );
}

/* ************************************************** */
/* ************************************************** */
/* *******************  PROTECTED ******************* */
/* ************************************************** */
/* ************************************************** */

/* ************************************************** */
/* ************************************************** */
/* ********************* PRIVATE ******************** */
/* ************************************************** */
/* ************************************************** */
