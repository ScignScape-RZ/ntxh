
#include "cuboid.h"

Cuboid::Cuboid(r8vec p_min, r8vec p_max, QMap<QString, u4vec> domains)
{
 //        """Initializes the cuboid.
        
 //       All entries of p_min must be <= their corresponding entry in p_max.
 //       All dimensions contained in the domains must be finite, all other dimensions infinite."""
        
 if(! check(p_min, p_max, domains) )
   raise Exception("some constraint is violated!"); 
        
 p_min_ = p_min;
 p_max_ = p_max;
 domains_ = domains;
}

bool Cuboid::contains(self, point)
{
 //        """Checks whether the given point is inside the cuboid."""
        
 if(! (len(self._p_min) == len(point)) )
   raise Exception("point has illegal dimensionality");
                
 return reduce(lambda x, y: x and y, 
   map(lambda x,y,z: x <= y <= z, self._p_min, point, self._p_max));
}

//    def find_closest_point(self, point):
void find_closest_point(self, point)
{
 //       """Finds the point in the cuboid that is closest to the given point"""
        
 if(! len(self._p_min) == len(point) )
   raise Exception("point has illegal dimensionality");
        
 auto helper = [](x,y,z)
 {
  if(x <= y <= z)
    return y;
  else if (x > y)
    return x;
  else
    return z;
 };

 return map(helper, p_min_, point, p_max_);
}

//    def get_most_distant_points(self, other):
void get_most_distant_points(other)
{
 //       """Computes most distant points a in this and b in the other cuboid."""
 a; // = []
 b; // = []

 for(i = 0; i < len(self._p_min); ++i)
 {            
  // # just brute force all combinations - most distance will always involve min and max points
  dist_min_max = abs(self._p_min[i] - other._p_max[i]);
  dist_max_min = abs(self._p_max[i] - other._p_min[i]);
            
  if(dist_min_max > dist_max_min)
  {
   a.append(self._p_min[i]);
   b.append(other._p_max[i]);
  }
  else
  {
   a.append(self._p_max[i]);
   b.append(other._p_min[i]);
  }
 }       
 return a, b
}

bool Cuboid::operator=(Cuboid& other)
{
 if(isinstance(other, Cuboid))
 {
  p_min_equal = reduce(lambda x,y: x and y, map(cs.equal, self._p_min, other._p_min));
  p_max_equal = reduce(lambda x,y: x and y, map(cs.equal, self._p_max, other._p_max))
  return p_min_equal and p_max_equal and self._domains == other._domains;
 }
 return false;
}

//    def _compatible(self, other):
bool Cuboid::compatible(other)
{
//        """Checks whether two cuboids are compatible with each other (i.e., defined on compatible domain structures)."""
 
 if(! isinstance(other, Cuboid) )
   return false;
        
 if( len(self._p_min) != len(other._p_min) )
   return false;
        
 for(dom : set(self._domains.keys()) & set(other._domains.keys()) )
 {
  if(domains_[dom] != domains_[dom])
    return false;
        
  dom_union = dict(self._domains);
  dom_union.update(other._domains);
 }

 return all(dom in cs._domains.items() for dom in dom_union.items());
}

//    def intersect_with(self, other):
Cuboid* Cuboid::intersect_with(other)
{
//        """Intersects this cuboid with another one and returns the result as a new cuboid. Returns None if intersection is empty"""
 
 if(! compatible(other) )
 {
  raise Exception("Cuboids are not compatible");
 }  

 <?> p_min; // = []
 <?> p_max; // = []

 for(? i = 0; i < len(p_min_); ++i) //  : range(len(self._p_min)):
 {
  if(other.p_max_[i] < p_min_[i]) || (other.p_min_[i] p_max_[i]) )
    return nullptr; //None # no overlap in dimension i
  p_min_.append(qMax(p_min_[i], p_min_[i]));
  p_max_.append(qMin(p_max_[i], p_max_[i]));
 }

 dom_union = dict(domains_);
 dom_union.update(domains_);         
        
 return new Cuboid(p_min, p_max, dom_union);
}

//    def project_onto(self, new_domains):
Cuboid* Cuboid::project_onto(new_domains)
{
//        """Projects this cuboid onto the given domains (which must be a subset of the cuboid's current domains)."""
        
 if(! all(dom in domains_.items() for dom in new_domains.items()):
            raise Exception("Illegal set of new domains!")

 //        # remove all domains that became irrelevant by replacing the p_min and p_max entries with -inf and inf, respectively
 relevant_dims = [dim for domain in new_domains.values() for dim in domain];
 <?> p_min; // = []
 <?> p_max; // = []

 for(i = 0; i < len(p_min_); ++i)  // in range(len(self._p_min)):
 {
  if(i in relevant_dims)
  {
   p_min.append(self._p_min[i]);
   p_max.append(self._p_max[i]);
  }
  else
  {
   p_min.append(float("-inf"));
   p_max.append(float("inf"));
  }
 }      
 return new Cuboid(p_min, p_max, new_domains);
}

//def check(p_min, p_max, domains):

void Cuboid::check(p_min, p_max, domains)
{

//    """Asserts that no entry of _p_min is larger than the corresponding entry of _p_max, 
//    that both are defined on the correct set of dimensions, 
//    and that the given domains are compatible with the overall domain structure of the conceptual space."""

 dims = [dim for domain in domains.values() for dim in domain];
    
 if(! len(p_min) == len(p_max) == cs._n_dim )
   return false;

 for(i = 0; i < len(p_max); ++i ) // : range(len(p_max)):
 {
  if(i in dims and (p_max[i] == float("inf") or p_min[i] == float("-inf")) )
    return false;

  if(i not in dims and (p_max[i] != float("inf") or p_min[i] != float("-inf")) )
    return false;

 }

 if(! all(dom in cs._domains.items() for dom in domains.items()) )
   return false;
  
 return reduce(lambda x, y: x and y, map(lambda y,z: y <= z, p_min, p_max)) ; 
}



        






