
float retR = 1, retL = 1;
float confR = 0, confL = 0;
void tracking_stright(float Speed, float kp, float ki, float kd)
{
  if(line[2] && !line[3]){confL=-Speed*0.4; confR=Speed*0.4;}
  else if(line[1] && !line[3]){retL = 0;}
  else if(line[0] && !line[3]){retL=-0.4; confL=confR=0;}
 
  if(line[3] && !line[2]){confR=-Speed*0.4; confL=Speed*0.4;}
  else if(line[4] && !line[2]){retL = 0;}
  else if(line[5] && !line[2]){retR=-0.4; confL=confR=0;}
  
  if(line[3] && line[2]){confL=confR=0;}
  if(line[0] && line[5]){retL=retR=0; resetPID();}
  
  float SpeedL = (Speed+confL)*retL;
  float SpeedR = (Speed+confR)*retR;
  retR = retL = 1;
  
  PID(SpeedL,SpeedR,kp,ki,kd);
}

void tracking_right(float Speed, float kp, float ki, float kd)
{
  if(line[2] && !line[3]){confL=-Speed*0.4; confR=Speed*0.4;}
  else if(line[1] && !line[3]){retL = 0;}
  else if(line[0] && !line[3]){retL=-0.4; confL=confR=0;}
 
  if(line[3] && !line[2]){confR=-Speed*0.4; confL=Speed*0.4;}

  if(line[5]){confL=confR=0; retR= -0.5;}
  else if(line[4] && !line[2]){confL=confR=0; retR= -0.25;}
  else if(line[3] && line[2]){confL=confR=0;}
  
  float SpeedL = (Speed+confL)*retL;
  float SpeedR = (Speed+confR)*retR;
  retR = retL = 1;
  
  PID(SpeedL,SpeedR,kp,ki,kd);
}

void tracking_left(float Speed, float kp, float ki, float kd)
{
  if(line[3] && !line[2]){confR=-Speed*0.4; confL=Speed*0.4;}
  else if(line[4] && !line[2]){retL = 0;}
  else if(line[5] && !line[2]){retR=-0.4; confL=confR=0;}
 
  if(line[2] && !line[3]){confL=-Speed*0.4; confR=Speed*0.4;}

  if(line[0]){confL=confR=0; retL= -0.5;}
  else if(line[1] && !line[3]){confL=confR=0; retL= -0.25;}
  else if(line[2] && line[3]){confL=confR=0;}
  
  float SpeedL = (Speed+confL)*retL;
  float SpeedR = (Speed+confR)*retR;
  retR = retL = 1;
  
  PID(SpeedL,SpeedR,kp,ki,kd);
}
