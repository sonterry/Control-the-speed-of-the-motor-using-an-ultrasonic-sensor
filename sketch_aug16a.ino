/*

int trig = 13;

int echo = 12;

int buzzer = 8;

int LED = 3;

float duration;

float distance;

 

void setup() 

{

  Serial.begin(9600);

  pinMode(echo,INPUT);

  pinMode(trig,OUTPUT);

  pinMode(buzzer,OUTPUT);

  pinMode(LED, OUTPUT);

}

 

void loop() 

{

  digitalWrite(trig,HIGH);

  delay(10);

  digitalWrite(trig,LOW);

  duration = pulseIn(echo,HIGH);

  distance = ((34000*duration)/1000000)/2;

  Serial.print(distance);

  Serial.println("cm");

 

  if(distance < 20)

  {

    analogWrite(LED,255-(distance*12));

    

    tone(buzzer,1000,100);

    delay(100);

    tone(buzzer,1000,100);

    delay(100);

  }

  else

  {

    digitalWrite(LED,LOW);

  }

  

  delay(100);

}

*/




















































































unsigned int count=0;

const int motor1=3;

const int trigPin1=13; 
const int echoPin1=12;

int distance1=0;

void setup() {
  Serial.begin(9600);
  pinMode(motor1, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  digitalWrite(trigPin1, LOW);

  TCCR0A = 0; //TCCR0A initialize
  TCCR0B = 0; //TCCR0B initialize
  TCNT0 = 0;  //TCNT0 initialize
  OCR0A= 154; //Period: 10ms , Frequency: 100Hz
//  OCR0B= 154;
  TCCR0A |= (1<<WGM01);
  TCCR0B |= (1<<CS02) | (1<<CS00);
  TIMSK0 |= (1<<OCIE0A);
//  TIMSK0 |= (1 << OCIE0B) | (1<<OCIE0A);
  
  sei();
}
 
ISR(TIMER0_COMPA_vect){
  count++;
  
  if(count>13) // 100ms 마다 초기화
  {
    digitalWrite(trigPin1, LOW);
    distance1=pulseIn(echoPin1, HIGH)/58.2;
    if(distance1>250) distance1=250;
    Serial.print("sens1 : ");
    Serial.println(distance1);
    count=0;
    TCNT0=0;
    digitalWrite(trigPin1, HIGH);
  }
  
  if(distance1/13<count) digitalWrite(motor1, HIGH);
  else digitalWrite(motor1, LOW);
}

void loop() {
  
}
