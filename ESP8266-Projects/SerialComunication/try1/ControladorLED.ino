char Number;
String Mensaje1 = "Ingrese un valor entre 1 y 0"; 

void setup() {
  Serial.begin(500000);
  pinMode(2, OUTPUT);
  delay(100);
}

void loop() {
  Serial.println(Mensaje1);
  while(Serial.available() == 0){}
  Number = Serial.read();
  if(Number == '0' or Number == '1'){
    if (Number == '1'){
      digitalWrite(2, LOW);
      Serial.println("Led encendido");
    }
    if (Number == '0'){
      digitalWrite(2, HIGH);
      Serial.println("Led apagado");
    }
  }else{
    Serial.println("Número o valor invalido");
  }
}
