/* 
 * button snap 1.0.0
 */
 
int snapLed = 10;
int snapLedState = LOW;

int playerOneLed = 13;
int playerOneBtn = 7;
int playerOneVal = LOW

int playerTwoLed = 6;
int playerTwoBtn = 3;
int playerTwoVal = LOW;

long currentMillis = 0;
long previousMillis = 0;
long interval = 1000;

int winner = -1;

void setup() {  
  pinMode(snapLed, OUTPUT);
  
  pinMode(playerOneLed, OUTPUT);  
  pinMode(playerOneBtn, INPUT);
  
  pinMode(playerTwoLed, OUTPUT);  
  pinMode(playerTwoBtn, INPUT);
}

void loop(){
  
  delay(1);

  digitalWrite(playerOneLed, LOW);
  digitalWrite(playerTwoLed, LOW);  
  
  if (!playerOneVal && !playerTwoVal) // thwarting cheaters
    currentMillis++;
  
  if (currentMillis - previousMillis > interval) {
    if (snapLedState == LOW) { // red light is off
     winner = -1;     // reset winner var
     interval = 500;  // show light for 1 ms only
    }
    else              // red light is on
      interval = random(100,6000);      

    previousMillis = currentMillis;
    snapLedState = ! snapLedState;
    digitalWrite(snapLed, snapLedState);
  }
    
  playerOneVal = digitalRead(playerOneBtn);
  playerTwoVal = digitalRead(playerTwoBtn);
  
  if (snapLedState == HIGH && winner < 0) { // if snap led is on and we don't yet have a winner
    if (playerOneVal == HIGH && playerTwoVal == HIGH)
      winner = 99;
    else if (winner < 0 && playerOneVal == HIGH)
      winner = 0;
    else if (winner < 0 && playerTwoVal == HIGH)
      winner = 1; 
  }
  
  if (winner == 0)
    digitalWrite(playerOneLed, HIGH); // player one wins
  else if (winner == 1)
    digitalWrite(playerTwoLed, HIGH); // player two wins
  else if (winner == 99) {            // draw
    digitalWrite(playerOneLed, HIGH);
    digitalWrite(playerTwoLed, HIGH);
  }

}
