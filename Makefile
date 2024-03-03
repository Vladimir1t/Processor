All : Ass proc
	Ass.exe Programs\factorial.txt Assembler\res_ass.txt
	proc.exe
	
Res_Ass : Ass
	Ass.exe Programs\factorial.txt Assembler\res_ass.txt

Res_Cpu : proc
	proc.exe
 

proc : CPU\CPU.cpp  Onegin\src\file_size.cpp  Onegin\src\string_read.cpp  Onegin\src\destruct.cpp  Onegin\src\str_print.cpp  Stack\src\stack.cpp 
	g++ -o proc CPU\src\CPU.cpp  Onegin\src\file_size.cpp  Onegin\src\string_read.cpp  Onegin\src\destruct.cpp  Onegin\src\str_print.cpp  Stack\src\stack.cpp
	  
Ass :  Assembler\src\assembler.cpp  Onegin\src\file_size.cpp  Onegin\src\string_read.cpp  Onegin\src\destruct.cpp  Onegin\src\str_print.cpp 
	g++ -o Ass Assembler\src\assembler.cpp  Onegin\src\file_size.cpp  Onegin\src\string_read.cpp  Onegin\src\destruct.cpp  Onegin\src\str_print.cpp



