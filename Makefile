All : Ass proc
	Assembler\assembler.exe Programs\factorial.txt Assembler\res_ass.txt
	CPU\proc.exe
	
Res_Ass : Ass
	Assembler\assembler.exe Programs\factorial.txt Assembler\res_ass.txt

Res_Cpu : proc
	CPU\proc.exe
 

proc : CPU\src\CPU.cpp  Onegin\src\file_size.cpp  Onegin\src\string_read.cpp  Onegin\src\destruct.cpp  Onegin\src\str_print.cpp  Stack\src\stack.cpp 
	g++ -o CPU\proc CPU\src\CPU.cpp  Onegin\src\file_size.cpp  Onegin\src\string_read.cpp  Onegin\src\destruct.cpp  Onegin\src\str_print.cpp  Stack\src\stack.cpp
	  
Ass :  Assembler\src\assembler.cpp  Onegin\src\file_size.cpp  Onegin\src\string_read.cpp  Onegin\src\destruct.cpp  Onegin\src\str_print.cpp 
	g++ -o Assembler\assembler Assembler\src\assembler.cpp  Onegin\src\file_size.cpp  Onegin\src\string_read.cpp  Onegin\src\destruct.cpp  Onegin\src\str_print.cpp



