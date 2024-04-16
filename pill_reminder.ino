/*
  Pill timer - Starts blinking every 4 sec after 12 hours, then every 2 sec after 20 hours.
*/

const unsigned long ONE_SECOND = 1000; // One second in milliseconds
const unsigned long FOUR_SECONDS = ONE_SECOND * 4; 
const unsigned long TEN_SECONDS = 10 * ONE_SECOND; 
const unsigned long FIFTEEN_SECONDS = ONE_SECOND * 10; 
const unsigned long TWENTY_SECONDS = 20 * ONE_SECOND; 
const unsigned long THIRTY_SECONDS = 30 * ONE_SECOND; 

const unsigned long ONE_MINUTE = 60 * ONE_SECOND; 
const unsigned long TWO_MINUTES =  2 * ONE_MINUTE; 

const unsigned long ONE_HOUR =  60 * ONE_MINUTE; 
const unsigned long SIX_HOURS = 6 * ONE_HOUR; 
const unsigned long TWELVE_HOURS = 12 * ONE_HOUR; 
const unsigned long TWENTY_HOURS = 20 * ONE_HOUR; 

const unsigned long LED_LIT_DURATION = 200; // LED lit duration in milliseconds
const unsigned long BRIGHTNESS = 1; 

unsigned long startTime;
unsigned long lastBlinkTime;
unsigned long currentTime;


void setup() {
  //Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  startTime = millis();
  lastBlinkTime = startTime;

  analogWrite(LED_BUILTIN, BRIGHTNESS);
}

void loop() {
  currentTime = millis();
  unsigned long elapsedMsec = currentTime - startTime;
  unsigned long elapsedBlinkTime;

  //Serial.println(elapsedMsec);

  // checking to see if this ever happens - shouldn't happen.
  if (currentTime < startTime) {
    //Serial.println("currentTime < startTime");

    for(;;) {
      analogWrite(LED_BUILTIN, BRIGHTNESS);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
    }
  }
  
  // 20 hours elapsed
  if (elapsedMsec >= TWENTY_HOURS ) {
    blinkConstantly();
  }

  // 12 hours elapsed
  else if (elapsedMsec >= TWELVE_HOURS) {
    elapsedBlinkTime = currentTime - lastBlinkTime;

    // blink 2x every 4 sec
    if (elapsedBlinkTime > FOUR_SECONDS) {
      blink(2);
    }
  } 

  // 6 hours elapsed
  else if (elapsedMsec >= SIX_HOURS) {
    elapsedBlinkTime = currentTime - lastBlinkTime;

    // blink every 4 sec
    if (elapsedBlinkTime > FOUR_SECONDS) {
      blink(1);
    }
  } 
  else {
    delay(ONE_SECOND);
  }
  
  delay(50);
}

void blink(int numBlinks) {
  lastBlinkTime = currentTime;

  for (int i = 0; i < numBlinks; i++) { 
    analogWrite(LED_BUILTIN, BRIGHTNESS);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(LED_LIT_DURATION);
    digitalWrite(LED_BUILTIN, LOW);
    delay(LED_LIT_DURATION);
  }
}

void blinkConstantly() {
  lastBlinkTime = currentTime;

  for (;;) { 
    analogWrite(LED_BUILTIN, BRIGHTNESS);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(LED_LIT_DURATION/2);
    digitalWrite(LED_BUILTIN, LOW);
    delay(LED_LIT_DURATION/2);
  }
}
