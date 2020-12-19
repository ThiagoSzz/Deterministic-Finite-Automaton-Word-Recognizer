# **Deterministic Finite Automaton Word Recognizer**
### C.17, 27/11/2020

### A program to convert a DFA into a RG and to verify if the word entered is or not accepted by the DFA
#### The DFA is entered in a text file this way:
#####
###### AUTOMATO: ({q0,q1,q2,...,qn},{A,B,C,...,Z},Prog,initial state,end state)
###### (q0,A)=q1
###### (q1,B)=q2
###### ...
###### (state 1, terminal)=state 2, with state 1 != state 2
#####
#### For a better example, see the file 'AFD.txt'
#### -> The DFA must have only one initial and end states and the maximum amount of states and terminals that can be present in the text file is 20 (can be changed)

#### Run the program and enter the file's name. After that, enter any word and the program will print in the screen as the word belongs or not to the language read in the text file
#### To stop the entry of words, enter 'stop'
