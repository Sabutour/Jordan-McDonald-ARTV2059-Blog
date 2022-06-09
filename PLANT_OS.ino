// PLANT OS - BOARD 1
// Plant-based eLectronically Assisted Near Traveller
// Version Number: Alpha 1
// Programmers: Jordan McDonald, Emily James, Jonathon Hanlon, Izzy Nesci
// Date of last edit: 07/6/2022

// INCLUDED LIBRARIES

#include <Wire.h>

// GLOBAL VARIABLES

  // MOTORS

    // Pin numbers for motor one.
    const int enablePin1 = 9; // Must have high power for motor one (left) to function.
    const int motorPin1A = 4;
    const int motorPin2A = 3;

    // Pin numbers for motor two.
    const int enablePin2 = 10; // Must have high power for motor two (right) to function.
    const int motorPin3A = 6;
    const int motorPin4A = 5;

  // SONAR

    // Pin numbers for sonar sensor.
    const int trigPin = 22;
    const int echoPin = 24;

    // How many measurements the sonar makes in each set of pings to measure distance.
    int sonarPings = 3;

    // The distance in cm before the platform will stop to avoid a direct obstacle.
    int triggerDistance = 12;

  // MOISTURE

    // Pin number for the moisture reader
    const int moisturePin = A3;

    // The current moisture level of the plant.
    int moistureLevel;

  // MICROPHONE
  
    // Pin numbers for microphone
    const int microphonePin = A0;

    // Adjustable sensitivity level for the SoundReact function.
    int microphoneSensitivity = 2;

  // STATE MACHINE

    // Current state of state machine.
    State currentState;
    State savedState;

    // Possible states for the state machine.
    enum State
    {
      SURPRISED,
      HAPPY,
      HAPPYALT,
      SAD,
      SADALT,
      CONTENT,
      BORED
    };


