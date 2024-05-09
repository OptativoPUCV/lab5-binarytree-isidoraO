#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) 
{
  TreeMap *new_map = (TreeMap *) malloc(sizeof(TreeMap));
  new_map->root = NULL;
  new_map->current = NULL;
  new_map->lower_than = lower_than;
  return new_map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) 
{
  TreeNode *new_node = createTreeNode(key, value);
  if(tree->root == NULL)
  {
    tree->root = new_node;
    tree->current = tree->root;
    return;
  }
  
  TreeNode *aux = tree->root;
  TreeNode *parent = NULL;
  while((aux != NULL) && (!is_equal(tree, aux->pair->key, key)))
    {
      parent = aux;
      if(tree->lower_than(key, aux->pair->key))
        aux = aux->left;
      else
        aux = aux->right;
    }
  if(tree->lower_than(key, parent->pair->key))
    parent->left = new_node;
  else
    parent->right = new_node;
  
  new_node->parent = parent;
  tree->current = new_node;
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
