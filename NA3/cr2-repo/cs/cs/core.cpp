
#include "core.h"

Core::Core(QVector<Cuboid*> cuboids, QMap<QString, u4vec> domains)
{
 //   def __init__(self, cuboids, domains):
 //       """Initializes the concept's core.
        
 //       The parameter cuboids must be a list of cuboids."""
        
 if( len(cuboids) == 0 )
   raise Exception("empty list of cuboids");

 if(! check(cuboids, domains) )
   raise Exception("cuboids do not intersect or are defined on different domains")
        
 cuboids_ = simplify(cuboids);
 domains_ = domains;
}

bool Core::add_cuboid(self, cuboid)
//    """Adds the given cuboid to the internal list if it does not violate any constraints.
{        
 //       Returns true if the addition was successful and false if it was not successful."""

 extended_list = list(cuboids_) + [cuboid];
 if( check(extended_list, domains_) )
 {
  cuboids_.append(cuboid);
  return true
 }
 else
   return false;
}

bool Core::operator=(const Core& rhs)
{
 if( len(self._cuboids) != len(other._cuboids) )
   return false
 for( c : cuboids_ )
 {
  if(! c : other.cuboids() )
    return false;
 }
 return true;
}

QList<?> find_closest_point_candidates(point)
{
 //       """Returns a list that contains for each cuboid the closest point in the cuboid to the given point."""
        
 return map([point] (? c) { c.find_closest_point(point) }, cuboids_ );
}

? Core::unify_with(self, other)
//        """Computes the union of this core with another core."""
{        
 if(! cuboids_[0].compatible(other.cuboids_[0]) )
   raise Exception("Incompatible cores");
        
 extended_list = list(cuboids_) + list(cuboids_);
        
 return from_cuboids(extended_list, domains_);
}

QPair<Core*, Core*> Core::cut_at(dimension, value)
{
 //        """Cuts the given core into two parts (at the given value on the given dimension).
        
 //       Returns the lower part and the upper part as a tuple (lower, upper)."""
        
 <?> lower_cuboids; // = []
 <?> upper_cuboids; // = []
        
 for( cuboid : cuboids_ )
 {
  if( value >= cuboid.p_max()[dimension] )
    lower_cuboids.append(cuboid);
  else if( value <= cuboid._p_min[dimension] )
    upper_cuboids.append(cuboid);
  else
  {
   p_min = list(cuboid.p_min());
   p_min[dimension] = value;
   p_max = list(cuboid.p_max());
   p_max[dimension] = value;
   lower_cuboids.append(cub.Cuboid(list(cuboid._p_min), p_max, cuboid._domains));
   upper_cuboids.append(cub.Cuboid(p_min, list(cuboid._p_max), cuboid._domains));
  }
 }
  
 lower_core = len(lower_cuboids) == 0 ? nullptr : new Core(lower_cuboids, domains_);     
 upper_core = len(upper_cuboids) == 0 ? nullptr : new Core(upper_cuboids, domains_);     

 return {lower_core, upper_core};

}


Core* Core::project_onto(new_domains)
{
 //       """Projects this core onto the given set of new domains (must be a subset of the core's current domains)."""
        
 if( ! all(dom in self._domains.items() for dom in new_domains.items()) )
            raise Exception("Illegal set of new domains!")
        
 projected_cuboids = map(lambda c: c.project_onto(new_domains), self._cuboids);
        
 return new Core(projected_cuboids, new_domains);
}

r8vec Core::midpoint()
{
 //       """Computes the midpoint of this core's central region.
        
 //       Fills in 0 for all dimensions on which this core is not defined."""
 Cuboid* central_region = self.get_center();

// midpoint = map(lambda x, y: 0.5*(x + y), 
//   central_region.p_min(), 
//   central_region.p_max() );

 r8vec result;
 r8vec midpoint;

 midpoint.resize(central_region->p_min().size());
 result.resize(midpoint.size());
 
 //midpoint = 
 std::transform(central_region->p_min().begin(),
   central_region->p_min().end(), 
   central_region->p_max().begin(), midpoint.begin, [](r8 x, r8 y)
   {
    return 0.5*(x + y);
   }); 

 std::transform(midpoint.begin(),
   midpoint.end(), 
   result.begin, [](r8 x)
   {
    return qIsNaN(x)? 0 : x;
   }); 
 
  // midpoint = std::transform(
  // map([] (? x) { isnan(x)? 0.0 : x }, midpoint);
 return result;
}

