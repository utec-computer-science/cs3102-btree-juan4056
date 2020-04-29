#include <iostream>
#include <vector>

#define BST_NODE_FLAGXX 1
#define B_NODE_FLAGXX 2

#define SS_FLAGXX 1
#define BS_FLAGXX 2

template <typename T>
class SS_Traits{
public:
  typedef T  value_t;
  typedef std::vector<value_t> container_t;
  typedef typename container_t::iterator iterator_t;
  
  class simple_search{
  public:
    int operator() (container_t a, value_t v, int size){
      int i = 0;

      return i;
    }
  };

  class post_order_print{
  public:
    void operator() (void){
      std::cout << "post order" << std::endl;
    }
  };

  typedef simple_search functor_t;
  typedef post_order_print print_t;
};

template <typename T>
class BS_Traits{
public:
  typedef T  value_t;
  typedef std::vector<value_t> container_t;
  typedef typename container_t::iterator iterator_t;
  
  class binary_search{
  public:
    int operator() (container_t a, value_t v, int size){

      int m=0;

      return m;
    }
  };

  class pre_order_print{
  public:
    void operator() (void){
      std::cout << "pre order" << std::endl;
    }
  };

  typedef binary_search functor_t;
  typedef pre_order_print print_t;
};

template <typename Search>
struct SearchTraits {
  static const int flag_type = 0;
};

template <typename T>
struct SearchTraits <SS_Traits <T>> {
  static const int flag_type = SS_FLAGXX;
};

template <typename T>
struct SearchTraits <BS_Traits <T>> {
  static const int flag_type = BS_FLAGXX;
};

class BSTNodeTraits{
  public:
    typedef int value_t;
};

class BSTNode : public BSTNodeTraits{
  public: 
  typedef typename  BSTNodeTraits::value_t value_t;

  value_t data;
  BSTNode ** children;

  BSTNode(value_t data){
    children = new BSTNode*[2];
  }

  ~BSTNode(void){}

};


template <typename T, int S>
class BNode {
  public:
  typedef typename T::value_t value_t;
  typedef typename T::container_t container_t;
  typedef std::vector<BNode<T, S>*> pcontainer_t;
  typedef T search_t;
  typedef BNode <T, S> node_t;
  typedef typename search_t::print_t print_t;
  
  container_t keys;
  pcontainer_t children;
  std::size_t order;
  std::size_t size;

  BNode(void):order(S), size(0){
    keys = container_t(order,-1);
    children = pcontainer_t(order,NULL);
  }

  ~BNode(void){}

};

template <typename BN, int Flag>
struct SearchHelper {
  typedef typename BN::node_t node_t;
  typedef typename BN::value_t value_t;
  typedef typename BN::search_t search_t;
  typedef typename search_t::functor_t functor_t;
  typedef typename search_t::print_t print_t;

  static void print (node_t ** head){
    std::cout << "Impresión inválida" << std::endl;
  }

  static void search (node_t** head, const value_t& val){
    std::cout << "Busqueda invalida" << std::endl;
  }

};


template <typename BN>
struct SearchHelper <BN, SS_FLAGXX> {
  typedef typename BN::node_t node_t;
  typedef typename BN::value_t value_t;
  typedef typename BN::search_t search_t;
  typedef typename search_t::functor_t functor_t;
  typedef typename search_t::print_t print_t;

  static void print (node_t ** head) {
    std::cout << "Simple search print" << std::endl;
    print_t print_t;
    print_t();
  }

  static void search (node_t** head, const value_t& val){
    std::cout << "Simple search busqueda" << std::endl;
  }
};

template <typename BN>
struct SearchHelper <BN, BS_FLAGXX> {
  typedef typename BN::node_t node_t;
  typedef typename BN::value_t value_t;
  typedef typename BN::search_t search_t;
  typedef typename search_t::functor_t functor_t;
  typedef typename search_t::print_t print_t;

  static void print (node_t ** head) {
    std::cout << "Binary search print" << std::endl;
    print_t print_t;
    print_t();
  }

  static void search (node_t** head, const value_t& val){
    std::cout << "Binary search busqueda" << std::endl;
  }
};

template <typename Node>
struct NodeTraits{
  static const int  flag_type = 0;
};

template <>
struct NodeTraits< BSTNode >{
  static const int  flag_type = BST_NODE_FLAGXX;
};


template <typename T, int S>
struct NodeTraits< BNode <T, S> >{
  static const int  flag_type = B_NODE_FLAGXX;
};

template<typename  Node, int Flag>
struct TreeHelper{
  typedef Node  node_t;
  typedef typename node_t::value_t value_t;
  
  static void  insert (node_t** head, const value_t& val){
    std::cout << "el tipo de dato no es compatible" << std::endl;
  }

  static void  print (node_t** head){
  }

  static void search (node_t ** head, const value_t& val){

  }

};

template<>
struct TreeHelper<BSTNode,BST_NODE_FLAGXX>{
  typedef BSTNode  node_t;
  typedef typename node_t::value_t value_t;
  
