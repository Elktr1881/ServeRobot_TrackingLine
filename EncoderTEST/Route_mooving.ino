int cnt = 0, mission = 0;
bool prof = false, deliver = false;
unsigned int missionPost;

void GetServiceTable(int table)
{
  unsigned int MissionTime = millis()-missionPost;
  switch(mission)
  {
    case 0 :
      PID(0,0,0,0,0); 
      resetPID();
      if(weightRead() > 200 and !prof){prof = true; missionPost = millis();}
      else if(MissionTime > 2000 and prof and table <= 3){mission = 11;}
      else if(MissionTime > 2000 and prof and table >= 4){mission = 10;}
      break;

    case 10:
      PID(-10,100,0.5,0.001,1);
      if(line[2] or line[3]){mission = 20; resetPID(); }
      break; 

    case 11:
      PID(100,-10,0.5,0.001,1);
      if(line[2] or line[3]){mission = 21; resetPID();}
      break;

    case 20:
       tracking_stright(140,0.8,0.002,1); 
       if(line[5] and line[4] and line[3]){mission = 30; resetPID(); missionPost = millis();}
       break;

   case 21:
       tracking_stright(140,0.8,0.002,1);
       if(line[0] and line[1] and line[2]){mission = 31; resetPID(); missionPost = millis();}
       break;

    case 30:
      PID(100,25,1.5,0.003,0.8); digitalWrite(buz,LOW); prof = false;
      if(!line[5] and !line[4] and line[3]){mission = 40; cnt=0; resetPID();}
      break;

    case 31:
      PID(25,100,1.5,0.003,0.8); digitalWrite(buz,LOW); prof = false;
      if(!line[0] and !line[1] and line[2]){mission = 41; cnt=0; resetPID();}
      break;

    case 40:
       tracking_stright(140,0.8,0.002,1.5);

       if(line[5] and line[3]){digitalWrite(buz,HIGH); prof = true; missionPost = millis();}
       else if(prof and !line[4] and !line[5])
       {digitalWrite(buz,LOW); if(MissionTime > 500){prof = false; cnt++;}}
       
       if(table <= 3){if(cnt >= table-1 and line[5] and line[3]){mission = 50; resetPID(); missionPost = millis();}}
       else{if(cnt >= table-4 and line[5] and line[3]){mission = 50; resetPID(); missionPost = millis();}}
       break;
       
     case 41:
       tracking_stright(140,0.8,0.002,1.5);

       if(line[0] and line[2]){digitalWrite(buz,HIGH); prof = true; missionPost = millis();}
       else if(prof and !line[1] and !line[0])
       {digitalWrite(buz,LOW); if(MissionTime > 500){prof = false; cnt++;}}

       if(table <= 3){if(cnt >= table-1 and line[0] and line[2]){mission = 51; resetPID(); missionPost = millis();}}
       else{if(cnt >= table-4 and line[0] and line[2]){mission = 51; resetPID(); missionPost = millis();}}
       break;

    case 50:
      PID(100,25,1.5,0.003,0.8); digitalWrite(buz,LOW);
      if(!line[5] and !line[4] and line[3]){mission = 60; resetPID(); prof = false;}
      break;

    case 51:
      PID(25,100,1.5,0.003,0.8); digitalWrite(buz,LOW);
      if(!line[0] and !line[1] and line[2]){mission = 61; resetPID(); prof = false;}
      break;

    case 60:
      tracking_stright(140,0.8,0.002,1);
      if(weightRead() < 200 and !deliver)
      {mission = 70; resetPID(); deliver = true; missionPost = millis();}
      else if(line[0] and line[5] and deliver){mission = 80; deliver = false;}
      break;

   case 61:
      tracking_stright(140,0.8,0.002,1);
      if(weightRead() < 200 and !deliver)
      {mission = 71; resetPID(); deliver = true; missionPost = millis();}
      else if(line[0] and line[5] and deliver){mission = 81; deliver = false;}
      break;

    case 70:
      PID(100,-100,1,0.002,1);
      if(!line[5] and !line[4] and line[2] and MissionTime > 3000){mission = 21; resetPID();}
      break;

    case 71:
      PID(-100,100,1,0.002,1);
      if(!line[0] and !line[1] and line[3] and MissionTime > 3000){mission = 20; resetPID();}
      break;

    case 80:
      PID(100,100,0.5,0.0003,1); missionPost = millis();
      if(!line[0] and !line[5]){mission = 90;} 
      break;

    case 81:
      PID(100,100,0.5,0.0003,1); missionPost = millis();
      if(!line[0] and !line[5]){mission = 91;} 
      break;

    case 90:
      if(MissionTime < 1200){PID(120,-100,1,0.005,1);} 
      else if(MissionTime < 1700){PID(-90,-90,1,0.005,1);}
      else{mission = 0;}
      break;

    case 91:
      if(MissionTime < 1300){PID(-100,120,1,0.005,1);}
      else if(MissionTime < 1800){PID(-90,-90,1,0.005,1);}
      else{mission = 0;}
      break;   

    default : PID(0,0,0,0,0); resetPID(); break;
  }
}
