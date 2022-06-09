## Welcome to a journey of coding and craziness.

You can use the [editor on GitHub](https://github.com/Sabutour/Jordan-McDonald-DESN2010-Blog/edit/gh-pages/index.md) to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run [Jekyll](https://jekyllrb.com/) to rebuild the pages in your site, from the content in your Markdown files.

### Markdown

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [Basic writing and formatting syntax](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax).

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

So, right now the main code loop just calls four or five functions in order, such as the Sonar detector, the wheels, etc. My group members are working on other functions (such as the moisture detection and LCD face) and I will be responsible for integrating all the code together. I’m looking forward to it!

![Image](https://media.discordapp.net/attachments/966494031918014494/973083534925365299/Screen_Shot_2022-05-09_at_2.45.34_pm.png)
_Circuit diagram for two motors and sonar module._

Thankfully I kept the wiring diagram for how to wire up the motors and the sonar module, because I really really didn’t want to have to re-figure all that out. Housing the device has fallen through a little, unfortunately. Our original plan was to create a 3D printed, custom housing for the device, and also have 3D printed caterpillar tracks for movement. However our prints have kept failing and we don’t believe we have the time to commit to it anymore. But, for posterity, here is an early concept model! Fun times!

![Image](https://i.imgur.com/f2ihtNn.jpg)
_WIP 3D model for device shell, made by Isabella Nesci._
