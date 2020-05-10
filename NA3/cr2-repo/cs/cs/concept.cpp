
#include "concept.h"

#include <tgmath.h>


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

r8 Concept::hypervolume_cuboid(cuboid)
     //   """Computes the hypervolume of a single fuzzified cuboid."""
{
 //?       all_dims = [dim for domain in core_.domains().values() for dim in domain]
 u4 n = len(all_dims);
 //        # calculating the factor in front of the sum
 r8 weight_product = 1.0;
 for (dom, dom_weight : weights_.domain_weights().items())
 {
  for (dim, dim_weight : weights_.dimension_weights()[dom].items())
  {
   weight_product *= dom_weight * qSqrt(dim_weight);
  }
 }
 factor = self.mu_ / ( qExp(self.c_, n) * weight_product ) );
 //        # outer sum
 r8 outer_sum = 0.0;
 for(i = 0; i < n + 1; ++i)
   //         # inner sum
 {
  r8 inner_sum = 0.0;
  ? subsets = list(itertools.combinations(all_dims, i));
  for(? subset : subsets)
   //             # first product
  {
   first_product = 1.0;
   for(? dim : set(all_dims) - set(subset))
   {
    ? = filter([] (? x, ?y) { dim in y }, core_.domains().items());
    dom =  ? [0][0];
    w_dom = weights_.domain_weights()[dom];
    w_dim = weights_.dimension_weights()[dom][dim];
    ? b = cuboid._p_max[dim] - cuboid._p_min[dim]
    first_product *= w_dom * qSqrt(w_dim) * b * self.c_;
   }
//                # second product
   r8 second_product = 1.0;
   ? reduced_domain_structure = reduce_domains(core_.domains, subset);
   for( (dom, dims) : reduced_domain_structure.items())
   {
    u4 n_domain = len(dims);
     // // tgamma in  <tgmath.h> 
    second_product *= factorial(n_domain) * ( 
      (qExp(pi, (n_domain/2.0))) / ( tgamma((n_domain/2.0) + 1)) );
   }
   inner_sum += first_product * second_product;
  }
  outer_sum += inner_sum;
 }
 return factor * outer_sum;
}

r8 Concept::size(self)
{
 //        """Computes the hypervolume of this concept."""
 hypervolume = 0.0
 num_cuboids = len(core_.cuboids());
        
 //       # use the inclusion-exclusion formula over all the cuboids
 for( l = 1; l <= num_cuboids + 1):
 r8 inner_sum = 0.0;

 subsets = list(itertools.combinations(core_.cuboids(), l));
 for(subset : subsets)
 {
  intersection = subset[0];
  for( cuboid : subset)
  {
   intersection = intersection.intersect_with(cuboid);
   inner_sum += self._hypervolume_cuboid(intersection);
  }
  hypervolume += inner_sum * qExp((-1.0), (l+1));
 }
 return hypervolume
}

r8 Concept::subset_of(Concept& other)
{

 //       """Computes the degree of subsethood between this concept and a given other concept."""

 QMap <?> common_domains; // = {}
 for( dom, dims : core_.domains().iteritems() )
 {
  if( dom in other.core_.domains() && other.core_.domains()[dom] == dims )
    common_domains[dom] = dims;
 }
 projected_self = self.project_onto(common_domains)
 projected_other = other.project_onto(common_domains)
        
 intersection = projected_self.intersect_with(projected_other)
 intersection._c = projected_other._c
 intersection._weights = projected_other._weights
 projected_self._c = projected_other._c
 projected_self._weights = projected_other._weights
 subsethood = intersection.size() / projected_self.size()
 return subsethood;
}

