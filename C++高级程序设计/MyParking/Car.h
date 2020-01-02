#ifndef CAR_H
#define CAR_H
#define CarSizeNum 3
#include<string>
using namespace std;
static string carSize[] = {"С����","С��","�п�","��"};
class Car{
private:
    string plate; // ���ƺ�
    string color;//��ɫ
    string size;//����
public:
    Car(string plate="", string color="red", string size="С����"){
        setPlate(plate);
        setColor(color);
        setSize(size);
    }
    void setPlate(string plate)
    {
        if(plate.size()!=7){ //��Ч�Լ��
            //error()
            this->plate = "��111111";
        }else{
            this->plate = plate;
        }
    }
    string getPlate()
    {
        return this->plate;
    }
    void setColor(string color)
    {
       this->color = color;
    }
    string getColor()
    {
        return this->color;
    }
    void setSize(string size)
    {
        for(int i = 0;i<CarSizeNum;++i){
            if(carSize[i]==size){
                this->size = size;
                return;
            }
        }
        this->size = carSize[0];
    }
    string getSize(){
        return this->size;
    }
};

#endif // CAR_H
