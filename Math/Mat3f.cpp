#include "Mat3f.hpp"

#include "Vec2f.hpp"
#include "Vec3f.hpp"

#include <cstdio>
#include <cstring>

static const unsigned int MATRIX_SIZE = sizeof( float ) * 9;

/* ************************************************** */
/* ************************************************** */
/* **************** CON-/DESTRUCTORS  *************** */
/* ************************************************** */
/* ************************************************** */
Mat3f::Mat3f( void )
{
  memset( m_Values, 0.0f, MATRIX_SIZE );
}

Mat3f::Mat3f( const Mat3f& other )
{
  memcpy( m_Values, other.m_Values, MATRIX_SIZE );
}

Mat3f::Mat3f( const Vec3f& row1, const Vec3f& row2, const Vec3f& row3 )
{
  m_Values[ 0 ][ 0 ] = row1.X(); m_Values[ 0 ][ 1 ] = row1.Y(); m_Values[ 0 ][ 2 ] = row1.Z();
  m_Values[ 1 ][ 0 ] = row2.X(); m_Values[ 1 ][ 1 ] = row2.Y(); m_Values[ 1 ][ 2 ] = row2.Z();
  m_Values[ 2 ][ 0 ] = row3.X(); m_Values[ 2 ][ 1 ] = row3.Y(); m_Values[ 2 ][ 2 ] = row3.Z();
}

Mat3f::~Mat3f( void ) { return; }

/* ************************************************** */
/* ************************************************** */
/* ********************* PUBLIC  ******************** */
/* ************************************************** */
/* ************************************************** */
Mat3f&
Mat3f::Identity( void )
{
  memset( m_Values, 0.0f, MATRIX_SIZE );

  m_Values[ 0 ][ 0 ] = 1.0f;
  m_Values[ 1 ][ 1 ] = 1.0f;
  m_Values[ 2 ][ 2 ] = 1.0f;

  return *this;
}

Mat3f&
Mat3f::Scale( const Vec2f& s )
{
  return Scale( s.X(), s.Y() );
}

Mat3f&
Mat3f::Scale( const float& x, const float& y )
{
  m_Values[ 0 ][ 0 ] = x;
  m_Values[ 1 ][ 1 ] = y;

  return *this;
}

Mat3f&
Mat3f::Translation( const Vec2f& t )
{
  return Translation( t.X(), t.Y() );
}

Mat3f&
Mat3f::Translation( const float& x, const float& y )
{
  m_Values[ 0 ][ 2 ] = x;
  m_Values[ 1 ][ 2 ] = y;

  return *this;
}

Mat3f
Mat3f::operator *( const Mat3f& factor ) const
{
  Mat3f result;

  for ( unsigned int row = 0 ; row < 3 ; row++ )
    for ( unsigned int col = 0 ; col < 3; col++ )
      result.m_Values[ row ][ col ] = m_Values[ row ][ 0 ] * factor.m_Values[ 0 ][ col ] +
                                      m_Values[ row ][ 1 ] * factor.m_Values[ 1 ][ col ] +
                                      m_Values[ row ][ 2 ] * factor.m_Values[ 2 ][ col ];

  return result;
}

Vec3f
Mat3f::operator *( const Vec3f& v ) const
{
  Vec3f result;

  for ( unsigned int row = 0 ; row < 3 ; row++ )
    for ( unsigned int col = 0 ; col < 3; col++ )
      result[ row ] = m_Values[ row ][ 0 ] * v.X() +
                      m_Values[ row ][ 1 ] * v.Y() +
                      m_Values[ row ][ 2 ] * v.Z();

  return result;
}

Mat3f&
Mat3f::operator *=( const Mat3f& factor )
{
  Mat3f result;

  for ( unsigned int row = 0 ; row < 3 ; row++ )
    for ( unsigned int col = 0 ; col < 3; col++ )
      for( unsigned int trow = 0; trow < 3; trow++ )
        result.m_Values[ row ][ col ] += m_Values[ trow ][ col ] * factor.m_Values[ row ][ trow ];

  memcpy( m_Values, result.m_Values, MATRIX_SIZE );

  return *this;
}

float*
Mat3f::operator []( unsigned int row )
{
  return m_Values[ row ];
}

const float*
Mat3f::operator []( unsigned int row ) const
{
  return m_Values[ row ];
}

const float*
Mat3f::Values( void ) const
{
  return *m_Values;
}

void
Mat3f::Print( void ) const
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
