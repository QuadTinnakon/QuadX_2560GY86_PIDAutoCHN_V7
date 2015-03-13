# QuadX_2560GY86_PIDAutoCHN_V7
หนังสือเขียนโปรแกรมเครื่องบินสี่ใบพัด การเขียนโปรแกรม Quadrotor พื้นฐาน ,การบินอากาศยาน 4 ใบพัด ,โดรน drone  ,โดรนคอร์ดคอปเตอร์ Drone QuadCopter ,อากาศยานไร้คนขับ
# ดูหน้าเวป http://quad3d-tin.lnwshop.com/category/13/quadrotor_develop_auto

![](https://cloud.githubusercontent.com/assets/9403558/5894707/72734434-a53e-11e4-9152-d86ab0c2d0bc.jpg)
![](https://cloud.githubusercontent.com/assets/9403558/5894709/81c26596-a53e-11e4-8eda-188f70940c84.jpg)
![](https://cloud.githubusercontent.com/assets/9403558/5851227/60b83d90-a236-11e4-82c5-efd6538aba85.jpg)

/*
project_QuadX_2560 GY86_PIDAuto_V5 

1. Automatic  Takeoff 

2. Landing

3. GPS Position Hold

by: tinnakon kheowree  

tinnakon_za@hotmail.com

tinnakonza@gmail.com

http://quad3d-tin.lnwshop.com/

https://www.facebook.com/tinnakonza

date: 22-12-2557(2014)  V.1 QuadX_2560 GY86_PIDAuto_V1

date: 28-12-2557(2014)      QuadX_2560 GY86_PIDAuto_V2   ,Write P-PID Controller

date: 28-12-2557(2014)      QuadX_2560 GY86_PIDAuto_V3   ,Ultrasonic and baro ,,Ultrasonic max 0.8 m change to Baro

date: 30-12-2557(2014)      QuadX_2560 GY86_PIDAuto_V4   ,tuning P-PID Controller

date: 31-12-2557(2014)      QuadX_2560 GY86_PIDAuto_V5   ,tuning Altitude Hold , Position Hold

date: 26-01-2558(2015)      QuadX_2560GY86_PIDAutoCHN_V7 ,tuning P-PID Controller, Read Receiver 8 CH

support:  Board 2560  GY86

• Atmega2560
• MPU6050 Gyro Accelerometer //400kHz nois gyro +-0.05 deg/s , acc +-0.04 m/s^2

• MS561101BA Barometer

• HMC5883L Magnetometer //400kHz

• GPS BS-300

• Ultrasonic Sensor Module

• ESC Dargon 30A

• motor sunny 2212 1400kv 

Quad4-X

---------motor---------

int MOTOR_FrontL_PIN = 2;

int MOTOR_FrontR_PIN = 5;

int MOTOR_BackL_PIN = 6;

int MOTOR_BackR_PIN = 3;

----------rx-----------  

//#define THROTTLEPIN                1  //PIN 62 =  PIN A10

//#define ROLLPIN                    2  //PIN 63 =  PIN A8

//#define PITCHPIN                   0  //PIN 64 =  PIN A9

//#define YAWPIN                     3  //PIN 65 =  PIN A11

//#define AUX1PIN                    4  //PIN 66 =  PIN A12

//#define AUX2PIN                    5  //PIN 67 =  PIN A13

//#define AUX3PIN                    6  //PIN 68 =  PIN A14

//#define AUX4PIN                    7  //PIN 69 =  PIN A15
*/
