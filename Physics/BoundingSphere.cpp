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

 \file BoundingSphere.cpp

 Created on: Mar 9, 2015
 \author     fkzey
 */

#include "BoundingSphere.h"

#include "AABB.h"
#include "IntersectData.h"
#include "ColliderTypes.hpp"

#include <cstdio>

BoundingSphere::BoundingSphere( const float& Radius, const Vec3f& Center ) :
  Collider( Sphere_COLLIDER ),
  m_Radius( Radius ),
  m_Center( Center ) { return; }

BoundingSphere::~BoundingSphere( void ) { return; }

void
BoundingSphere::Translate( const Vec3f& Translation )
{
  m_Center += Translation;
}

Vec3f
BoundingSphere::Center( void ) const
{
  return m_Center;
}

IntersectData
BoundingSphere::Intersect( const Collider& other ) const
{
  if      ( other.Type() == Sphere_COLLIDER )
    return IntersectBSphere( (const BoundingSphere&)other );
  else if ( other.Type() == AABB_COLLIDER )
    return IntersectAABB( (const AABB&)other );

  return IntersectData( false, 0 );
}

IntersectData
BoundingSphere::IntersectAABB( const AABB& aabb ) const
{
  puts( "BoundingSphere::IntersectAABB currently not implemented." );

  return IntersectData( false, 0 );
}

IntersectData
BoundingSphere::IntersectBSphere( const BoundingSphere& Sphere ) const
{
  float radiusDistance  = m_Radius + Sphere.m_Radius;
  Vec3f direction       = Sphere.m_Center - m_Center;

  float centerDistance = direction.Length();

  direction /= centerDistance;

  float distance = centerDistance - radiusDistance;

  return IntersectData( distance < 0, direction * distance );
}
