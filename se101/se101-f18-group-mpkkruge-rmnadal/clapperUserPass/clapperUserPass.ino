#define SENSOR_PIN 10
#define LED_OUT 13
#define LOCKED_LED 7
#define TOLERANCE 950
#define LOWER 400

int clapped_on = 1;
int passSet = 0;
int passLength = 0;

unsigned long last_clap = 0;
unsigned long current_clap;
int unlocked = 0;

//CommandClap
long CC_U_Bound[3] = {350,350,350};
long CC_L_Bound[3] = {100,100,100};

//UserPassword
long pass_U_Bound[12] = {0};
long pass_L_Bound[12] = {0};

//User's clap data
long pass_Claps[8] = {0};
long CC_Claps[3] = {0};

void setup() {
  Serial.begin(9600);
  pinMode(LED_OUT,OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LOCKED_LED, OUTPUT);
  //Tells user when to start clapping
  delay(2000);
  digitalWrite(LOCKED_LED, HIGH);
}

//int clap_count(unsigned long last_clap){
//  int count = 0;
//  return count;
//}

//check if the user has correctly entered a clap code
int checkClaps(long l_bound[], long u_bound[], int clapLength, long claps[]){
  for(int i= 0; i < clapLength-1; i++){       
    if(claps[i] < l_bound[i]){
      Serial.println("Too Slow");
      return 0;      
    }
    if(claps[i] > u_bound[i]){
      Serial.println("Too Fast");
      return 0;
    }
  } 
  return 1;  
}

//Add data to the end of the claps array, and bump out the first data point
void bumpClaps(long point[], int n, long newData){
  for(int x = n-1; x > 0; x--){
    point[x] = point[x-1];
  }
  point[0] = newData;
}
  
void loop() {
 if(passSet){  
  if(digitalRead(SENSOR_PIN) == LOW){
    Serial.println("CLAPPED");
    current_clap = millis();
    Serial.println(current_clap);

    //Store and output the user's clapData
    bumpClaps(pass_Claps, 8, current_clap - last_clap);
    for(int i = 0; i < 8; i++)
    {
      Serial.print(pass_Claps[i]);
      Serial.print(" ");
    }
    Serial.println("");

    Serial.println("Password Is:");
        for(int i = 0; i < passLength; i++){
          Serial.print(pass_L_Bound[i]);
          Serial.print("-");
          Serial.print(pass_U_Bound[i]);
          Serial.print(", ");
        }
    Serial.println("");

    
    int pass = checkClaps(pass_L_Bound, pass_U_Bound, passLength, pass_Claps);
    
    int diff = current_clap - last_clap;

    //If the light should do something, reset the password data
    if (pass == 1 || diff < TOLERANCE && diff > LOWER && unlocked){
      for(int x = 0; x < 8; x++){
        pass_Claps[x] = 0;
      }
    }

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
    }//If the light is on and the clapper is unlocked, turn the light ON
    else if(clapped_on && diff < TOLERANCE && diff > LOWER && unlocked){
      Serial.println("LIGHT ON");
      digitalWrite(LED_OUT, HIGH);
      delay(TOLERANCE);
      clapped_on = 0;
    }//If the light is off and the clapper is unlocked, turn the light off
    else if(diff < TOLERANCE && diff > LOWER && unlocked){
      Serial.println("LIGHT OFF");
      digitalWrite(LED_OUT, LOW);
      delay(TOLERANCE);
      clapped_on = 1;
    }
    //Record the most recent clap for later
    last_clap = current_clap;
    //Prevent spam clapping
    delay(50);
  }//End of sound sensor reading
 }//End of braces to turn lights on and off
 
 //Have the user set their password
 else{  
  if(digitalRead(SENSOR_PIN) == LOW){
    current_clap = millis();
    
    //Store and output the user's clapData
    bumpClaps(CC_Claps, 3, current_clap - last_clap);
    Serial.println("CC Claps:");
    for(int i = 0; i < 3; i++)
    {
      Serial.print(CC_Claps[i]);
      Serial.print(" ");
    }
    Serial.println("");

    bumpClaps(pass_U_Bound, 8, current_clap - last_clap + 300);
    bumpClaps(pass_L_Bound, 8, current_clap - last_clap - 300);
    
    passLength++;

    Serial.println("Current Password:");
    for(int i = 0; i < 8; i++){
       Serial.print(pass_L_Bound[i]);
       Serial.print("-");
       Serial.print(pass_U_Bound[i]);
       Serial.print(", ");
    }
    Serial.println("");
    
    int check = checkClaps(CC_L_Bound, CC_U_Bound, 3, CC_Claps);
    
    if(check == 1){
      //Empty the cc claps data
      for(int x = 0; x < 8; x++){
         pass_Claps[x] = 0;
      }
      
      //Verify that the password is long enough
      if(passLength > 5){
        passSet = 1;
        //Output the password
        Serial.println("Password Set!");        
      }else{
        Serial.println("Too few claps!");
      }
      
      //Clear the last 3 entries of the userPassword array as these are the command claps
      
      for(int x = 0; x < 5; x++){
        pass_L_Bound[x] = pass_L_Bound[x+3];
        pass_U_Bound[x] = pass_U_Bound[x+3];
      }
      
      for(int i = 0; i < passLength -3; i++){
          Serial.print(pass_L_Bound[i]);
          Serial.print("-");
          Serial.print(pass_U_Bound[i]);
          Serial.print(", ");
      }
      Serial.println("");
        
      passLength -= 3;
      
    }//Force the user's password to end if they have entered 8 claps
    else if(passLength > 10){
      passSet = 1;
      //Output the password
      Serial.println("Password Set!");
      for(int i = 0; i < passLength -3; i++){
         Serial.print(pass_U_Bound[i]);
         Serial.print("-");
         Serial.print(pass_L_Bound[i]);
         Serial.print(", ");
       }
      Serial.println("");
    }//End of forcing the password to be ended
    delay(50);
    last_clap = current_clap;
    Serial.println("");
  }//End of sound sensor reading
 }//End of password setting
}//End of Loop method