// CODE BEGINS

  // Quick setup output showing version number, etc. Mostly for flavour.
  void initialisation()
  {
    Serial.println("Initialising...");
    Serial.println("P.L.A.N.T OS");
    Serial.println("Plant-based eLectronically Assisted Near Traveller OS");
    Serial.print("Version Number: ");
    Serial.println(versionNumber);
    Serial.println("Programmer/s: Jordan McDonald, Emily James, Jonathon Hanlon, Izzy Nesci");
  }

  // Main setup loop. Starts the Serial Monitor, begins data transfer with FaceManager 
  // Board, makes sure the motors are ready, and sets everything to a default state.
  void setup()
  {
    Serial.begin(9600);

    initialisation();

    Wire.begin(); 

    Serial.print("Initialising motor 1...");
    pinMode(enablePin1, OUTPUT);
    pinMode(motorPin1A, OUTPUT);
    pinMode(motorPin2A, OUTPUT);
    digitalWrite(enablePin1, LOW);
    Serial.println("Done!");

    Serial.print("Initialising motor 2...");
    pinMode(enablePin2, OUTPUT);
    pinMode(motorPin3A, OUTPUT);
    pinMode(motorPin4A, OUTPUT);
    digitalWrite(enablePin2, LOW);
    Serial.println("Done!");

    Serial.print("Initialising sonar sensor...");
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
    Serial.println("Done!");

    Serial.print("Setting initial State...");
    currentState = CONTENT;
    Serial.println("Done!");

    Serial.println("Initialisation complete.");
  }

  // Main repeated code loop. First checks for sounds, then updates the state machine,
  // sends that update to FaceManager Board, then checks moisture. These functions have been
  // split up for modularity and for easier debugging (able to turn off whole functions
  // to check what is causing a possible issue.)
  void loop()
  {
    SoundReact();
    stateMachine();
    Transmitter();
    MoistureReader();
  }

  // CORE FUNCTION
  // Sends the current state information to the FaceManager board.
  void Transmitter() {
    Serial.print("State = ");
    Serial.println(currentState);
    Serial.println("Transmitting");
    Wire.beginTransmission(9);      // transmit to device #9
    Wire.write(currentState);       // sends currentState 
    Wire.endTransmission();         // stop transmitting
    delay(500);
  }
  
  // CORE FUNCTION
  // Reads the plant moisture and sends data to the state machine.
  void MoistureReader()
  {
    // read the input on analog pin 0
    int sensorValue = analogRead(moisturePin);  // Reads the input of the moisture sensor (0-1023)
    int timeSince = millis() / 1000;            // This is a second counter, it gets reset if the values below aren't met

    if (sensorValue < 255 && timeSince > 60)
    { // No water during last 60 seconds.
      moistureLevel = 0;
    }
    else if (sensorValue < 255 && timeSince > 10)
    { // No water during last 10 seconds
      moistureLevel = 1;
    }
    else if (sensorValue > 765 && timeSince > 20)
    { // Reading too much water
      moistureLevel = 3;
    }
    else
    { // Water level good
      moistureLevel = 2;
      timeSince = 0;
    }

    switch (moistureLevel)
    {
    case 0: // SAD
      currentState = BORED;
      Serial.print("In dire need of water.");
      break;
    case 1: // 
      currentState = SAD;
      Serial.print("In mild need of water.");
      break;
    case 2: // CONTENT
      currentState = HAPPY;
      Serial.print("Water levels geeen.");
      break;
    case 3: // SURPRISED
      currentState = SURPRISED;
      Serial.print("Too much water.");
      break;
    }
  }

  // CORE FUNCTION
  // Reacts to loud noises and makes the plant enter SURPRISED state temporarily.
  void SoundReact()
  {
    Serial.println("Checking sounds.");
    int mn = 1024;
    int mx = 0;

    for (int i = 0; i < 100; ++i)
    {
      int val = analogRead(microphonePin);

      mn = min(mn, val);
      mx = max(mx, val);
    }

    int delta = mx - mn;

    Serial.print("Delta = ");
    Serial.println(delta);

    if (delta > microphoneSensitivity)
    { // sensitivity
      savedState = currentState;
      currentState = SURPRISED;
      Transmitter();  // Immediately updates the FaceManager board.
      Serial.println("Sound Detected");
      delay(10);
    }
  }

  // CORE FUNCTION
  // Changes the plant state based on current data and makes robot act accordingly.
  void stateMachine()
  {
    switch (currentState)
    {
    // CONTENT State
    // When content, the Plant will sit in place and not move.
    case CONTENT:
      Serial.println("");
      Serial.println("Current State: CONTENT");
      break;

    // BORED State
    /* When bored, the Plant will drive around looking for things. It
    will avoid obstacles and drive in random paths. */
    case BORED:
      // Serial.println("");
      // Serial.println("Current State: BORED");

      motorReset();
      if (getDistance() < triggerDistance)
      {
        avoidObstacle();
      }
      else if (getDistance() > triggerDistance)

      {
        bothForwardsForTime(2000);
      }
      break;

    // SAD State
    // When sad, the plant will sit in place and look sad.
    case SAD:
      Serial.println("");
      Serial.println("Current State: CONTENT");
      break;

    // HAPPY State
    /* When happy, the Plant will do a little dance. */
    case HAPPY:
      // Serial.println("Current State: HAPPY");

      int x = random(1000, 3000);

      turnLeft(x);

      int y = random(1, 3000);

      turnRight(y);
      break;

    // SURPRISED STATE
    /* When surprised, the Plant will stop, make a face, and turn around,
    then return to it's previous state. */
    case SURPRISED:
      motorReset();
      delay(1000);
      turnLeft(500);
      turnRight(1000);
      turnLeft(3000);
      currentState = savedState;
      break;
    }
  }

  // HELPER FUNCTION
  // Determines the distance of an object in front of the sonar.
  int getDistance()
  {

    // Array of three sensor outputs
    int sonarArray[sonarPings];

    long duration;
    int distance;

    // Clears the trigPin.
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Saves the last three detected elements to an array to be processed. The array is overwritten
    // from one loop to the next to prevent high memory usage as values before the last three are not needed.
    for (int i = 0; i < sonarPings; i++)
    {
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      // Reads the echoPin, returns the sound wave travel time in microseconds.
      duration = pulseIn(echoPin, HIGH);

      // Calculates the distance (in cm).
      distance = duration * 0.0345 / 2;

      sonarArray[i] = distance;

      delay(1);
    }

    // Built in function to sort the last three sonar measurements into ascending order.
    qsort(sonarArray, sonarPings, sizeof(int), compare);

    // Takes the median of the last three sonar measurements.
    int distanceMedian = sonarArray[1];

    // Prints the distance on the Serial Monitor.
    Serial.print("Distance Median (CM): ");
    Serial.println(distanceMedian);

    return distanceMedian;
  }

  // HELPER FUNCTION
  // sorts an array in ascending order using qsort.
  int compare(const void *a, const void *b)
  {
    return (*(int *)a - *(int *)b);
  }

  // MOTOR FUNCTIONS

    // HELPER FUNCTION
    // Resets all motors to off. Disables all enable pins and motor pins.
    void motorReset()
    {
      Serial.println("Resetting Motors...");
      digitalWrite(enablePin1, LOW);
      digitalWrite(enablePin2, LOW);

      delay(50);

      digitalWrite(motorPin1A, LOW);
      digitalWrite(motorPin2A, LOW);
      digitalWrite(motorPin3A, LOW);
      digitalWrite(motorPin4A, LOW);
    }

    // HELPER FUNCTION
    // Logic that tells the robot how to drive in such a way to
    // avoid it and drive either around or away from it.
    void avoidObstacle()
    {
      motorReset();
      Serial.print("Checking left...");
      turnLeft(2050);
      if (getDistance() > triggerDistance)
      {
        Serial.println("Path clear.");
      }
      else
      {
        Serial.println("Path blocked. Checking right...");

        turnRight(2050);
        turnRight(2050);

        if (getDistance() > triggerDistance)
        {
          Serial.println("Path clear.");
        }
        else
        {
          Serial.println("Path blocked. Back the way we came.");

          turnRight(2050);

          if (getDistance() > triggerDistance)
            ;
          {
            Serial.println("Path clear.");
          }
        }
      }
    }

    // HELPER FUNCTION
    // Sets the rover to drive forwards for a specified amount of time in milliseconds.
    void bothForwardsForTime(int timeDrive)
    {
      Serial.println("Full ahead.");
      digitalWrite(enablePin1, HIGH);
      digitalWrite(enablePin2, HIGH);

      digitalWrite(motorPin1A, HIGH);
      digitalWrite(motorPin3A, HIGH);

      delay(timeDrive);
      motorReset();
    }

    // HELPER FUNCTION
    // Sets the rover to drive forwards continuously.
    // Use this when needing to be interrupted by obstacle avoidance.
    void LockForwards()
    {
      Serial.println("Locking forwards.");
      digitalWrite(enablePin1, HIGH);
      digitalWrite(enablePin2, HIGH);

      digitalWrite(motorPin1A, HIGH);
      digitalWrite(motorPin3A, HIGH);
    }
    
    // HELPER FUNCTION 
    // Sets the rover to drive forwards for a specified amount of time in milliseconds.
    void bothBackwardsForTime(int timeDrive)
    {
      Serial.println("Full reverse.");
      digitalWrite(enablePin1, HIGH);
      digitalWrite(enablePin2, HIGH);

      digitalWrite(motorPin2A, HIGH);
      digitalWrite(motorPin4A, HIGH);

      delay(timeDrive);
      motorReset();
    }

    // HELPER FUNCTION
    // Turns the rover left for a specified amount of time in milliseconds.
    void turnLeft(int timeDrive)
    {
      Serial.println("Turning left.");
      digitalWrite(enablePin1, HIGH);
      digitalWrite(enablePin2, HIGH);

      delay(500);

      digitalWrite(motorPin1A, HIGH);
      digitalWrite(motorPin4A, HIGH);

      delay(timeDrive);
      motorReset();
    }

    // HELPER FUNCTION
    // Turns the rover right for a specified amount of time in milliseconds.
    void turnRight(int timeDrive)
    {
      Serial.println("Turning right.");
      digitalWrite(enablePin1, HIGH);
      digitalWrite(enablePin2, HIGH);

      delay(500);

      digitalWrite(motorPin2A, HIGH);
      digitalWrite(motorPin3A, HIGH);

      delay(timeDrive);
      motorReset();
    }