#define SENSOR_PIN 10
#define LED_OUT 13
#define TOLERANCE 950

//Boolean to determine when the light is on or off
int clapped_on = 1;
//Holds the time value of when the user last previously clapped
unsigned long last_clap = 0;
//Holds the time value when the user claps
unsigned long current_clap;

//Holds the upper bound of the user's password
long u_bound[3] = {2000,2000,2000};
long l_bound[3] = {500,500,500};

//Holds the data of the user's claps
long claps[3] = {0};

//Initialize the arduino pins
void setup() {
  Serial.begin(9600);
  pinMode(LED_OUT,OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  delay(2000);
}

//This method takes in a data point and adds it to the end of an array, bumping the first data entry out
void bumpClaps(long point[], int n, long newData){
  for(int x = 0; x < n-1; x++){
    point[x] = point[x+1];
  }
  point[n-1] = newData;
}

//This does nothing so far
int clap_count(unsigned long last_clap){
  int count = 0;
  return count;
}

//Determine whether the user has successfully clapped their password
int checkPass(void){
  for(int i=1;i<3;i++){
    //Check each clap against the upper and lower bounds of the password
    if(claps[i] < l_bound[i] || claps[i] > u_bound[i]){
      return 0;
    }
  }
  //Returns 1 if the entered password is incorrect  
  return 1;
}
  
void loop() {
  
  if(digitalRead(SENSOR_PIN) == LOW){
    Serial.println("CLAPPED");
    current_clap = millis();
    Serial.println(current_clap - last_clap);
    
    bumpClaps(claps, 3, current_clap - last_clap);

    for(int i = 0; i < 3; i++)
      {
        Serial.print(claps[i]);
        Serial.print(" ");
      }
    Serial.println("");
    
    if(checkPass()){
      digitalWrite(LED_OUT, HIGH);
      Serial.println("PASSWORD CORRECT");
      delay(2000);  
    }
        
    last_clap = current_clap;
    delay(50);

  }
}
