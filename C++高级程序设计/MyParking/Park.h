#ifndef PARK_H
#define PARK_H
#include"Position.h"
#define PosRow 3
#define PosCol 3
class Park{
private:
    static Position **p;
    static constexpr double feePerHour=1.0;//ÿСʱ��ͣ������

public:
    Park();
   static string queryEmptyPos(int flag);//��ѯ�ճ�λ�����ذ����ճ�λλ����Ϣ���ַ���
   static Position** initAll(); // ��ʼ����̬��Ա����
    bool parkCar(Car car);//����,���ز����Ƿ�ɹ��Ĳ���ֵ
    string takeCar(Car car);//ȡ��,����ȡ���Ľ��(һ�����ѵ�ʱ��,��ͣ��ʲô�ط�)
    string queryCar(string plate);//��ѯ������Ϣ,����ɹ����س���λ��,��Ȼ����ʧ�ܴ�

};
Position **Park::p = Park::initAll();
#endif // PARK_H
