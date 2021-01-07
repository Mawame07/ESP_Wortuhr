String rgbToJSON(int r, int g, int b, int Br){

String temp = "<p>{\"rgb\":{ \"r\":" + String(r) + ",\"g\": " +String(g) + ",\"b\": " +String(b) + ",\"br\":" + String(Br) + "}}</p>";

return temp;
}

void SearchStringFor(String str, int &wert)
{
 str = str + "="; 
 int stringlaenge = str.length();     //Gibt Stringlänge an

/*for(int i = s2.indexOf(str); i<=s2.indexOf(("&"),s2.indexOf(str))-3; i++)
  {
  //Serial.print(s2[i+2]);  
  }
*/
wert = header.substring(header.indexOf(str)+stringlaenge, header.indexOf(("&"),header.indexOf(str))).toInt();
 
}
