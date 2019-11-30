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
static int totalError = 0;
long long int addnow = 0x0000;
long long int countId = 0;
void error() {	
	hasError = true;
	totalError = totalError + 1;
}
void error(string e) {
	hasError = true;
	totalError = totalError + 1;
	if (ch == -1)return;
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
string tryToCover(ifstream& fread);
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
string condition(ifstream& fread); 
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
						getword(fread);
						if (totalError != 0) {
							error("�������:"+to_string(totalError));
							return "���ɴ���ʧ��";
						}
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
	canDefineId = true;
	variableDiscribePart(fread); //�������ĵ�һ����,��������(��Ŀ������в�����)
	canDefineId = false;
	if (word == ";") {
		getword(fread);
		code = sentencePart(fread);//��������Ŀ�������൱����䲿�ֵ�Ŀ�����
		return code;
	}
	else {
		error(errorString[fenhaoError]);
		while (word != ";" && word != "}" && !fread.eof()) {
			getword(fread);
		}getword(fread);
		code = sentencePart(fread);//��������Ŀ�������൱����䲿�ֵ�Ŀ�����
		return "Error:������Ŀ���������ʧ��\n";
	}
}

inline void variableDiscribePart(ifstream& fread) {
	variableDiscribe(fread);
	if (hasError != true) {
		identSheet(fread);
	}
	else {//���ԴӴ����лָ�����������������
		while (word != ";" && word != "}" && !fread.eof()) {
			getword(fread);
		}
		hasError = false;//���ǵðѱ�־�ָ������ں����Ĳ��
		identSheet(fread);
	}
}

inline void variableDiscribe(ifstream& fread) {
	if (word == "int") {
		getword(fread);
	}
	else error(errorString[variableDiscribeError]);
}

inline void identSheet(ifstream& fread) {
	string id =identity(fread);
	identSheet1(fread);
}

inline void identSheet1(ifstream& fread) {
	if (word == ",") {
		getword(fread);
		identity(fread);
		if (hasError == false)
			identSheet1(fread);
		else {
			error("�����,");
		}
	}
}

inline string identity(ifstream& fread) {//���ر�ʶ����id,���ڸ�ֵ�������
	//��ǰ��ȡ�ĵ��ʵ�����Ϊ��ʶ��
	string id;
	if (sym == ident) {
		id = word;
		if (canDefineId == true) {//���Զ����ʶ��
			for (int i = 0; i < idSheet.size(); i++) {
				if (idSheet[i].name == word) {//�ظ����壡
					error("�ظ������ʶ��!");
					return "ERROR";
				}
			}
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
		return id;
	}
	else { error("�����ʶ������,�˴�ӦΪ��ʶ��"); return id; }
}

inline string sentencePart(ifstream& fread)
{
	string code;
	code += sentence(fread);//<��䲿��>�ĵ�һ����<���>
	code += sentencePart1(fread);//<��䲿��>�ĵڶ�����<��䲿��1>
	return code;
}

inline string sentencePart1(ifstream& fread)
{
	string code = "";
	if (word == ";") {
		getword(fread);
		if (word == "}") {
			error("�����;");
			return code;
		}
		code += sentence(fread); //<��䲿��1>�ĵ�һ����<���>
		code += sentencePart1(fread);//<��䲿��1>�ĵڶ�����<��䲿��1>
	}
	else if (sym == ident || word == "if" || word == "while") {//�������Ĳ���Ӧ����<���>,��ȴȱ�ٷֺŷָ�
		error("ȱ�ٷֺ�");
		code += tryToCover(fread);
	}
	else if (word != "}" && ch != -1) {
		error("�����" + word);
		code += tryToCover(fread);
	}
	return code;
}

inline string sentence(ifstream& fread)
{
	string code = "";
	//FIRST(��ֵ���)={<��ʶ��>}	FIRST(�������)={'if'}	FIRST(ѭ�����)={'while'}
	if (sym == ident) {
		code += assumeSentence(fread);//<���>Ϊ<��ֵ���
	}
	else if (word == "if") {
		code += conditionSentence(fread);//<���>Ϊ<�������>
	}
	else if (word == "while") {
		code += loopSentence(fread);//<���>Ϊ<ѭ�����>
	}
	else error("�����" + (word));
	return code;
}

inline string assumeSentence(ifstream& fread)
{
	string code = "";
	expressBean bean;
	string id  = identity(fread);
	if (word == "=") {
		getword(fread);
		bean = expression(fread); 
		if (hasError == true) {
			code += tryToCover(fread);
			return code;
		}
		code += bean.code;//���Ƚ����ʽ�Ĵ��븳ֵ��code
		unsigned int address = getAddress(id);//��ñ�ʶ���ĵ�ַ
		code += "\tsw "+id+","+bean.place+"\n";//�����ʽ�ĵ�ַ�е�ֵ������ʶ��
		giveBackRgister(bean.place); // �ͷżĴ���
	}
	else { 
		error(errorString[assumeError]); 
		code += tryToCover(fread);
	}
	return code;
}

inline string condition(ifstream& fread)
{
	expressBean bean, bean1;
	string op;
	string code;
	bean = expression(fread);
	op = relationOp(fread);
	bean1 = expression(fread);
	code += bean.code;
	code += bean1.code;
	code += "\tJ" + op + "," + bean.place + "," + bean1.place + "\n";
	return code;
}

inline string relationOp(ifstream &fread)
{
	string op;
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
	}
	else error("ȱ�ٹ�ϵ�����");
	return op;
}

