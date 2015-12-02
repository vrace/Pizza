#define PIN_FROM 4
#define PIN_NUM 8
#define PIN_TO (PIN_FROM + PIN_NUM)
#define PIN_ID(id) (PIN_FROM + id)

#define SPEED_INITIAL 30
#define SPEED_STOP 1200
#define SPEED_STEP 10

#define BEFORE_SPEED_CHANGE 7000

typedef int BOOL;
#define TRUE 1
#define FALSE 0

BOOL played = FALSE;

void lightOn(int id)
{
  digitalWrite(PIN_ID(id), HIGH);
}

void lightOff(int id)
{
  digitalWrite(PIN_ID(id), LOW);
}

int playWithFullSpeed()
{
  int next = 0;
  int duration = random() % (BEFORE_SPEED_CHANGE + SPEED_INITIAL * PIN_NUM);
  
  while (duration > 0)
  {
    lightOn(next);
    delay(SPEED_INITIAL);
    lightOff(next);
    
    next = (next + 1) % PIN_NUM;
    duration -= SPEED_INITIAL;
  }
  
  return next;
}

void play()
{
  int next;
  int speed = SPEED_INITIAL;
  
  next = playWithFullSpeed();
  
  while (speed <= SPEED_STOP)
  {
    lightOn(next);
    delay(speed);
    lightOff(next);
    
    speed += (int)(speed * SPEED_STEP / 100.0f);
    next = (next + 1) % PIN_NUM;
  }
  
  lightOn(next);
}

void setup()
{
  int i;
  for (i = PIN_FROM; i < PIN_TO; i++)
  {
    pinMode(i, OUTPUT);
  }
  
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop()
{
  if (!played)
  {
    play();
    played = TRUE;
  }
}

