All : Ass proc
	Ass.exe Assembler\commands.txt res_ass.txt
	proc.exe
	
Res_Ass : Ass
	Ass.exe Assembler\commands.txt res_ass.txt

Res_Cpu : proc
	proc.exe
 

proc : CPU\CPU.cpp  Onegin\FileSize.cpp  Onegin\StringRead.cpp  Onegin\Destruct.cpp  Onegin\StrPrint.cpp  Stack\Stack.cpp 
	g++ -o proc CPU\CPU.cpp  Onegin\FileSize.cpp  Onegin\StringRead.cpp  Onegin\Destruct.cpp  Onegin\StrPrint.cpp  Stack\Stack.cpp
	  
Ass :  Assembler\Assembler.cpp  Onegin\FileSize.cpp  Onegin\StringRead.cpp  Onegin\Destruct.cpp  Onegin\StrPrint.cpp 
	g++ -o Ass Assembler\Assembler.cpp  Onegin\FileSize.cpp  Onegin\StringRead.cpp  Onegin\Destruct.cpp  Onegin\StrPrint.cpp



