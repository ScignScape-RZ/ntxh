#ifndef __GRAPH__
#define __GRAPH__
#define NULL 0
#include "BioCoder.h"

#include "global-types.h"

#include <QDateTime>
#include <QString>
#include <QVector>

struct Node;

typedef QVector<Node*> Nodelist;

struct Node 
{
 u4 id;
 QDateTime time;
 QString unit;
 u4 type;
 QString name;
 u4 pcr_or_centrifuge;
 Nodelist* in;
 Nodelist* out;
 Node();
};

//struct Nodelist {
// Node* node;
// Nodelist* next;
//};

class Graph
{
 Nodelist all_nodes_;
 u4 max_node_id_; 

public:

 Graph();

 // create a new node, with the given name, and assign it a unique id
 Node* create_node(QString name);

 // adds an edge from node1 to node2
 void create_edge(Node* node1, Node* node2);

 // adds an edge from x1 to x2, where x1 and x2 are Fluids, Samples, or Operations
 // if nodes do not yet exist for these quantities, then create them
 void create_edge_from_fluids(void* x1, void* x2);

 void create_edge_from_containers(void* x1, void* x2);

 void create_edge_from_fluid_to_container(void* x1, void* x2);

 void create_edge_from_container_to_fluid(void* x1, void* x2);

 // adds the given node to the list of nodes.
 void add_to_list(Node* node, Nodelist* list);

 // exports the current runtime graph to the given filename, in .dot format
 void export_graph(QString filename);
};


#endif
