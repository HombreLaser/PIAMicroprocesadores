/* MICROPROCESADORES - PROYECTO INTEGRADOR DE APRENDIZAJE. 
   Luis Sebastián Martínez Vega
   Luis Javier Olivares Lara
   José de Jesús Jaramillo Aguilera
   Daniel Hipólito Galindo Hernández

   Parte de la librería para el análisis sintáctico de 
   expresiones aritméticas: el lexer.
*/
#include <cstddef>
#include <string>
#include <string_view>
#ifndef LEXER_H
#define LEXER_H

constexpr size_t STR_MAX_LEN = 11;

using std::string;

enum token_type{
  number,
  sum,
  substraction,
  multiplication,
  division,
  left_parens,
  right_parens,
  nil, // Para indicar fin de la cadena.
};

struct Token{
  token_type type {};
  char *value {};
};

class Lexer{
private:
  char *text;
  char *current_pos; // Carácter actual del texto a escanear.
  char *createNumber();
public:
  Lexer(char *text);
  void setText(char *text);
  Token nextToken();
};

class LexerException{
private:
  string error;
public:
  LexerException(const string error_msg);
  string getError() const;
};

class MaxIntSize {
private:
string error;
public:
  MaxIntSize(const string error_msg);
  string getError() const;
};
#endif /* LEXER_H */
