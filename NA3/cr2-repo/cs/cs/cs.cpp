
#include "cs.h"

Conceptual_Space::Conceptual_Space(n_dim, domains, dim_names = None)
{
//def init(n_dim, domains, dim_names = None):
//    """Initializes a conceptual space with the given numer of dimensions and the given set of domains.
    
//    'n_dim' is an integer >= 1 and 'domains' is a dictionary from domain ids to sets of dimensions.
//    The optional argument 'dim_names' contains names for the individual dimensions. Its length must be identical to 'n_dim'.
//    If it is not given, numbered dimension names are generated."""

 if(n_dim < 1)
   raise Exception("Need at least one dimension");
    
 if(! check_domain_structure(domains, n_dim) )
   raise Exception("Invalid domain structure");
        
 n_dim_ = n_dim;
 domains_ = domains;
 <?> concepts_ = {};
 <?> concept_colors_ = {};
 //   # take care of dimension names
 if( !dim_names.isEmpty()  ) //dim_names != None:
 {
  if( len(dim_names) != n_dim )
    raise Exception("Invalid number of dimension names");
  else
    this.dim_names_ = dim_names;
 }
 else
   this.dim_names_ = {} ; //["dim_{0}".format(i) for i in range(n_dim)]
    
 //   # construct default weights
 dim_weights = {}
 dom_weights = {}
 for( (dom, dims) : domains.items() )
 {
  dom_weights[dom] = 1.0;
  local_dim_weights = {};
  for(dim : dims)
  {
   local_dim_weights[dim] = 1;
  }
  dim_weights[dom] = local_dim_weights;
 }
 this._no_weights = wghts.Weights(dom_weights, dim_weights)
}

void check_domain_structure(domains, n_dim)
//def _check_domain_structure(domains, n_dim):
//    """Checks whether the domain structure is valid."""
{
 vals = [val for domain in domains.values() for val in domain] # flatten values
   
 //   # each dimension must appear in exactly one domain
 for(i = 0; i < n_dim; ++i) //: range(n_dim))
 {
  if(vals.count(i) != 1)
    return false;
 }
    
 //  # we need the correct number of dimensions in total
 if(len(vals) != n_dim)
   return false;
    
 //  # there are no empty domains allowed
 for( (k,v) : domains.items() )
 {
  if( v.isEmpty() )
    return false;
 }   
 return true;
}

r8 Concept::distance(x, y, weights)
{
 //    """Computes the combined metric d_C(x,y,W) between the two points x and y using the weights in 'weights'."""
    
 if( (len(x) != n_dim_) || (len(y) != n_dim_) )
   raise Exception("Points have wrong dimensionality");
    
 r8 distance = 0.0;

 for( domain : domains_.keys() )
 {
  r8 inner_distance = 0.0;
  if(! (domain in weights.domain_weights()) )
    //    # don't take into account domains w/o weights
    continue;

  for(dimension : domains_[domain])
  {
   inner_distance += weights.dimension_weights()[domain][dimension] * 
     (x[dimension] - y[dimension])**2;
   distance += weights.domain_weights()[domain] * qSqrt(inner_distance);
  }
 }
    
 return distance;
}

//def add_concept(key, concept, color = None):
void Conceptual_Space::add_concept(key, concept, color = None)
{
 //   """Adds a concept to the internal storage under the given key."""
    
 if(! isinstance(concept, con.Concept) )
   raise Exception("Not a valid concept");
 concepts_[key] = concept;
    
 if( color != None )
   concept_colors_[key] = color;
}

//def add_concept(key, concept, color = None):
void Conceptual_Space::delete_concept(key)
{
 //    """Deletes the concept with the given key form the internal storage."""
    
 if(key : concepts_)
   del concepts_[key];
 if(key : concept_colors_)
   del concept_colors_[key];
}

//def add_concept(key, concept, color = None):
void Conceptual_Space::between(first, middle, second, weights=None, method="crisp")
{
 //"""Computes the betweenness relation between the three given points.
    
 //   Right now only uses the crisp definition of betweenness (returns either 1.0 or 0.0)."""
    
 if( weights == None )
   weights = no_weights_;
    
 if( method == "crisp" )
 {
  if (distance(first, middle, no_weights_) 
    + distance(middle, second, no_weights_) 
    - distance(first, second, this._no_weights)) < 0.00001)
    return 1.0;
  else
    return 0.0;
 }
 else if( method == "soft" )
 {
  d1 = distance(first, middle, weights);
  d2 = distance(middle, second, weights);
  d3 = distance(first, second, weights);
  return (d1 + d2 > 0)? d3 / (d1 + d2) : 1.0;
 }    
 else
   raise Exception("Unknown method");
}

//def round(x):
void Conceptual_Space::round(? x)
{
 //   """Rounds the given number to a globally constant precision."""
 return __builtin__.round(x, precision_digits_);
}

void Conceptual_Space::equal(? x, y)
{
 //def equal(x, y):
 //    """Checks whether two floating point numbers 
   //  are considered to be equal under the globally set precision."""
 return (abs(x - y) < epsilon_) 
   || (isinf(x) and isinf(y) and (x>0) == (y>0));
}

void Conceptual_Space::export_concept_samples(num_samples = 100, 
  path_to_file = './samples.csv', labeling_threshold = 0.9)
{
 //def export_concept_samples(num_samples = 100, path_to_file = './samples.csv', labeling_threshold = 0.9):
 //   """Samples 'num_samples' points each concept, labels it with the concept with highest membership as well
 //   as all concepts with a membership above the labeling_threshold (relative to the highest membership concept)
 //    and stores them as csv file under the given 'path_to_file'."""
    
 //   # collect data points
 <?> samples; // = []
 for(? concept : concepts_.values() )
   samples += concept.sample(num_samples);
    
 //   # collect labels
 <?> labeled_samples; // = []
 for(? sample : samples)
 {
  <?> memberships; // = []
  for( name, concept : concepts_.iteritems() )
  {
   memberships.append((name, concept.membership_of(sample)));
  }
  memberships.sort(key = lambda x: x[1], reverse = true);
  l_sample = list(sample);
  l_sample.append(memberships[0][0]);
  idx = 1;
  threshold = labeling_threshold * memberships[0][1];
  while( memberships[idx][1] > threshold )
  {
   l_sample.append(memberships[idx][0]);
   ++idx;
  }
  labeled_samples.append(l_sample);
 } 
 with open(path_to_file, 'w') as f
 {
  for l_sample in labeled_samples:
          f.write("{0}\n".format(",".join(map(str, l_sample))))
 }
}