bool Concept::crisp_subset_of(Concept& other)
{
 //       """Checks whether this concept is a crisp subset of the given other concept."""

 //       # self._mu must not be greater than other._mu
 if(mu_ > other.mu_)
   return false

 //       # core of self must be subset of other's alpha-cut with alpha = self._mu
 ? corner_points; // = []
 <?> self_dims ;// = [dim for dims in self._core._domains.values() for dim in dims]
 
 for(dims : core_.domains().values())
 {
  for(dim : dims)
    self_dims.push_back(dim);
 }

 for(? cuboid : core_.cuboids())
 {
  binary_vecs = itertools.product([False, True], repeat = len(self_dims));
  for(vec : binary_vecs)
  {
   <?> point;// = []
   j = 0;
   for(i : range(cs->number_of_dimensions())
   {
    if(i in self_dims)
    {
     point.append(vec[j] ? cuboid.p_max()[i] : cuboid.p_min()[i]);
     ++j;
    }
    else
      point.append(0.0);
   }
   corner_points.append(point);
  }
 }
 for(point : corner_points)
 {
  if(other.membership_of(point) < self._mu)
    return false;
 }
//       # domains on which other is defined must be subset of domains on which self is defined
 for(dom, dims : other.core_.domains().iteritems())
 {
  if(! (dom in self.core_.domains() && self.core_.domains()[dom] == dims))
    return false;
 }
//        # for all dimensions: c * w_dom * sqrt(dim) must not be larger for other than for self
 for( dom, dims : other.core_.domains().iteritems())
 {
  for(? dim : dims)
  {
   other_value = other.c_ * other.weights_.domain_weights()[dom] 
     * qSqrt(other.weights_.dimension_weights()[dom][dim]);
   self_value = c_ * weights_.domain_weights()[dom] 
     * qSqrt(weights_.dimension_weights()[dom][dim]);
   if(other_value > self_value)
     return false;
  }
 }
 return true;
}

r8 Concept::implies(Concept& other)
{
 //       """Computes the degree of implication between this concept and a given other concept."""
        
 return subset_of(other);
}

//    def similarity_to(self, other, method="Jaccard"):
r8 Concept::similarity_to(Concept& other, QString method) //="Jaccard")
{
 //       """Computes the similarity of this concept to the given other concept.
        
 //       The following methods are avaliable:
 //           'Jaccard':                Jaccard similarity index (size of intersection over size of union) - used as default
 //           'subset':                 degree of subsethood as computed in subset_of()
//        """
 
//         # project both concepts onto their common domains to find a common ground                              
 QMap<?> common_domains; // = {}
 for( dom, dims : core_.domains().iteritems())
 {
  if( (dom in other.core_.domains()) and (other.core_.domains()[dom] == dims) )
    common_domains[dom] = dims;
 }

 if(len(common_domains) == 0)
//            # can't really compare them because they have no common domains --> return 0.0
   return 0.0;
 projected_self = project_onto(common_domains);
 projected_other = other.project_onto(common_domains);
 if(method == "Jaccard")
 {
  intersection = projected_self.intersect_with(projected_other);
  unify = projected_self.unify_with(projected_other);
  r8 sim = intersection.size() / unify.size();
  return sim;
 }
 else if(method == "subset")
 {
  return projected_self.subset_of(projected_other);
 }  
 else
 {
  raise Exception("Unknown method");
 }
}
 
r8 Concept::between(Concept& first, Concept& second, 
  QString method, u4 num_alpha_cuts) // ="integral", num_alpha_cuts = 20):
{
 //        """Computes the degree to which this concept is between the other two given concepts.
       
 //       The following methods are avaliable:
 //           'minimum':  minimum over all alpha-cuts
 //           'integral': coarse approximation of the integral over all alpha-cuts
 //       """

//         # if the three concepts are not defined on the exact same set of domains, we return zero
 if(len(core_.domains().keys()) != len(first.core_.domains().keys()))
   return 0.0;
 if(len(core_.domains().keys()) != len(second.core_.domains().keys()))
   return 0.0;

 //        # now we know that the number of domains is the same --> check whether the domains themselves are the same
 for(dom, dims : core_.domains().iteritems())
 {
  if(! (dom in first.core_.domains() && first.core_.domains()[dom] == dims))
    return 0.0;
  
  if(! (dom in second.core_.domains() && second.core_.domains()[dom] == dims))
    return 0.0;
 }

 if(method == "minimum")            
//            # if self._mu is greater than any of first and second, the result is automatically zero
 {
  if( (mu_ > first.mu_) || (mu_ > second.mu_) )
    return 0.0;
//            # if self is a crisp subset of either of first or second, the result is automatically one
  if(crisp_subset_of(first) || crisp_subset_of(second))
    return 1.0;

//            # for all dimensions: c * w_dom * sqrt(w_dim) must not be larger for first and second than for self
  for(dom, dims : core_.domains().iteritems())
  {
   for(dim : dims)
   {
    first_value = first.c_ * first.weights_.domain_weights()[dom] 
      * qSqrt(first.weights_.dimension_weights()[dom][dim]);

    self_value = c_ * weights_.domain_weights()[dom] 
      * qSqrt(weights_.dimension_weights()[dom][dim]);

    second_value = second.c_ * second.weights_.domain_weights()[dom] 
      * qSqrt(second.weights_.dimension_weights()[dom][dim]));

    if( (first_value > self_value) && (second_value > self_value) )
      return 0.0;
   }
  }

  ? first_point = first.core_.midpoint();
  ? second_point = second.core_.midpoint();            
            
//            # start at each corner of each cuboid to get a good estimation of minimum over all points in self
  ? corners_min = [c._p_min for c in self._core._cuboids] 
  ? corners_max = [c._p_max for c in self._core._cuboids]

  ? candidates = [(point, "min") for point in corners_min] + [(point, "max") for point in corners_max];

  <?> candidate_results; // = []
  r8 tolerance = 0.01; //   # tolerance with respect to constraint violation, needed to ensure convergence

  for(? candidate : candidates)
  {                
   //             # push the points a bit over the edge to ensure we have some sort of gradient in the beginning
   if( candidate[1] == "min")
     cand = list(map([] (x) { x - cs->epsilon() }, candidate[0]));
   else
     cand = list(map([] (x) { x + cs->epsilon() }, candidate[0]));
                
//                # start with three different values of alpha to get a good estimate over the minmum over all alphas
   alpha_candidates = [0.05 * self._mu, 0.5 * self._mu, 0.95 * self._mu];
   for(alpha : alpha_candidates)
   {                  
//                    # inner optimization: point in first and point in second (maximizing over both)                     
    inner_x = first_point + second_point;
                    
//                    # function to minimize in inner optimization
    auto neg_betweenness = [](x_inner,x_outer)
    {
     x = x_inner[:cs._n_dim]                
                        y = x_outer[:-1]
                        z = x_inner[cs._n_dim:]
                        
     return -1.0 * cs.between(x, y, z, self._weights, method='soft');
    }

   }     
  }
  

 }

}

