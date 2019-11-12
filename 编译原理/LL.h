#pragma once
#ifndef LL_H
#define LL_H
#include"GetWord.h"
#include<string>
using namespace std;
/*
	��e��������ַ�/epsion
*/

//ö�ٿ��ܳ��ֵ��﷨����
enum errorType {
	variableDiscribeError,
	fenhaoError,
	kuohaoError,
	keyWordError,
	assumeError,
	ifError,
	whileError,
};
string errorString[] = {
	"����˵������,Ӧ����int��",
	"ȱ��;",
	"���Ų�ȫ!",
	"�ؼ��ʴ���!",
	"������ȷ�ĸ�ֵ���!",
	"ȱ��else!",
	"ȱ��do!",
};
void error() {	
	cout << "Error!" << endl;
	cout << nowline << "^" << word << "\t At row: " << row << endl;
}
void error(string e) {
	cout << "Error:" << e << endl;
	cout << nowline << "^" << word << "\t At row: " << row << endl;
}
//���忪ʼ

// <����> ::= main(){<������>}
void program(ifstream& fread);
// <������> ::=<����˵������> ; <��䲿��>
void mainFunction(ifstream& fread);
// <����˵������> ::= <����˵��> <��ʶ����>
void variableDiscribePart(ifstream& fread);
// <����˵��> ::= int
void variableDiscribe(ifstream& fread);
// <��ʶ����> ::= <��ʶ��><��ʶ����1>
void identSheet(ifstream& fread);
//<��ʶ����1> ::= , <��ʶ��><��ʶ����1> | e
void identSheet1(ifstream& fread);
//<��ʶ��> ͨ��getword���ж�
void identity(ifstream& fread);
//<��䲿��> ::= <���><��䲿��1>
void sentencePart(ifstream& fread);
//<��䲿��1> ::= ;<���><��䲿��1> | e 
void sentencePart1(ifstream& fread);
//<���> ::=<��ֵ���> | <�������> | <ѭ�����>
void sentence(ifstream& fread);
//<��ֵ���> ::=<��ʶ��> = <���ʽ>
void assumeSentence(ifstream& fread);
//<����> ::= <���ʽ><��ϵ�����><���ʽ>
void condition(ifstream& fread);
//<��ϵ�����> ͨ��getword���õ�
void relationOp(ifstream &fread);
// <���ʽ> ::=<��><���ʽ1>
void expression(ifstream& fread);
//<���ʽ1> ::= <�ӷ������><��><���ʽ1> | e
void expression1(ifstream& fread);
//<�ӷ������> ��getword�õ�
void plusOp(ifstream& fread);
//<��> ::= <����><��1>
void term(ifstream& fread);
//<��1> ::=<�˷������><����><��1> | e
void term1(ifstream& fread);
//<�˷������> ��getword�õ�
void multiOp(ifstream& fread);
// <����> ::= <��ʶ��>|<����>|(<���ʽ>)
void factor(ifstream& fread);
//<����> ��getword�õ�
void constVal(ifstream& fread);
// <�������> ::= {<��䲿��>}
void complexSentence(ifstream& fread);
// <���1> ::= <���>|<�������>
void sentence1(ifstream& fread);
// <�������> ::= if(<����>) <���1> else <���1>
void conditionSentence(ifstream& fread);
// <ѭ�����> ::= while(<����>)do<���1>
void loopSentence(ifstream& fread);

