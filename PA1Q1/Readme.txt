Vicki Chen 8757122
Main.cpp takes inputs hw1_q1_in1 and hw_q1_in2 as arguments and generates and output file for each containing hashed values.

compile main on terminal by calling: make main
then run by : ./main hw1_q1_in1.txt hw1_q1_out1.txt
argv[1] is always going to be the name of the input txt file
argv[2] is the name of the newly generated txt file we will be outputting our values in
*TO RUN AND GET OUTPUT FOR FIRST FILE, CALL :./main hw1_q1_in1.txt hw1_q1_out1.txt
FOR SECOND FILE, CALL: ./main hw1_q1_in2.txt hw1_q1_out2.txt

It reads each binary value in the file and converts it to decimal, creates a matrix to proceed to hash with level 1 hashing where m = n. If collisions occur, level 2 hashing is used where m = nj^2. This is a recursive function and is applied repeatedly until no collisions happen in a table. which is why a dump hash function is used to clear hash matrices with collisions. New hash matrices are generated until no collision occurs. 
The total space usage is calculated to be less than 4n and space usage is reported after running main on the terminal.
The reported number of accesses for each element is also printed.

New file named out.txt is generated for each input with the matrices


In output txt file:
- First level hashing printed on each line
- Second level hashing printed after separated by a empty line
- For bins that did not require further hashing NULL is printed
- Total space use reported (sum of the sizes of all hash tables in entries)
- Number of accesses for the search operation of each element (last part)
	- output 1 if no elements were mapped to same bin during level 1
	- output 2 if level 2 hashing was required

If perfect hashing achieved, code will output "perfect hashing completed" on terminal.
