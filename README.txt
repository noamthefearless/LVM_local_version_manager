welcom to LVM!
this is my attempt to make a version manager that would resemble git, but local!
this cli application is usefull 
for small projects and codes that i want to save, but dont 
want to uploade them to github/gitlab.


the version manager is not a big fleshed out project, but more of a side project iv'e been working
on. because of that. the installation is very specific, but also straightforword:

1 - take the folder named LVM and put it on the hard drive C:
2 - add the folder LVM (path: C:\LVM) to the PATH.

that's it! the reason it must be on C: is because the project's save path is defined as 
C:\LVM\projects. that might change in possible future updates. also the folder should be on
the PATH to make sure that you can access lvm from anywhere on you machine.






how to use lvm:
the application dose not have a help flag yet, so for now ill write the user instructions here.


first of all open cmd, and type lvm.
to start the application and enter the menu. from here there are several commands to choose from:

1 - lvm new project <project name>: this command will create a new project under the name of the project.
(make sure that the name is a valid directory name, and that you have no other projects
with the same name!)


2 - lvm delete <project name>: this command is pretty self explanatory. delete any exsiting
project.


3 - lvm show projects: this command will show a list of all projects on lvm.


4 - lvm exit - exits lvm

5 - lvm open <project name>: opens the project you inputted and takes you to the project menu.
(only 1 project can be opened at a time!)



if you open a project, youll enter the project menu, from wich you can take actions
regarding your project.


1 - lvm clone <commit number optional>: this command clones the project to the folder from wich
you activated lvm. this way you can work on the project from a different directory, and save the changes
to lvm when you are done. you can put in the number of a specific commit to clone, or use the
command with no parameter to clone the latest commit.

2 - lvm commit <message>: takes a working directory in the directory from wich you opened lvm,
and takes a snapshot of it to be a commit in the project. this way you can save the work you have
been doing to lvm, and clone it back whenever you want.


3 - lvm show commits: this shows the list of commits, all of their masseges, and their number.
using the number you can clone specific commits with the optional clone parameter.

4 - lvm close project: closes the project.






these are all the commands in lvm. 
if lvm dosen't work, make sure that you follow this guide, and make sure that the savePath:
C:\LVM\projects is valid and existing.

report bugs to me at noamshaharut@gmail.com

have fun!










