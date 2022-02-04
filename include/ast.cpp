/* MICROPROCESADORES - PROYECTO INTEGRADOR DE APRENDIZAJE.
   Luis Sebastián Martínez Vega
   Luis Javier Olivares Lara
   José de Jesús Jaramillo Aguilera
   Daniel Hipólito Galindo Hernández

   Parte de la librería para el análisis sintáctico de
   expresiones aritméticas: implementación de el árbol
   de sintaxis abstracta.
*/
#include <stdexcept>
#include <string>
#include <cstdio>
#include <stdexcept>
#include <type_traits>
#include "ast.hpp"
#include "lexer.hpp"

using std::sscanf;
using std::stol;
using std::invalid_argument;

AST::AST(Node *tree_root)
  : root{tree_root}{}

void AST::postOrderDelete(Node *current) {
  if(current->left)
    postOrderDelete(current->left);

  if(current->right)
    postOrderDelete(current->right);

  if(current->value.type == number)
    delete [] current->value.value; // Borramos también la cadena de carácteres asignada.

  delete current;
}

AST::~AST() {
  postOrderDelete(root);
}

Node *AST::getRoot() const {
  return root;
}

float AST::eval(Node *current){
  float result;

  // Checamos si tenemos un nodo de negación.
  if(current->left != NULL && current->right == NULL)
    return -1 * eval(current->left);
  
  switch(current->value.type)
  {
  case sum:
    return eval(current->left) + eval(current->right);
  case substraction:
    return eval(current->left) - eval(current->right);
  case multiplication:
    return eval(current->left) * eval(current->right);
  case division:
  {
    float denominator = eval(current->left);

    if(denominator == 0)
      throw ZeroDivisionException("División entre 0.");
    
    return eval(current->right) / denominator;
  }
  default: // Es un número.
    if(sscanf(current->value.value, "%f", &result) == EOF)
      throw invalid_argument("Conversión fallida.");

    return result;
  }
}

ZeroDivisionException::ZeroDivisionException(string msg)
  : error_msg{msg} {}

string ZeroDivisionException::getErrorMsg() const{
  return error_msg;
}
