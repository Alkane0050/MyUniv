#pragma once
#ifndef LL_H
#define LL_H
#include"GetWord.h"
#include<string>
#include<vector>
#include<stack>
using namespace std;

//	��e��������ַ�/epsion

//ö�ٿ��ܳ��ֵ��﷨����
enum errorType {
	variableDiscribeError,
	fenhaoError,
	kuohaoError,
	keyWordError,
	assumeError,
	ifError,
	whileError,
	otherError,
	identifiError,
};
string errorString[] = {
	"����˵������,Ӧ����int��",
	"ȱ��;",
	"���Ų�ȫ!",
	"�ؼ��ʴ���!",
	"������ȷ�ĸ�ֵ���!",
	"ȱ��else!",
	"ȱ��do!",
	"�����;!",//otherError
	"δ����ı�ʶ��"
};
vector<identsheetTemplate> idSheet;
bool canDefineId = false;
bool hasError = false;
long long int addnow = 0x0000;
long long int countId = 0;
void error() {	
	hasError = true;
	cout << "Error!" << endl;
	cout << nowline << "^" << word << "\t At row: " << row << endl;
}
void error(string e) {
	hasError = true;
	cout << "Error:" << e << endl;
	cout << nowline << "^" << word << "\t At row: " << row << endl;
}
stack<string>rgister;
string to_register(int i) {
	return string("r") + to_string(i);
}
//��ʼ���Ĵ������ڵ�ջ
void rgisterInit() {
	for (int i = 35; i>=0; --i) {
		rgister.push(to_register(i));
	}
}
// ��ջ�л��һ���Ĵ���
//�����ʱ��ջ�Ѿ���,�򷵻ء�\0��
string getRgister() {
	string res = "\0";
	if (!rgister.empty()) {//���ջ����
		res = rgister.top();
		rgister.pop();
	}
	return res;
}

//������ļĴ����ͻ�ջ��
void giveBackRgister(string str) {
	rgister.push(str);
}

//����һ�����ڴ�ű��ʽ�����õ��Ľṹ��
struct expressBean {
	string code;//��Ŵ���
	string place;//��ŵ�ַ,�п����ǼĴ���,Ҳ�п����Ǵ洢��ַ
};

//�ӱ�ʶ���ı����ҵ���ʶ���ĵ�ַ
unsigned int getAddress(string id) {
	int indx = -1;
	for (int i = 0; i < idSheet.size(); ++i) {
		if (id == idSheet[i].name) {
			indx = idSheet[i].adress;
			break;
		}
	}
	return indx;
}

//���忪ʼ

// <����> ::= main(){<������>}
string program(ifstream& fread);
// <������> ::=<����˵������> ; <��䲿��>
string mainFunction(ifstream& fread);
// <����˵������> ::= <����˵��> <��ʶ����>
void variableDiscribePart(ifstream& fread);
// <����˵��> ::= int
void variableDiscribe(ifstream& fread);
// <��ʶ����> ::= <��ʶ��><��ʶ����1>
void identSheet(ifstream& fread);
//<��ʶ����1> ::= , <��ʶ��><��ʶ����1> | e
void identSheet1(ifstream& fread);
//<��ʶ��> ͨ��getword���ж�
string identity(ifstream& fread);
//<��䲿��> ::= <���><��䲿��1>
string sentencePart(ifstream& fread);
//<��䲿��1> ::= ;<���><��䲿��1> | e 
string sentencePart1(ifstream& fread);
//<���> ::=<��ֵ���> | <�������> | <ѭ�����>
string sentence(ifstream& fread);
//<��ֵ���> ::=<��ʶ��> = <���ʽ>
string assumeSentence(ifstream& fread);
//<����> ::= <���ʽ><��ϵ�����><���ʽ>
string condition(ifstream& fread); //TODO
//<��ϵ�����> ͨ��getword���õ�
string relationOp(ifstream &fread);
// <���ʽ> ::=<��><���ʽ1>
expressBean expression(ifstream& fread);
//<���ʽ1> ::= <�ӷ������><��><���ʽ1> | e
expressBean expression1(ifstream& fread, string &place);
//<�ӷ������> ��getword�õ�
void plusOp(ifstream& fread);
//<��> ::= <����><��1>
expressBean term(ifstream& fread);
//<��1> ::=<�˷������><����><��1> | e
expressBean term1(ifstream& fread, string &place);
//<�˷������> ��getword�õ�
void multiOp(ifstream& fread);
// <����> ::= <��ʶ��>|<����>|(<���ʽ>)
expressBean factor(ifstream& fread);
//<����> ��getword�õ�
string constVal(ifstream& fread);
// <�������> ::= {<��䲿��>}
string complexSentence(ifstream& fread);
// <���1> ::= <���>|<�������>
string sentence1(ifstream& fread);
// <�������> ::= if(<����>) <���1> else <���1>
string conditionSentence(ifstream& fread);
// <ѭ�����> ::= while(<����>)do<���1>
string loopSentence(ifstream& fread);

