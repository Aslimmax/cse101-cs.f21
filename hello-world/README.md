### A simple test assignment

This simple assignment gives you the basic template for how assignments and tests will be set up.
I have already solved this assignment, but you may want to play around with the code. You may find this code (like the Makefile, I/O) useful for further assignments. Feel free to copy this code for further assignments.


### Fire a terminal to understand the structure

Go the the Tools menu item, and click on "Terminal". This gives you access to your own personal Linux box, configured 
specifically for this assignment. It is best to do as much as possible through the command line.

All the action happens in the "workspace" folder. In that folder, you will see the following:

**hello.pdf**: This file contains instructions for the assignment. In all assignments, you will find such a file. Click on it to open it in your browser. Read through the instructions carefully.

**Hello/**: This folder contains the solution. In future assignments, there will always be a specific folder titled with the assignment name. Often, this folder will be preloaded with test inputs and outputs, to test your solution. You must write your solution code in this folder.

**checkcode.sh**: *This is very important!* This is a script to do some basic checks on your solution. You can run it as "./checkcode.sh", in terminal (while you're in the workspace folder). I recommend that you keep a separate terminal open, where you only run this command.

The command produces console output that explains the checks. If it finally ends with "PASS", this means your solution passed the tests. This does not guarantee that your code is correct, or that you will get any points. But if your code does not pass the test, you will not get any points when you submit.

**README.md**: That is the file you're reading right now :) You can click on this file, to get a tab with this. Again, keep this open for your convenience.

**RoboGrader/**: This has my checking and testing scripts. Do not modify anything here!

### Coding

Ideally, you should code directly through the command line, using an editor like vi or vim. Alternately, you can upload files directly. Go to the File menu, and click on "Upload".  But pleae compile your codes through the command line, and make sure everything runs in the Codio box. There is no guarantee that code compiled on your machine works on the Codio box (often, because of incompatible OSes or text editors introducing strange symbols, etc.) We will be testing your code directly in the Codio box, so ensure that you compile codes here.  Please use the checkcode.sh script to ensure everything is running. A significant part of grading is automated, so it is essential that you follow these rules.
  
Even if you're not familiar with Unix, I highly recommend sticking to the command line. You will get better at it, and it will help you greatly in the long run.

Formally, Codio is providing a "container" (similar to a virtual machine), which provides the illusion of a full fledged operating system. From your standpoint, think of each Codio box (for every assignment) as a fresh computer, provided just for that assignment. The different Codio boxes are completely independent of each other. Only you and me (the instructor) has access to this machine. In reality, each of these boxes is hosted in the cloud.

### Editing files in Codio

As I said earlier, the best method is through the terminal, using an editor like vi or vim. Alternately, you can click on a file in the left pane, and you will get a tab with the file. You can directly edit the file in that tab. While the editor is decent, sometimes changes you make do not immediately update the file in the actual container (stored on the cloud). (What you see in the editor tab is stored in your browser, which periodically syncs with the cloud.) To force an update, click on the small double arrow icon in the left pane, right above the file tree. That will force all updates. If you are editing your code through the tabs as described above, please click on that icon before you compile your code (just to be on the safe side).


### More Codio Details 

Codio is really cool! You get an easily configurable personal box that you have full control over. Feel free to play around with it. Some details from Codio below.

#### GUI Applications and the Virtual Desktop 
The Virtual Desktop allows you auto develop GUI based applications using any programming language. You can install a Virtual Desktop in your Box. You can then start the desktop and view it within the Codio IDE or in a new browser tab.

[Virtual Desktop documentation](https://codio.com/docs/ide/boxes/installsw/gui/)

#### Command line access and the Terminal window
All Codio Boxes provide sudo level privileges to the underlying Ubuntu server. This means you can install and configure any component you like. You access the terminal from the **Tools->Terminal** menu item.

#### Debugger
The Codio IDE comes with a powerful visual debugger. Currently we support Python, Java, C, C++ and NodeJS. 

[Debugger documentation](https://codio.com/docs/ide/features/debugging/)

