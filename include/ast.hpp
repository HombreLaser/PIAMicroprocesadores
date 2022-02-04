/* MICROPROCESADORES - PROYECTO INTEGRADOR DE APRENDIZAJE.
   Luis Sebastián Martínez Vega
   Luis Javier Olivares Lara
   José de Jesús Jaramillo Aguilera
   Daniel Hipólito Galindo Hernández

   Parte de la librería para el análisis sintáctico de
   expresiones aritméticas: el árbol de sintaxis abstracta.
*/
#include <string>
#include "lexer.hpp"
#ifndef AST_H
#define AST_H

using std::string;

struct Node {
  Node *left {};
  Node *right {};
  Token value {};
};

class AST{
private:
  Node *root;
  void postOrderDelete(Node *current); // Recorrido del árbol en postorden.
public:
  AST(Node *tree_root);
  ~AST();
  Node *getRoot() const;
  float eval(Node *current);
};

class ZeroDivisionException{
private:
  string error_msg;
public:
  ZeroDivisionException(string msg);
  string getErrorMsg() const;
};

#endif /* AST_H */
