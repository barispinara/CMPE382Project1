Summary:
We created a unix shell. Our shell has two modes which are interactive and batch modes.In interactive mode, system takes inputs from user. In batch mode, system takes input as a file then it executes each line through the end of file in threaded section. This unix shell contains 10 threads which we decide number of thread number.Therefore,threads are static.

Design Overview:
As we mentioned above, unix shell has two modes which  are interactive and batch modes.The system decides that which mode will be active with respect to argument number(argc) such as if user types “./myshell”, system will determine that interactive mode will be used. However, if user types “./myshell fileName(.bat)” then system will determine that batch mode will be used. 
This unix shell starts splitting strings after taking inputs. First part of the splitting string is seperating strings according to “|” character. While working on first part, system adds strings which is seperated with strtok() into char array. Also, system counts number of seperating operations. This count number determines that how many times thread will restart. Second part of the splitting string is  seperating strings according to “;” character. While working on the second part, system starts to assign threads with respect to parsed inputs. In addition, there is an another counter variable that stores thread number which amount of threads will work concurrently (in threaded mode). 
Lastly, user can exit from our unix shell with “quit” command. If the “quit” command is on the same line with other commands or not, system recognizes “quit”. Firstly, it executes other input commands. After  that, it exit from unix shell. 

Complete specification:
    • Input commands are splitted via “;” runs in concurrently
    • Input commands are splitted via “|” runs in sequentially.
    • Input commands work on both “;” and “|” characters.
    • System gives error message when user gives input that is not belong to these mode types that we mentioned such as “./myshell fileName1 fileName2”. 
    • Unix shell handles the batch file does not exist or can not be opened with giving error message in terminal.
    • When input size is bigger than 512, our system will give error.
    • Unix shell passes new line when command line is an empty but it does not give error message.
    • Handling of extra white spaces are working without error except quit command.
    • Batch files which end without quit command works each line of bat file then it passes to interactive mode.
Test cases:
	•Test1 case (test1.txt):
	This test case that we created is an example test situation both ";" and "|" characters that works. 
	•Test2 case (test2.txt):
	This test case is an example of if ";" character occurs twice as sequential then shell continues working.
	•Test3 case (test3.txt):
	This test case is an example of if multiple ";" character occurs from the start of input. System will work properly.
	•Test4 case (test4.txt):
	This case is a simple test which checks quit command. Also, it checks concurrently work.
	•Test5 case (test5.txt):
	This an another simple test case to check pipeline commands.
	•Test6 case (test6.txt):
	This case tests a very long command but which is not consisting of 512 characters.
	•Test7 case (test7.txt):
	This test case is another probability that if there is an whitespaces between ";" and "|" characters. System creates extra thread for the blank space between ";" and "|". This an known problem.
	•Test8 case (test8.txt):
	This is a test case which checks if given file contains two or more line inputs, system will read inputs line by line. Moreover, system will execute commands line by line. 
	•Test9 case (test9.txt):
	This is an last test case that controls a long command line which is bigger than 512 characters and it gives an error messages.
	•Test10 case(test10.txt):
	This test case shows that system will not exit if quit command has two or more extra whitespaces. This case is one of the known problem in the shell.
	
Known bugs or problems: 
    • System will not exit if quit command has two or more extra whitespaces.
    • Our thread limit is not dynamic. That’s why, it does not set thread number as dynamic with respect to given input.
    • System creates extra unnecessary threads if input has blank spaces between signs(";" and "|")
