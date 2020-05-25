/* 
 *  William Hamilton
 *  25/5/2020
 *  
 *  Lighting for Kayne's kart trailer
 *  Control front and rear internal LED lighting with a couple of momentary switches 
 *  Still to add:
 *  "f&*k I forgot to turn the lights off and the battery is now flat" timer.
 *  
 * 
 *  The circuit:
 *  Arduino powered from 12V batter source
 *  two momentary switches connected to defined below arduino pins and ground
 *  multo relay module connected to defined below arduino pins, power and ground
 *  LED strips connected via relay output to 12V batter source
 *  
 */

long front_press_length = 0;
long back_press_length = 0;

// Define the minimum length of time, in milli-seconds that the button must be pressed for a particular option to be triggered
int local_toggle_milliseconds = 100; // debounce should be covered with this time but make longer if required
int all_on_milliseconds = 2000; 
int all_off_milliseconds = 4000;        

int front_button_pin = 2;
int back_button_pin = 3;

int relay_front = 6;
int relay_back = 7;

int state_front = HIGH;
int state_back = HIGH;

float off_timer = 10000; //How long a delay before all lights are turned off (in milliseconds)
float on_time;


void setup(){

  pinMode(front_button_pin, INPUT_PULLUP);  //** NOTE - PULLUP will invert the logic but means less hardware
  pinMode(back_button_pin, INPUT_PULLUP);   //** NOTE - PULLUP will invert the logic but means less hardware
  pinMode(relay_front, OUTPUT); 
  pinMode(relay_back, OUTPUT); 
  Serial.begin(115200);   
                                    
}


void loop() {
// reset the button press timer each time around
  front_press_length = 0;
  back_press_length = 0;
  
  while (digitalRead(front_button_pin) == LOW ){ 

    delay(100);  //if you want more resolution, lower this number 
    front_press_length = front_press_length + 100;   

    //display how long button is has been held
    Serial.print("front ms = ");
    Serial.println(front_press_length);

  }

  //Record *roughly* the tenths of seconds the button in being held down
  while (digitalRead(front_button_pin) == LOW ){ 

    delay(100);  //if you want more resolution, lower this number 
    back_press_length = back_press_length + 100;   

    //display how long button is has been held
    Serial.print("back ms = ");
    Serial.println(back_press_length);

  }//close while


/*  if-else conditions to define what happens after a particular butten event and duration
 *  Start with the longest duration and work down from there.
 */
Serial.print("on_time ");
Serial.print(on_time);
Serial.println();
Serial.print("millis ");
Serial.print(millis());
Serial.println();

//turn all off
  if (front_press_length >= all_off_milliseconds || back_press_length >= all_off_milliseconds ){
    state_back = HIGH;
    state_front = HIGH;

    digitalWrite(relay_front, state_front);  
    digitalWrite(relay_back, state_back); 
    on_time = 0;
    
  } 
  
//turn all on
  else if (front_press_length >= all_on_milliseconds || back_press_length >= all_on_milliseconds){

    state_front = LOW;
    on_time = millis();
    state_back = LOW;
    on_time = millis();

    digitalWrite(relay_front, state_front);  
    digitalWrite(relay_back, state_back); 

  } 

//Local toggle - toggle the state of the relay
  else if(front_press_length >= local_toggle_milliseconds){
    if (state_front == HIGH){
      state_front = LOW;
      on_time = millis();
    }
    else{
      state_front = HIGH;
    }

    digitalWrite(relay_front, state_front);  
    Serial.print("toggle state_front");     
    Serial.print(state_front);     

  }




}
