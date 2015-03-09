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

 \file Collider.h

 Created on: Mar 9, 2015
 \author     fkzey
 */

#ifndef LIBGEEKMATH_PHYSICS_COLLIDER_H_
#define LIBGEEKMATH_PHYSICS_COLLIDER_H_

#include "ColliderTypes.hpp"

class Vec3f;
class IntersectData;

class Collider
{
public:
  Collider( const GEEK_Collider_Type& Type );
  virtual
  ~Collider( void );

  const GEEK_Collider_Type&
  Type( void ) const;

  virtual void
  Translate( const Vec3f& Translation ) = 0;

  virtual Vec3f
  Center( void ) const = 0;

  virtual IntersectData
  Intersect( const Collider& other ) const = 0;

protected:
private:
  GEEK_Collider_Type  m_Type;

};

#endif /* LIBGEEKMATH_PHYSICS_COLLIDER_H_ */
