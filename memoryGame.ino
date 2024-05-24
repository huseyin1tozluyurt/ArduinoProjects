#define led1 4
#define led2 5
#define led3 6
#define led4 7
#define but1 8
#define but2 9
#define but3 10
#define but4 11
#define buzzer 12
void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(but1,INPUT);
  pinMode(but2,INPUT);
  pinMode(but3,INPUT);
  pinMode(but4,INPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
  randomSeed(millis());
}
void lightOff()
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
}

void lightOn()
{
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,HIGH);
}

void buzzFunc(int value)
{
  tone(buzzer,value);
  delay(300);
  noTone(buzzer);
  delay(100);
}

void victoryMessage()
{
  Serial.println("You won the game!...");
  Serial.println("Bravoooooo!!!.......");
  lightOn();
  delay(500);
  lightOff();
  buzzFunc(200);
  delay(500);
  lightOn();
  buzzFunc(200);
  delay(500);
  lightOff();
  delay(500);
  lightOn();
  buzzFunc(200);
  delay(500);
  lightOff();
}


void loop() {

  int turn=random(5,8);
  int* requestedMoves=new int[turn]; 
  for(int i=0;i<turn-1;i++)
  {
    int move=random(1,5);
    if(move==1)
    {
      digitalWrite(led1,HIGH);
      requestedMoves[i]=1;
      delay(800);
    }
    else if(move==2)
    {
      digitalWrite(led2,HIGH);
      requestedMoves[i]=2;
      delay(800);
    }
    else if(move==3)
    {
      digitalWrite(led3,HIGH);
      requestedMoves[i]=3;
      delay(800);
    }
    else if(move==4)
    {
      digitalWrite(led4,HIGH);
      requestedMoves[i]=4;
      delay(800);
    }
    Serial.println(move);
    lightOff();
    delay(300);
  }
  int takenMove=0;
  int* takenMoves=new int[turn];
  while(1)
  {
    int but1State=digitalRead(but1);
    int but2State=digitalRead(but2); 
    int but3State=digitalRead(but3);
    int but4State=digitalRead(but4);
    if(but1State==HIGH)
    {
      digitalWrite(led1,HIGH);
      takenMoves[takenMove]=1;
      takenMove++;
      Serial.println("Button1 is pressed");
      buzzFunc(120);
      delay(300);
    }
    if(but2State==HIGH)
    {
      digitalWrite(led2,HIGH);
      takenMoves[takenMove]=2;
      takenMove++;
      Serial.println("Button2 is pressed");
      buzzFunc(240);
      delay(300);
    }
    if(but3State==HIGH)
    {
      digitalWrite(led3,HIGH);
      takenMoves[takenMove]=3;
      takenMove++;
      Serial.println("Button3 is pressed");
      buzzFunc(410);
      delay(300);
    }
    if(but4State==HIGH)
    {
      digitalWrite(led4,HIGH);
      takenMoves[takenMove]=4;
      takenMove++;
      Serial.println("Button4 is pressed");
      buzzFunc(540);
      delay(300);
    }
    lightOff();
    if(takenMove==turn-1)
    {
      if(*requestedMoves==*takenMoves)
      {
        victoryMessage();
        delay(500);
        break;
      }
      else
      {
        Serial.println("Invalid enterance");
        Serial.println("Try again! ");
        Serial.println("requestedMoves");
        for(int i=0;i<turn-1;i++)
        {
          Serial.println(requestedMoves[i]);
        }

        Serial.println("takenMoves");
        for(int j=0;j<turn-1;j++)
        {
          Serial.println(takenMoves[j]);
        }
        takenMove=0;
      }
      delay(1500);
    }
  }
}
