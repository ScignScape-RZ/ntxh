
#include "concept.h"


Concept::Concept(Conceptual_Space* cs, r8 self, Core core, r8 mu, r8 c, Weights weights)
  :  cs_(cs), core_(core), mu_(mu), c_(c), weights_(weights)
{
 
}

bool Concept::operator=(const Concept& rhs)
{
 if(core_ != rhs.core_)
   return false;

 if(weights_ != rhs.weights_)
   return false;

 if(!cs_->equal(mu_, rhs.mu_))
   return false;

 if(!cs_->equal(c_, rhs.c_))
   return false;
 
 // //  cs.equal for mu and c_ ...
  
 return true;
}

r8 Concept::membership_of(Point p)
{
//  min_distance = reduce(min, map(lambda x: cs.distance(x, point, weights_),
//    core_.find_closest_point_candidates(p)))
 r8 min_distance = 0;      
 return mu_ * qExp(-c_ * min_distance)
}

void Concept::intersection_mu_special_case(QVector<u4>& a, r8 c2, QVector<u4>& b, r8 mu)
{
 auto make_fun = [&b](r8 idx) -> r8(*)(r8)
 {
  return [&b] (QVector<u4>& y)
  {
   return y[idx] - b[idx];
  };
 };
 
 r8 distance = - qLn(mu / mu_) / c_; 
 QVector<u4> y;
 for(u4 i : cs_.number_of_dimensions())
 {
  if(a[i] == b[i])
    y.push_back(a[i]);
  else
  {
   //                constr = [{"type":"eq", "fun":(lambda y: cs.distance(a,y,self._weights) - distance)}]
   for(u4 j : cs_.number_of_dimensions())
   {
    if (i != j)
    {
     //? constr.append({"type":"eq", "fun":makeFun(j)})
    }
    if(a[i] < b[i]
    {
     opt = scipy.optimize.minimize([](QVector<u4>& y)
     {
      -y[i]
     }, b, /* constraints */ constr);
      //              if not opt.success:
      //                  raise Exception("Optimizer failed!")
     y.append(opt.x[i]); //  x is solution array ...
    }
    else
    {
     opt = scipy.optimize.minimize([](QVector<u4>& y)
     {
      y[i]
     }, b, /* constraints */ constr);
      //              if not opt.success:
      //                  raise Exception("Optimizer failed!")
     y.append(opt.x[i]); //  x is solution array ...
    }

   }
  }
 }
 // # arrange entries in b and y to make p_min and p_max; make sure we don't fall out of c2
 r8 p_min = map(max, map(min, b, y), c2._p_min)
 r8 p_max = map(min, map(max, b, y), c2._p_max)
        
 // # take the unification of domains
 return {p_min, p_max};
}

void Concept::intersect_fuzzy_cuboids(Cuboid c1, Cuboid c2, Concept& other)
{
 // //  """Find the highest intersection of the 
  //    two cuboids (c1 from this, c2 from the other concept)."""
 crisp_intersection = c1.intersect_with(c2)
 if (crisp_intersection != nullptr):  // # crisp cuboids already intersect
   return {min(mu_, other.mu_), crisp_intersection};
 
 //       # already compute new set of domains
 new_domains = dict(c1.domains_);
 new_domains.update(c2.domains_); 

 std::bind(a_range, b_range) = c1.get_closest_points(c2);
 a = map([](QVector<u4>& x){ x[0] }, a_range)
 b = map([](QVector<u4>& x){ x[0] }, b_range)
 extrude = map([](QVector<u4>& x){ x[0] != x[1] }, a_range);

 mu = 0;
 p_min = 0;
 p_max = 0;
 if(mu_ * qExp(-self.c_ * cs_->distance(a, b, weights_)) >= other.mu_)
 {
  //          # intersection is part of other cuboid
  mu = other.mu_;
  std::bind(p_min, p_max) = intersection_mu_special_case(a, c2, b, mu);
 }
 else if(other.mu_ * qExp(-other.c_ * cs_->distance(a, b, other.weights_)) >= mu_)
 {
  // # intersection is part of this cuboid
  mu = mu_;
  std::bind(p_min, p_max) = other.intersection_mu_special_case(b, c1, a, mu);
 }       
 else
 {
  //          # intersection is in the cuboid between a and b
  //          # --> find point with highest identical membership to both cuboids
        
  //          # only use the relevant dimensions in order to make optimization easier
  auto membership = [&extrude, this](x, point, mu, c, weights)
  {
   QVector<u4>& x_new; // = [];
   u4 j = 0;
   for(u4 dim : cs_->number_of_dimensions())
   {
    if(extrude[dim])
      x_new.append(point[dim]);
    else
    {
     x_new.append(x[j]);
     ++j;
    }
   }
   return mu * exp(-c * cs_->distance(point, x_new, weights));   
  }
  
  QVector<u4>& bounds; // = []
  for(u4 dim : cs_->number_of_dimensions())
  {
   if(!extrude[dim])
     bounds.push_back({qMin(a[dim], b[dim]), qMax(a[dim], b[dim])});
  }
  first_guess = map([](r8 x, r8 y){ (x + y)/2.0 }, bounds);
  auto to_minimize = [this](r8 x}
  {
   -membership(x, a, mu_, c_, weights_);
  };
  //constr = [{"type":"eq", "fun":(lambda x: abs(membership(x, a, self._mu, 
  //  self._c, self._weights) - membership(x, b, other._mu, other._c, other._weights)))}]
  opt = scipy.optimize.minimize(to_minimize, first_guess, 
    constraints = constr, 
    bounds = bounds, options = {"eps":cs._epsilon})// #, "maxiter":500
    ;
  if(! (opt.success & qAbs(opt.fun - membership(opt.x, b, other.mu_, other.c_, other.weights_)) < 1e-06)
   //             # if optimizer failed to find exact solution, but managed to find approximate solution: take it
      ; //          raise Exception("Optimizer failed!")
   

    // # reconstruct full x by inserting fixed coordinates that will be extruded later
  x_star = []
  j = 0;
  for(u4 dim : cs_->number_of_dimensions())
  {
   if(extrude[dim])
     x_star.append(a[dim]);
   else
   {
    x_star.append(opt.x[j])
    ++j;
   }
  }
  mu = membership(opt.x, a, mu_, c_, weights_);
   // # check if the weights are linearly dependent w.r.t. all relevant dimensions            
  QVector<?> relevant_dimensions; // = []
  for(u4 dim : cs_->number_of_dimensions())
  {    
   if(!extrude[dim])
     relevant_dimensions.append(dim);
  }
  relevant_domains = reduce_domains_(cs.domains_, relevant_dimensions);
  t = 0;
  weights_dependent = true;
  for (QPair<?> pr /*dom, dims*/ : relevant_domains.items() )
  {
   for(dim : pr.second)
   {
    if(t == 0)
      t = (weights_.domain_weights()[dom] * 
      qSqrt(weights_.dimension_weights()[dom][dim])) /
      (other.weights_.domain_weights()[dom] * 
      qSqrt(weights_.dimension_weights()[dom][dim]));
    else
    {
     //                 # compare
     t_prime = (weights_.domain_weights()[dom] * 
       qSqrt(weights_.dimension_weights()[dom][dim])) /
       (other.weights_.domain_weights()[dom] * 
       qSqrt(other.weights_.dimension_weights()[dom][dim]));
     if(round(t,10) != round(t_prime,10))
     {
      weights_dependent = false;
      break;
     }
    }
   }
   if(!weights_dependent)
     break;
  }
  if(weights_dependent && len(relevant_domains.keys()) > 1)
  {   
   //           # weights are linearly dependent and at least two domains are involved
   //           # --> need to find all possible corner points of resulting cuboid
   r8 epsilon_1 = -qLn(mu / mu_) / c_;
   r8epsilon_2 = -qLn(mu / other.mu_) / other.c_;
   QVector<?> points;
   for(u4 num_free_dims: range(1, len(relevant_dimensions))
   {
    //              # start with a single free dimensions (i.e., edges of the bounding box) and increase until we find a solution
    for(QVector<?> free_dims: itertools.combinations(relevant_dimensions, num_free_dims))
    {
      //                 # free_dims is the set of dimensions that are allowed to vary, all other ones are fixed
     binary_vecs = list(itertools.product([false,true], 
       repeat = len(relevant_dimensions) - num_free_dims))
     for(<?> vec: binary_vecs)
     {
      //# compute the difference between the actual distance and the desired epsilon-distance
      auto epsilon_difference = [](x, point, weights, epsilon)
      {
       u4 i = 0;
       u4 j = 0;
       QVector<?> x_new; // = []
       //                       # puzzle together our large x vector based on the fixed and the free dimensions 
       for(u4 dim : cs_->number_of_dimensions())
       {    
        if(dim is-in free_dims)
        {
         x_new.append(x[i]);
         ++i;
        }
        else if(extrude[dim])
          x_new.append(a[dim]);
        else
        {
         x_new.append(vec[j]? a[dim] : b[dim]);   //?a[dim] if vec[j] else b[dim])
         ++j;
        }
       }
       return qAbs(cs_->distance(point, x_new, weights) - epsilon);
      };
        
      QVector<?> bounds; // = []
      for(? dim : free_dims)
      {
       bounds.append((min(a[dim], b[dim]), max(a[dim], b[dim])));
      }
      first_guess = map([] (r8 x, r8 y) { (x + y)/2.0 }, bounds);
                          
      to_minimize = [](u4 x)
      {
       max(epsilon_difference(x, a, weights_, epsilon_1)**2, 
         epsilon_difference(x, b, weights_, epsilon_2)**2);
      };
      opt = scipy.optimize.minimize(to_minimize, first_guess); //#tol = 0.000001
      if(opt.success)
      {
       dist1 = epsilon_difference(opt.x, a, weights_, epsilon_1);
       dist2 = epsilon_difference(opt.x, b, weights_, epsilon_2);
       bool between = true;
       k = 0
       for(? dim : free_dims)
       {
        if(! (qMin(a[dim], b[dim]) <= opt.x[k] <= qMax(a[dim], b[dim])))
        {
         between = false;
         break;
        }
        k += 1
       }
//                               # must be between a and b on all free dimensions AND must be a sufficiently good solution
       if( (dist1 < 0.0001) && (dist2 < 0.0001) && between )
       {
        <?> point; // = []
        i = 0;
        j = 0;
              //                    # puzzle together our large x vector based on the fixed and the free dimensions
        for(u4 dim : cs_->number_of_dimensions())
        {
         if(dim is-in free_dims)
         {
          point.append(opt.x[i]);
          ++i;
         }
         else if(extrude[dim])
           point.append(a[dim])
         else
         {
          point.append(vec[j]? a[dim] : b[dim])
          j += 1
         }
        }
        points.append(point);
       }
      }
     }
    }
    if(len(points) > 0)
//    # if we found a solution for num_free_dims: stop looking at higher values for num_free_dims
    {
     <?> p_min; // =  []
     <?> p_max; //                 p_max = []
     for(dim : cs->number_of_dimensions())
     {
      p_min.append(max(min(a[i],b[i]), reduce(min, map(lambda x: x[i], points))));
      p_max.append(min(max(a[i],b[i]), reduce(max, map(lambda x: x[i], points))));
     }
     break;
    }
   }
   if (p_min.isEmpty()) or p_max.isEmpty())// == None:  
//                    # this should never happen - if the weights are dependent, there MUST be a solution
       ;//                  raise Exception("Could not find solution for dependent weights")
     

  }
  else
  {
    //           # weights are not linearly dependent: use single-point cuboid
   p_min = list(x_star);
   p_max = list(x_star);
   //no op...  // pass;
  } 
 }
 //        # round everything, because we only found approximate solutions anyways
 mu = cs_->round(mu);
 p_min = map(&cs_->round, p_min)
 p_max = map(&cs_->round, p_max)
                                                  
 //     # extrude in remaining dimensions
 for(u4 i : len(extrude))
 {
  if(extrude[i])
    p_max[i] = a_range[i][1];
 }
//        # finally, construct a cuboid and return it along with mu
 Cuboid cuboid = cub.Cuboid(p_min, p_max, new_domains)
 return {mu, cuboid};
}

Concept* Concept::intersect_with(const Concept& other)
   //     """Computes the intersection of two concepts."""
{
 // # intersect all cuboids pair-wise in order to get cuboid candidates
 QVector<Cuboid> candidates; // = []
 for(Cuboid c1 : core_.cuboids_)
 {
  for(Cuboid c2 : core_.cuboids_)
  {
   candidates.append(intersect_fuzzy_cuboids(c1, c2, other));
  }
 }
 mu = reduce(max, map([](? x) { x[0] }, candidates)); // i.e., maximum of x[0]
 cuboids = map([cs_](? x) { x[1] }, 
   filter([cs_] (? y) { cs_->equal(y[0],mu) }, candidates));
 
 //       # create a repaired core
 ? core = cor.from_cuboids(cuboids, cuboids[0].domains());
 
 //       # calculate new c and new weights
 ? c = min(c_, other.c_)
 ? weights = weights_.merge_with(other.weights_, 0.5, 0.5);
 return new Concept(core, mu, c, weights);
   
}

Concept* Concept::unify_with(const Concept& other)
{
 // """Computes the union of two concepts."""
 ? core = core_.unify_with(other.core_); 
 ? mu = qMax(mu_, other.mu_);
 ? c = qMin(c_, other.c_)
 ? weights = weights_.merge_with(weights_, 0.5, 0.5);
 return new Concept(core, mu, c, weights);
}

Concept* Concept::project_onto(? domains)
{
 //       """Computes the projection of this concept onto a subset of domains."""
        
 //       # no explicit check for domains - Core will take care of this
 ? new_core = core_.project_onto(domains);
 ? new_weights = weights_.project_onto(domains);
        
 return new Concept(new_core, mu, c_, new_weights);
}

QPair<Concept*, Concept*> Concept::cut_at(dimension, value)
{
 //       """Computes the result of cutting this concept into two parts (at the given value on the given dimension).
        
 //        Returns the lower part and the upper part as a tuple (lower, upper)."""
 //QPair<?> pr
        
    //{lower_core, upper_core}
 std::bind(lower_core, upper_core) = core_.cut_at(dimension, value);
  
 Concept* lower_concept = lower_core? new Concept(lower_core, mu_, c_, weights_)
    : nullptr;

 Concept* upper_concept = upper_core? new Concept(upper_core, mu_, c_, weights_)
    : nullptr;

 return {lower_concept, upper_concept};
}

QVector<?>  Concept::reduce_domains(domains, dimensions)
{
 //        """Reduces the domain structure such that only the given dimensions are still contained."""
 ? new_domains = {}

 for (? dom, dims : domains_.items())
 {
  filtered_dims = ? //[dim for dim in set(dims) & set(dimensions)]
  if(len(filtered_dims) > 0)
    new_domains[dom] = filtered_dims;
 } 
 return new_domains;
}

void Concept::hypervolume_couboid(cuboid)
     //   """Computes the hypervolume of a single fuzzified cuboid."""
{

}




