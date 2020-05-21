
#include "cuboid.h"

Weights::Weights(QMap<QString, r8>& domain_weights, 
  QMap<QString, QMap<u4, r8>>& dimension_weights)
{
 //        """Initializes the cuboid.
        
 //       All entries of p_min must be <= their corresponding entry in p_max.
 //       All dimensions contained in the domains must be finite, all other dimensions infinite."""

 domain_weights_ = normalize(domain_weights,
   domain_weights.keys().length());
   //len(domain_weights.keys()));
 <?> dimension_weights_ = {};
 
 for( (domain, weights) in dimension_weights.items() )
   dimension_weights_[domain] = normalize(weights, 1.0);       

 QMutableMapIterator<QString, QMap<u4, r8>> it (domain_weights);
 while(it.hasNext())
 {
  it.next();
  dimension_weights_[it.key()] = normalize( it.val
 }
 
}

//QList<?> Weights::normalize(weights, total)

QMap<QString, r8> Weights::normalize(
  const QMap<QString, r8>& weights, r8 total);
{
 //       """Normalizes a given set of weights such that they sum up to the desired total."""
        
 QMap<QString, r8> result; // = {}
 r8 old_sum = std::accumulate(weights.values().begin(), 
   weights.values().end(), 0.0);
        
 QMapIterator<QString, r8> it(weights);

 while(it.hasNext())
 {
  it.next();
  result[it.key()] = (it.value()*total)/old_sum;
 }

 //for (k,v) in weights.items():
 //  result[k] = (1.0*v*total)/(old_sum);
        
 return result;
}

//    def __str__(self):
//        return "<{0},{1}>".format(str(self._domain_weights),str(self._dimension_weights))

bool Weights::operator=(const Weights& other)
{
// if(! isinstance(other, Weights) )
//   return false;
            
 if( len(domain_weights_) != len(domain_weights_) )
   return false;

 for( dom, weight in domain_weights_.iteritems() )
 {
  if(dom not in other.domain_weights_)
    return false;
  if(! cs_->equal(other.domain_weights_[dom], weight ) _
    return false;
 }

 if( len(dimension_weights_) != len(other.dimension_weights_) )
   return false;
 
 for( dom, dims in dimension_weights_.iteritems() )
 {
  if( dom not in other.dimension_weights_)
    return false;

  other_dims = other._dimension_weights[dom]
  if( len(dims) != len(other_dims) )
    return false;

  for( dim, weight in dims.iteritems() )
  {
   if( dim not in other_dims )
     return false;
   if(! cs->equal(other_dims[dim], weight) )
     return false;
  }
 }
 return true;
}

//    def merge_with(self, other, s = 0.5, t = 0.5):

Weights* Weights::merge_with(Weights& other, 
  r8 s = 0.5, r8 t = 0.5)
{
 //       """Merge two weights, using the parameters s and t to interpolate between domain and dimension weights, respectively."""
        
 QMap<QString, r8> dom_weights; // = {}
 QMap<QString, QMap<u4, r8>> dim_weights; // = {}

 QSet<QString> doms0 = QSet::fromList(domain_weights_.keys());
 QSet<QString> domso = QSet::fromList(other.domain_weights_.keys());

 QSet<QString> doms = doms0;
 doms &= domso;

 //for(? dom in set(self._domain_weights.keys())
 //  & set(other._domain_weights.keys()) )

 for(QString dom : doms)
 {
  r8 weight_dom = ( s * domain_weights_[dom] ) 
    + ( (1.0 - s) * other.domain_weights_[dom] );
  dom_weights[dom] = weight_dom;

  QMap<u4, r8> weights_dim; // = {};

  for(u4 dim : dimension_weights_[dom].keys() )
  {
   r8 w = t * dimension_weights_[dom][dim] 
     + ( (1.0 - t) * other.dimension_weights_[dom][dim] );
   weights_dim[dim] = w;
  }
  dim_weights[dom] = weights_dim;
 }

 QSet<QString> doms1 = doms;
 doms -= domso;

// for( dom in set(self._domain_weights.keys()) 
//   - set(other._domain_weights.keys()) )
 for(QString dom : dom1) 
 {
  dom_weights[dom] = domain_weights_[dom];
  dim_weights[dom] = dimension_weights_[dom]; //.copy();
 }

 QSet<QString> doms2 = domso;
 doms2 -= doms0;

// for( dom in set(other._domain_weights.keys()) 
//   - set(self._domain_weights.keys()) )
 for(QString dom : dom2) 
 {
  dom_weights[dom] = other.domain_weights_[dom];
  dim_weights[dom] = other.dimension_weights_[dom]; //.copy();
 }

 return new Weights(dom_weights, dim_weights)
}

//    def project_onto(self, new_domains):

Weights* Weights::project_onto(
  const QMap<QString, QString<u4, r8>>& new_domains)
{
 //       """Projects this set of weights onto a subset of domains."""

 QMap<QString, r8> dom_weights; // = {}
 QMap<QString, QMap<u4, r8>> dim_weights; // = {}

// <?> dom_weights; // = {}
// <?> dim_weights; // = {}

 for(QString dom : new_domains.keys() )
 {
  dom_weights[dom] = domain_weights_[dom];
  dim_weights[dom] = dimension_weights_[dom];
 }
 return new Weights(dom_weights, dim_weights);
}

//def check(domain_weights, dimension_weights):

bool Weights::check(domain_weights, dimension_weights)
{
//    """Checks if all normalization constraints are fulfilled."""

 if(! cs_->equal(sum(domain_weights.values()), len(domain_weights.keys())) )
   return false;
    
 for( weights in dimension_weights.values() )
 {
  if(! cs_->equal(sum(weights.values()), 1.0) )
    return false;
 }   
 return true;
}