//�������
//
//
//
inline string program(ifstream& fread) {
	string code;
	rgisterInit();
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
					code = mainFunction(fread);  //�����Ŀ�����͵�����������Ŀ�����
					//���������з��ص�ʱ���Ѿ�ȡ������һ��������
					if (word == "}") {
						cout << "��Լ��<����>" << endl;
						getword(fread);
						return code;
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
	return "����Ŀ�����ʧ��";
}

inline string mainFunction(ifstream& fread) {
	string code;
	cout << "��ʼ��Լ<������>" << endl;
	canDefineId = true;
	variableDiscribePart(fread); //�������ĵ�һ����,��������(��Ŀ������в�����)
	canDefineId = false;
	if (word == ";") {
		getword(fread);
		code = sentencePart(fread);//��������Ŀ�������൱����䲿�ֵ�Ŀ�����
		cout << "��Լ��<������>" << endl;
		return code;
	}
	else {
		error(errorString[fenhaoError]);
		return "Error:������Ŀ���������ʧ��\n";
	}
}

inline void variableDiscribePart(ifstream& fread) {
	cout << "��ʼ��Լ<����˵������>" << endl;
	variableDiscribe(fread);
	if (hasError != true) {
		identSheet(fread);
	}
	else {//���ԴӴ����лָ�����������������
		while (word != ";" && word != "}" && !fread.eof()) {
			getword(fread);
		}
		hasError = false;//���ǵðѱ�־�ָ������ں����Ĳ��
	}
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
	string id =identity(fread);
	identSheet1(fread);
	cout << "��Լ��<��ʶ����>" << endl;
}

inline void identSheet1(ifstream& fread) {
	cout << "��ʼ��Լ<��ʶ����1>" << endl;
	if (word == ",") {
		getword(fread);
		string id =identity(fread);
		identSheet1(fread);
		cout << "��Լ��<��ʶ����1>" << endl;
	}
	else cout << "��Լ��<��ʶ����1>" << endl;
}

inline string identity(ifstream& fread) {//���ر�ʶ����id,���ڸ�ֵ�������
	string id = "";
	cout << "��ʼ��Լ<��ʶ��>" << endl;
	//��ǰ��ȡ�ĵ��ʵ�����Ϊ��ʶ��
	if (sym == ident) {
		id = word;
		if (canDefineId == true) {//���Զ����ʶ��
			identsheetTemplate temp(word,countId++, addnow+=2);
			idSheet.push_back(temp);
		}
		else {//��ʱ���ܶ����ʶ��
			bool flag = 0;
			for (int i = 0; i < idSheet.size(); i++) {
				if (idSheet[i].name == word)
					flag = 1;
			}
			if(flag!=1)
				error(errorString[identifiError]);
		}
		getword(fread);
		cout << "��Լ��<��ʶ��>" << endl;
		return id;
	}
	else error();
}

inline string sentencePart(ifstream& fread)
{
	string code;
	cout << "��ʼ��Լ<��䲿��>" << endl;
	code += sentence(fread);//<��䲿��>�ĵ�һ����<���>
	code += sentencePart1(fread);//<��䲿��>�ĵڶ�����<��䲿��1>
	cout << "��Լ��<��䲿��>" << endl;
	return code;
}

inline string sentencePart1(ifstream& fread)
{
	string code = "";
	cout << "��ʼ��Լ<��䲿��1>" << endl;
	if (word == ";") {
		getword(fread);
		code += sentence(fread); //<��䲿��1>�ĵ�һ����<���>
		code += sentencePart1(fread);//<��䲿��1>�ĵڶ�����<��䲿��1>
		cout << "��Լ��<��䲿��1>" << endl;
	}
	else if (word != "}") {
		error(errorString[fenhaoError]);
	}
	else cout << "��Լ��<��䲿��1>" << endl;
	return code;
}

inline string sentence(ifstream& fread)
{
	string code = "";
	cout << "��ʼ��Լ<���>" << endl;
	//FIRST(��ֵ���)={<��ʶ��>}	FIRST(�������)={'if'}	FIRST(ѭ�����)={'while'}
	if (sym==ident) {
		code += assumeSentence(fread);//<���>Ϊ<��ֵ���>
		cout << "��Լ��<���>" << endl;
	}
	else if (word == "if") {
		code += conditionSentence(fread);//<���>Ϊ<�������>
		cout << "��Լ��<���>" << endl;
	}
	else if (word == "while") {
		code += loopSentence(fread);//<���>Ϊ<ѭ�����>
		cout << "��Լ��<���>" << endl;
	}
	else error();
	if (hasError == true) {
		while (word != ";" && word != "}" && !fread.eof()) {//�����Ų����ֱ�������ֺţ���ֵ��������������������
			getword(fread);
		}
		hasError = false;
	}
	return code;
}

inline string assumeSentence(ifstream& fread)
{
	string code = "";
	expressBean bean;
	cout << "��ʼ��Լ<��ֵ���>" << endl;
	string id  = identity(fread);
	if (word == "=") {
		getword(fread);
		bean = expression(fread); 
		code += bean.code;//���Ƚ����ʽ�Ĵ��븳ֵ��code
		unsigned int address = getAddress(id);//��ñ�ʶ���ĵ�ַ
		code += "\tsw "+id+","+bean.place+"\n";//�����ʽ�ĵ�ַ�е�ֵ������ʶ��
		cout << "��Լ��<��ֵ���>" << endl;
		giveBackRgister(bean.place); // �ͷżĴ���
	}
	else { 
		error(errorString[assumeError]); 
	}
	return code;
}

inline string condition(ifstream& fread)
{
	expressBean bean, bean1;
	string op;
	string code;
	cout << "��ʼ��Լ<����>" << endl;
	bean = expression(fread);
	op = relationOp(fread);
	bean1 = expression(fread);
	code += bean.code;
	code += bean1.code;
	code += "\tJ" + op + "," + bean.place + "," + bean1.place + "\n";
	cout << "��Լ��<����>" << endl;
	return code;
}

inline string relationOp(ifstream &fread)
{
	string op;
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
		op = word;
		getword(fread);
		cout << "��Լ��<��ϵ�����>" << endl;
	}
	else error();
	return op;
}

