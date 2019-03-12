#define SENSOR_PIN 10
#define LED_OUT 13
#define LOCKED_LED 7
#define TOLERANCE 950
#define LOWER 400

int clapped_on = 1;
unsigned long last_clap = 0;
unsigned long current_clap;
int unlocked = 0;

//Locking password
long u_bound[3] = {350,350,350};
long l_bound[3] = {100,100,100};
//User's clap data
long claps[3] = {0};

void setup() {
  Serial.begin(9600);
  pinMode(LED_OUT,OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LOCKED_LED, OUTPUT);
  //Delay prevents the user from immediately turning the light on with one clap
  delay(2000);
  digitalWrite(LOCKED_LED, HIGH);

}

//int clap_count(unsigned long last_clap){
//  int count = 0;
//  return count;
//}

//check if the user has correctly entered their password
int checkPass(void){
  for(int i=1;i<3;i++){
    if(claps[i] < l_bound[i] || claps[i] > u_bound[i]){
      return 0;
    }
  }
  return 1;
}

//Add data to the end of the claps array, and bump out the first data point
void bumpClaps(long point[], int n, long newData){
  for(int x = 0; x < n-1; x++){
    point[x] = point[x+1];
  }
  point[n-1] = newData;
}
  
void loop() {  
  if(digitalRead(SENSOR_PIN) == LOW){
    Serial.println("CLAPPED");
    current_clap = millis();
    Serial.println(current_clap);
    bumpClaps(claps, 3, current_clap - last_clap);

    for(int i = 0; i < 3; i++)
    {
      Serial.print(claps[i]);
      Serial.print(" ");
    }
    Serial.println("");
    int pass = checkPass();
    int diff = current_clap - last_clap;

    //If the clapper is locked and the user enters their password, unlock the clapper
    if(unlocked == 0 && pass == 1){
      Serial.println("PASSWORD CORRECT");
      Serial.println("UNLOCKED"); 
      digitalWrite(LOCKED_LED, LOW);
      unlocked = 1;
      delay(TOLERANCE);
    }//If the arduino is unlocked, and the user enters their password, lock the clapper
    else if(unlocked == 1 && pass == 1){
      //digitalWrite(LED_OUT, LOW);
      Serial.println("PASSWORD CORRECT"); 
      Serial.println("LOCKED"); 
      digitalWrite(LOCKED_LED, HIGH);

      unlocked = 0;
      delay(TOLERANCE);
    }//If the light is one and the clapper is unlocked, turn the light off
    else if(clapped_on && diff < TOLERANCE && diff > LOWER && unlocked){
      Serial.println("THIS SHOULD BE ON");
      digitalWrite(LED_OUT, HIGH);
      delay(TOLERANCE);
      clapped_on = 0;
    }//If the light is off and the clapper is unlocked, turn the light on
    else if(diff < TOLERANCE && diff > LOWER && unlocked){
      Serial.println("quiet quiet");
      digitalWrite(LED_OUT, LOW);
      delay(TOLERANCE);
      clapped_on = 1;
    }
    //Record the most recent clap for later
    last_clap = current_clap;
    //Prevent spam clapping
    delay(50);
  }
}
