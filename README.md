# Terminal-Based-File-Explorer
This Repository contains the Terminal Based File Explorer built as part of Advanced Operating Systems Coursework.
## BRIEF:
This Repository is the implementation of File-Explorer in Terminal as part of Advanced Operating Systems Coursework using the proper invocations of various system call and not relying on ncurses for GUI.

## For TAs: 
Put all files in a single directory for compiling use g++ *.cpp and then use ./a.out
## Makefile users:
Binaries are present in `/bin`
* `make`: Builds the binaries
* `make clean` : Remove the object files
* `make run` : Build and run the application
## For Debugging:
`Makefile` is already configured to use debugging just use the attached `.vscode` configuration.
### Libraries Used:


<hr>

## NORMAL MODE :
<img src="images/FileXplorer-normal_mode.png">
Navigation Keys:

* ` ↑ `: Moves the cursor arrow upwards.
* ` ↓ `: Moves the cursor arrow downwards.
* ` ← `: Goes back to previously visited directory.
* ` → `: Goes to next directory.
* `h`: Goes to `Home` which is where the file-explorer starts from.
* `Backspace` : Goes to parent directory.
* ` k `: Scroll Window Up
* ` l `: Scroll Window down
* ` q `: Quit the Explorer
 
<hr>

### COMMAND MODE:
<img src="images/FileXplorer-command_mode.png">

#### Live Update in COMMAND MODE:
<img src="images/FileXplorer-live-change.png">
All the commands are built in a way that their actions are reflected in a live way in the directory listing of the normal mode , to provide users a sense that their commands are actually working. 