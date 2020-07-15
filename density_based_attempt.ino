    #include<TimerOne.h>
    int signal1[] = {23, 25, 27};
    int signal2[] = {46, 48, 50};
    int redDelay = 5000;
    int yellowDelay = 2000;
    int pirA = 31;    
    int pirB = 29;       
    volatile long time;                    // Variable for storing the time traveled
    volatile int S1, S2, S3, S4;           // Variables for storing the distance covered
    int t = 5;  // distance under which it will look for vehicles.
    void setup(){
      Serial.begin(115200);
      Timer1.initialize(100000);  //Begin using the timer. This function must be called first. "microseconds" is the period of time the timer takes.
      Timer1.attachInterrupt(softInterr); //Run a function each time the timer period finishes.
      // Declaring LED pins as output
      for(int i=0; i<3; i++){
        pinMode(signal1[i], OUTPUT);
        pinMode(signal2[i], OUTPUT);
      }
      // Declaring ultrasonic sensor pins as output
      pinMode(pirA, INPUT);
      pinMode(pirB, INPUT);
    }
    void loop()
    {
      // If there are vehicles at signal 1
      if(S1<t)
      {
        signal1Function();
      }
      // If there are vehicles at signal 2
      if(S2<t)
      {
        signal2Function();
      }
    }
    // This is interrupt function and it will run each time the timer period finishes. The timer period is set at 100 milli seconds.
    void softInterr()
    {
      delayMicroseconds(10);
      time = pulseIn(pirA, HIGH); 
      S1= time*0.034/2; 
      delayMicroseconds(10);
      time = pulseIn(pirB, HIGH); 
      S2= time*0.034/2;
      // Print distance values on serial monitor for debugging
      Serial.print("S1: ");
      Serial.print(S1);
      Serial.print("  S2: ");
      Serial.print(S2);
    }
    void signal1Function()
    {
      Serial.println("1");
      low();
      // Make RED LED LOW and make Green HIGH for 5 seconds
      digitalWrite(signal1[0], LOW);
      digitalWrite(signal1[2], HIGH);
      delay(redDelay);
      // if there are vehicels at other signals
      if(S2<t)
      {
        // Make Green LED LOW and make yellow LED HIGH for 2 seconds
        digitalWrite(signal1[2], LOW);
        digitalWrite(signal1[1], HIGH);
        delay(yellowDelay);
      }
    }
    void signal2Function()
    {
      Serial.println("2");
      low();
      digitalWrite(signal2[0], LOW);
      digitalWrite(signal2[2], HIGH);
      delay(redDelay);
      
      if(S1<t)
      {
        digitalWrite(signal2[2], LOW);
        digitalWrite(signal2[1], HIGH);
        delay(yellowDelay);   
      }
    }
    // Function to make all LED's LOW except RED one's.
    void low()
    {
      for(int i=1; i<3; i++)
      {
        digitalWrite(signal1[i], LOW);
        digitalWrite(signal2[i], LOW);
      }
      for(int i=0; i<1; i++)
      {
        digitalWrite(signal1[i], HIGH);
        digitalWrite(signal2[i], HIGH);
      }
    }
