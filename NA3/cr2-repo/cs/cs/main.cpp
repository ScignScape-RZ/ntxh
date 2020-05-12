
#include "core.h"

#include "cs.h"

#include <QMap>
#include <QVector>
#include <QString>
#include <QStringList>



void apple()
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
 w_sweet = new Weights( {{"taste", 1.0}}, {{"taste", {{1, 0.7}, {2, 1.0} }});
 sweet = new Concept(s_sweet, 1.0, 40.0, w_sweet);
 cs.add_concept("sweet", sweet, "gray");


}

void fruit()
{


}

int main(int argc, char* argv[])
{
 apple();

 fruit();

}
