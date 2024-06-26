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

TreeNode * minimum(TreeNode * x)
{
  TreeNode *aux = x;
  if(aux->left == NULL) return aux;

  while(aux->left != NULL)
    aux = aux->left;
  return aux;
}


void removeNode(TreeMap * tree, TreeNode* node) 
{
  //caso 1: el nodo no tiene hijos.
  if((node->left == NULL) && (node->right == NULL))
  {
    if(tree->lower_than(node->pair->key, node->parent->pair->key))
      node->parent->left = NULL;
    else
      node->parent->right = NULL;
    node->parent = NULL;
    free(node);
  }
  //caso 2: el nodo tiene un hijo.
  else if(node->right == NULL || node->left == NULL)
  {
    TreeNode *aux_child;
    if(node->left != NULL)
      aux_child = node->left;
    else
      aux_child = node->right;

    if(node->parent->left == node)
      node->parent->left = aux_child;
    else
      node->parent->right = aux_child;
    aux_child->parent = node->parent;
    free(node);
      
  }
  //caso 3: el nodo tiene dos hijos.
  else
  {
    TreeNode *aux = node->right;
    while((aux->left != NULL) && (!is_equal(tree, aux->pair->key, node->pair->key)))
        aux = aux->left;
    node->pair = aux->pair;
    removeNode(tree, aux);
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) 
{
  TreeNode *aux = tree->root;
  if(aux == NULL || tree == NULL) return NULL;

  while((aux != NULL) && (!is_equal(tree, key, aux->pair->key)))
  {
    if(tree->lower_than(key, aux->pair->key))
      aux = aux->left;
    else
      aux = aux->right;
  }
  
  if(aux != NULL)
  {
    tree->current = aux;
    return aux->pair;
  }

  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) 
{
  if(tree == NULL) return NULL;
  
  Pair *aux_upper = searchTreeMap(tree, key);
  
  Pair *aux = tree->current->pair;
  if(aux_upper == NULL)
  {
    while(aux != NULL)
      {
        if(tree->lower_than(key, aux->key))
        {
          aux_upper = aux;
          return aux_upper;
        }
        aux = nextTreeMap(tree);
      }
  }
  return aux_upper;
}

Pair * firstTreeMap(TreeMap * tree) 
{
  TreeNode *aux = tree->root;
  while(aux->left != NULL)
      aux = aux->left;
  return aux->pair;
}

Pair * nextTreeMap(TreeMap * tree) 
{  
  if(tree == NULL || tree->current == NULL) return NULL;

  TreeNode *aux = tree->current;
  if(aux->right != NULL)
    aux = minimum(aux->right);
  else
  {    
    TreeNode *temp_aux = aux;
    while(aux->parent != NULL)
      {
        temp_aux = aux;
        aux = aux->parent;
        if(aux->left == temp_aux)
        {
          tree->current = aux;
          return aux->pair;
        }
      }
    return NULL;
  }
  tree->current = aux;
  return aux->pair;
}
