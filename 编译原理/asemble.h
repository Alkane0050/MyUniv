#pragma once
#ifndef ASEMBLE_H
#define ASEMBLE_H
#include"LL.h"
#include<string>
using namespace std;

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
	temp.append("\n\t lw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("H\n\tadd $t3 , $t1,$t2");
	temp.append("\n\tsw $t3 ,");
	temp.append(to_string(idSheet[indx3].adress));
	temp.append("H\n\tpopl\n\t");
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
	temp.append("H\n\t addi ");
	temp.append(to_string(imm));
	temp.append(", $t1,$t2");
	temp.append("\n\t sw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("H\n\tpopl\n\t");
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
	temp.append("H\n\tlw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("\n\tsubw $t3 , $t1,$t2");
	temp.append("\n\t sw $t3, ");
	temp.append(to_string(idSheet[indx3].adress));
	temp.append("H\n\tpopl\n\t");
	return temp;
}
//id2<- id1-imm
//���������ļ���
string asm_sum(int imm,string id1,string id2) {
	int indx1 = -1, indx2 = -1;
	for (int i = 0; i < idSheet.size(); i++) {
		if (idSheet[i].name == id1)indx1 = i;
		if (idSheet[i].name == id2)indx2 = i;
	}
	if (indx1 < 0 || indx2 < 0) {
		error("�������δ�ҵ���ʶ��!");
		return "ERROR";
	}
	imm = -imm; //MIPS ��û��subi��ֻ��Ҫ�ı��������ķ��žͿ�����
	string temp = "\n\t";
	temp.append("pushl\n\t");
	temp.append("lw $t1,");
	temp.append(to_string(idSheet[indx1].adress));
	temp.append("H\n\t addi ");
	temp.append(to_string(imm));
	temp.append(", $t1,$t2");
	temp.append("\n\t sw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("H\n\tpopl\n\t");
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
	temp.append("H\n\t lw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("H\n\t mult $t1,$t2");
	temp.append("\n\t mflo $t1\n\t");
	temp.append("sw $t1, ");
	temp.append(to_string(idSheet[indx3].adress));
	temp.append("H\n\tpopl\n\t");
	return temp;
}
string asm_mul(int imm,string id1,string id2){
	return "ERROR";
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
	temp.append("H\n\t lw $t2,");
	temp.append(to_string(idSheet[indx2].adress));
	temp.append("\n\t div $t1,$t2");
	temp.append("\n\t mflo $t1\n\t");
	temp.append("sw $t1,");
	temp.append(to_string(idSheet[indx3].adress));
	temp.append("H\n\tpopl\n\t");
	return temp;
}
#endif // !ASEMBLE_H

