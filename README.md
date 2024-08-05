# Answers to The Linux Programming Interface

Here are my solutions for *The Linux Programming Interface* programming 
problems. These were completed for fun and should not be taken as complete or 
correct.

## Building the Code

Building the code requires you to create a `libs/` folder at the root of this 
project to house a few dependencies. To do this, you'll have to get the source 
from [The Linux Programming Interface website][1] and follow the instructions to
compile `libtlpi.a`. Move this archive along with all the `.h` files under 
`libs/` and you should be able to build any of the solutions with a simple 
`make` command. 

[1]: https://man7.org/tlpi/code/index.html