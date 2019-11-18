#pragma once
#ifndef ASEMBLE_H
#define ASEMBLE_H
#include"LL.h"
#include<string>
using namespace std;


// ��������
/* id3 <- id1 + id2
	�ӷ�����Ļ�����
*/
string asm_add(string id1, string id2, string id3) {
	int indx1=-1, indx2=-1, indx3=-1;
	for (int i = 0; i < idSheet.size(); i++) {
		if (idSheet[i].name == id1)indx1 = i;
		if (idSheet[i].name == id2)indx2 = i;
		if (idSheet[i].name == id3)indx3 = i;
	}
	if (indx1 < 0 || indx2 < 0 || indx3 < 0) {
		error("�������δ�ҵ���ʶ��!");
		return "ERROR";
	}
	string temp = "\n\t";
	temp.append("pushl\n\t");
	temp.append("lw $t1,");
	temp.append(to_string(idSheet[indx1].adress));
	temp.append("\n\tlw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("\n\tadd $t3 , $t1,$t2");
	temp.append("\n\tsw $t3 ,");
	temp.append(to_string(idSheet[indx3].adress));
	temp.append("\n\tpopl\n\t");
	return temp;
}
//id2<-id1+imm
//��������imm�ļӷ�ָ��
string asm_add(int imm,string id1,string id2) {
	int indx1 = -1, indx2 = -1;
	for (int i = 0; i < idSheet.size(); i++) {
		if (idSheet[i].name == id1)indx1 = i;
		if (idSheet[i].name == id2)indx2 = i;
	}
	if (indx1 < 0 || indx2 < 0) {
		error("�������δ�ҵ���ʶ��!");
		return "ERROR";
	}
	string temp = "\n\t";
	temp.append("pushl\n\t");
	temp.append("lw $t1,");
	temp.append(to_string(idSheet[indx1].adress));
	temp.append("\n\taddi ");
	temp.append(to_string(imm));
	temp.append(", $t1,$t2");
	temp.append("\n\tsw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("\n\tpopl\n\t");
	return temp;
}

/* id3<- id1-id2
	��������Ļ�����
*/
string asm_sub(string id1, string id2, string id3) {
	int indx1 = -1, indx2 = -1, indx3 = -1;
	for (int i = 0; i < idSheet.size(); i++) {
		if (idSheet[i].name == id1)indx1 = i;
		if (idSheet[i].name == id2)indx2 = i;
		if (idSheet[i].name == id3)indx3 = i;
	}
	if (indx1 < 0 || indx2 < 0 || indx3 < 0) {
		error("�������δ�ҵ���ʶ��!");
		return "ERROR";
	}
	string temp = "\n\t";
	temp.append("pushl\n\t");
	temp.append("lw $t1,");
	temp.append(to_string(idSheet[indx1].adress));
	temp.append("\n\tlw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("\n\tsubw $t3 , $t1,$t2");
	temp.append("\n\tsw $t3, ");
	temp.append(to_string(idSheet[indx3].adress));
	temp.append("\n\tpopl\n\t");
	return temp;
}
//id2<- imm -id1
//���������ļ���
string asm_sub(int imm, string id1, string id2) {
	int indx1 = -1, indx2 = -1;
	for (int i = 0; i < idSheet.size(); i++) {
		if (idSheet[i].name == id1)indx1 = i;
		if (idSheet[i].name == id2)indx2 = i;
	}
	if (indx1 < 0 || indx2 < 0) {
		error("�������δ�ҵ���ʶ��!");
		return "ERROR";
	}
	string temp = "\n\t";
	temp.append("pushl\n\t");
	temp.append("lw $t1,");
	temp.append(to_string(idSheet[indx1].adress));
	temp.append("\n\tneg $t1,$t1");	//id1 := -id1
	temp.append("\n\taddi ");
	temp.append(to_string(imm));
	temp.append(", $t1,$t2");
	temp.append("\n\tsw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("\n\tpopl\n\t");
	return temp;
}
//id2<- id1 - imm
string asm_sub(string id1, int imm, string id2) {
	int indx1 = -1, indx2 = -1;
	for (int i = 0; i < idSheet.size(); i++) {
		if (idSheet[i].name == id1)indx1 = i;
		if (idSheet[i].name == id2)indx2 = i;
	}
	if (indx1 < 0 || indx2 < 0) {
		error("�������δ�ҵ���ʶ��!");
		return "ERROR";
	}
	imm = -imm; 
	string temp = "\n\t";
	temp.append("pushl\n\t");
	temp.append("lw $t1,");
	temp.append(to_string(idSheet[indx1].adress));
	temp.append("\n\taddi ");
	temp.append(to_string(imm));
	temp.append(", $t1,$t2");
	temp.append("\n\tsw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("\n\tpopl\n\t");
	return temp;
}


/*id3<-id1*id2
  �˷�����Ļ�����
*/
string asm_mul(string id1, string id2, string id3) {
	int indx1 = -1, indx2 = -1, indx3 = -1;
	for (int i = 0; i < idSheet.size(); i++) {
		if (idSheet[i].name == id1)indx1 = i;
		if (idSheet[i].name == id2)indx2 = i;
		if (idSheet[i].name == id3)indx3 = i;
	}
	if (indx1 < 0 || indx2 < 0 || indx3 < 0) {
		error("�������δ�ҵ���ʶ��!");
		return "ERROR";
	}
	string temp = "\n\t";
	temp.append("pushl\n\t");
	temp.append("lw $t1,");
	temp.append(to_string(idSheet[indx1].adress));
	temp.append("\n\t lw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("\n\t mult $t1,$t2");
	temp.append("\n\t mflo $t1\n\t");
	temp.append("sw $t1, ");
	temp.append(to_string(idSheet[indx3].adress));
	temp.append("\n\tpopl\n\t");
	return temp;
}
// id2 <- id1*imm
//���������ĳ˷�
string asm_mul(int imm, string id1, string id2) {
	int indx1 = -1, indx2 = -1;
	for (int i = 0; i < idSheet.size(); i++) {
		if (idSheet[i].name == id1)indx1 = i;
		if (idSheet[i].name == id2)indx2 = i;
	}
	if (indx1 < 0 || indx2 < 0) {
		error("�������δ�ҵ���ʶ��!");
		return "ERROR";
	}
	string temp = "\n\t";
	temp.append("pushl\n\t");
	temp.append("lw $t1,");
	temp.append(to_string(idSheet[indx1].adress));
	temp.append("\n\taddi $t2,$zero,");
	temp.append(to_string(imm));
	temp.append("\n\tmult $t1,$t2");
	temp.append("\n\tmflo $t1\n\t");
	temp.append("sw $t1, ");	
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("\n\tpopl\n\t");
	return temp;
}

/*id3<-id1/id2
  ��������Ļ�����
*/
string asm_div(string id1, string id2, string id3) {
	int indx1 = -1, indx2 = -1, indx3 = -1;
	for (int i = 0; i < idSheet.size(); i++) {
		if (idSheet[i].name == id1)indx1 = i;
		if (idSheet[i].name == id2)indx2 = i;
		if (idSheet[i].name == id3)indx3 = i;
	}
	if (indx1 < 0 || indx2 < 0 || indx3 < 0) {
		error("�������δ�ҵ���ʶ��!");
		return "ERROR";
	}
	string temp = "\n\t";
	temp.append("pushl\n\t");
	temp.append("lw $t1,");
	temp.append(to_string(idSheet[indx1].adress));
	temp.append("\n\tlw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("\n\tdiv $t1,$t2");
	temp.append("\n\tmflo $t1\n\t");
	temp.append("sw $t1,");
	temp.append(to_string(idSheet[indx3].adress));
	temp.append("\n\tpopl\n\t");
	return temp;
}
//id2<- imm/id1
//���������ĳ�������
string asm_div(int imm, string id1, string id2) {
	int indx1 = -1, indx2 = -1;
	for (int i = 0; i < idSheet.size(); i++) {
		if (idSheet[i].name == id1)indx1 = i;
		if (idSheet[i].name == id2)indx2 = i;
	}
	if (indx1 < 0 || indx2 < 0) {
		error("�������δ�ҵ���ʶ��!");
		return "ERROR";
	}
	string temp = "\n\t";
	temp.append("pushl\n\t");
	temp.append("addi $t1,$zero,");
	temp.append(to_string(imm));
	temp.append("\n\tlw $t2,");
	temp.append(to_string(idSheet[indx1].adress));
	temp.append("\n\tdiv $t1,$t2");
	temp.append("\n\tmflo $t1\n\t");
	temp.append("sw $t1,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("\n\tpopl\n\t");
	return temp;
}
//id2<-id1/imm
string asm_div(string id1, int imm, string id2) {
	int indx1 = -1, indx2 = -1;
	for (int i = 0; i < idSheet.size(); i++) {
		if (idSheet[i].name == id1)indx1 = i;
		if (idSheet[i].name == id2)indx2 = i;
	}
	if (indx1 < 0 || indx2 < 0) {
		error("�������δ�ҵ���ʶ��!");
		return "ERROR";
	}
	string temp = "\n\t";
	temp.append("pushl\n\t");
	temp.append("addi $t1,$zero,");
	temp.append(to_string(imm));
	temp.append("\n\tlw $t2,");
	temp.append(to_string(idSheet[indx1].adress));
	temp.append("\n\tdiv $t2,$t1");
	temp.append("\n\tmflo $t1\n\t");
	temp.append("sw $t1,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("\n\tpopl\n\t");
	return temp;
}


// ��ֵ
// id1:=imm
string asm_assume(string id1, int imm) {
	int indx1 = -1;
	for (int i = 0; i < idSheet.size(); i++) {
		if (idSheet[i].name == id1)indx1 = i;
	}
	if (indx1 < 0) {
		return "ERROR!";
	}
	else {
		string temp = "\n\tpushl\n\t";
		temp.append("li $t1,");
		temp.append(to_string(imm));
		temp.append("\n\tsw $t1,");
		temp.append(to_string(idSheet[indx1].adress));
		temp.append("\n\tpopl\n");
		return temp;
	}
}

// �������



//ѭ�����
#endif // !ASEMBLE_H

