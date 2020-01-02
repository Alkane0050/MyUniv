#ifndef POSITION_H
#define POSITION_H
#include<ctime>
#include"Car.h"
class Position{
private:
    Car *car; // �����ͣ��λ�ϵĳ�
    int col,row; //λ��
    string inTime;//�볡ʱ��
    string outTime;//����ʱ��
    int flag;//��־λ����¼�ó�λ����С�͡����͡����Ǵ��ͳ�
    bool valid;
public:
    Position(int col,int row,int flag);
    Position();
    bool isValid();
    void setValid();
    void resetValid();
    void setPos(int col, int row);
    void setInTime(string t);
    string getInTime();
    void setOutTime(string t);
    string getOutTime();
    int getFlag();
};

#endif // POSITION_H
