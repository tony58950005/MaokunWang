import serial
import array
import time
import re

distance_threshold=10
distanceL=None
distanceM=None
distanceR=None
#x=1
receivedData='\0'
serialport =serial.Serial("/dev/serial0", baudrate=115200, timeout=3.0)

print(serialport)
if serialport.isOpen():
    print("open success")
else:
    print("open failed")

def str_to_int(input_str):
    output_int=0
    if(input_str[0]=='-'):
        start_idx=1
        is_negative=True
    else:
        start_idx=0
        is_negative=False
    for i in range(start_idx, len(input_str)):
        place=10**(len(input_str)-(i+1))
        digit=ord(input_str[i])-ord('0')
        output_int+=place*digit
    if is_negative:
        return -1*output_int
    else:
        return output_int

def ErrorHandler():
    global receivedData
    if receivedData != "OK\r\n":
        Stop()
       


def ObstacleDetection():
    serialport.write("Distance\r\n")
    strings=serialport.readline()
    print(strings)
    distance=re.split(':',strings)
    print(distance)
    print("The distance values are %s,%s,%s") %(distance[0],distance[1],distance[2])
    global distanceL, distanceM, distanceR
    distanceL=str_to_int(distance[2])
    distanceM=str_to_int(distance[1])
    distanceR=str_to_int(distance[0])
#    distanceL=int(distance[0])
#    distanceM=int(distance[1])
#    distanceR=int(distance[2])
    if(distanceL>distance_threshold and distanceM>distance_threshold and distanceR>distance_threshold):
        return 0
    else:
        return 1
    
def Stop():
    global receivedData
    serialport.write("Stop\r\n")
    receivedData=serialport.readline()
    ErrorHandler()
    print("Response to Stop: %s" %(receivedData))
	#TODO: check the response. It is okay, when you receive back OK. Otherwise, call an error handle, in which you stop the car.


def Move(x):
    global receivedData
    serialport.write("Move\r\n,%d") %(x) 
    receivedData=serialport.readline()
    print("Response to Move: %s") %(receivedData)
#    time.sleep(200)
    ErrorHandler()
	#TODO: check the response. It is okay, when you receive back OK. Otherwise, call an error handle, in which you stop the car.

def Turn(x):
    global receivedData
    serialport.write("Turn\r\n,%d") %(x)
    receivedData=serialport.readline()
    print("Response to Turn: %s") %(receivedData)
#    time.sleep(100)
    ErrorHandler()
	#TODO: check the response. It is okay, when you receive back OK. Otherwise, call an error handle, in which you stop the car.

#Delay unit is second(s)
def Delay(x):
    global receivedData
    serialport.write("Delay\r\n,%d") %(x*1000)
    receivedData=serialport.readline()
    print("Response to Delay:%s") %(receivedData)
    ErrorHandler()

#Simple algorithm: if meet obstacle ->move back ->Detect&Turn
def ObstacleAvoid1():
    global distanceL, distanceM, distanceR
    returnValue=ObstacleDetection()
#    print("returnValue=%d") %(returnValue)
    if(returnValue==1):
        print("We want to stop.")
        Stop()
        print("We want to move backward.")
        Move(-10)
        Delay(1)
        Stop()
        print("distances are %d,%d,%d") %(distanceL,distanceM,distanceR)
        if(distanceL<distanceR):
            print("We want to move right.")
            Turn(45)
        else:
            print("We want to move left")
            Turn(-45)
    else:
        print("We want to move forward.")
        Move(10)

#Handle 8 cases
def ObstacleAvoid2():
    global distanceL, distanceM, distanceR
    returnValue=ObstacleDetection()
    print("distances={%d,%d,%d}") %(distanceL,distanceM,distanceR)
    print("threshold=%d") %(distance_threshold)
    if distanceL>distance_threshold and distanceM>distance_threshold and distanceR>distance_threshold:
        Move(10)
        print("No obstacle;Move forward.")
    elif distanceL>distance_threshold and distanceM<=distance_threshold and distanceR>distance_threshold:
        Stop()
        Turn(-45)
        print("Have obstacles on the middle,right;Move left")
    elif distanceL>distance_threshold and distanceM>distance_threshold and distanceR<=distance_threshold:
        Stop()
        Turn(-45)
        print("Have a obstacle on the right;Move left")
    elif distanceL<=distance_threshold and distanceM>distance_threshold and distanceR>distance_threshold:
        Stop()
        Turn(45)
        print("Have a obstacle on the left;Move right")
    elif distanceL>distance_threshold and distanceM<=distance_threshold and distanceR<=distance_threshold:
        Stop()
        Turn(-45)
        print("Have obstacles on the middle,right;Move left")
    elif distanceL<=distance_threshold and distanceM<=distance_threshold and distanceR>distance_threshold:
        Stop()
        Turn(45)
        print("Have obstaclea on the left,middle;Move right")
    elif distanceL<=distance_threshold and distanceM>distance_threshold and distanceR<=distance_threshold:
        Stop()
        Move(5)
        print("Have obstacles on the left,right;Move forward")
    elif distanceL<=distance_threshold and distanceM<=distance_threshold and distanceR<=distance_threshold:
        Stop()
        Move(-10)
        print("Trapped;Stop&BACK")
    else:
        pass

#test
#Turn(30)
#print(ObstacleDetection())
for i in range(3):
#    print(ObstacleDetection())
#    ObstacleAvoid1()
#    Delay(1000)
    ObstacleAvoid2()

serialport.close()



