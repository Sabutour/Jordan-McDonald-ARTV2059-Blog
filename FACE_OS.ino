// FACE OS - BOARD 2
// Fairly Automatic Controller of Expressions OS
// Version Number: Alpha 1
// Programmer: Jordan McDonald, Emily James, Jonathon Hanlon, Izzy Nesci
// Date of last edit: 07/6/2022

// LCD DISPLAY PIN DIAGRAM

    /*
        A
       ---
    F |   | B
      | G |
       ---
    E |   | C
      |   |
       ---
        D
    */

// INCLUDED LIBRARIES

#include <Wire.h>

// GLOBAL VARIABLES

    // LCD DISPLAY

        // Pins 1-8 each relate to a specific segment on the display (pictured above A-G)

        int pinA = 2;
        int pinB = 3;
        int pinC = 4;
        int pinD = 5;
        int pinE = 6;
        int pinF = 7;
        int pinG = 8;

        // Pins 9-12 each relate to a specific digit on the display

        int D4 = 9;
        int D3 = 10;
        int D2 = 11;
        int D1 = 12;

    // EXPRESSION VARIABLES

        // Disables certain functions while the face is blinking
        bool isBlinking = false;

        // Number variable for current expression.
        // 0 = CONTENT,
        // 1 = HAPPY,
        // 2 = HAPPYALT
        // 3 = SAD
        // 4 = SADALT
        // 5 = SURPRISED
        // 6 = BORED
        int currentExpression = 0; 

        int eyes = 0;
        int mouth = 0;

    // BLINK VARIABLES

        int t = 0;                  // continually counts up, used to control timing of blink
        int t2 = 0;                 // saves time at a specific point
        int ran = random(100, 500); // variable to allow a non-regular amount of time between blinks

        int s = 0;

        int LED = 13;
        int x = 0;
        String y;

    
    // CODE BEGINS

        // Main setup loop. Starts the Serial Monitor, begins data transfer with FaceManager 
        // Board, makes sure the motors are ready, and sets everything to a default state.
        void setup()
        {
            // Define the LED pin as Output
            pinMode(LED, OUTPUT);
            // Start the I2C Bus as Slave on address 9
            Wire.begin(9);
            // Attach a function to trigger when something is received.
            Wire.onReceive(receiveEvent);
            Serial.begin(9600);

            // set the digital pins as outputs.
            pinMode(pinPt, OUTPUT);
            pinMode(pinA, OUTPUT);
            pinMode(pinB, OUTPUT);
            pinMode(pinC, OUTPUT);
            pinMode(pinD, OUTPUT);
            pinMode(pinE, OUTPUT);
            pinMode(pinF, OUTPUT);
            pinMode(pinG, OUTPUT);
            pinMode(D1, OUTPUT);
            pinMode(D2, OUTPUT);
            pinMode(D3, OUTPUT);
            pinMode(D4, OUTPUT);
        }

        // CORE LOOP
        void loop()
        {
            blinkManager();
            faceManager();
            eyeManager();
            mouthManager();
        }

        // HELPER FUNCTION
        // Receives state information from Board 1, updates to match.
        void receiveEvent(int bytes)
        {
            currentExpression = Wire.read(); // read one character from the I2C
            Serial.println("Receiving");
        }

        // DEMO FUNCTION
        // Demo that cycles through all the faces.
        void demoFace {

             s++;
             Serial.println(s);
            
             if ( s > 100 && s < 200){
               currentExpression = 0;
             } else if ( s > 200 && s < 300){
               currentExpression = 1;
             } else if ( s > 300 && s < 400){
               currentExpression = 2;
             } else if ( s > 400 && s < 500){
               currentExpression = 3;
             } else if ( s > 500 && s < 600){
               currentExpression = 4;
             } else if ( s > 600 && s < 700){
               currentExpression = 5;
             } else if ( s > 700 && s < 800){
               currentExpression = 6;
               s = 0;
             }
        }

        // CORE FUNCTION
        // A constantly-running function that makes the face blink
        // every now and then at pseudo-random intervals.
        void blinkManager() {
            // Serial.println(ran);  // random number (time between blinks random)
            t++; // basic timer
            if (t > 2200)
            { // if timer goes too high it resets
                t = 0;
            }

            Serial.println(t);

            if (t == ran)
            {           // when the timer reaches the random number
                t2 = t; // save the time as t2 (t keeps going up)
            }

            if (t > ran)
            {
                Serial.println("Huh");

                if (t > t2 && t < t2 + 20 && eyes == 0 && !isBlinking)
                { // when the random number is reached close eyes
                    Serial.println("Blinking.");
                    isBlinking = true;
                    eyes = 1; // close eyes
                }
                else if (t > t2 + 50 && isBlinking)
                {    
                    Serial.println("Stop blink.");                       // when it's been a little more time, open eyes again
                    eyes = 0;               // open eyes
                    t = 0;                  // reset t to 0
                    ran = random(100, 2000); // choose another random number
                    isBlinking = false;
                }
            }
        }

        // CORE FUNCTION
        // Switches the current expression based on data received from Board 1.
        void faceManager() {
            if (isBlinking == false)
            {
                switch (currentExpression)
                { 
                // CONTENT
                case 0:
                    eyes = 0;
                    mouth = 1;
                    break;

                // HAPPY
                case 1:
                    eyes = 2;
                    mouth = 0;
                    break;

                // HAPPYALT
                case 2:
                    eyes = 0;
                    mouth = 0;
                    break;

                // SAD
                case 3:
                    eyes = 3;
                    mouth = 4;
                    break;

                // SADALT
                case 4:
                    eyes = 0;
                    mouth = 4;
                    break;

                // SURPRISED
                case 5:
                    eyes = 1;
                    mouth = 3;
                    break;

                // BORED    
                case 6:
                    eyes = 3;
                    mouth = 0;
                    break;
                }
            }
        }

        // CORE FUNCTION
        // Renders the selected eyes based on data received by the faceManager.
        void eyeRenderer() {
            // note: in D1-4 "low" means on, in the pins "low" means off

            if (eyes == 0)
            { // open eyes

                digitalWrite(D1, LOW);
                digitalWrite(D2, HIGH);
                digitalWrite(D3, HIGH);
                digitalWrite(D4, LOW);

                digitalWrite(pinPt, LOW);
                digitalWrite(pinA, HIGH);
                digitalWrite(pinB, HIGH);
                digitalWrite(pinC, HIGH);
                digitalWrite(pinD, HIGH);
                digitalWrite(pinE, HIGH);
                digitalWrite(pinF, HIGH);
                digitalWrite(pinG, LOW);
                delay(1);
            }

            if (eyes == 1)
            { // closed eyes

                digitalWrite(D1, LOW);
                digitalWrite(D2, HIGH);
                digitalWrite(D3, HIGH);
                digitalWrite(D4, LOW);

                digitalWrite(pinPt, LOW);
                digitalWrite(pinA, LOW);
                digitalWrite(pinB, LOW);
                digitalWrite(pinC, LOW);
                digitalWrite(pinD, LOW);
                digitalWrite(pinE, LOW);
                digitalWrite(pinF, LOW);
                digitalWrite(pinG, HIGH);
                delay(1);
            }

            if (eyes == 2)
            { // happy eyes

                digitalWrite(D1, LOW);
                digitalWrite(D2, HIGH);
                digitalWrite(D3, HIGH);
                digitalWrite(D4, LOW);
                // 2
                digitalWrite(pinPt, LOW);
                digitalWrite(pinA, HIGH);
                digitalWrite(pinB, HIGH);
                digitalWrite(pinC, LOW);
                digitalWrite(pinD, LOW);
                digitalWrite(pinE, LOW);
                digitalWrite(pinF, HIGH);
                digitalWrite(pinG, LOW);
                delay(1);
            }

            if (eyes == 3)
            { // sad eyes

                digitalWrite(D1, LOW);
                digitalWrite(D2, HIGH);
                digitalWrite(D3, HIGH);
                digitalWrite(D4, LOW);

                digitalWrite(pinPt, LOW);
                digitalWrite(pinA, LOW);
                digitalWrite(pinB, HIGH);
                digitalWrite(pinC, LOW);
                digitalWrite(pinD, LOW);
                digitalWrite(pinE, LOW);
                digitalWrite(pinF, HIGH);
                digitalWrite(pinG, HIGH);
                delay(1);
            }

        }

        // CORE FUNCTION
        // Renders the selected mouth based on data from the faceManager.
        void mouthRenderer() {

            if (mouth == 0)
            { // Happy mouth

                digitalWrite(D1, HIGH); // left
                digitalWrite(D2, LOW);
                digitalWrite(D3, HIGH);
                digitalWrite(D4, HIGH);

                digitalWrite(pinPt, LOW);
                digitalWrite(pinA, LOW);
                digitalWrite(pinB, LOW);
                digitalWrite(pinC, LOW);
                digitalWrite(pinD, HIGH);
                digitalWrite(pinE, HIGH);
                digitalWrite(pinF, LOW);
                digitalWrite(pinG, LOW);
                delay(1);

                digitalWrite(D1, HIGH); // right
                digitalWrite(D2, HIGH);
                digitalWrite(D3, LOW);
                digitalWrite(D4, HIGH);

                digitalWrite(pinPt, LOW);
                digitalWrite(pinA, LOW);
                digitalWrite(pinB, LOW);
                digitalWrite(pinC, HIGH);
                digitalWrite(pinD, HIGH);
                digitalWrite(pinE, LOW);
                digitalWrite(pinF, LOW);
                digitalWrite(pinG, LOW);
                delay(1);
            }

            if (mouth == 1)
            { // neutral down

                digitalWrite(D1, HIGH); // left & right
                digitalWrite(D2, LOW);
                digitalWrite(D3, LOW);
                digitalWrite(D4, HIGH);
                // 1
                digitalWrite(pinPt, LOW);
                digitalWrite(pinA, LOW);
                digitalWrite(pinB, LOW);
                digitalWrite(pinC, LOW);
                digitalWrite(pinD, HIGH);
                digitalWrite(pinE, LOW);
                digitalWrite(pinF, LOW);
                digitalWrite(pinG, LOW);
                delay(1);
            }

            if (mouth == 2)
            { // neutral middle

                digitalWrite(D1, HIGH); // left & right
                digitalWrite(D2, LOW);
                digitalWrite(D3, LOW);
                digitalWrite(D4, HIGH);

                digitalWrite(pinPt, LOW);
                digitalWrite(pinA, LOW);
                digitalWrite(pinB, LOW);
                digitalWrite(pinC, LOW);
                digitalWrite(pinD, LOW);
                digitalWrite(pinE, LOW);
                digitalWrite(pinF, LOW);
                digitalWrite(pinG, HIGH);
                delay(1);
            }

            if (mouth == 3)
            { // suprised mouth

                digitalWrite(D1, HIGH); // left
                digitalWrite(D2, LOW);
                digitalWrite(D3, HIGH);
                digitalWrite(D4, HIGH);

                digitalWrite(pinPt, LOW);
                digitalWrite(pinA, HIGH);
                digitalWrite(pinB, LOW);
                digitalWrite(pinC, LOW);
                digitalWrite(pinD, HIGH);
                digitalWrite(pinE, HIGH);
                digitalWrite(pinF, HIGH);
                digitalWrite(pinG, LOW);
                delay(1);

                digitalWrite(D1, HIGH); // right
                digitalWrite(D2, HIGH);
                digitalWrite(D3, LOW);
                digitalWrite(D4, HIGH);

                digitalWrite(pinPt, LOW);
                digitalWrite(pinA, HIGH);
                digitalWrite(pinB, HIGH);
                digitalWrite(pinC, HIGH);
                digitalWrite(pinD, HIGH);
                digitalWrite(pinE, LOW);
                digitalWrite(pinF, LOW);
                digitalWrite(pinG, LOW);
                delay(1);
            }

            if (mouth == 4)
            { // sad mouth

                digitalWrite(D1, HIGH); // left
                digitalWrite(D2, LOW);
                digitalWrite(D3, HIGH);
                digitalWrite(D4, HIGH);

                digitalWrite(pinPt, LOW);
                digitalWrite(pinA, LOW);
                digitalWrite(pinB, LOW);
                digitalWrite(pinC, LOW);
                digitalWrite(pinD, LOW);
                digitalWrite(pinE, HIGH);
                digitalWrite(pinF, LOW);
                digitalWrite(pinG, HIGH);
                delay(1);

                digitalWrite(D1, HIGH); // right
                digitalWrite(D2, HIGH);
                digitalWrite(D3, LOW);
                digitalWrite(D4, HIGH);

                digitalWrite(pinPt, LOW);
                digitalWrite(pinA, LOW);
                digitalWrite(pinB, LOW);
                digitalWrite(pinC, HIGH);
                digitalWrite(pinD, LOW);
                digitalWrite(pinE, LOW);
                digitalWrite(pinF, LOW);
                digitalWrite(pinG, HIGH);
                delay(1);
            }
        }

        