/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COMMA = 258,
    DVOTACKA = 259,
    PERCENT = 260,
    DOLLAR = 261,
    EOL = 262,
    PLUS = 263,
    STAR = 264,
    L_BRACKET = 265,
    R_BRACKET = 266,
    HEX_NUMBER = 267,
    NUMBER = 268,
    GLOBAL = 269,
    EXTERN = 270,
    SECTION = 271,
    WORD = 272,
    SKIP = 273,
    EQU = 274,
    END = 275,
    HALT = 276,
    INT = 277,
    IRET = 278,
    CALL = 279,
    RET = 280,
    JMP = 281,
    JEQ = 282,
    JNE = 283,
    JGT = 284,
    PUSH = 285,
    POP = 286,
    XCHG = 287,
    ADD = 288,
    SUB = 289,
    MUL = 290,
    DIV = 291,
    CMP = 292,
    NOT = 293,
    AND = 294,
    OR = 295,
    XOR = 296,
    TEST = 297,
    SHL = 298,
    SHR = 299,
    LDR = 300,
    STR = 301,
    STACK_POINTER = 302,
    PROGRAM_COUNTER = 303,
    PROGRAM_STATUS_WORD = 304,
    REGISTER = 305,
    SIMBOL = 306
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 11 "parser.y" /* yacc.c:1909  */

    int num;
    char* str;

#line 111 "parser.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
