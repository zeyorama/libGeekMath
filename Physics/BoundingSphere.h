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

 \file BoundingSphere.h

 Created on: Mar 9, 2015
 \author     fkzey
 */

#ifndef LIBGEEKMATH_PHYSICS_BOUNDINGSPHERE_H_
#define LIBGEEKMATH_PHYSICS_BOUNDINGSPHERE_H_

#include "Collider.h"
#include "../Math/Vec3f.h"

class AABB;
class IntersectData;

class BoundingSphere : public Collider
{
public:
  BoundingSphere( const float& Radius, const Vec3f& Center );
  virtual
  ~BoundingSphere( void );

  void
  Translate( const Vec3f& Translation );

  Vec3f
  Center( void ) const;

  IntersectData
  Intersect( const Collider& other ) const;

protected:
private:
  IntersectData
  IntersectAABB( const AABB& aabb ) const;
  IntersectData
  IntersectBSphere( const BoundingSphere& Sphere ) const;

  float m_Radius;
  Vec3f m_Center;

};

#endif /* LIBGEEKMATH_PHYSICS_BOUNDINGSPHERE_H_ */