inline expressBean expression(ifstream& fread)
{
	expressBean bean,bean1, ans; // bean ��������<��>�ķ���ֵ ,bean1 ��������<���ʽ1>�ķ���ֵ
	cout << "��ʼ��Լ<���ʽ>" << endl;
	bean = term(fread);
	bean1 = expression1(fread,bean.place);
	ans.code += bean.code;
	ans.code += bean1.code;
	ans.place = bean.place;	//��صĵ�ַΪ<��>�ĵ�ַ
	cout << "��Լ��<���ʽ>" << endl;
	return ans;
}

inline expressBean expression1(ifstream& fread, string &place)
{
	expressBean bean, bean1, ans;
	cout << "��ʼ��Լ<���ʽ1>" << endl;
	if (sym == pls || sym == mins) {
		int sym1 = sym;
		plusOp(fread);
		bean = term(fread);
		ans.code += bean.code;
		if (sym1 == pls)
			ans.code += "\taddw " + place + "," + bean.place + "," + place + "\n";
		else if (sym1 == mins)
			ans.code += "\tminw " + place + "," + bean.place + "," + place + "\n";
		bean1 = expression1(fread,place);
		ans.code += bean1.code;
		ans.place = place;
	}
	cout << "��Լ��<���ʽ1>" << endl;
	return ans;
}

inline void plusOp(ifstream& fread)
{
	if (sym == pls || sym == mins) {
		getword(fread);
	}
	else error();
}

inline expressBean term(ifstream& fread)
{
	expressBean bean, bean1, ans;
	cout << "��ʼ��Լ<��>" << endl;
	bean = factor(fread);
	bean1 = term1(fread, bean.place);
	ans.code += bean.code;
	ans.code += bean1.code;
	ans.place = bean.place;
	cout << "��Լ��<��>" << endl;
	return ans;
}

