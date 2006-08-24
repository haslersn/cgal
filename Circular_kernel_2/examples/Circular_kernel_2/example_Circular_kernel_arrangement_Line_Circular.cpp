//#include <fstream>

#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Algebraic_kernel_2_2.h>
#include <CGAL/intersections.h>
#include <CGAL/Circular_kernel_2.h>
#include <CGAL/Arr_circular_line_arc_traits.h>
#include <CGAL/Arrangement_2.h>
#include <CGAL/Arr_naive_point_location.h>
#include <boost/variant.hpp>

#include <CGAL/Random.h>


typedef CGAL::Quotient<CGAL::MP_Float>                      NT;
typedef CGAL::Cartesian<NT>                                 Linear_k;
typedef CGAL::Algebraic_kernel_for_circles_2_2<NT>          Algebraic_k;
typedef CGAL::Circular_kernel_2<Linear_k,Algebraic_k>       Circular_k;

typedef Circular_k::Point_2                           Point_2;
typedef Circular_k::Circle_2                          Circle_2;
typedef Circular_k::Circular_arc_2                    Circular_arc_2;
typedef Circular_k::Line_arc_2                        Line_arc_2;

typedef boost::variant< Circular_arc_2, Line_arc_2>        Arc;
typedef std::vector< Arc> ArcContainer;

#ifndef CGAL_CURVED_KERNEL_DEBUG
typedef CGAL::Arr_circular_line_arc_traits<Circular_k, Circular_arc_2, Line_arc_2>                  Traits;
#else
typedef CGAL::Arr_circular_line_arc_traits<Circular_k, Circular_arc_2, Line_arc_2>                  Traits0;
typedef CGAL::Variant_traits_tracer<Traits0>            Traits;
#endif


typedef Traits::Curve_2                             Conic_arc_2;
typedef CGAL::Arrangement_2<Traits>                 Pmwx;
typedef CGAL::Arr_naive_point_location<Pmwx>        Point_location;

typedef Traits::X_monotone_curve_2                  X_monotone_curve_2;

int main(){
  
  CGAL::Random generatorOfgenerator;
  int random_seed = generatorOfgenerator.get_int(0, 123456);
  std::cout << "random_seed = " << random_seed << std::endl;
  CGAL::Random theRandom(random_seed);
  int random_max = 128;
  int random_min = -128;
  ArcContainer ac;
  int x1;
  int y1;
  int x2;
  int y2;

  for(int i = 0; i < 10; i++){
    x1 = theRandom.get_int(random_min,random_max);
    y1 = theRandom.get_int(random_min,random_max);
    do{
      x2 = theRandom.get_int(random_min,random_max);
      y2 = theRandom.get_int(random_min,random_max);
    }while((x1 == x2) && (y1 == y2));
      
    std::cout << x1 << " "
  	      << y1 << " "
  	      << x2 << " "
  	      << y2 << std::endl;
    boost::variant< Circular_arc_2, Line_arc_2 > v =  Line_arc_2(Point_2(x1,y1), Point_2(x2,y2));
    ac.push_back( v);
  }
  
   for(int i = 0; i < 10; i++){
    x1 = theRandom.get_int(random_min,random_max);
    y1 = theRandom.get_int(random_min,random_max);
    boost::variant< Circular_arc_2, Line_arc_2 > v = Circle_2( Point_2(x1,y1), x1*x1 + y1*y1);
    ac.push_back(v);
  }



  
  Pmwx _pm;
  Point_location _pl(_pm);
  for (ArcContainer::const_iterator it=ac.begin();
       it != ac.end(); ++it) {
    //insert(_pm,_pl,*it);
    insert_curve(_pm,*it,_pl);
      };
  
  return 0;
};