Cuboid* Core::get_center()
{
 Cuboid* central_region = cuboids_[0];
 for(Cuboid* c : cuboids_)
   central_region = central_region.intersect_with(c);
        
 return central_region;
}

bool Core::check(cuboids, domains):
//    """Asserts that the intersection of all cuboids is nonempty and that they are defined on the same domains"""
{
 intersection = cuboids[0];
 for( c : cuboids )
 {
  intersection = intersection.intersect_with(c);
  if( intersection == nullptr )
    return false;
 }

 if(! all(dom in cs._domains.items() for dom in domains.items()) )
   return false;
    
 for(? c : cuboids)
 {
  if(c.domains() != domains_)
    return false;
 }
 return true;
}

Core* Core::from_cuboids(const QVector<Cuboid*>& cuboids, u4vec& domains)
{
 //  # first: simplify the cuboids to make life easier (and avoid weird results down the road)
 QVector<Cuboid*> cubs = simplify(cuboids);
    
 if(check(cubs, domains))
   return new Core(cubs, domains); //  # all cuboids already intersect --> nothing to do

 //    # need to perform repair mechanism        
 QList<r8vec> midpoints; // = []
 //midpoints.resize(cubs.size());
 for(Cuboid* cuboid : cubs) // # midpoint of each cuboid
 {
  r8vec r8v;
  r8v.resize(cuboid.p_min().size());
  std::transform(cuboid.p_min().begin(), 
    cuboid.p_min().end(), cuboid.p_max().begin(), 
    r8v.begin(), [](r8 x, r8 y) { return 0.5*(x + y); }); 
//   midpoints.append(map(lambda x, y: 0.5*(x + y), cuboid.p_min(), cuboid.p_max()));
  midpoints.append(r8v);
 }
 
 //    # sum up all midpoints & divide by number of cuboids
 //? midpoint = reduce(lambda x, y: map(lambda a,b: a+b, x, y), midpoints);
 //r8vec initial; initial.resize(midpoints.first.size());
 
 r8vec midpoint = std::accumulate(std::next(midpoints.begin()),
   midpoints.end(), midpoints.first(), [](const& r8vec x, const& r8vec y)
  {
   r8vec result;
   result.resize(x);
   std::transform(x.begin(), x.end(), y.begin(),
     result.begin(), [](r8 rr1, r8 rr2)
    {
     return rr1 + rr2;
    });
   return result;
  });

 //midpoint = map([] (? x) { x/len(cubs) }, midpoint);
 for(r8& rr: midpoint)
 {
  rr /= cubs.length();
 }
 
 //    # extend cuboids
 QVector<Cuboid*> modified_cuboids; // = []
 for(Cuboid* cuboid : cubs)
 {
  r8vec p_min;
  p_min.resize(midpoint.length());

  r8vec p_max;
  p_max.resize(midpoint.length());

  std::transform(midpoint.begin(), midpoint.end(), 
    p_min.begin(), &qMin);

  std::transform(midpoint.begin(), midpoint.end(), 
    p_max.begin(), &qMax);

   // = map(min, cuboid._p_min, midpoint);
   // = p_max = map(max, cuboid._p_max, midpoint);

  //modified_cuboids.append(cub.Cuboid(p_min, p_max, cuboid._domains));

  modified_cuboids.append(new Cuboid(p_min, p_max, cuboid.domains() ) ); 
 }   

 return new Core(modified_cuboids, domains)
}

QVector<Cuboid*> Core::simplify(QVector<Cuboid*>& cuboids)
{
 //    """Simplifies the given set of cuboids by removing redundant ones."""
    
 // keep = [true]*len(cuboids);
 QVector<Cuboid*> result = cuboids;

 for(i = 0; i < cuboids.length(); ++i) // in range(len(cuboids)):
 {       
  r8vec p_min = cuboids[i].p_min();
  r8vec p_max = cuboids[i].p_max();
  for(j = 0; j < cuboids.length(); ++j)  // j in range(len(cuboids)):
  {
   if( (i == j) || (keep[j] == nullptr) )
     continue;
   if( (cuboids[j]->contains(p_min)) && (cuboids[j]->contains(p_max))
   {
    keep[i] = nullptr;
    break;
   }
  }
 } 
 result.erase(std::remove_if(result.begin(), 
   result.end(), [](Cuboid* c) { return c == nullptr; }), 
   result.end());

 return result;      
 //return list(compress(cuboids, keep));
}




