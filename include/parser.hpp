/* MICROPROCESADORES - PROYECTO INTEGRADOR DE APRENDIZAJE.
   Luis Sebastián Martínez Vega
   Luis Javier Olivares Lara
   José de Jesús Jaramillo Aguilera
   Daniel Hipólito Galindo Hernández

   Parte de la librería para el análisis sintáctico de
   expresiones aritméticas: el parser, el analizador sintáctico.
*/
#include <cstddef>
#include <string>
#include <vector>
#include "lexer.hpp"
#include "ast.hpp"
#ifndef PARSER_H
#define PARSER_H

using std::string;
using std::vector;

/* La pila que guardará los nodos del árbol tendrá una capacidad inicial de 4
   nodos, al final terminaremos con un solo nodo en la pila (la raíz del árbol)
   y regularmente tendremos al menos 2 nodos. (dos operandos). */
constexpr size_t INITIAL_STACK_SIZE = 4;

class ParserException{
private:
  string error;
public:
  ParserException(string error_msg);
  string getError() const; 
};

class Parser{
private:
  Lexer tokenizer;
  char *text;
  Token current_token;
  vector< Node * >node_stack;
  void nextToken();
  Node *popStack();
  bool parseExpression();
  bool parsePrimeExpression();
  bool parseTerm();
  bool parsePrimeTerm();
  bool parseFactor();
public:
  Parser(char *text);
  AST *parse();
};
#endif /* PARSER_H */
