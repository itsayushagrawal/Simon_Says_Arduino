#define MAX_GAME_LENGTH 12

const uint8_t digitTable[] =
{
  0b11000000,  // 0
  0b11111001,  // 1
  0b10100100,  // 2
  0b10110000,  // 3
  0b10011001,  // 4
  0b10010010,  // 5
  0b10000010,  // 6
  0b11111000,  // 7
  0b10000000,  // 8
  0b10010000   // 9
};

#define speakerPin 8
const uint8_t ledPins[] = {9,10,11,12};
const uint8_t buttonPins[] = {2,3,4,5};
const uint16_t gameTones[] = {500,600,700,800};

const uint8_t DATA_PIN = A0;
const uint8_t LATCH_PIN = A1;
const uint8_t CLOCK_PIN = A2;

uint8_t sequence[MAX_GAME_LENGTH];
byte gameIndex = 0;

void flashLed(uint8_t ledIndex, uint16_t duration);
byte readButtons();
bool checkUserSequence();


void setup() 
{
  for(int i=0; i<4; i++)
  {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  randomSeed(analogRead(A3));


}

void loop() 
{
  sequence[gameIndex] = random(0,4);
  gameIndex++;

  playSequence();

  if(!checkUserSequence())
  {
    gameOver();
    gameIndex=0;
  }

  displayScore(gameIndex);

  if(gameIndex >= MAX_GAME_LENGTH)
    gameIndex =0;

  delay(500);
  
}

void flashLed(uint8_t ledIndex, uint16_t duration)
{
      tone(speakerPin, gameTones[ledIndex]);
      digitalWrite(ledPins[ledIndex], HIGH);
      delay(duration);
      noTone(speakerPin);
      digitalWrite(ledPins[ledIndex], LOW);
      delay(duration);
}

byte readButtons()
{
  while(true)
  {
    for(byte i =0; i< 4; i++)
    {
      if(digitalRead(buttonPins[i]) == LOW)
      {
        while(digitalRead(buttonPins[i]) == LOW)
        {
          delay(1);
        }
        return i;
      }
    }
    delay(1);
  }
}

bool checkUserSequence()
{
  for(byte i=0; i<gameIndex; i++)
  {
    byte expected = sequence[i];
    byte actual = readButtons();

    flashLed(actual,150);

    if(expected != actual )
      return false;
  }
  return true;
}

void playSequence()
{
  for (byte i=0 ; i < gameIndex; i++)
  {
    flashLed(sequence[i],150);
  }

}

void gameOver()
{
  for(byte i=0 ; i<4 ; i++)
  {
    tone(speakerPin, 1000);
    for(byte j=0 ; j<4 ; j++)
      digitalWrite(ledPins[j],HIGH);

    delay(100);

    noTone(speakerPin);
    for(byte j=0 ; j<4 ; j++)
      digitalWrite(ledPins[j],LOW);
    
    delay(100);
  }

}

void displayScore(uint8_t gameScore)
{
  uint8_t onesDigit = gameScore % 10 ;
  uint8_t tensDigit = (gameScore / 10) % 10;

  sendData(onesDigit, tensDigit);
}

void sendData(uint8_t onesDigit, uint8_t tensDigit)
{
  digitalWrite(LATCH_PIN,LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, digitTable[onesDigit]);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, digitTable[tensDigit]);
  digitalWrite(LATCH_PIN, HIGH);
}
