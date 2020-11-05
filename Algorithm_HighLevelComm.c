HAL_Delay(1000);
setSteering(servoPWM, 0.0);
HAL_Delay(1000);
setSteering(servoPWM, 10.0);
HAL_Delay(1000);
setSteering(servoPWM, 20.0);
HAL_Delay(1000);
setSteering(servoPWM, 30.0);
//HighLevelCommTest.ParseMessage();
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