inline expressBean term1(ifstream& fread, string &place)
{
	expressBean bean, bean1, ans;
	cout << "��ʼ��Լ<��1>" << endl;
	if (sym == times || sym == divide) {
		int sym1 = sym;
		multiOp(fread);
		bean = factor(fread);
		ans.code += bean.code;
		if (sym1 == times)
			ans.code += "\tmul " + place + "," + bean.place + "," + place + "\n";
		else if (sym1 == divide) 
			ans.code += "\tdiv " + place + "," + bean.place + "," + place + "\n";
		bean1 = term1(fread, place);
		ans.code += bean1.code;
		ans.place = place;
	}
	cout << "��Լ��<��1>" << endl;
	return ans;
}

inline void multiOp(ifstream& fread)
{
	if (sym == times || sym == divide) {
		getword(fread);
	}
	else error();
}

inline expressBean factor(ifstream& fread)
{
	expressBean bean, ans;
	cout << "��ʼ��Լ<����>" << endl;
	if (sym == ident) {
		string id = identity(fread);
		string rigster = getRgister();
		ans.code += "\tlw " +id + "," + rigster + "\n";
		ans.place = rigster;
		cout << "��Լ��<����>" << endl;
	}
	else if (sym == number) {
		string val = constVal(fread);
		string rigster = getRgister();
		ans.code += "\taddi " + val + ",$zero," + rigster + "\n";
		ans.place = rigster;
	}
	else if (word == "(") {
		getword(fread);
		bean = expression(fread);
		if (word == ")") {
			ans.code = bean.code;
			ans.place = bean.place;
			getword(fread);
			cout << "��Լ��<����>" << endl;
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[assumeError]);
	return ans;
}

inline string constVal(ifstream& fread)
{
	string val;
	if (sym == number) {
		val = word;
		getword(fread);
		cout << "��Լ��<����>" << endl;
	}
	else error();
	return val;
}

inline string complexSentence(ifstream& fread)
{
	string code;
	if (word == "{") {
		getword(fread);
		code = sentencePart(fread);
		if (word == "}") {
			getword(fread);
			cout << "��Լ��<�������>" << endl;
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[kuohaoError]);
	return code;
}

inline string sentence1(ifstream& fread)
{
	string code;
	if (word == "{") {
		code = complexSentence(fread);
	}
	else {
		code = sentence(fread);
	}
	cout << "��Լ�� <���1>" << endl;
	return code;
}

inline string conditionSentence(ifstream& fread)
{
	string code;
	string con;
	string sen, sen1;
	if (word == "if") {
		getword(fread);
		if (word == "(") {
			getword(fread);
			con = condition(fread);
			if (word == ")") {
				getword(fread);
				sen = sentence1(fread);
				if (word == "else") {
					getword(fread);
					sen1 = sentence1(fread);
					code += con;
					code += "\tJNZ A" + to_string(row) + "\n";
					code += sen1;
					code += "\tJMP QUIT" + to_string(row) + "\n";
					code += "A" + to_string(row) + " :\n" + sen;
					code += "QUIT" + to_string(row) + ":\n";
					cout << "��Լ��<�������>" << endl;
				}
				else if (word == ";") { 
					error(errorString[otherError]);
				}
				else error(errorString[ifError]);
			}
			else error(errorString[kuohaoError]);
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[keyWordError]);
	return code;
}

inline string loopSentence(ifstream& fread)
{
	string code, con, sen;
	if (word == "while") {
		getword(fread);
		if (word == "(") {
			getword(fread);
			con = condition(fread);
			if (word == ")") {
				getword(fread);
				if (word == "do") {
					getword(fread);
					sen = sentence1(fread);
					code += "IN" + to_string(row) + ":\n";
					code += con;
					code += "\tJNZ QUIT" + to_string(row) + "\n";
					code += sen;
					code += "\tJMP IN" + to_string(row) + "\n";
					code += "QUIT" + to_string(row) + ":\n";
					cout << "��Լ��<ѭ�����>" << endl;
				}
				else error(errorString[whileError]);
			}
			else error(errorString[kuohaoError]);
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[keyWordError]);
	return code;
}


#endif