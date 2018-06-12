Vicki Chen 8757122
HT.cpp takes inputs hw1_q2_in1 and hw_q2_out2 as arguments and generates an output file containing answers to each query

compile by: g++ -o p2 HT.cpp 
then run by : ./p2 hw1_q2_in.txt hw1_q2_out.txt
argv[1] is always going to be the name of the input txt file
argv[2] is the name of the newly generated txt file we will be outputting our values in
*TO RUN AND GET OUTPUT FILE, CALL :./p2 hw1_q2_in.txt hw1_q2_out.txt


the first level of cache implemented as a Hash Table (HT) with linear probing 
second level as a Max Heap (MH). Each data element has three fields: 
1. address of the element (key) 
2. value of the element 
3. priority of the element (representing its importance as in its frequency of recent accesses for a TLB).

Load MH : Load the values from a specified input file into the MH. The priorities are set to 0. HT is initially empty.
Load HT : Move the top k (size of HT) priority elements to HT. Some elements from the HT may need to be moved to the MH. If the priorities are same, then the element with higher key value will be present in HT.
Access(key) : Find the specified element, increase its priority by 1 and print whether it is present in HT/MH along with value of the element.
	Print format : (0/1/-1) <value of the element> 
			a) 0 : if present in HT
			b) 1: if present in MQ
			c) -1 : if element is not present

Display : Returns all the elements present in the HT/MH.


- data from input file is read and loaded into Max Heap.
- move the top k(size of HT) priority elements to hash table.
- whenever query has been made element is accessed


New file named out.txt is generated for each input 

Input File:
A.2		//Total number of test cases
B.2		//Hash Table size for 1st test case
C.3		//Number of inputs for 1st test case
D.5		//Number of Queries for 1st test case
E.25 30		// Inputs for 1st test case in format <address> and <value>
F.20 18		//..cont.
G.11 15		//..cont.
H.2 20		//Queries for first test case: Access element with key 20
I.2 11		//Access element with key 11
J.3		//display
K.1		//Load HT
L.3		//Display
M.1		//Hash Table size for 2nd test case = 1
N.2		//Number of Inputs for 2nd test case = 2
O.3		//Number of queries for 2nd test case = 2
P.15 10		//Inputs for 2nd test case in format <address> and <value>
Q.16 11		//...cont.
R.2 15		//Queries for 2nd test case
S.1		//..cont.
T.2 15		//..cont.


In output txt file:

I 0 18 			//corresponds to query in line (H)

II 1 15   		//corresponds to query in line (I)

III 20 25 		//corresponds to query in line (I)

IV 11  			//corresponds to query in line (J)

V 20 11			//corresponds to query in line (J)
			
VI 25 			//corresponds to query in line (L)

VII			//Empty line to signify end of test case 1

VIII 1 10		//corresponds to query in line (R)

IX 0 10			//corresponds to query in line (T)