//�������
//
//
//
inline void program(ifstream& fread) {
	cout << "��ʼ��Լ<����>" << endl;
	getword(fread);
	if (word == "main") {
		getword(fread);
		if (word == "(") {
			getword(fread);
			if (word == ")") {
				getword(fread);
				if (word == "{") {
					getword(fread);//�ڽ�������������֮ǰ��ȡ��һ������
					mainFunction(fread);
					//���������з��ص�ʱ���Ѿ�ȡ������һ��������
					if (word == "}") {
						cout << "��Լ��<����>" << endl;
						getword(fread);
						return;
					}
					else error(errorString[kuohaoError]);
				}
				else error(errorString[kuohaoError]);
			}
			else error(errorString[kuohaoError]);
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[keyWordError]);
}

inline void mainFunction(ifstream& fread) {
	cout << "��ʼ��Լ<������>" << endl;
	variableDiscribePart(fread);
	if (word == ";") {
		getword(fread);
		sentencePart(fread);
		cout << "��Լ��<������>" << endl;
	}
	else {
		error(errorString[fenhaoError]);
	}
}

inline void variableDiscribePart(ifstream& fread) {
	cout << "��ʼ��Լ<����˵������>" << endl;
	variableDiscribe(fread);
	identSheet(fread);
	cout << "��Լ��<����˵������>" << endl;
}

inline void variableDiscribe(ifstream& fread) {
	cout << "��ʼ��Լ<����˵��>" << endl;
	if (word == "int") {
		getword(fread);
		cout << "��Լ��<����˵��>" << endl;
	}
	else error(errorString[variableDiscribeError]);
}

inline void identSheet(ifstream& fread) {
	cout << "��ʼ��Լ<��ʶ����>" << endl;
	identity(fread);
	identSheet1(fread);
	cout << "��Լ��<��ʶ����>" << endl;
}

inline void identSheet1(ifstream& fread) {
	cout << "��ʼ��Լ<��ʶ����1>" << endl;
	if (word == ",") {
		getword(fread);
		identity(fread);
		identSheet1(fread);
		cout << "��Լ��<��ʶ����1>" << endl;
	}
	else cout << "��Լ��<��ʶ����1>" << endl;
}

inline void identity(ifstream& fread) {
	cout << "��ʼ��Լ<��ʶ��>" << endl;
	//��ǰ��ȡ�ĵ��ʵ�����Ϊ��ʶ��
	if (sym == ident) {
		getword(fread);
		cout << "��Լ��<��ʶ��>" << endl;
		return;
	}
	else error();
}

inline void sentencePart(ifstream& fread)
{
	cout << "��ʼ��Լ<��䲿��>" << endl;
	sentence(fread);
	sentencePart1(fread);
	cout << "��Լ��<��䲿��>" << endl;
}

inline void sentencePart1(ifstream& fread)
{
	cout << "��ʼ��Լ<��䲿��1>" << endl;
	if (word == ";") {
		getword(fread);
		sentence(fread);
		sentencePart1(fread);
		cout << "��Լ��<��䲿��1>" << endl;
	}
	else if (word != "}") {
		error(errorString[fenhaoError]);
	}
	else cout << "��Լ��<��䲿��1>" << endl;
}

inline void sentence(ifstream& fread)
{
	cout << "��ʼ��Լ<���>" << endl;
	//FIRST(��ֵ���)={<��ʶ��>}	FIRST(�������)={'if'}	FIRST(ѭ�����)={'while'}
	if (sym==ident) {
		assumeSentence(fread);
		cout << "��Լ��<���>" << endl;
	}
	else if (word == "if") {
		conditionSentence(fread);
		cout << "��Լ��<���>" << endl;
	}
	else if (word == "while") {
		loopSentence(fread);
		cout << "��Լ��<���>" << endl;
	}
	else error();
}

inline void assumeSentence(ifstream& fread)
{
	cout << "��ʼ��Լ<��ֵ���>" << endl;
	identity(fread);
	if (word == "=") {
		getword(fread);
		expression(fread);
		cout << "��Լ��<��ֵ���>" << endl;
	}
	else error(errorString[assumeError]);
}

inline void condition(ifstream& fread)
{
	cout << "��ʼ��Լ<����>" << endl;
	expression(fread);
	relationOp(fread);
	expression(fread);
	cout << "��Լ��<����>" << endl;
}

inline void relationOp(ifstream &fread)
{
	cout << "��ʼ��Լ<��ϵ�����>" << endl;
	/*
	neq,// !=
	eq,// ==
	leq,// <=
	lt,//<
	geq,// >=
	gt,//>
	*/
	if (sym >= neq && sym <= gt) {
		getword(fread);
		cout << "��Լ��<��ϵ�����>" << endl;
	}
	else error();
}

inline void expression(ifstream& fread)
{
	cout << "��ʼ��Լ<���ʽ>" << endl;
	term(fread);
	expression1(fread);
	cout << "��Լ��<���ʽ>" << endl;
}

inline void expression1(ifstream& fread)
{
	cout << "��ʼ��Լ<���ʽ1>" << endl;
	if (sym == pls || sym == mins) {
		plusOp(fread);
		term(fread);
		expression1(fread);
	}
	cout << "��Լ��<���ʽ1>" << endl;
}

inline void plusOp(ifstream& fread)
{
	if (sym == pls || sym == mins) {
		getword(fread);
	}
	else error();
}

inline void term(ifstream& fread)
{
	cout << "��ʼ��Լ<��>" << endl;
	factor(fread);
	term1(fread);
	cout << "��Լ��<��>" << endl;
}

inline void term1(ifstream& fread)
{
	cout << "��ʼ��Լ<��1>" << endl;
	if (sym == times || sym == divide) {
		multiOp(fread);
		factor(fread);
		term1(fread);
	}
	cout << "��Լ��<��1>" << endl;
}

inline void multiOp(ifstream& fread)
{
	if (sym == times || sym == divide) {
		getword(fread);
	}
	else error();
}

inline void factor(ifstream& fread)
{
	cout << "��ʼ��Լ<����>" << endl;
	if (sym == ident) {
		identity(fread);
		cout << "��Լ��<����>" << endl;
	}
	else if (sym == number) {
		constVal(fread);
	}
	else if (word == "(") {
		getword(fread);
		expression(fread);
		if (word == ")") {
			getword(fread);
			cout << "��Լ��<����>" << endl;
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[kuohaoError]);
}

inline void constVal(ifstream& fread)
{
	if (sym == number) {
		getword(fread);
		cout << "��Լ��<����>" << endl;
	}
	else error();
}

inline void complexSentence(ifstream& fread)
{
	if (word == "{") {
		getword(fread);
		sentencePart(fread);
		if (word == "}") {
			getword(fread);
			cout << "��Լ��<�������>" << endl;
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[kuohaoError]);
}

inline void sentence1(ifstream& fread)
{
	if (word == "{") {
		complexSentence(fread);
	}
	else {
		sentence(fread);
	}
	cout << "��Լ�� <���1>" << endl;
}

inline void conditionSentence(ifstream& fread)
{
	if (word == "if") {
		getword(fread);
		if (word == "(") {
			getword(fread);
			condition(fread);
			if (word == ")") {
				getword(fread);
				sentence1(fread);
				if (word == "else") {
					getword(fread);
					sentence1(fread);
					cout << "��Լ��<�������>" << endl;
				}
				else error(errorString[ifError]);
			}
			else error(errorString[kuohaoError]);
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[keyWordError]);
}

inline void loopSentence(ifstream& fread)
{
	if (word == "while") {
		getword(fread);
		if (word == "(") {
			getword(fread);
			condition(fread);
			if (word == ")") {
				getword(fread);
				if (word == "do") {
					getword(fread);
					sentence1(fread);
					cout << "��Լ��<ѭ�����>" << endl;
				}
				else error(errorString[whileError]);
			}
			else error(errorString[kuohaoError]);
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[keyWordError]);
}


#endif