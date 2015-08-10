#include "Mat3i.hpp"

#include <cstdio>
#include <cstring>

static const unsigned int MATRIX_SIZE = sizeof( int ) * 9;

/* ************************************************** */
/* ************************************************** */
/* **************** CON-/DESTRUCTORS  *************** */
/* ************************************************** */
/* ************************************************** */
Mat3i::Mat3i( void )
{
  memset( m_Values, 0, MATRIX_SIZE );
}

Mat3i::Mat3i( const Mat3i& other )
{
  memcpy( m_Values, other.m_Values, MATRIX_SIZE );
}

Mat3i::~Mat3i( void ) { return; }

/* ************************************************** */
/* ************************************************** */
/* ********************* PUBLIC  ******************** */
/* ************************************************** */
/* ************************************************** */
Mat3i&
Mat3i::Identity( void )
{
  memset( m_Values, 0, MATRIX_SIZE );

  m_Values[ 0 ][ 0 ] = 1;
  m_Values[ 1 ][ 1 ] = 1;
  m_Values[ 2 ][ 2 ] = 1;

  return *this;
}

Mat3i&
Mat3i::Translation( const int& x, const int& y )
{
  Identity();

  m_Values[ 0 ][ 2 ] = x;
  m_Values[ 1 ][ 2 ] = y;

  return *this;
}

Mat3i
Mat3i::Inverse( void ) const
{
  Mat3i result;
  int determinant = m_Values[0][0] * ( m_Values[1][1] * m_Values[2][2] - m_Values[2][1] * m_Values[1][2] ) -
                    m_Values[0][1] * ( m_Values[1][0] * m_Values[2][2] - m_Values[1][2] * m_Values[2][0] ) +
                    m_Values[0][2] * ( m_Values[1][0] * m_Values[2][1] - m_Values[1][1] * m_Values[2][0] );

  if ( determinant == 0 ) return *this;

  float invdet = 1.0f / determinant;

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

Mat3i
Mat3i::Transpose( void ) const
{
  Mat3i result;

  result.m_Values[ 0 ][ 1 ] = m_Values[ 1 ][ 0 ];
  result.m_Values[ 0 ][ 2 ] = m_Values[ 2 ][ 0 ];
  result.m_Values[ 1 ][ 0 ] = m_Values[ 0 ][ 1 ];
  result.m_Values[ 1 ][ 2 ] = m_Values[ 2 ][ 1 ];
  result.m_Values[ 2 ][ 0 ] = m_Values[ 0 ][ 2 ];
  result.m_Values[ 2 ][ 1 ] = m_Values[ 1 ][ 2 ];

  return result;
}

Mat3i
Mat3i::operator *( const Mat3i& factor ) const
{
  Mat3i result;

  for ( unsigned int row = 0 ; row < 3 ; row++ )
    for ( unsigned int col = 0 ; col < 3; col++ )
      result.m_Values[ row ][ col ] = m_Values[ row ][ 0 ] * factor.m_Values[ 0 ][ col ] +
                                      m_Values[ row ][ 1 ] * factor.m_Values[ 1 ][ col ] +
                                      m_Values[ row ][ 2 ] * factor.m_Values[ 2 ][ col ];

  return result;
}

Mat3i&
Mat3i::operator *=( const Mat3i& factor )
{
  Mat3i result;

  for ( unsigned int row = 0 ; row < 3 ; row++ )
    for ( unsigned int col = 0 ; col < 3; col++ )
      for( unsigned int trow = 0; trow < 3; trow++ )
        result.m_Values[ row ][ col ] += m_Values[ trow ][ col ] * factor.m_Values[ row ][ trow ];

  memcpy( m_Values, result.m_Values, MATRIX_SIZE );

  return *this;
}

int*
Mat3i::operator []( unsigned int row )
{
  return m_Values[ row ];
}

const int*
Mat3i::operator []( unsigned int row ) const
{
  return m_Values[ row ];
}

const int*
Mat3i::Values( void ) const
{
  return *m_Values;
}

void
Mat3i::Set( const unsigned int row, const unsigned int col, const int& value )
{
  m_Values[ row ][ col ] = value;
}

void
Mat3i::Print( void ) const
{
  printf( "( %i | %i | %i )", m_Values[ 0 ][ 0 ], m_Values[ 0 ][ 1 ], m_Values[ 0 ][ 2 ] );
  printf( "( %i | %i | %i )", m_Values[ 1 ][ 0 ], m_Values[ 1 ][ 1 ], m_Values[ 1 ][ 2 ] );
  printf( "( %i | %i | %i )", m_Values[ 2 ][ 0 ], m_Values[ 2 ][ 1 ], m_Values[ 2 ][ 2 ] );
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
