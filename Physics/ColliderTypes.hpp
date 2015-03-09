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

\file ColliderTypes.hpp

Created on: Mar 9, 2015
\author     fkzey
*/

#ifndef LIBGEEKMATH_PHYSICS_COLLIDERTYPES_HPP_
#define LIBGEEKMATH_PHYSICS_COLLIDERTYPES_HPP_

enum GEEK_Collider_Type
{
  AABB_COLLIDER   = 1,
  OBB_COLLIDER    = 2,
  Sphere_COLLIDER = 3,
  Plane_COLLIDER  = 4
};

#endif /* LIBGEEKMATH_PHYSICS_COLLIDERTYPES_HPP_ */
