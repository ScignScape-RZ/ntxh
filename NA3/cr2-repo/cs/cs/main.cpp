
#include "core.h"

#include "cs.h"

#include <QMap>
#include <QVector>
#include <QString>
#include <QStringList>



void apple() // Conceptual_Space& cs)
{
// # define the conceptual space
 Conceptual_Space cs;


 QMap<QString, QVector<u4> > domains { {"color", {0}}, {"taste", {1, 2}} }; 

   //{"color":[0], "taste":[1, 2]}
 QStringList dimension_names = {"hue", "sour", "sweet"}; //["hue", "sour", "sweet"]
 cs.init(3, domains, dimension_names);

 // # define red property
 c_red = new Cuboid( {0.7, QtNegINF, QtNegINF}, 
   { 1.0, QtINF, QtINF }, { {"color", {0}} });

   //[0.7, QtNegINF, QtNegINF], [1.0, QtINF, QtINF], {"color":[0]})

 s_red = new Core( {c_red}, { {"color", {0}} } );
// s_red = Core([c_red], {"color":[0]})

 w_red = new Weights( {{"color", 1.0}}, {{"color", {{0, 1.0} }});
// w_red = Weights({"color":1.0}, {"color":{0:1.0}})

 red = new Concept(s_red, 1.0, 40.0, w_red);

 cs.add_concept("red", red, "r");


 // # define yellow property
 c_yellow = new Cuboid( {0.4, QtNegINF, QtNegINF}, 
   { 0.6, QtINF, QtINF }, { {"color", {0}} });

   //[0.7, QtNegINF, QtNegINF], [1.0, QtINF, QtINF], {"color":[0]})

 s_yellow = new Core( {c_yellow}, { {"color", {0}} } );
// s_red = Core([c_red], {"color":[0]})

 w_yellow = new Weights( {{"color", 1.0}}, {{"color", {{0, 1.0} }});
// w_red = Weights({"color":1.0}, {"color":{0:1.0}})

 yellow = new Concept(s_yellow, 1.0, 40.0, w_yellow);

 cs.add_concept("yellow", yellow, "y");


 // # define green property
 c_green = new Cuboid( {0, QtNegINF, QtNegINF}, 
   { 0.3, QtINF, QtINF }, { {"color", {0}} });

   //[0.7, QtNegINF, QtNegINF], [1.0, QtINF, QtINF], {"color":[0]})

 s_green = new Core( {c_green}, { {"color", {0}} } );
// s_red = Core([c_red], {"color":[0]})

 w_green = new Weights( {{"color", 1.0}}, {{"color", {{0, 1.0} }});
// w_red = Weights({"color":1.0}, {"color":{0:1.0}})

 green = new Concept(s_green, 1.0, 40.0, w_green);

 cs.add_concept("green", green, "g");


 // # define sour property
 c_sour = new Cuboid( {QtNegINF, 0.5, 0}, 
   { QtINF, 1, 0.4 }, { {"taste", {1, 2}} });
 s_sour = new Core( {c_sour}, { {"taste", {1, 2}} } );
 w_sour = new Weights( {{"taste", 1.0}}, {{"taste", {{1, 0.7}, {2, 1.0} }});
 sour = new Concept(s_sour, 1.0, 40.0, w_sour);
 cs.add_concept("sour", sour, "gray");


 // # define sweet property
 c_sweet = new Cuboid( {QtNegINF, 0, 0.5}, 
   { QtINF, 0.4, 1.0 }, { {"taste", {1, 2}} });
 s_sweet = new Core( {c_sweet}, { {"taste", {1, 2}} } );
 w_sweet = new Weights( {{"taste", 1.0}}, {{"taste", {{1, 0.3}, {2, 0.7} }});
 sweet = new Concept(s_sweet, 1.0, 40.0, w_sweet);
 cs.add_concept("sweet", sweet, "blue");

 //# define apple concept
 c_apple_1 = new Cuboid({0.1, 0.5, 0.1}, {0.55, 0.9, 0.5}, domains);
 c_apple_2 = new Cuboid({0.3, 0.3, 0.4}, {0.7, 0.6, 0.55}, domains);
 c_apple_3 = new Cuboid({0.45, 0.1, 0.45}, {0.9, 0.5, 0.9}, domains);
 s_apple = new Core({c_apple_1, c_apple_2, c_apple_3}, domains);
 w_apple = new Weights( {{"color",0.67}, {"taste",1.33}}, 
   {{"color",{{0, 1.0}}, {"taste", {{1, 1.0}, {2, 1.0} }});
 apple = new Concept(s_apple, 1.0, 20.0, w_apple);
 cs.add_concept("apple", apple, "r");

 // concept inspector ...  ci.init()
}

void fruit()
{
// # define the conceptual space
 Conceptual_Space cs;

// #  define the conceptual space
 domains = { {"color", {0} }, { {"shape", {1}}, {"taste", {2} };
 dimension_names = {"hue", "round", "sweet"};
 cs.init(3, domains, dimension_names)

// # standard weights for the dimensions within each domain
 w_dim = { {"color", {{0,1}}}, {"shape", {{1,1}}}, 
   {"taste", {{2:1}}} };

 //# define pear concept
 c_pear = new Cuboid({0.5, 0.4, 0.35}, {0.7, 0.6, 0.45}, domains);
 s_pear = new Core({c_pear}, domains);
 w_pear = new Weights( {{"color", 0.50}, {"shape",1.25}, 
   {"taste",1.25}}, w_dim);
 pear = new Concept(s_pear, 1.0, 24.0, w_pear);
 cs.add_concept("pear", pear, "g");

 //# define orange concept
 c_orange = new Cuboid({0.8, 0.9, 0.6}, {0.9, 1.0, 0.7}, domains);
 s_orange = new Core({c_orange}, domains);
 w_orange = new Weights( {{"color", 1.0}, {"shape",1.0}, 
   {"taste",1.0}}, w_dim);
 orange = new Concept(s_orange, 1.0, 30.0, w_orange);
 cs.add_concept("pear", orange, "orange");

 //# define lemon concept
 c_lemon = new Cuboid({0.7, 0.45, 0.0}, {0.8, 0.55, 0.1}, domains);
 s_lemon = new Core({c_lemon}, domains);
 w_lemon = new Weights( {{"color", 0.5}, {"shape",0.5}, 
   {"taste",2.0}}, w_dim);
 lemon = new Concept(s_lemon, 1.0, 40.0, w_lemon);
 cs.add_concept("lemon", lemon, "y");

 //# define Granny Smith concept
 c_granny_smith = new Cuboid({0.55, 0.70, 0.35}, {0.6, 0.8, 0.45}, domains);
 s_granny_smith = new Core({c_granny_smith}, domains);
 w_granny_smith = new Weights( {{"color", 1.0}, {"shape",1.0}, 
   {"taste",1.0}}, w_dim);
 granny_smith = new Concept(s_granny_smith, 1.0, 50.0, w_granny_smith);
 cs.add_concept("granny_smith", granny_smith, "g");

 //# define apple concept
 c_apple_1 = new Cuboid({0.5, 0.65, 0.35}, {0.8, 0.8, 0.5}, domains);
 c_apple_2 = new Cuboid({0.65, 0.65, 0.4}, {0.85, 0.8, 0.55}, domains);
 c_apple_3 = new Cuboid({0.7, 0.65, 0.45}, {1.0, 0.8, 0.6}, domains);
 s_apple = new Core({c_apple_1, c_apple_2, c_apple_3}, domains);

 w_apple = new Weights( {{"color", 0.5}, {"shape",1.5}, 
   {"taste",1.0}}, w_dim);
 apple = new Concept(s_apple, 1.0, 20.0, w_apple);
 cs.add_concept("apple", apple, "r");

 //# define banana concept
 c_banana_1 = new Cuboid({0.5, 0.1, 0.35}, {0.75, 0.30, 0.55}, domains);
 c_banana_2 = new Cuboid({0.7, 0.1, 0.5}, {0.8, 0.3, 0.7}, domains);
 c_banana_3 = new Cuboid({0.75, 0.1, 0.5}, {0.85, 0.3, 1.00}, domains);
 s_banana = new Core({c_banana_1, c_banana_2, c_banana_3}, domains);

 w_banana = new Weights( {{"color", 0.75}, {"shape",1.5}, 
   {"taste",0.75}}, w_dim);
 banana = new Concept(s_banana, 1.0, 20.0, w_banana);
 cs.add_concept("banana", banana, "r");

//# define nonSweet property
//c_non_sweet = Cuboid([QtNegINF, QtNegINF, 0.0], [QtINF, QtINF, 0.2], {"taste":[2]})
//s_non_sweet = Core([c_non_sweet], {"taste":[2]})
//w_non_sweet = Weights({"taste":1.0}, {"taste":{2:1.0}})
//non_sweet = Concept(s_non_sweet, 1.0, 14.0, w_non_sweet)
//space.add_concept("nonSweet", non_sweet, 'gray')

 c_non_sweet = new Cuboid( {QtNegINF, QtNegINF, 0.0}, 
   { QtINF, QtINF, 0.2 }, { {"taste", {2}} });
 s_non_sweet = new Core( {c_non_sweet}, { {"taste", {2}} } );
 w_non_sweet = new Weights( {{"taste", 1.0}}, {{"taste", {{2, 1.0} }});
 non_sweet = new Concept(s_non_sweet, 1.0, 14.0, w_non_sweet);
 cs.add_concept("nonSweet", non_sweet, "gray");




//# define red property
//c_red = Cuboid([0.9, QtNegINF, QtNegINF], [1.0, QtINF, QtINF], {"color":[0]})
//s_red = Core([c_red], {"color":[0]})
//w_red = Weights({"color":1.0}, {"color":{0:1.0}})
//red = Concept(s_red, 1.0, 40.0, w_red)
//space.add_concept("red", red, 'r')

 c_red = new Cuboid( {0.9, QtNegINF, QtNegINF}, 
   { 0.55, QtINF, QtINF }, { {"color", {0}} });
 s_red = new Core( {c_red}, { {"color", {0}} } );
 w_red = new Weights( {{"color", 1.0}}, {{"color", {{0, 1.0} }});
 red = new Concept(s_red, 1.0, 40.0, w_red);
 cs.add_concept("red", red, "r");

//# define green property
 c_green = new Cuboid( {0.45, QtNegINF, QtNegINF}, 
   { 1.0, QtINF, QtINF }, { {"color", {0}} });
 s_green = new Core( {c_green}, { {"color", {0}} } );
 w_green = new Weights( {{"color", 1.0}}, {{"color", {{0, 1.0} }});
 green = new Concept(s_green, 1.0, 40.0, w_green);
 cs.add_concept("green", green, "g");

//# define blue property
 c_blue = new Cuboid( {0.2, QtNegINF, QtNegINF}, 
   { 0.3, QtINF, QtINF }, { {"color", {0}} });
 s_blue = new Core( {c_blue}, { {"color", {0}} } );
 w_blue = new Weights( {{"color", 1.0}}, {{"color", {{0, 1.0} }});
 blue = new Concept(s_blue, 1.0, 40.0, w_blue);
 cs.add_concept("blue", blue, "b");
 
 // ci.init();
}

void demo()
{
 //    """Runs a short demo tour on how to use the implementation."""
    
 auto wait_for_user() = []
 {
  qDebug() << "\nPress Enter to continue...";
  raw_input();
  qDebug() << "----------------------------\n";
 };

 qDebug() << R"(\nWelcome to the demo tour.
It will give you a quick overview of the operations provided by this implementation of the conceptual spaces framework.)");

 wait_for_user();

 qDebug() << R"(A conceptual space can be defined as follows:
  (1) import cs.cs as space')
  (2) domains = {"color":[0], "shape":[1], "taste":[2]}')
  (3) space.init(3, domains)')

The first line imports the module responsible for representing the overall conceptual space.

The second line provides the domain structure of the space.
In this case, we have three domains: color, shape, and taste.
Each of them consists of a single dimension.
The domain structure is thus a dictionary mapping from domain names to list of dimension indices.
Note that each dimension of the space must belong to exactly one domain.

The third line initializes the space with the desired number of dimensions and the specified domain structure.
Note that the number of dimension given here and the number of dimensions in the domain structure must match.)";

    wait_for_user();

 qDebug() << R"(We can now define a concept as follows:
  (1) c_pear = Cuboid([0.5, 0.4, 0.35], [0.7, 0.6, 0.45], domains)')
  (2) s_pear = Core([c_pear], domains)')
  (3) w_dim = {"color":{0:1}, "shape":{1:1}, "taste":{2:1}}')
  (4) w_pear = Weights({"color":0.50, "shape":1.25, "taste":1.25}, w_dim)')
  (5) pear = Concept(s_pear, 1.0, 24.0, w_pear)')

The first line defines a cuboid with the support points p_min = [0.5, 0.4, 0.35] and p_max = [0.7, 0.6, 0.45].
Note that this cuboid is defined on the whole space, as there are values for all three dimensions.
This is also the reason why we pass the overall domain structure as a second argument - the cuboid is defined on all domains.

The second line builds a core out of this single cuboid.
In theory, we can give a list of multiple cuboids as a first parameter to this constructor. The only constraint is that these cuboids need to have a nonempty intersection.
We also need again to specify the set of domains on which this core is defined (which in this case is again the whole space).

The third line defines a set of weights for the dimensions.
As the sum of dimension weights within each dimension must equal 1.0, and as each domain only contains a single dimension, all the dimension weights are set to 1.0 here.

The fourth line defines the domain weights and the overall weights parameter.
As one can see, the 'shape' and the 'taste' domain are weighted higher than the 'color' domain in this case.
Note that the sum of the domain weights must equal the number of domains. If the provided numbers don't add up, the constructor of the Weights class will normalize them automatically.

Finally, the fifth line creates the 'pear' concept.
We use the core defined in line 2 and the weights defined in line 4.
The maximal membership is set to 1.0 and the sensitivity parameter (which controls the rate of the membership function's exponential decay) is set to 24.)";

 wait_for_user();

 qDebug() << R"(For convenience, the conceptual space also contains a dictionary for storing concepts.
We can add our newly created concept to this dictionary under the identifier 'pear' as follows:
    space.add_concept("pear", pear)')

In this file, we have already defined several concepts for different types of fruit along with some properties.
Variables for fruit concepts (with identifiers in parentheses): pear ('pear'), orange ('orange'), lemon ('lemon'), granny_smith ('Granny Smith'), apple ('apple'), banana ('banana')
Variables for properties: red ('red'), green, ('green'), blue ('blue'), non_sweet ('nonSweet')

The folder 'conceptual_spaces/demo/images' contains some 2D and 3D visualizations of these concepts.)";

 wait_for_user();

 qDebug() << R"(We can display a concept by simply printing it:
    print(pear)

This results in the following output:
    core: {[0.5, 0.4, 0.35]-[0.7, 0.6, 0.45]}')
    mu: 1.0')
    c: 24.0')
    weights: <{'color': 0.5, 'taste': 1.25, 'shape': 1.25},{'color': {0: 1.0}, 'taste': {2: 1.0}, 'shape': {1: 1.0}}>)";

 wait_for_user();

 qDebug() << R"(We can execute the following operations on a concept c:
    c.membership_of(x): computes the membership of a point x to the concept c.
    c.intersect_with(d): computes the intersection of the concepts c and d.
    c.unify_with(d): computes the unification of the two concepts c and d.
    c.project_onto(domains): projects the concept c onto the given domains.
    c.cut_at(dimension, value): cuts the concept c into two parts. The cut is placed at the given value on the given dimension.
    c.size(): computes the size of the concept c.
    c.subset_of(d): computes the degree to which the concept c is a subset of the concept d.
    c.implies(d): computes the degree to which the concept c implies the concept d.
    c.similarity_to(d): computes the degree of similarity between the concept c and the concept d.
    c.between(d, e): decides whether the concept c is between the concepts d and e.)";

 wait_for_user();

 qDebug() << R"(Let us illustrate these operations with some examples:
    
    pear.membership_of([0.6, 0.5, 0.4])
        1.0
    
    pear.membership_of([0.3, 0.2, 0.1])
        1.243706023602872e-07
    
    print(pear.intersect_with(apple))
        core: {[0.5, 0.625, 0.35]-[0.7, 0.625, 0.45]}
        mu: 0.4723665527
        c: 20.0
        weights: <{'color': 0.5, 'taste': 1.125, 'shape': 1.375},{'color': {0: 1.0}, 'taste': {2: 1.0}, 'shape': {1: 1.0}}>)";

 wait_for_user();

 qDebug() << R"(    print(pear.unify_with(apple))
        core: {[0.5, 0.4, 0.35]-[0.7125, 0.6687500000000001, 0.45625000000000004], [0.5, 0.65, 0.35]-[0.8, 0.8, 0.5], [0.65, 0.65, 0.4]-[0.85, 0.8, 0.55], [0.7, 0.65, 0.45]-[1.0, 0.8, 0.6]}
        mu: 1.0
        c: 20.0
        weights: <{'color': 0.5, 'taste': 1.125, 'shape': 1.375},{'color': {0: 1.0}, 'taste': {2: 1.0}, 'shape': {1: 1.0}}>
    
    print(pear.project_onto({'color':[0]}))
        core: {[0.5, -inf, -inf]-[0.7, inf, inf]}
        mu: 1.0
        c: 24.0
        weights: <{'color': 1.0},{'color': {0: 1.0}}>)";

 wait_for_user();

 qDebug() << R"(    first, second = pear.cut_at(1, 0.5)
    print(first)
        core: {[0.5, 0.4, 0.35]-[0.7, 0.5, 0.45]}
        mu: 1.0
        c: 24.0
        weights: <{'color': 0.5, 'taste': 1.25, 'shape': 1.25},{'color': {0: 1.0}, 'taste': {2: 1.0}, 'shape': {1: 1.0}}>
    print(second)
        core: {[0.5, 0.5, 0.35]-[0.7, 0.6, 0.45]}
        mu: 1.0
        c: 24.0
        weights: <{'color': 0.5, 'taste': 1.25, 'shape': 1.25},{'color': {0: 1.0}, 'taste': {2: 1.0}, 'shape': {1: 1.0}}>)";

 wait_for_user();

 qDebug() << R"(    apple.size()
        0.0455
    lemon.size()
        0.005000000000000002
    granny_smith.subset_of(apple)
        1.0
    apple.subset_of(granny_smith)
        0.07635041551246535
    granny_smith.crisp_subset_of(apple)
        True
    apple.crisp_subset_of(granny_smith)
        False
    apple.implies(red)
        0.2727272727272726
    lemon.implies(non_sweet)
        1.0)";

 wait_for_user();

 qDebug() << R"(    apple.similarity_to(pear)
        0.0398322124027715
    pear.similarity_to(apple)
        0.0398322124027715
    granny_smith.similarity_to(apple)
        0.1537267080745342
    apple.similarity_to(pear, method='subset')
        0.05043467196991022
    pear.similarity_to(apple, method='subset')
        0.118091638175
    granny_smith.similarity_to(apple, method='subset')
        1.0;)";

 wait_for_user();

 qDebug() << R"(    apple.between(lemon, orange)
        0.87552874038096906
    banana.between(granny_smith, pear)
        0.43811732667337056
    granny_smith.between(lemon, orange)
        0.8789129336237107
    apple.between(lemon, orange, method='minimum')
        0.0
    banana.between(granny_smith, pear, method='minimum')
        0.0
    granny_smith.between(lemon, orange, method='minimum')
        0.82471568013506558)";


 wait_for_user();

 qDebug() << R"(Our implementation provides also a visualization tool: The so-called ConceptInspector.
You can execute it with the following code:
    import visualization.concept_inspector as ci 
    ci.init()
The first line imports the necessary package.
The second line calls the initialization method of the ConceptInspector.
The ConceptInspector grabs all information about domains, dimensions, and concepts from the cs module. You should therefore only call 'ci.init()' once you have initialized your conceptual space and created all concepts.
The ConceptInspector provides one 3D and three 2D visualizations of the conceptual space. You can interactively change the dimensions used for these visualizations as well as the set of concepts being displayed.
If you have added, modified, or removed concepts after your call to 'ci.init()', you can tell the ConceptInspector to update its internal list of concepts:
    ci.update()
Only when this function is called, the ConceptInspector will update its internal list of concepts based on the concepts stored in the cs module.
    
This is already the end of our little tour. We hope it gave you an impression of how you can use our framework.
Feel free to play around with the fruit space a little bit more by typing in your own operations on the given concepts or by defining new ones.)";

 wait_for_user();

}


int main(int argc, char* argv[])
{
 apple();

 fruit();

}
