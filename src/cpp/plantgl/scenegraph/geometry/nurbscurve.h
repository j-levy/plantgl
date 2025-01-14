/* -*-c++-*-
 *  ----------------------------------------------------------------------------
 *
 *       PlantGL: The Plant Graphic Library
 *
 *       Copyright CIRAD/INRIA/INRA
 *
 *       File author(s): F. Boudon (frederic.boudon@cirad.fr) et al. 
 *
 *  ----------------------------------------------------------------------------
 *
 *   This software is governed by the CeCILL-C license under French law and
 *   abiding by the rules of distribution of free software.  You can  use, 
 *   modify and/ or redistribute the software under the terms of the CeCILL-C
 *   license as circulated by CEA, CNRS and INRIA at the following URL
 *   "http://www.cecill.info". 
 *
 *   As a counterpart to the access to the source code and  rights to copy,
 *   modify and redistribute granted by the license, users are provided only
 *   with a limited warranty  and the software's author,  the holder of the
 *   economic rights,  and the successive licensors  have only  limited
 *   liability. 
 *       
 *   In this respect, the user's attention is drawn to the risks associated
 *   with loading,  using,  modifying and/or developing or reproducing the
 *   software by the user in light of its specific status of free software,
 *   that may mean  that it is complicated to manipulate,  and  that  also
 *   therefore means  that it is reserved for developers  and  experienced
 *   professionals having in-depth computer knowledge. Users are therefore
 *   encouraged to load and test the software's suitability as regards their
 *   requirements in conditions enabling the security of their systems and/or 
 *   data to be ensured and,  more generally, to use and operate it in the 
 *   same conditions as regards security. 
 *
 *   The fact that you are presently reading this means that you have had
 *   knowledge of the CeCILL-C license and that you accept its terms.
 *
 *  ----------------------------------------------------------------------------
 */


/*! \file geom_nurbscurve.h
    \brief Definition of the geometry class NurbsCurve and NurbsCurve2D.
*/


#ifndef __geom_nurbscurve_h__
#define __geom_nurbscurve_h__

/* ----------------------------------------------------------------------- */

#include "beziercurve.h"

/* ----------------------------------------------------------------------- */


PGL_BEGIN_NAMESPACE

class RealArray;
typedef RCPtr<RealArray> RealArrayPtr;
class RealArray2;
typedef RCPtr<RealArray2> RealArray2Ptr;

PGL_END_NAMESPACE

/* ----------------------------------------------------------------------- */

PGL_BEGIN_NAMESPACE

/* ----------------------------------------------------------------------- */

/**
   \class NurbsCurve
   \brief A NURBS Curve represented by an array of control Points, a knots
   list and a degree.
*/

/* ----------------------------------------------------------------------- */

class SG_API NurbsCurve : public BezierCurve
{

public:

  /// The \b Degree field default value.
  static const uint_t DEFAULT_NURBS_DEGREE;


  /// A structure which helps to build a NurbsCurve when parsing.
  struct SG_API Builder : public BezierCurve::Builder {

    /// A pointer to the \b KnotsList field.
    RealArrayPtr * KnotList;


    /// Constructor.
    Builder( );

    /// Destructor.
    virtual ~Builder( );

    virtual SceneObjectPtr build( ) const;

    virtual void destroy( );

    virtual bool isValid( ) const;

  };

  /// Default Constructor. Build object is invalid.
  NurbsCurve();

  /** Constructs a NurbsCurve of degree \e degree with the points \e points and the knot vector knotsList.
      \pre
      - \e degree must be strictly positive;
      - \e points must contain at least 2 points;
      - the number of \e knots must be equal to \e degree + 1 + number of control points
      \post
      - \e self is valid. */
  NurbsCurve(  const Point4ArrayPtr& ctrlPoints,
           const RealArrayPtr knots = TOOLS(RealArrayPtr()),
           uint_t degree = DEFAULT_NURBS_DEGREE,
           uint_t stride = DEFAULT_STRIDE,
           uchar_t width = DEFAULT_WIDTH );

  NurbsCurve(  const Point4ArrayPtr& ctrlPoints,
               uint_t degree,
               const RealArrayPtr knots = TOOLS(RealArrayPtr()),
               uint_t stride = DEFAULT_STRIDE,
               uchar_t width = DEFAULT_WIDTH  );

  NurbsCurve(  const Point3ArrayPtr& ctrlPoints,
               uint_t degree = DEFAULT_NURBS_DEGREE,
               const RealArrayPtr knots = TOOLS(RealArrayPtr()),
               uint_t stride = DEFAULT_STRIDE,
               uchar_t width = DEFAULT_WIDTH  );

  /// Destructor
  virtual ~NurbsCurve( );

  PGL_OBJECT(NurbsCurve)

  /// Returns \e Degree value.
  virtual const uint_t getDegree( ) const;

  /// Returns \e Degree field.
  uint_t& getDegree( );

