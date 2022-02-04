/* MICROPROCESADORES - PROYECTO INTEGRADOR DE APRENDIZAJE.
   Luis Sebastián Martínez Vega
   Luis Javier Olivares Lara
   José de Jesús Jaramillo Aguilera
   Daniel Hipólito Galindo Hernández

   Parte de la librería para el análisis sintáctico de
   expresiones aritméticas: implentación del parser,
   el analizador sintáctico.
*/
#include <iostream>
#include "parser.hpp"
#include "lexer.hpp"
#include "ast.hpp"

ParserException::ParserException(string error_msg)
  : error{error_msg}{}

string ParserException::getError() const{
  return error;
}

Parser::Parser(char *text)
    : tokenizer(text){
  nextToken();
  node_stack.reserve(INITIAL_STACK_SIZE);
}

AST *Parser::parse(){
  if(!parseExpression())
    throw ParserException("SYNTAX ERROR");

  /* De haber salido todo bien, habrá un solo
     nodo en la pila: la raíz del árbol. */
  AST *syntaxTree = new AST(popStack());

  return syntaxTree;
}

void Parser::nextToken(){
  current_token = tokenizer.nextToken();
}

Node *Parser::popStack(){
  Node *new_node = node_stack.back();
  node_stack.pop_back(); 

  return new_node;
}

bool Parser::parseExpression(){
  if(!parseTerm())
    return false;

  return parsePrimeExpression();
}

bool Parser::parsePrimeExpression(){
  if(current_token.type == sum || current_token.type == substraction)
  {
    Token current_operator = current_token;
    nextToken();
    
    if(!parseTerm())
      return false;

    node_stack.push_back(new Node{popStack(), popStack(), current_operator});
    
    return parsePrimeExpression();
  }
  
  return true;
}

bool Parser::parseTerm(){
  if(!parseFactor())
    return false;

  return parsePrimeTerm();
}

bool Parser::parsePrimeTerm(){
  if(current_token.type == multiplication || current_token.type == division)
  {
    Token current_operator = current_token;
    nextToken();
      
    if(!parseFactor())
      return false;

    node_stack.push_back(new Node{popStack(), popStack(), current_operator});
      
    return parsePrimeTerm();
  }
  
  return true;
}

bool Parser::parseFactor(){
  Token current_operator;

  switch(current_token.type)
  {
  case substraction:
    current_operator = current_token;  // Nodo de negación.
    nextToken();
    
    if(!parseExpression())
      return false;

    node_stack.push_back(new Node{popStack(), NULL, current_operator});

    break;
  case left_parens:
    nextToken();
    
    if(!parseExpression())
      return false;

    if(current_token.type != right_parens)
      return false;
    
    break;
  case number:
    node_stack.push_back(new Node{NULL, NULL, current_token});
    nextToken();
    
    break;
  default:
    return false;
  }

  return true;
}
