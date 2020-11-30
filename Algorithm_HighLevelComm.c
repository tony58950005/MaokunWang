/*HAL_Delay(1000);
setSteering(servoPWM, 0.0);
HAL_Delay(1000);
setSteering(servoPWM, 10.0);
HAL_Delay(1000);
setSteering(servoPWM, 20.0);
HAL_Delay(1000);
setSteering(servoPWM, 30.0);
HighLevelCommTest.ParseMessage();
*/

if(obstacleDetection(adc)){
//Simple algorithm: if meet obstacle ->move back ->Detect&Turn
HighLevelCommTest.Stop();
HAL_Delay(100);
//moveBackward();
HAL_Delay(300);
HighLevelCommTest.Stop();
HAL_Delay(200);
    if(distanceR>=distanceL){
        HighLevelCommTest.Turn(30);//turn right
        HighLevelCommTest.Stop();
    }else{
        HighLevelCommTest.Turn(-30);//turn left
        HighLevelCommTest.Stop();
    }
}else{
    HighLevelCommTest.Move(10);
}

//Simple algorithm: 8 cases with solution based on 3 distance sensors(permutation&combination)
/*	if(distanceL>10 && distanceM>10 && distanceR>10){
        HighLevelCommTest.Move(10);
}else if(distanceL>10 && distanceM<=10 && distanceR>10){
        HighLevelCommTest.Stop();
        HighLevelCommTest.Turn(-30);
}else if(distanceL>10 && distanceM>10 && distanceR<=10){
        HighLevelCommTest.Stop();
        HighLevelCommTest.Turn(-30);
}else if(distanceL<=10 && distanceM>10 && distanceR>10){
        HighLevelCommTest.Stop();
        HighLevelCommTest.Turn(30);
}else if(distanceL>10 && distanceM<=10 && distanceR<=10){
        HighLevelCommTest.Stop();
        HighLevelCommTest.Turn(-30);
}else if(distanceL<=10 && distanceM<=10 && distanceR>10){
        HighLevelCommTest.Stop();
        HighLevelCommTest.Turn(30);
}else if(distanceL<=10 && distanceM>10 && distanceR<=10){
        HighLevelCommTest.Stop();
        HighLevelCommTest.Move(10);
}else if(distanceL<=10 && distanceM<=10 && distanceR<=10){
        HighLevelCommTest.Stop();
}else{

}


snprintf(myTxData_Distance, 20,"%d%c%d%c%d", distanceL,':',distanceM,':',distanceR);

HighLevelComm 
-myTxData_OK[5]: uint8_t
-myTxData_Battery[6]: uint8_t
-myTxData_Distance[6]: uint8_t
-receivedCommand[100]: char
-realNumber: uint8_t
-uart: ClassUart
-pwm: PWM
+HighLevelComm(UART_HandleTypeDef&, TIM_HandleTypeDef&)
+ParseMessage():bool
+Move(int): bool
+Stop():bool
+Turn(int): bool
+showBattery():bool
+showDistance():bool
+isRun: bool