  /// Returns whether \b Degree is set to its default value.
  bool isDegreeToDefault( ) const;

  /// Returns \e knotsList value.
  const RealArrayPtr& getKnotList( ) const ;

  /// Returns \e knotsList field.
  RealArrayPtr& getKnotList( );

  virtual const real_t getFirstKnot( ) const ;

  virtual const real_t getLastKnot( ) const;

  /** Set \e knotsList field to a default computed value.
      \pre
      - \e degree must be fill;
      - \e points must be fill and must contain at least 2 points;
      \post
      - \e self is valid. */
   virtual bool setKnotListToDefault( );
   static RealArrayPtr defaultKnotList( uint_t nbCtrlPoints, uint_t degree );

  /// Returns whether \b KnotList is set to its default value.
  bool isKnotListToDefault( ) const;
  static bool defaultKnotListTest(const RealArrayPtr& knots, uint_t nbCtrlPoints, uint_t degree );

  virtual bool isValid( ) const;

  /*!
     Compute point on the NURBS for u = \b u
     From the NURBS Book A4.1 p 124.
  */
  virtual Vector3 getPointAt(real_t u) const;

  /* Returns the \e Tangent for u = \e u.
      (see the Nurbs book p.12)
     \pre
      - \e u must be in [0,1];*/
  virtual Vector3 getTangentAt(real_t u) const;

  /* Returns the principal \e Normal for u = \e u.
     \pre
      - \e u must be in [0,1];*/
  virtual Vector3 getNormalAt(real_t u) const;

  /*!
    \brief Computes the derivative of degree \a d of the
    curve at parameter \a u in the homonegeous domain
    \author Philippe Lavoie
  */
  Point4ArrayPtr deriveAtH(real_t u, int d, int span ) const;

  /*!
    \brief Computes the derivative of the curve at the parameter \a u
    \author Philippe Lavoie
  */
  Point3ArrayPtr deriveAt(real_t  u, int d, int span  ) const;

  /*! Returns the \e derivative of degree \e d for u = \e u.
     \pre
     - \e u must be in [0,1];*/
  virtual Vector3 getDerivativeAt(real_t u, int d) const;

  /*! Returns the \e derivative of degree \e d for u = \e u.
     \pre
     - \e u must be in [0,1];*/
  virtual Point3ArrayPtr getDerivativesAt(real_t u) const;


  Vector3 projectTo(const Vector3& p,
                    real_t guess, real_t& u,
                    real_t e1=0.001, real_t e2=0.001,int maxTry=100) const;


  /// @name  Computational Algorithms
  //@{


  /*! Determine the knot Span index.
    From the Nurbs Book : A2.1 p68
  */
  uint_t findSpan(real_t u) const ;

  /*! \brief Compute the Basis Functions Values
    Algo 2.2 From The Nurbs Book p70
  */
  RealArrayPtr computeBasisFunctions(uint_t span, real_t u) const ;

  /*!
    \brief Compute the Derivates Basis Functions Values
    Algo A2.3 p72 Nurbs Book
    \author Philippe Lavoie
  */
  RealArray2Ptr computeDerivatesBasisFunctions(int n, real_t u, int span) const ;


  //@}

protected:

  /// The \b Degree field.
  uint_t __degree;

  /// The \b knotsList field.
  RealArrayPtr __knotList;


}; // NurbsCurve

/// NurbsCurve Pointer
typedef RCPtr<NurbsCurve> NurbsCurvePtr;


/* ----------------------------------------------------------------------- */


/**
   \class NurbsCurve2D
   \brief A 2D NURBS Curve represented by an array of control Points, a knots
   list and a degree.
*/


class SG_API NurbsCurve2D : public BezierCurve2D
{

public:

  /// A structure which helps to build a NurbsCurve2D when parsing.
  struct SG_API Builder : public BezierCurve2D::Builder {

    /// A pointer to the \b KnotsList field.
    RealArrayPtr * KnotList;


    /// Constructor.
    Builder( );

    /// Destructor.
    virtual ~Builder( );

    virtual SceneObjectPtr build( ) const;

    virtual void destroy( );

    virtual bool isValid( ) const;

  };

  /// Default Constructor. Build object is invalid.
  NurbsCurve2D();

  /** Constructs a NurbsCurve2D of degree \e degree with the points \e points and the knot vector knotsList.
      \pre
      - \e degree must be strictly positive;
      - \e points must contain at least 2 points;
      - the number of \e knots must be equal to \e degree + 1 + number of control points
      \post
      - \e self is valid. */
  NurbsCurve2D(  const Point3ArrayPtr& ctrlPoints,
         const RealArrayPtr knots = TOOLS(RealArrayPtr()),
         uint_t degree = NurbsCurve::DEFAULT_NURBS_DEGREE,
         uint_t stride = BezierCurve::DEFAULT_STRIDE,
         uchar_t width = DEFAULT_WIDTH );

