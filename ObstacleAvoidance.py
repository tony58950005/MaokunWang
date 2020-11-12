#g++ -o main.so -shared -fPIC main.cpp
#python ObstacleAvoidance.py
import serial
import ctypes
so=ctypes.cdll.LoadLibrary
lib=so("./main.so")
print 'obstacleDetection(adc)'
state=lib.obstacleDetection(adc)
#from main.cpp import obstacleDetction

distanceL=lib.getDistanceL()
distanceM=lib.getDistanceM()
distanceR=lib.getDistanceR()
serialport =serial.Serial("COM1", baudrate=115200, timeout=3.0)
serialport.open()
print(serialport)
if serialport.isOpen():
    print("open success")
else:
    print("open failed")

#Simple algorithm: if meet obstacle ->move back ->Detect&Turn
def ObstacleAvoid1():
    if(state):
        serialport.write("Stop\n")
        #print(serialport.readline())
        serialport.write("Move\n,-10")
        #print(serialport.readline())
        serialport.write("Stop\n")
        #print(serialport.readline())
        if():
            serialport.write("Turn\n,45")
            #print(serialport.readline())
            serialport.write("Stop\n")
            #print(serialport.readline())
        else:
            serialport.write("Turn\n,-45")
            #print(serialport.readline())
            serialport.write("Stop\n")
            #print(serialport.readline())
    else:
        serialport.write("Move\n,10")
        #print(serialport.readline())

#Handle 8 cases
def ObstacleAvoid2():
    if distanceL>10 & distanceM>10 & distanceR>10:
        serialport.write("Move\n,10")
    elif distanceL>10 & distanceM<=10 & distanceR>10:
        serialport.write("Stop\n")
        serialport.write("Turn\n,-45")
    elif distanceL>10 & distanceM>10 & distanceR<=10:
        serialport.write("Stop\n")
        serialport.write("Turn\n,-45")
    elif distanceL<=10 & distanceM>10 & distanceR>10:
        serialport.write("Stop\n")
        serialport.write("Turn\n,45")
    elif distanceL>10 & distanceM<=10 & distanceR<=10:
        serialport.write("Stop\n")
        serialport.write("Turn\n,-45")
    elif distanceL<=10 & distanceM<=10 & distanceR>10:
        serialport.write("Stop\n")
        serialport.write("Turn\n,45")
    elif distanceL<=10 & distanceM>10 & distanceR<=10:
        serialport.write("Stop\n")
        serialport.write("Move\n,45")
    elif distanceL<=10 & distanceM<=10 & distanceR<=10:
        serialport.write("Stop\n")
        serialport.write("Stop\n")
    else:
        pass

#test
ObstacleAvoid1()
#ObstacleAvoid2()

serialport.close()



