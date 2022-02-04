/* MICROPROCESADORES - PROYECTO INTEGRADOR DE APRENDIZAJE. 
   Luis Sebastián Martínez Vega
   Luis Javier Olivares Lara
   José de Jesús Jaramillo Aguilera
   Daniel Hipólito Galindo Hernández

   Parte de la librería para el análisis sintáctico de 
   expresiones aritméticas: implementación del lexer.
*/
#include <cctype>
#include <string>
#include <iterator>
#include "lexer.hpp"

using std::string;
using std::size;

Lexer::Lexer(char *text){
  setText(text);
}

void Lexer::setText(char *text){
  this->text = text;
  current_char = text; // Se inicializa el puntero al inicio del texto.
}

char *Lexer::createNumber(){
  char *number = {new char[STR_MAX_LEN]}, *ptr;
  size_t i = 0;
  ptr = number;
  
  while(isdigit(*current_char))
  {
    if(i > (STR_MAX_LEN - 1))
    {
      delete [] number;
      throw MaxIntSize("Alcanzado máximo número de carácteres en un entero.");
    }
    
    *ptr = *current_char;
    ++current_char;
    ++ptr;
    ++i;
  }

  return number;
}

Token Lexer::nextToken(){
  Token next_token;

  if(*current_char == '\0')
  {
    next_token = {nil, NULL};
    current_char = text; // Regresamos el puntero al principio.

    return next_token;
  }
  
  if(isdigit(*current_char))
  {
    next_token = {number, createNumber()};

    return next_token;
  }
  
  switch(*current_char)
  {
  case '(':
    next_token = {left_parens, NULL};
    break;
  case ')':
    next_token = {right_parens, NULL};
    break;
  case '+':
    next_token = {sum, NULL};
    break;
  case '-':
    next_token = {substraction, NULL};
    break;
  case '*':
    next_token = {multiplication, NULL};
    break;
  case '/':
    next_token = {division, NULL};
    break;
  default:
    throw LexerException("Carácter inválido.");
  }
  
  ++current_char;

  return next_token;
}

LexerException::LexerException(const string error_msg)
  : error{error_msg} {}

string LexerException::getError() const {
  return error;
}

MaxIntSize::MaxIntSize(const string error_msg)
  : error{error_msg} {}

string MaxIntSize::getError() const {
  return error;
}
