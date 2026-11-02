
OS PRACTICALS 1 TO 8 - UBUNTU QUICK GUIDE
========================================

Extract this ZIP, open Terminal in this folder, and follow the commands below.
Use: gcc filename.c -o outputname
Run: ./outputname

PRACTICAL 1 - ADDRESS BOOK USING SHELL SCRIPT
---------------------------------------------
File: practical1.sh
Commands:
  chmod +x practical1.sh
  ./practical1.sh
Menu: Add, View, Search, Delete, Exit.
The address book is stored in address.txt in the same folder.

PRACTICAL 2 - FORK, EXECVE AND WAIT
-----------------------------------
Files: practical2.c and descending.c
Commands:
  gcc descending.c -o descending
  gcc practical2.c -o practical2
  ./practical2
Enter count and integers. Parent sorts ascending. Child uses execve()
to run the separate descending program.

PRACTICAL 3 - SEMAPHORE / MUTUAL EXCLUSION (PYTHON THREADS)
----------------------------------------------------------
File: practical3.py
Command:
  python3 practical3.py
This teaching demonstration uses Python threading.Semaphore(1) to allow
only one thread at a time inside the critical section. It demonstrates
thread synchronization (not separate-process IPC).

PRACTICAL 4 - DINING PHILOSOPHERS
---------------------------------
File: practical4.c
Commands:
  gcc practical4.c -o practical4 -pthread
  ./practical4
The room semaphore allows at most four of five philosophers to try to
pick up forks at once, preventing circular-wait deadlock.

PRACTICAL 5 - BANKER'S ALGORITHM
--------------------------------
File: practical5.c
Commands:
  gcc practical5.c -o practical5
  ./practical5
Enter the number of processes/resources, Allocation matrix, Max matrix,
and Available vector. The program prints whether the state is safe and,
if safe, the safe sequence.

Sample input:
5 3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
3 3 2

Expected safe sequence:
P1 -> P3 -> P4 -> P0 -> P2

PRACTICAL 6 - FULL-DUPLEX FIFO BETWEEN TWO INDEPENDENT PROGRAMS
----------------------------------------------------------------
Files: process1.c and process2.c
Commands (run from this folder):
  mkfifo pipe1 pipe2
  gcc process1.c -o process1
  gcc process2.c -o process2
Open TWO terminal windows in this same folder.
Terminal 1:
  ./process2
Terminal 2:
  ./process1
Type a sentence in Process 1. Process 2 counts characters, words and
newline-terminated lines, writes result.txt, and sends the result back.
Type exit in Process 1 to stop it; stop Process 2 with Ctrl+C.
If the FIFOs already exist, do not run mkfifo again. To remove them:
  rm -f pipe1 pipe2

PRACTICAL 7 - PARENT-CHILD COMMUNICATION USING TWO UNNAMED PIPES
----------------------------------------------------------------
File: practical7.c
Commands:
  gcc practical7.c -o practical7
  printf 'Hello from Practical 7\\n' > sample.txt
  ./practical7
When prompted, enter: sample.txt
The parent sends the pathname to the child using Pipe 1. The child reads
the file and sends its contents back through Pipe 2.

PRACTICAL 8 - DISK SCHEDULING: SSTF, SCAN, C-LOOK
------------------------------------------------
File: practical8.c
Commands:
  gcc practical8.c -o practical8
  ./practical8
Sample input:
  200
  8
  98 183 37 122 14 124 65 67
  53
Inputs are: total cylinders, number of requests, request queue, initial
head position. The head initially moves towards cylinder 0.
Expected totals for the sample:
  SSTF  = 299
  SCAN  = 236
  C-LOOK = 326

IMPORTANT NOTES
---------------
1. These are simple educational implementations. Use your college's exact
   practical statement if its required program differs.
2. For Practical 6, the sentence character count includes the newline
   received from fgets(). Line count counts newline characters.
3. For Practical 8, SCAN includes movement to cylinder 0; C-LOOK jumps from
   the lowest pending request to the highest pending request, then continues
   downwards, matching the supplied practical's direction.
