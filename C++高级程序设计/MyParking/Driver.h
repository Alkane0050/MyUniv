#pragma once
#ifndef DRIVER_H
#define DRIVER_H
#include"Car.h"
#include"Park.h"
class Driver {
private:
	Car car;
public:
	Driver(Car car);
	void parkCar();//����
	string queryEmptyPos();//��ѯ�ճ�λ
	string takeCar();//ȡ��
	void payForPark();//�ɷ�
};

#endif