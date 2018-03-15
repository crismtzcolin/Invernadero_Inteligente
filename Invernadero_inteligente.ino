/*Invernadero inteligente 

_______________________________________________________________________________
HUMEDAD:

  000-300 Superficie seca
  300-500 Superficie humeda
  500-750 Superficie mojada 

  65% = 487.5
  70% = 525
________________________________________________________________________________



*/

int tiempo=0;
int humedad=0;
int timeBombeo=500;       //Tiempo que dura encendida la bomba
int iluminacion='d';      // La letra 'd' sera para dia, y la letra 'n' para noche
int Bomba=2;
int LED=3;
int duracionDia=12;       //Horas de luz solar
int duracionNoche, duracion;
int sensorPin=A4;
int lightLevel;
int estado = 'd';     //Pendiente revisar esto

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(Bomba, OUTPUT);
}

void loop() {
  if(Serial.available()>0){
    estado=Serial.read();
    }
  if(estado=='a'){
    digitalWrite(LED, HIGH);
    }
  if(estado=='b'){
    digitalWrite(LED, LOW);
    }
  if(estado=='c'){
    digitalWrite(Bomba, HIGH);
    delay(timeBombeo);
    digitalWrite(Bomba, LOW);
    }
  if(estado=='d'){
    digitalWrite(Bomba, LOW);
    }

    
  if(estado=='e'){                      //NOTA: Checar este bloque de 'e'
    /*______________________________ Humedad ___________________________________________________*/
    humedad=analogRead(sensorPin);
    if(humedad<487){
      digitalWrite(Bomba, HIGH);
      if(humedad>525){
        digitalWrite(Bomba, LOW);
        } else{
          delay(timeBombeo);
          digitalWrite(Bomba, LOW);
          delay(500);
          }
      }
    /*_________________________________ Iluminación ________________________________________________________________*/
    
    duracionNoche= 24 - duracionDia;
    duracionDia= duracionDia*1000*60*60;
    duracionNoche= duracionNoche*1000*60*60;
    lightLevel= analogRead(A5);

    if(iluminacion=='d'){
      if(tiempo < duracionDia){
        tiempo++;
        if(lightLevel < 20){              //NOTA: Pendiente determinar los valores y porcentajes de la fotoresistencia
          digitalWrite(LED, HIGH);
          } else{
            digitalWrite(LED, LOW);
            }
        /*  _________________________ Pendiente por escribir respuestas en pantalla__________________________________________________________________
         
         Serial.println(lightLevel);

         */
        
        } else {
          iluminacion='n';
          }
      } else{
        tiempo=0;
        if(tiempo < duracionNoche){
          tiempo++;
          } else{
            iluminacion='d';
            }
        }
    }
}
