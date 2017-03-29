

objects = main.o uart.o process.o

main.out : $(objects)
	gcc	-Wall	-o	main.out	$(objects)

main.o : main.c
	gcc	-Wall 	-c 	main.c  
	
uart.o : uart.c
	gcc	-Wall 	-c 	uart.c  

process.o : process.c
	gcc	-Wall 	-c 	process.c 
	
clearn :
	-rm main.out	$(objects)
