#g++ -o main.so -shared -fPIC main.cpp
#python ObstacleAvoidance.py
import serial
#import ctypes
#so=ctypes.cdll.LoadLibrary
#lib=so("./main.so")
#print 'obstacleDetection(adc)'
# state=lib.obstacleDetection(adc)
#from main.cpp import obstacleDetction

# distanceL=lib.getDistanceL()
# distanceM=lib.getDistanceM()
# distanceR=lib.getDistanceR()
distance_threshold=10
distanceL=0
distanceM=0
distanceR=0
serialport =serial.Serial("COM1", baudrate=115200, timeout=3.0)
serialport.open()
print(serialport)
if serialport.isOpen():
    print("open success")
else:
    print("open failed")


def ObstacleDetection():
    serialport.write("Distance\n")
    str=print(serialport.readline())
    distance=str.split(str=":")
    new_numbers = []
    for n in numbers:
        new_numbers.append(int(n))
    distance = new_numbers
    distanceL=distance[0]
    distanceM=distance[1]
    distanceR=distance[2]
    for i in range(len(distances)):
        if(distance[i]<distance_threshold):
            return False
    
def Stop():
    serialport.write("Stop\n")
    receivedData=serialport.readline()
    if receivedData != "OK":
        Stop()
    print("Response for Stop: %s" %(receivedData))
	#TODO: check the response. It is okay, when you receive back OK. Otherwise, call an error handle, in which you stop the car.


def Move(x):
    serialport.write("Move\n,x")
    serialport.write("Delay\n,1000")
    receivedData=serialport.readline()
    if receivedData != "OK":
        Stop()
    print("Response for Move: %s" %(receivedData))
	#TODO: check the response. It is okay, when you receive back OK. Otherwise, call an error handle, in which you stop the car.

def Turn(x):
    serialport.write("Turn\n,x")
    serialport.write("Delay\n,1000")
    receivedData=serialport.readline()
    if receivedData != "OK":
        Stop()
    print("Response for Turn: %s" %(receivedData))
	#TODO: check the response. It is okay, when you receive back OK. Otherwise, call an error handle, in which you stop the car.

#Simple algorithm: if meet obstacle ->move back ->Detect&Turn
def ObstacleAvoid1():
    if(ObstacleDetection()):
        Stop()
        Move(-10)
        Stop()
        if(distanceL<distanceR):
            Turn(45)
            Stop()
        else:
            Turn(-45)
            Stop()
    else:
        Move(10)
        

#Handle 8 cases
def ObstacleAvoid2():
    if distanceL>distance_threshold & distanceM>distance_threshold & distanceR>distance_threshold:
        Move(10)
    elif distanceL>distance_threshold & distanceM<=distance_threshold & distanceR>distance_threshold:
        Stop()
        Turn(-45)
    elif distanceL>distance_threshold & distanceM>distance_threshold & distanceR<=distance_threshold:
        Stop())
        Turn(-45)
    elif distanceL<=distance_threshold & distanceM>distance_threshold & distanceR>distance_threshold:
        Stop()
        Turn(45)
    elif distanceL>distance_threshold & distanceM<=distance_threshold & distanceR<=distance_threshold:
        Stop()
        Turn(-45)
    elif distanceL<=distance_threshold & distanceM<=distance_threshold & distanceR>distance_threshold:
        Stop()
        Turn(45)
    elif distanceL<=distance_threshold & distanceM>distance_threshold & distanceR<=distance_threshold:
        Stop()
        Move(45)
    elif distanceL<=distance_threshold & distanceM<=distance_threshold & distanceR<=distance_threshold:
        Stop()
        Stop()
    else:
        pass

#test
ObstacleAvoid1()
#ObstacleAvoid2()

serialport.close()



