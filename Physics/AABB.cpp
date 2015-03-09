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

 \file AABB.cpp

 Created on: Mar 9, 2015
 \author     fkzey
 */

#include "AABB.h"

#include "IntersectData.h"
#include "BoundingSphere.h"
#include "ColliderTypes.hpp"

#include <cstdio>

AABB::AABB( const Vec3f& MinExtend, const Vec3f& MaxExtend ) :
  Collider( AABB_COLLIDER ),
  m_Max( MaxExtend ),
  m_Min( MinExtend ) { return; }

AABB::~AABB( void ) { return; }

void
AABB::Translate( const Vec3f& Translation )
{
  (void)Translation;
}

Vec3f
AABB::Center( void ) const
{
  return Vec3f();
}

IntersectData
AABB::Intersect( const Collider& other ) const
{
  if      ( other.Type() == Type() )
    return IntersectAABB( (const AABB&)other );
  else if ( other.Type() == Type() )
    return IntersectBSphere( (const BoundingSphere&)other );

  return IntersectData( false, 0 );
}

IntersectData
AABB::IntersectAABB( const AABB& aabb ) const
{
  Vec3f distances1 = aabb.m_Max - m_Max;
  Vec3f distances2 = m_Min - aabb.m_Min;
  Vec3f distances  = Vec3f( distances1.Max( distances2 ) );

  float maxDistance = distances.Max();

  //TODO: This might actually need to return the minDistance if they are intersecting.
  return IntersectData(maxDistance < 0, distances);
}

IntersectData
AABB::IntersectBSphere( const BoundingSphere& Sphere ) const
{
  puts( "AABB::IntersectBSphere currently not implemented." );

  return IntersectData( false, 0 );
}
