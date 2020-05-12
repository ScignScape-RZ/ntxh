
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
 c_red = new Cuboid( {0.7, float("-inf"), float("-inf")}, 
   { 1.0, float("inf"), float("inf") }, { {"color", {0}} });

   //[0.7, float("-inf"), float("-inf")], [1.0, float("inf"), float("inf")], {"color":[0]})

 s_red = new Core( {c_red}, { {"color", {0}} } );
// s_red = Core([c_red], {"color":[0]})

 w_red = new Weights( {{"color", 1.0}}, {{"color", {{0, 1.0} }});
// w_red = Weights({"color":1.0}, {"color":{0:1.0}})

 red = new Concept(s_red, 1.0, 40.0, w_red);

 cs.add_concept("red", red, "r");


 // # define yellow property
 c_yellow = new Cuboid( {0.4, float("-inf"), float("-inf")}, 
   { 0.6, float("inf"), float("inf") }, { {"color", {0}} });

   //[0.7, float("-inf"), float("-inf")], [1.0, float("inf"), float("inf")], {"color":[0]})

 s_yellow = new Core( {c_yellow}, { {"color", {0}} } );
// s_red = Core([c_red], {"color":[0]})

 w_yellow = new Weights( {{"color", 1.0}}, {{"color", {{0, 1.0} }});
// w_red = Weights({"color":1.0}, {"color":{0:1.0}})

 yellow = new Concept(s_yellow, 1.0, 40.0, w_yellow);

 cs.add_concept("yellow", yellow, "y");


 // # define green property
 c_green = new Cuboid( {0, float("-inf"), float("-inf")}, 
   { 0.3, float("inf"), float("inf") }, { {"color", {0}} });

   //[0.7, float("-inf"), float("-inf")], [1.0, float("inf"), float("inf")], {"color":[0]})

 s_green = new Core( {c_green}, { {"color", {0}} } );
// s_red = Core([c_red], {"color":[0]})

 w_green = new Weights( {{"color", 1.0}}, {{"color", {{0, 1.0} }});
// w_red = Weights({"color":1.0}, {"color":{0:1.0}})

 green = new Concept(s_green, 1.0, 40.0, w_green);

 cs.add_concept("green", green, "g");


 // # define sour property
 c_sour = new Cuboid( {float("-inf"), 0.5, 0}, 
   { float("inf"), 1, 0.4 }, { {"taste", {1, 2}} });
 s_sour = new Core( {c_sour}, { {"taste", {1, 2}} } );
 w_sour = new Weights( {{"taste", 1.0}}, {{"taste", {{1, 0.7}, {2, 1.0} }});
 sour = new Concept(s_sour, 1.0, 40.0, w_sour);
 cs.add_concept("sour", sour, "gray");


 // # define sweet property
 c_sweet = new Cuboid( {float("-inf"), 0, 0.5}, 
   { float("inf"), 0.4, 1.0 }, { {"taste", {1, 2}} });
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
//c_non_sweet = Cuboid([float("-inf"), float("-inf"), 0.0], [float("inf"), float("inf"), 0.2], {"taste":[2]})
//s_non_sweet = Core([c_non_sweet], {"taste":[2]})
//w_non_sweet = Weights({"taste":1.0}, {"taste":{2:1.0}})
//non_sweet = Concept(s_non_sweet, 1.0, 14.0, w_non_sweet)
//space.add_concept("nonSweet", non_sweet, 'gray')

 c_non_sweet = new Cuboid( {float("-inf"), float("-inf"), 0.0}, 
   { float("inf"), float("inf"), 0.2 }, { {"taste", {2}} });
 s_non_sweet = new Core( {c_non_sweet}, { {"taste", {2}} } );
 w_non_sweet = new Weights( {{"taste", 1.0}}, {{"taste", {{2, 1.0} }});
 non_sweet = new Concept(s_non_sweet, 1.0, 14.0, w_non_sweet);
 cs.add_concept("nonSweet", non_sweet, "gray");




//# define red property
//c_red = Cuboid([0.9, float("-inf"), float("-inf")], [1.0, float("inf"), float("inf")], {"color":[0]})
//s_red = Core([c_red], {"color":[0]})
//w_red = Weights({"color":1.0}, {"color":{0:1.0}})
//red = Concept(s_red, 1.0, 40.0, w_red)
//space.add_concept("red", red, 'r')

 c_red = new Cuboid( {0.9, float("-inf"), float("-inf")}, 
   { 0.55, float("inf"), float("inf") }, { {"color", {0}} });
 s_red = new Core( {c_red}, { {"color", {0}} } );
 w_red = new Weights( {{"color", 1.0}}, {{"color", {{0, 1.0} }});
 red = new Concept(s_red, 1.0, 40.0, w_red);
 cs.add_concept("red", red, "r");

//# define green property
 c_green = new Cuboid( {0.45, float("-inf"), float("-inf")}, 
   { 1.0, float("inf"), float("inf") }, { {"color", {0}} });
 s_green = new Core( {c_green}, { {"color", {0}} } );
 w_green = new Weights( {{"color", 1.0}}, {{"color", {{0, 1.0} }});
 green = new Concept(s_green, 1.0, 40.0, w_green);
 cs.add_concept("green", green, "g");

//# define blue property
 c_blue = new Cuboid( {0.2, float("-inf"), float("-inf")}, 
   { 0.3, float("inf"), float("inf") }, { {"color", {0}} });
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

 qDebug() << R"\nWelcome to the demo tour.\n")
    print("It will give you a quick overview of the operations provided by this implementation of the conceptual spaces framework.")
    wait_for_user()



 


}


int main(int argc, char* argv[])
{
 apple();

 fruit();

}
