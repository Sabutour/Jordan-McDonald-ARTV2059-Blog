## Coding and Craziness
Welcome to the blog! This blog details my haphazard and disjointed journey through DESN2010, and my insights into the projects I'm workong on for the class. Enjoy the read.

# Week 1 - Getting Started

I’m excited for this course. I’m lucky enough to say that this isn’t my first rodeo with Arduino’s and the like. It’s my second rodeo, that’s like a 100% increase in experience, right? I’m sure that’s how that works.

So, for my first blog post I figured I’d collate some resources I’m already familiar with, why they’re useful, and what I’m using them for. Sound good? Let’s get to it.

So, I’ve gone through quite a few code editors and IDEs in my time. While I’ve had good use in the past with the likes of [Atom](https://atom.io/), [IntelliJ IDEA](https://www.jetbrains.com/idea/) and others, I’ve settled on [Visual Studio Code](https://code.visualstudio.com/) as my editor of choice. It’s fast, customisable, has a ton of useful extensions and available basically everywhere. And it’s been thoroughly tested by many much much more experienced coders for years. And it has extensions to make it play nicely with the Arduino code software! All good points.

So, that’s the code editor sorted, what next? For me, when doing any sort of coding project that’s either solo or group-based, version control software is non-negotiable. It’s mission critical to have access to old versions of code, and backups. For that, like many people, I use [GitHub](github.com). I have experience with it from previous code projects, it integrates nicely with Visual Studio Code, and it has saved my code more than once. May it serve me well again for this course. And, it lets me set up this blog! The one you're reading now! Wild.

So that’s all the code taken care of, but how do we go about building our devices? Throwing some wires together and praying is all well and good, but it’s good to avoid permanently damaging all our precious components. In the past, I’ve used [TinkerCAD](tinkercad.com) as a pretty decent online Arduino wiring and code simulator. Build a circuit, upload some code, see if it works as expected! Useful! It doesn’t solve every use case, and it’s not perfect, but it can really help for testing and to share circuit diagrams quickly.

So, those are the main tools that’ll be getting me through this class! Let’s get to it.

# Week 4 - Assignment 1 Project Proposal

When I bought an Arduino starter kit (specifically the "[ELEGOO MEGA 2560 THE MOST COMPLETE STARTER KIT](https://www.amazon.com.au/ELEGOO-Complete-Ultimate-Tutorial-Mega2560/dp/B01EWNUUUA)"), my options as to what I could actually make were drastically expanded. Of the many materials included in the kit, the ones that drew my attention most immediately were the Membrane Keypad and the RFID scanner. In this digital world, inputs such as these are routinely used for security devices like safes and door locks.

![Image](https://i.imgur.com/6BijcZv.png)
_All the things that come in the kit._

However, I intend to use both of them simultaneously. Two-Factor Authentication (TFA or 2FA) is one of the most effective ways to increase the security of an online account, so I wish to apply this concept to a physical lock. My plan to two create a 2FA lock by requiring both the input of a password from the keypad alongside a specific RFID card. If either of these materials are incorrect or not present, the lock will not open.

![Image](https://i.imgur.com/lBpiIYN.png)
_The components I plan to use for my project._

That’s the general idea. I’m thinking of using two LEDs, one green and one red, to signal to the user that the code has been either accepted or denied. I’ll have to play around with it some more. It’s still in the concept phase for now. I expect to run into several problems that will slow me down or make me have to change my plans somewhat. I’m not very experienced in C++ (The programming language Arduino is based off of) and so will have to get used to syntax that isn’t JavaScript again. Any issues and I’ll ask Pia for some help. 

# Week 6 - Assignment 1 Reflection

It worked! We did it, way to go, team. A working 2FA security lock. It all came together mostly as intended. Let me run you through it.

![Image](https://i.imgur.com/eojOqmM.png)
_Final circuit diagram, made using Cirkit Designer._

As you can see from this mess of a circuit, there are multiple components: the Arduino, an RFID reader, a 4x4 keypad, and an LCD display. My original concept omitted the LCD display, as I was planning on using green and red LEDs to provide user feedback if the door was locked or unlocked. However, following some in-class feedback, I decided to be a bit more ambitious and use the display to provide more detailed feedback to the user. I think it was a good idea overall. Cheers Pia.

![Image](https://i.imgur.com/duWGzDk.jpg)
_Final construction. Mind the mess._

The physical construction is much more messy, but hey, it’s a proof of concept. So, how did the final code end up? Actually more complicated than originally intended because of one reason: My ambition. But I’m getting ahead of myself, how does it actually work?

Well, it’s a two stage lock that has to be completed in a specific order. The user has to provide their keycard to the reader. The code searches for the specific user that matches the ID on the card, then waits for their passcode. If the passcode also matches the user, access is temporarily granted, then locked again. (No actual lock or motor is moved, as I wanted to focus on the security part and didn’t want to do everything).

Early code prototypes were much more simple to code, but had a fatal flaw in that it was the least secure lock ever. Originally, any valid passcode could be mixed and matched with any valid keycard. Not good. I had foolishly assumed it was a simple task to make a custom User class, give them a passcode and ID variable and then go from there. 

Nope! JavaScript this is not. I had to write a broken little custom library and include it just to get this idea to work at all, and even then it was janky. But I got there, and I learnt a bit about C, so that’s cool. 

So, what would I change?

Well, I’d give it a proper chassis for one. But in terms of code logic, a classmate actually made me realise during the class demonstration that I forgot something. If a user taps their passcard, that ID is stored on the lock indefinitely, until a passcode is entered. Really I should’ve implemented a timer that times it out and resets the lock. Also, Pia suggested more instruction to the user on how to use the lock. That the ‘#’ key clears the passcode entry and that the ‘*’ key enters it. I was used to this setup from other actual passcode locks, but I shouldn’t have assumed, documentation is always useful.

Either way, I really enjoyed this project, and feel much more comfortable working with more Arduino components now.

# Week 7 - Assignent 2 Prep and Concept

Group project time! Group projects are always a mixed bag, but I’ve been very lucky with them during my time as an ANU student so far. This is no exception! I’m on very good terms with my entire group and we enjoy working with and collaborating with each other. 

As for our plans overall, all of us are intrigued by the idea of meshing plant and robot together into some kind of WALL-E-esque plant tank thing. Fun!

![Image](https://i.imgur.com/4WX97q1.png)
_Our Miro board of ideas and brain-storming._

What does that mean? Well, by plant tank, I mean a mobile platform that allows for a potted plant to travel around of its “own accord” based on certain parameters. Parameters you say?

What does a plant need?

- Water
- Sunlight
- Nutrients
- Love
- Affection
- ~~World Domination~~

So, our concept is to help a plant attain these things. A plant robot that tells it’s owner what it needs, how to care for it, and injects a little personality into it. That’s the concept anyway.

![Image](https://i.imgur.com/vWyazBq.png)
_Adorable concept art by Isabella Nesci._

Like all good projects, we don’t expect to achieve all of our goals, and that this project will change shape quite a lot by the time of the final submission.

But for now, my job is to help with the mobility and logic of the plant. The tank part I guess. I actually have some experience in this field! Some years ago I was part of an Arduino project to make a robot that could solve and drive through a maze! It was a fun project that Covid made very very difficult. But, thanks to GitHub (see first blog post) I still have that code and those wiring diagrams! 

So, my plan is to go through this code and take what useful functions I can. No point reinventing my own wheel. Obviously not all of it will be applicable, but the basic driving functions I wrote, and the object avoidance ones, will be invaluable to this project.

# Week 9 - Progress on Plant Robot

Alright! Progress report.

We’ve been working through the robot as a group. Would you believe that making a robot is a difficult task with lots of complex problems to solve and can’t just be done in 10 minutes? Wild I know. It’s almost like it takes millions of dollars and hundreds of engineers and programmers and [good dance moves](https://www.youtube.com/watch?v=fn3KWM1kuAw).

But, still, we’ve been busy. I’ve spent many hours rewriting my old maze-solving code to be better. Rereading code that’s several years old was a chore. It was commented reasonably well, but even I can tell how terribly and inefficiently it was written. So I went back through and redid most of it, focusing on readability and modularity.

I am a big proponent of splitting almost everything into component functions that can be edited separately and either called or not as needed. Makes testing much easier when you can just not call a certain function instead of commenting out a huge portion of the main code loop.

```
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
  ```
  _Code excerpt from main file. Author me._

So, right now the main code loop just calls four or five functions in order, such as the Sonar detector, the wheels, etc. My group members are working on other functions (such as the moisture detection and LCD face) and I will be responsible for integrating all the code together. I’m looking forward to it!

![Image](https://media.discordapp.net/attachments/966494031918014494/973083534925365299/Screen_Shot_2022-05-09_at_2.45.34_pm.png)
_Circuit diagram for two motors and sonar module._

Thankfully I kept the wiring diagram for how to wire up the motors and the sonar module, because I really really didn’t want to have to re-figure all that out. Housing the device has fallen through a little, unfortunately. Our original plan was to create a 3D printed, custom housing for the device, and also have 3D printed caterpillar tracks for movement. However our prints have kept failing and we don’t believe we have the time to commit to it anymore. But, for posterity, here is an early concept model! Fun times!

![Image](https://i.imgur.com/f2ihtNn.jpg)
_WIP 3D model for device shell, made by Isabella Nesci._

So, we’ll need to come up with an alternate solution. It might not be pretty, but we hope it’ll be functional. Alright, back to work! See you next post.

# Week 12 - Taking Stock

Okay, ride or die time. The presentation is tomorrow. Consider this post a snapshot of where we're at. There's quite a bit to catch up on since my last post. A lot has had to come together in a very short time and even now there are still some problems we need to solve, but I think we're going to be okay.

![Image](https://i.imgur.com/C3o3SMX.gif)
_Face concepts by Isabella Nesci_

So, let's start with some cool stuff. Group member Emily James has done great work turning a 4 digit 7 segment LCD display into an adorable little face (see concept art above.) But we ran into a really interesting and unexpected issue with the LCD display. See, it does not light up each digit at the same time. Rather, it lights each digit one at a time, very quickly so that the eye doesn't notice the delay. This was problematic as once this face code was added to the main Arduino loop that includes sonar and driving code, the runtime of that extra code was enough to slow down the LCD refresh rate and completely broke the effect. 

![Image](https://media.discordapp.net/attachments/966494031918014494/975619529168277524/unknown.png)
_Legend of pin numbers for 4 digit 7 segment LCD Display._

Our solution? Two Arduinos! That's right, this baby is a dual core! Also, behold our amazing and makeshift shell for the device. After our 3D casing failed we resorted to a wooden box with cutouts for wires and the sonar module. It works, but unfortunately not pretty, but a prototype is a prototype. Anyway, dual core! Using the Arduino Wire library we have a main board that runs the majority of the code (Moisture Sensor, Sonar, Movement, etc) and the second board is only running the Face code. Board 1 makes note of the current state of the robot (HAPPY, SAD, BORED, etc) and sends this to Board 2 in the form of a single digit int. 

![Image](https://media.discordapp.net/attachments/966494031918014494/979090328399282266/PXL_20220525_183158377.MP.jpg?width=1776&height=1332)
_Our beautiful robot._

```
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
  ```
_Code excerpt. from the main file, transmits state to Board 2. Author me._
  
So yeah. One interesting and difficult problem solved by a fun and sorta rediculous solution. I love it! There is currently another issue that we're having and that is that the motors we have for the wheels seem to be broken. They're rather old ones that have had use before, and they seem to not handle charge properly. A set of replacement batteries were procured by group member Jonathon Hanlon but these likewise seemed to not work. As the presentation is tomorrow, this is a concern. Group member Emily is going to try and pick some up tomorrow morning before class, but it's likely going to be a late night.

# Week 14 - Reflections

Its...its done. The presentation, the robot. It's finished. I almost can't believe it.
  
Okay, I may be getting ahead of myself. The presentation has been completed, yes, but the assignment not yet. But boy is this going to be a finale of a blog post.
  
 So, full disclosure, I am overtired. Wayyy overtired. Group member Emily James and I had a very long night getting our robot fully ready for the presentation. Due to a whole series of issues that we had (see last post), we did not get to bed until about 5am. The presentation was at 9am the next morning. Not much sleep at all. Now I see how Crunch Time is such a pervasive issue in the programming world.
  
But I digress. We pushed through the night fixing issues one at a time. The LCD display issue which required dual core Arduinos, the motors (Emily had to go buy new motors the morning of and then we Blu-Tac'ed them onto the robot just before the presentation, which worked!) and issues with the microphone's sensitivity. If we had a few days to do all of this it would have been fine but all in one night (a 14 hour session) was a lot. Thankfully Emily was incredibly helpful and I found our collaboration invaluable in getting through it. Kudos Emily. Kudos.
  
So, what about the presentation? It went rather well! Our entire group presented together and our robot was firing on pretty much all cylinders. We showed up all of the functionality (moisture detection, sound detections, emotions with faces and behaviours, and movement) and they all worked as intended which was very gratifying to see after so much work. And we got some lovely feedback and reactions from Pia and the rest of the class. Several classmates provided audible "awwwws" when the robot was scared which smashed our goal of making a user create an emotional, protective connection with it. Great to see.
  
Obviously the very rag-tag nature of the robot's construction was brought up (literally held together with Blu-Tac in part) but we explained the issues we ran into with 3D printing and what our intentions were. They were understanding.
  
So where does this leave the project? Well, at a hair shy of 1000 lines of code (split across the [PLANT-OS](https://github.com/Sabutour/Jordan-McDonald-DESN2010-Blog/blob/main/PLANT_OS.ino) file and the [FACE-OS](https://github.com/Sabutour/Jordan-McDonald-DESN2010-Blog/blob/main/FACE_OS.ino) file) it's not a small bit of work for us. It accomplished the main feature set we focused on, and we all had a great time working on it. I myself learnt a ton about programming and Arduinos and I would love to work on this project further outside of class. It's sort of reignited my passion for fun, personal projects. Maybe I'll keep this blog updated after the fact. Haha, maybe.
  
  - Jordan