  static void  insert (node_t** head, const value_t& val){
    std::cout << "Insertando para un nodo BST" << std::endl;
  }

  static void  print (node_t** head){
  }

  static void search (node_t ** head, const value_t& val){

  }
};

template<typename T, int S>
struct TreeHelper<BNode<T, S>,B_NODE_FLAGXX>{
  typedef BNode<T, S>  node_t;
  typedef typename node_t::value_t value_t;

  static void split (node_t * father, int id){
    node_t * ynode = new node_t;
    node_t * znode = new node_t;

    int med = (S - 1) / 2;

    for (int i = 0; i < med ; i++){
      znode->keys [i] = father->children[id]->keys [med + 1 + i];
      ynode->keys [i] = father->children[id]->keys [i];

      znode->children [i] = father->children[id]->children [med + 1 + i];
      ynode->children [i] = father->children[id]->children [i];
    }
    znode->size = med;
    ynode->size = med;
    znode->children [med] = father->children[id]->children [2*med + 1];
    ynode->children [med] = father->children[id]->children [med];

    for (int j = S - 3; j >= id; j--){
      father->keys [j + 1] = father->keys [j];
      father->children [j + 2] = father->children [j + 1];
    }

    father->keys [id] = father->children[id]->keys [med];
    father->size ++;
    delete father->children[id];
    father->children[id] = ynode;
    father->children[id + 1] = znode;
  }
  
  static void  insert (node_t** head, const value_t& val){
    std::cout << "\nInsertando " << val << " para un nodo B" << std::endl;
    node_t * x = *head;
    if (!x){
      *head = new BNode<T, S>;
      (*head)->keys [0] = val;

      return;
    }

    BNode<T, S>* noFull = NULL;
    if ((*head)->keys [S-2] == -1)
      noFull = (*head);
    
    while (x->children [0]){
      int i = 0;
      while  (x->keys[i] < val && i < S - 1 && x->children[i + 1]){
        i++;
      }
      BNode <T, S>* y = x->children[i];
      x = y;
      if (x->keys [S-2] == -1){
        noFull = x;
      }
    }

    

    if (noFull != x){
      //std::cout << "Prepare to split \n";
      if (!noFull){
        BNode<T, S> * newroot = new BNode<T, S>;
        newroot->children [0] = (*head);
        (*head) = newroot;
        noFull = newroot;
      }
      x = noFull;
      while (x->children [0]){
        int i = 0;
        while  (x->keys[i] < val && i < S - 1 && x->children[i + 1]){
          i++;
        }
        //std::cout << "SPlit in " << i << "\n";

        //SPLIT
        split (x, i);
        if (val > x->keys [i])
          i++;

        x = x->children [i];
      }
    }

    int i = S - 2;
    //std::cout << "Prepare to insert\n" ;
    
    while (i >= 0 && (x->keys [i] > val || x->keys [i] == -1)){
      x->keys [i + 1] = x->keys [i];
      i--;
    }
    x->keys [i + 1] = val;
    x->size++;


  }

  static void  print (node_t** head){
    SearchHelper <node_t, SearchTraits <typename node_t::search_t>::flag_type> :: print (head);
  }

  static void search (node_t** head, const value_t& val){
    SearchHelper <node_t, SearchTraits <typename node_t::search_t>::flag_type> :: search (head, val);
  }
};

template <typename Node>
class Tree {
  public:
  typedef Node node_t;
  typedef typename node_t::value_t value_t;

  node_t * root;
  Tree (void) : root(nullptr){}

  ~Tree(void){}

  void insert(const value_t& val){
    add<NodeTraits<node_t>::flag_type>(&root,val);
  }

  void print(){
    TreeHelper <node_t, NodeTraits<node_t>::flag_type>::print (&root);
  }

  void search (const value_t& val){
    TreeHelper <node_t, NodeTraits<node_t>::flag_type>::search (&root, val);
  }

  template <int Flag> 
  void add(node_t**, const value_t&);

};

template<typename Node> template <int Flag>
void Tree<Node>::add(
  typename Tree<Node>::node_t ** root, 
  const typename Tree<Node>::value_t & val){
  TreeHelper<Tree<Node>::node_t,Flag>::insert(root,val);
}

int main (){
  typedef BNode<BS_Traits<int>, 4> bs_int_node;
  typedef BNode<SS_Traits<int>, 4> ss_int_node;
  typedef Tree<bs_int_node> bsb_tree;
  typedef Tree<ss_int_node> ssb_tree;

  bsb_tree tree;
  ssb_tree tree2;

  tree.insert (1);
  tree.insert (2);
  tree.insert (3);
  tree.insert (4);
  tree.insert (5);
  tree.insert (6);
  tree.insert (7);
  tree.insert (8);
  tree.insert (9);
  tree.insert (10);
  tree.insert (11);
  tree.insert (12);
  tree.search (1);
  tree.print ();

  tree2.insert(20);
  tree2.search (20);
  tree2.print();
}