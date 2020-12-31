String rgbToJSON(int r, int g, int b, int Br){

//String temp = "<p>{\"r\":" +String(r)+ ",\"g\":" +String(g) + ",\"b\":" +String(b)+ ",\"br\":" +String(Br+100)+ "}</p>";

String temp2 = "<p>{\"rgb\":{ \"r\":" + String(r) + ",\"g\": " +String(g) + ",\"b\": " +String(b) + ",\"br\":" + String(Br) + "}}</p>";

return temp2;
}
