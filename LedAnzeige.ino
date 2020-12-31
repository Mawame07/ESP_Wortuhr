void zeigeZeit(int stunde, int minute){

    //Serial.print(stunde);
    //Serial.print(":");
    //Serial.println(minute);


//Wortuhr
int individualPixels[NUMPIXELS]={0};
  if (stunde >= 13)
  {stunde - 12;}
  
  individualPixels[0]=1; //Light "E"
  individualPixels[1]=1; //Light "S" 
  individualPixels[2]=1; //Light "I"
  individualPixels[3]=1; //Light "S"
  individualPixels[4]=1; //Light "T"

/* LED die Zeit + 1 min anzeigt */
for(int i = 1; i < 57;i=i+5)
{
  if(minute == i)
  {
  individualPixels[93]=1;
  break;
  } 
}

/* LED die Zeit + 2 min anzeigt */
for(int i = 2; i < 58;i=i+5)
{
  if(minute == i)
  {
  individualPixels[94]=1;
  individualPixels[93]=1;
  break;
  } 
}

/* LED die Zeit + 3 min anzeigt */
for(int i = 3; i < 59;i=i+5)
{
  if(minute == i)
  {
  individualPixels[95]=1;
  individualPixels[93]=1;
  individualPixels[94]=1;
  break;
  } 
}

/* LED die Zeit + 4 min anzeigt */
for(int i = 4; i < 60;i=i+5)
{
  if(minute == i)
  {
  individualPixels[96]=1;
  individualPixels[95]=1;
  individualPixels[93]=1;
  individualPixels[94]=1;
  break;
  } 
}
  
  /* Minutes between 0-5 - Light "UHR" */
  if ((minute>=0 && minute<5)){
    individualPixels[85]=1;
    individualPixels[86]=1;
    individualPixels[87]=1;
  }
  
  /* Minutes between 5-10 or 55-60 - Light "FÜNF" */
  if ((minute>=5 && minute<10) || (minute>=55 && minute<60)){
    individualPixels[5]=1;
    individualPixels[6]=1;
    individualPixels[7]=1;
    individualPixels[8]=1;
  }
  
  /* Minutes between 10-15 or 50-55 - Light "ZEHN" */
  if ((minute>=10 && minute<15) || (minute>=50 && minute<55)){
    individualPixels[16]=1;
    individualPixels[17]=1;
    individualPixels[18]=1;
    individualPixels[19]=1;
  }
  
  /* Minutes between 15-20 or 45-50 - Light "VIERTEL" */
  if ((minute>=15 && minute<20) || (minute>=45 && minute<50)){
    individualPixels[24]=1;
    individualPixels[25]=1;
    individualPixels[26]=1;
    individualPixels[27]=1;
    individualPixels[28]=1;
    individualPixels[29]=1;
    individualPixels[30]=1;
  }
  
  /* Minutes between 20-25 or 40-45 - Light "ZWANZIG" */
  if ((minute>=20 && minute<25) || (minute>=40 && minute<45)){
    individualPixels[9]=1;
    individualPixels[10]=1;
    individualPixels[11]=1;
    individualPixels[12]=1;
    individualPixels[13]=1;
    individualPixels[14]=1;
    individualPixels[15]=1;
  }  
  
/* Minutes between 25-30 or 35-40 - Light "FÜNF VOR HALB" */
  if (minute>=25 && minute<30){
      
    individualPixels[5]=1;
    individualPixels[6]=1;
    individualPixels[7]=1;
    individualPixels[8]=1;


    individualPixels[31]=1;
    individualPixels[32]=1;
    individualPixels[33]=1;
    
    individualPixels[38]=1;
    individualPixels[39]=1;
    individualPixels[40]=1;
    individualPixels[41]=1;

  }
/* Es ist fünf nach halb */
if(minute >= 35 && minute<40)
{
    individualPixels[5]=1;
    individualPixels[6]=1;
    individualPixels[7]=1;
    individualPixels[8]=1;
  
    individualPixels[34]=1;
    individualPixels[35]=1;
    individualPixels[36]=1;
    individualPixels[37]=1;

    individualPixels[38]=1;
    individualPixels[39]=1;
    individualPixels[40]=1;
    individualPixels[41]=1;
}

  
 
  /* Minutes between 30-35 - Light "Halb" */
  if(minute>=30 && minute<35){
    individualPixels[38]=1;
    individualPixels[39]=1;
    individualPixels[40]=1;
    individualPixels[41]=1;
  }
  
  /* Minutes between 5-35 - Light "nach" */
  if((minute>=5) && (minute<=24)){
    individualPixels[34]=1;
    individualPixels[35]=1;
    individualPixels[36]=1;
    individualPixels[37]=1;
  }
   
  /* Minutes between 40-60 - Light "vor" & MODIFY CURRENT HOUR VALUE */
  if (minute>=40){
    individualPixels[31]=1;
    individualPixels[32]=1;
    individualPixels[33]=1;
  }
 
   if (minute>=25){
    stunde++; //Add 1 from current hour
    /*Set time to twelve for hour around midnight, noon */
    if (stunde==0) {
      stunde=12; 
    }
    /*Corner case for 12:35-12:59 */
    if (stunde==13){
      stunde=1; 
    }
    if (stunde==24){
      stunde=12; 
    }     
  }
 

  /* Hour=1 - Light "eins" */
  if (stunde==1 || stunde==13){
    individualPixels[52]=1;
    individualPixels[53]=1;
    individualPixels[54]=1;
    individualPixels[55]=1;
    if(minute>=0 && minute<5)       // Macht den Unterscheid zwischen "Es ist EIN Uhr" und "Es ist fünf nach EINS" 
    {
      individualPixels[52]=0;
    }
  }
  
  /* Hour=2 - Light "zwei" */
  if (stunde==2 || stunde==14){
    individualPixels[54]=1;
    individualPixels[55]=1;
    individualPixels[56]=1;
    individualPixels[57]=1;
  }
  
  /* Hour=3 - Light "drei" */
  if (stunde==3 || stunde==15){
    individualPixels[58]=1;
    individualPixels[59]=1;
    individualPixels[60]=1;
    individualPixels[61]=1; 
  }
  
  /* Hour=4 - Light "vier" */
  if (stunde==4 || stunde==16){
    individualPixels[66]=1;
    individualPixels[67]=1;
    individualPixels[68]=1;
    individualPixels[69]=1;  
  }
  
  /* Hour=5 - Light "fuenf" */
  if (stunde==5 || stunde==17){
    individualPixels[62]=1;
    individualPixels[63]=1;
    individualPixels[64]=1;
    individualPixels[65]=1;
  }
  
  /* Hour=6 - Light "Sechs" */
  if (stunde==6 || stunde==18){
    individualPixels[88]=1;
    individualPixels[89]=1;
    individualPixels[90]=1;
    individualPixels[91]=1;
    individualPixels[92]=1;
  }
  
  /* Hour=7 - Light "sieben" */
  if (stunde==7 || stunde==19){
    individualPixels[47]=1;
    individualPixels[48]=1;
    individualPixels[49]=1;
    individualPixels[50]=1;
    individualPixels[51]=1;
    individualPixels[52]=1;
  }
  
  /* Hour=8 - Light "Acht" */
  if (stunde==8 || stunde==20){
    individualPixels[77]=1;
    individualPixels[78]=1;
    individualPixels[79]=1;
    individualPixels[80]=1;
  }
  
  /* Hour=9 - Light "neun" */
  if (stunde==9 || stunde==21){
    individualPixels[70]=1;
    individualPixels[71]=1;
    individualPixels[72]=1;
    individualPixels[73]=1;
  }
  
  /* Hour=10 - Light "zehn" */
  if (stunde==10 || stunde==22){
    individualPixels[81]=1;
    individualPixels[82]=1;
    individualPixels[83]=1;
    individualPixels[84]=1;
   }
  
  /* Hour=11 - Light "elf" */
  if (stunde==11 || stunde==23){
    individualPixels[74]=1;
    individualPixels[75]=1;
    individualPixels[76]=1;
  }
  
  /* Hour=12 - Light "zwölf" */
  if (stunde==12 || stunde==0){
    individualPixels[42]=1;
    individualPixels[43]=1;
    individualPixels[44]=1;
    individualPixels[45]=1;
    individualPixels[46]=1;
  }

  
  /* Light pixels corresponding to current time */
  for (int i=0; i<sizeof(individualPixels); i++){
    if (individualPixels[i]==1){
      pixels.setPixelColor(i, pixels.Color(red,green,blue)); //Set Neopixel color
    }
    else{       
      pixels.setPixelColor(i,pixels.Color(0,0,0));
    }
  }

  pixels.show(); //Display Neopixel color
}
