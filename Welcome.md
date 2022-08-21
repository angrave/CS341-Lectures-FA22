Hi class!

Welcome to CS341 System Programming! I'm Lawrence Angrave. I'm excited to be your instructor this semester and to introduce you to C programming and System Programming. 

You can also use the course book and asynchronously watch recorded lectures or the previously online lectures both on ClassTranscribe to do well in the class - the choice is yours.

Live lectures will be friendly, relaxed, interactive, varied-format, CS341-y content demos and interesting - and a great time to ask questions too. You'll want to supplement these with our free(!) online course book on the website or if online learning is more your style, the pre-recorded videos on ClassTranscribe.

There will will also be online labs this week (Wednesday and Thursday).

You've probably heard this is a challenging class! Yes, you'll need is time, tenacity and readiness to learn and use C. And the big picture - this course is a stepping stone - You're leaving behind CS225/231 land (where you write code that works with the course's provided code) and instead we're your launch pad you for the big leagues CS4xx at a tier-1 CS school. Take this course seriously and you will be a different and better person at the end of it.

Prepare your neurons.

C is one of the smallest, portable and simplest and "close-to-the-metal" languages that you'll ever use. Unlike C++ it is possible to actually nearly know all of the C specification in under 50 hours. Even if you program in the future with python/Go/Javascript ... you'll be linking and using cross-platform libraries written in ... C. And if you want your new self-aware-high-performance AI/Vision/networking/neural net/quantum computing/picture mod ibrary to be used everywhere i.e. useful directly from Matlab/R/C++/Java programs... or you want to exploit meltdown CPU attack... you'll first or second choice will be ...C; understanding C gives you the foundational insights into how all of the other modern languages (Ruby, Rust, R, Python, Julia...) actually work when run on a CPU. In short, C because is "close to the metal", it is an important foundation that is part of your journey to mastering Computer Science.

C programs use a lot of memory pointers. This means your variables hold memory addresses (and the compiler uses the type of variable to infer how many bytes to read/write at that location). Everything is great providing your pointers point to the correct piece of memory and don't start reading or writing from incorrect pieces of memory. You can even indirectly cause "exciting things to happen" if you pass a bad pointer to a library or system call too.

Pointers can be tricky to learn, but it helps to remember the following -

Asterisk in code "*" is either part of the type ("This is a pointer!") but in an expression it means follow the pointer and read the memory that it points to.

They just hold a memory address (which CAN be changed e.g " myptr = ... " )

For a program to use ("dereference") a pointer, then the CPU will need to perform another memory access,

The variable type is a hint to the compiler as to how many bytes to read/write and is also useful to detect some programming errors at compile time.

(I admit I simplified the last part about compilers but hey this is about using pointers with confidence, not about implementing a compiler OK?)

Let's get started today, right now, with Homework Zero - my introductory mini-course. If you open the link below up on a powerful laptop or desktop using Chrome / Firefox you'll discover videos, man pages, and a complete virtual linux machine running inside your browser (yes it implements memory, disk and CPU in javascript and then boots up a linux machine with gcc and other standard tools - pretty cool! - it works best in Chrome). There's one #include issue with waitpid that I'll let you discover (and find a workaround) in the last lecture. Also, if nothing seems to be changing check the editor is editing the C file that is compiled and run (program.c).

http://cs-education.github.io/sys/
The questions are here, this is the same repo I will use for live Fall 2022 lectures. https://github.com/angrave/CS341-Lectures-FA22/blob/main/HW0.md
We will put up a link to submit HW0 starting the first lab section, although it won't be due until the following week. Just collect your answers in a simple long plain text document.

You can also use regular linux machines and other online environments of course. I suggest you work on HW0 a bit each day (it's much better for long term recall and innate skills acquisition if you exercise your CS341 neurons each day).

Please use Ed for discussion (and private posts for grading / logistics / emergency issues)- https://edstem.org Ed is not a U of I resource, so you could use a throw away email if you are concerned. Contact me if you have any concerns about this. Here's the link to join the Fall 2022 forum if you prefer to use an anonymous email-

(Link hidden; it is only for enrolled CS341 students)

Send all CS341 questions, comments, ideas, regrades, logistics, issues, grade requests,bananas-for-scale etc to Ed forums - not to my email. Most issues can be solved with a public or private post on Ed (or better, a search!). The course website (link currently under construction) is below. You can find links to the coursebook and syllabus (including learning objectives) here -

http://cs341.cs.illinois.edu/ 

Next steps: To help break down the digital barriers of an online course, I'd like to get to know you. So please share something about yourself on Ed. Where are you/what timezone? Any... Do you have any pets? Favorite movie? A picture of your favorite shoes. Favorite Poem, Cartoon, Joke or Music link. Up to you what you want to share. Who knows - maybe you'll find another student with similar interests and tastes.

Ready? Let's Go!

Captain Angrave

p.s. Myself and the course staff love teaching this course. We're here help as many of you as possible to become the best programmers and computer scientists that you can be. Are you ready to stand up, put in the effort, and be recognized as an University of Illinois Computer Scientist? Then you're in the right place. Let's kick it into gear and get this show started.
