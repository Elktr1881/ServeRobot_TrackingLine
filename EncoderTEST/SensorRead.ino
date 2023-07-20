void getLine()
{
  Serial.print("Line: ");
  for(int i=0; i<6; i++)
  {
    lineValue[i] = analogRead(linePin[i]);
    if(lineValue[i] > 1000){line[i] = true;} else{line[i] = false;}
    Serial.print(lineValue[i]); Serial.print(",");
  }
  Serial.print(">>");
}

float weightRead()
{
    float weight;
    scale.set_scale(calibration_weight); 
    weight = abs(scale.get_units());
    return(weight);
}

int ENCR = 0, ENCL = 0;
unsigned int postTime = 0;
void EncProcessR(){ENCR++;}
void EncProcessL(){ENCL++;}
void EncoderRead()
{
  unsigned int times = millis()-postTime;
  if(times >= 100)
  {
    TEMP[0] = ENCR*100/times; 
    TEMP[1] = ENCL*100/times; 
    ENCL = ENCR = 0; 
    postTime = millis();
  }
}
