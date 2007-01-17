/* -*-c++-*-
 *  ----------------------------------------------------------------------------
 *
 *       AMAPmod: Exploring and Modeling Plant Architecture
 *
 *       Copyright 1995-2000 UMR Cirad/Inra Modelisation des Plantes
 *
 *       File author(s): C. Pradal
 *
 *       $Source$
 *       $Id$
 *
 *       Forum for AMAPmod developers    : amldevlp@cirad.fr
 *
 *  ----------------------------------------------------------------------------
 *
 *                      GNU General Public Licence
 *
 *       This program is free software; you can redistribute it and/or
 *       modify it under the terms of the GNU General Public License as
 *       published by the Free Software Foundation; either version 2 of
 *       the License, or (at your option) any later version.
 *
 *       This program is distributed in the hope that it will be useful,
 *       but WITHOUT ANY WARRANTY; without even the implied warranty of
 *       MERCHANTABILITY or FITNESS For A PARTICULAR PURPOSE. See the
 *       GNU General Public License for more details.
 *
 *       You should have received a copy of the GNU General Public
 *       License along with this program; see the file COPYING. If not,
 *       write to the Free Software Foundation, Inc., 59
 *       Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *  ----------------------------------------------------------------------------
 */

/*! \file util_interpol.h
    \brief Interpolation algorithms.
*/


#ifndef __util_interpol_h__
#define __util_interpol_h__

/* ----------------------------------------------------------------------- */

#include "Tools/rcobject.h"
#include "Tools/util_vector.h"
#include "geom_namespace.h"

/* ----------------------------------------------------------------------- */

GEOM_BEGIN_NAMESPACE

/* ----------------------------------------------------------------------- */

class Point3Array;
typedef RCPtr<Point3Array> Point3ArrayPtr;
class RealArray;
typedef RCPtr<RealArray> RealArrayPtr;
class NurbsCurve;
typedef RCPtr<NurbsCurve> NurbsCurvePtr;
class NurbsCurve2D;
typedef RCPtr<NurbsCurve2D> NurbsCurve2DPtr;

/* ----------------------------------------------------------------------- */

/**
   \class Interpol
   \brief Class for interpolate 2D or 3D points with parameters.
*/

/* ----------------------------------------------------------------------- */

class GEOM_API Interpol
{
public:

  /// Default Constructor. Build object is invalid.
  Interpol();

  /// Constructs Points interpolator
  /// When it is closed, the last point have to be equal to the first,
  /// but parameters have to be different.
  // With 2D points, 3rd coordinate must be constant

  Interpol( const Point3ArrayPtr& _points,
            const RealArrayPtr&   _params,
            uint32_t _degree,
            bool _closed );

  /// Destructor
  virtual ~Interpol();

  /// Return the Point List value
  virtual const Point3ArrayPtr& getPoints( ) const;

  /// Return the Point List field
  virtual Point3ArrayPtr& getPoints( );

  /// Return the Parameter List value
  virtual const RealArrayPtr& getParameters( ) const;

  /// Return the Parameter List field
  virtual RealArrayPtr& getParameters( );

  /// Return the Interpolate Degree value
  virtual uint32_t getDegree( ) const;

  /// Return the Interpolate Degree field
  virtual uint32_t& getDegree( );

  /// Return the Closure value
  virtual bool getClosure( ) const;

  /// Return the Closure field
  virtual bool& getClosure( );

  /// Return the 2D result curve which interpolate datas
  virtual NurbsCurve2DPtr get2DCurve();

  /// Return the 3D result curve which interpolate datas
  virtual NurbsCurvePtr get3DCurve();

  /// Intersection of 2 lines
  /// L1(u): P + u * T1
  /// L2(u): Q + u * T2
  /// R= L1(a)= L2(b) the two intersect themselves
  /// else return false
  static bool intersectLine( TOOLS(Vector3) P, TOOLS(Vector3) T1,
                             TOOLS(Vector3) Q, TOOLS(Vector3) T2,
                             real_t& a, real_t& b  );

protected:

  /// Points to interpolate
  Point3ArrayPtr points;

  /// Parameter at the points
  RealArrayPtr knots;

  /// Interpolation degree
  uint32_t degree;

  /// the set of points is it closed?
  bool closed;

private:

  /// Control Points
  Point3ArrayPtr CP;

  /// List of limit arcs parameters
  RealArrayPtr params;

  /// Tangents
  Point3ArrayPtr T;

private:

  /// Compute tangent at each point
  virtual bool initTangent();

  /// Compute a trivial knot vector
  virtual RealArrayPtr bezierKV( const RealArrayPtr& _knots ) const;

  /// check the continuity of the result curve
  virtual uint32_t checkContinuity() const;

  /// compute one or two arcs between points (degree 2)
  virtual uint32_t bezierArc2( uint32_t _arcNum );

  /// compute one or two arcs between points (degree 3)
  virtual uint32_t bezierArc3( uint32_t _arcNum );

  /// compute curve data
  virtual bool run();
};


/* ----------------------------------------------------------------------- */

// __util_interpol_h__
/* ----------------------------------------------------------------------- */

GEOM_END_NAMESPACE

/* ----------------------------------------------------------------------- */
#endif