inline expressBean expression(ifstream& fread)
{
	expressBean bean,bean1, ans; // bean ��������<��>�ķ���ֵ ,bean1 ��������<���ʽ1>�ķ���ֵ
	bean = term(fread);
	bean1 = expression1(fread,bean.place);
	ans.code += bean.code;
	ans.code += bean1.code;
	ans.place = bean.place;	//��صĵ�ַΪ<��>�ĵ�ַ
	return ans;
}

inline expressBean expression1(ifstream& fread, string &place)
{
	expressBean bean, bean1, ans;
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
	bean = factor(fread);
	bean1 = term1(fread, bean.place);
	ans.code += bean.code;
	ans.code += bean1.code;
	ans.place = bean.place;
	return ans;
}

inline expressBean term1(ifstream& fread, string &place)
{
	expressBean bean, bean1, ans;
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
	if (sym == ident) {
		string id = identity(fread);
		string rigster = getRgister();
		ans.code += "\tlw " +id + "," + rigster + "\n";
		ans.place = rigster;
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
		}
		else {
			error(errorString[kuohaoError]);
		}
	}
	else error("����ı��ʽ");
	return ans;
}

inline string constVal(ifstream& fread)
{
	string val;
	if (sym == number) {
		val = word;
		getword(fread);
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
			if (hasError == true) {//��������,���Իָ�
				code += tryToCover(fread);
				return code;
			}
			if (word == ")") {
				getword(fread);
				sen = sentence1(fread);
				if (hasError == true) {
					code += tryToCover(fread);
					return code;
				}
				if (word == "else") {
					getword(fread);
					sen1 = sentence1(fread);
					code += con;
					code += "\tJZ A" + to_string(row) + "\n";
					code += sen1;
					code += "\tJMP QUIT" + to_string(row) + "\n";
					code += "A" + to_string(row) + " :\n" + sen;
					code += "QUIT" + to_string(row) + ":\n";
				}
				else { 
					error(errorString[ifError]); 
					//���Իָ�
					code += tryToCover(fread);
				}
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
				}
				else { 
					error(errorString[whileError]);
					//���Իָ�
					code += tryToCover(fread);
				}
			}
			else error(errorString[kuohaoError]);
		}
		else error(errorString[kuohaoError]);
	}
	else error(errorString[keyWordError]);
	return code;
}

//���Իָ�
string tryToCover(ifstream& fread) {
	string code;
	while (word != ";" && word != "}" && !fread.eof()) {
		getword(fread);
	}
	do {
		getword(fread);
	} while ((word == ";" || word == "}"));
	hasError = false;
	if (ch == -1) {
		return code;
	}
	code = sentencePart(fread);
	return code;
}
#endif