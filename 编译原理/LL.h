#pragma once
#include"GetWord.h"
#include<string>
using namespace std;
/*
	��e��������ַ�/epsion
*/


// <����> ::= main(){<������>}
void program() {

}

// <������> ::=<����˵������> ; <��䲿��>
void mainFunction() {

}

// <����˵������> ::= <����˵��> <��ʶ����>
void variableDiscribePart() {

}

// <����˵��> ::= int
void variableDiscribe() {

}

// <��ʶ����> ::= <��ʶ��><��ʶ����1>
void identSheet() {

}

//<��ʶ����1> ::= , <��ʶ��><��ʶ����1> | e
void identSheet1() {

}

//<��䲿��> ::= <���><��䲿��1>
void sentencePart() {

}

//<��䲿��1> ::= ;<���><��䲿��1> | e 
void sentencePart1() {

}

//<���> ::=<��ֵ���> | <�������> | <ѭ�����>
void sentence() {

}

//<��ֵ���> ::=<��ʶ��> = <���ʽ>
void assumeSentence() {

}

//<����> ::= <���ʽ><��ϵ�����><���ʽ>
void condition() {

}

// <���ʽ> ::=<��><���ʽ1>
void expression() {

}

//<���ʽ1> ::= <�ӷ������><��><���ʽ1> | e
void expression1() {

}

//<��> ::= <����><��1>
void term() {

}

//<��1> ::=<�˷������><����><��1> | e
void term1() {

}

// <����> ::= <��ʶ��>|<����>|(<���ʽ>)
void factor() {

}

// <�������> ::= {<��䲿��>}
void complexSentence() {

}

// <���1> ::= <���>|<�������>
void sentence1() {

}

// <�������> ::= if(<����>) <���1> else <���1>
void conditionSentence() {

}

// <ѭ�����> ::= while(<����>)do<���1>
void loopSentence() {

}