
#ifndef DB_NODES_HPP
#define DB_NODES_HPP

// forward declarations
class Node;
class FEMFile;
class DB_Elements;

// includes
#include <map>
#include <vector>

// namespaces
using namespace std;

class DB_Nodes {

private:
  FEMFile* femfile;
  map<int,size_t> id2index;
  vector<Node*> nodes;
  DB_Elements* db_elements;

public:
  DB_Nodes(FEMFile* _femfile);
  ~DB_Nodes();
  size_t size();
  void reserve(const size_t _size);
  FEMFile* get_femfile();
  DB_Elements* get_db_elements();
  void set_db_elements(DB_Elements*);
  Node* add_node(int _id,vector<float> _coords);

  template<typename T>
  T get_id_from_index(size_t _id);
  template<typename T>
  size_t get_index_from_id(T _index);

  template<typename T>
  Node* get_nodeByID(T _id);
  template<typename T>
  Node* get_nodeByIndex(T _index);

};



/** Get the node index from it's id
 *
 * @param T _id : node id
 * @return size_t : node index
 */
template<typename T>
T DB_Nodes::get_id_from_index(size_t _index){

  if(_index > nodes.size()-1)
    throw( string("Node with index ")+to_string(_index)+string(" does not exist in the db.") );
  return _index;

}


/** Get the node id from it's index
 *
 * @param T _id : node id
 * @return size_t _index : node index
 */
template<typename T>
size_t DB_Nodes::get_index_from_id(T _id){

  map<int,size_t>::iterator it = this->id2index.find(_id);
  if(it == this->id2index.end())
    throw( string("Node with id ")+to_string(_id)+string(" does not exist in the db.") );
  return it->second;

}


/** Get a node from the node ID.
 *
 * @param T _id : id of the node
 * @return Node* node : pointer to the node or NULL if node is not existing!
 */
template <typename T>
Node* DB_Nodes::get_nodeByID(T _id){

  map<int,size_t>::iterator it = this->id2index.find(_id);
  if(it == this->id2index.end())
    return NULL;
  return this->nodes[ it->second ];

}


/** Get a node from the node index.
 *
 * @param int _nodeIndex : index of the node
 * @return Node* node : pointer to the node or NULL if node is not existing!
 */
template <typename T>
Node* DB_Nodes::get_nodeByIndex(T _nodeIndex){

  if(_nodeIndex >= this->nodes.size())
     return NULL;
  return this->nodes[_nodeIndex];

}

#endif
