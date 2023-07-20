
float EROR[2], ERORL[2], ERORDL[2], RPM[2];
unsigned long lastTime;
void resetPID() 
{
  EROR[0] = ERORL[0] = ERORDL[0] = PWM[0] = 0;
  EROR[1] = ERORL[1] = ERORDL[1] = PWM[1] = 0;
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW); 
}

void PID(float kec2, float kec1, float KP, float KI, float KD)
{
  unsigned long now = millis();
  unsigned long deltaTime = (now - lastTime);
  lastTime = now;
  
  RPM[0] = abs(kec1);
  RPM[1] = abs(kec2);
  
  float P[2], I[2], D[2];
  float kP[2], kI[2], kD[2];

  kP[0]=kP[1]= KP;
  kI[0]=kI[1]= KI;
  kD[0]=kD[1]= KD;

  int i;
  for(i=0; i<2; i++)
  {
    EROR[i] = (abs (RPM[i])) - TEMP[i];
    P[i] = kP[i] * EROR[i];
    ERORL[i] += kI[i] * EROR[i] * deltaTime;
    if (ERORL[i]>= 255.00){ERORL[i]= 255.00;}
    if (ERORL[i]<=-255.00){ERORL[i]=-255.00;}
    I[i] = ERORL[i];
    D[i] = kD[i] * 1/deltaTime * (EROR[i] - ERORDL[i]);
    ERORDL[i] = EROR[i];
    PWM[i] = P[i] + I[i] + D[i];
    
    if (PWM[i]<=0){PWM[i] = 0;}
    else if (PWM[i]>=255){PWM[i] = 255;}
  }

  if(kec1 >= 0){digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW);}
  else{digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH);}

  if(kec2 >= 0){digitalWrite(IN4,HIGH); digitalWrite(IN3,LOW);}
  else{digitalWrite(IN4,LOW); digitalWrite(IN3,HIGH);}
  
  analogWrite(EN1,PWM[0]);
  analogWrite(EN2,PWM[1]); 
}