  NurbsCurve2D(  const Point3ArrayPtr& ctrlPoints,
         uint_t degree,
         const RealArrayPtr knots = TOOLS(RealArrayPtr()),
         uint_t stride = BezierCurve::DEFAULT_STRIDE,
         uchar_t width = DEFAULT_WIDTH );

  NurbsCurve2D(  const Point2ArrayPtr& ctrlPoints,
         uint_t degree = NurbsCurve::DEFAULT_NURBS_DEGREE,
         const RealArrayPtr knots = TOOLS(RealArrayPtr()),
         uint_t stride = BezierCurve::DEFAULT_STRIDE,
         uchar_t width = DEFAULT_WIDTH );

  /// Destructor
  virtual ~NurbsCurve2D( );

  PGL_OBJECT(NurbsCurve2D)

  /// Returns \e Degree value.
  virtual const uint_t getDegree( ) const;

  /// Returns \e Degree field.
  uint_t& getDegree( );

  /// Returns whether \b Degree is set to its default value.
  bool isDegreeToDefault( ) const;

  /// Returns \e knotsList value.
  virtual const RealArrayPtr& getKnotList( ) const;

  /// Returns \e knotsList field.
  RealArrayPtr& getKnotList( );


  virtual const real_t getFirstKnot( ) const;

  virtual const real_t getLastKnot( ) const;

  /** Set \e knotsList field to a default computed value.
      \pre
      - \e degree must be fill;
      - \e points must be fill and must contain at least 2 points;
      \post
      - \e self is valid. */
  virtual bool setKnotListToDefault( );

  /// Returns whether \b KnotList is set to its default value.
  bool isKnotListToDefault( ) const;

  virtual bool isValid( ) const;

  /*! Determine the knot Span index.
    From the Nurbs Book : A2.1 p68
  */
  uint_t findSpan(real_t u) const ;

  /*! \brief Compute the Basis Functions Values
    Algo 2.2 From The Nurbs Book p70
  */
  RealArrayPtr computeBasisFunctions(uint_t span, real_t u) const ;

  /*!
    \brief Compute the Derivates Basis Functions Values
    Algo A2.3 p72 Nurbs Book
    \author Philippe Lavoie
  */
  RealArray2Ptr computeDerivatesBasisFunctions(int n, real_t u, int span) const ;

  /*!
    \brief Computes the derivative of degree \a d of the
    curve at parameter \a u in the homonegeous domain
    \author Philippe Lavoie
  */
  Point3ArrayPtr deriveAtH(real_t u, int d, int span ) const;

  /*!
    \brief Computes the derivative of the curve at the parameter \a u
    \author Philippe Lavoie
  */
  Point3ArrayPtr deriveAt(real_t  u, int d, int span  ) const;

  /*! Returns the \e derivative of degree \e d for u = \e u.
     \pre
     - \e u must be in [0,1];*/
  virtual Vector3 getDerivativeAt(real_t u, int d) const;

  /*! Returns the \e derivative of degree \e d for u = \e u.
     \pre
     - \e u must be in [0,1];*/
  virtual Point3ArrayPtr getDerivativesAt(real_t u) const;

  /*!
     Compute point on the NURBS for u = \b u
     From the NURBS Book A4.1 p 124.
  */
  virtual Vector2 getPointAt(real_t u) const;

  /* Returns the \e Tangent for u = \e u.
      (see the Nurbs book p.12)
     \pre
      - \e u must be in [0,1];*/
  virtual Vector2 getTangentAt(real_t u) const;

  /* Returns the principal \e Normal for u = \e u.
     \pre
      - \e u must be in [0,1];*/
  virtual Vector2 getNormalAt(real_t u) const;

protected:

  /// The \b Degree field.
  uint_t __degree;

  /// The \b knotsList field.
  RealArrayPtr __knotList;


}; // NurbsCurve

/// NurbsCurve2D Pointer
typedef RCPtr<NurbsCurve2D> NurbsCurve2DPtr;

  /*! Determine the knot Span index.
    From the Nurbs Book : A2.1 p68
  */
uint_t SG_API findSpan(real_t u,  uint_t _degree,
        const RealArrayPtr& _knotList);

/*! \brief Compute the Basis Functions Values
  Algo 2.2 From The Nurbs Book p70
*/
RealArrayPtr SG_API basisFunctions(uint_t span, real_t u,
                   uint_t _degree,
                   const RealArrayPtr& _knotList );

/*!
  \brief Compute the Derivates Basis Functions Values
  Algo A2.3 p72 Nurbs Book
  \author Philippe Lavoie
*/
RealArray2Ptr SG_API derivatesBasisFunctions(int n, real_t u,
                      int span,
                      uint_t _degree,
                      const RealArrayPtr& _knotList );

/* ----------------------------------------------------------------------- */

PGL_END_NAMESPACE

/* ----------------------------------------------------------------------- */
// __geom_nurbscurve_h__
#endif

