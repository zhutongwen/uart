

objects = main.o uart.o

main.out : $(objects)
	gcc	-Wall	-o	main.out	$(objects)

main.o : main.c
	gcc	-Wall 	-c 	main.c  
	
uart.o : uart.c
	gcc	-Wall 	-c 	uart.c  

clearn :
	-rm main.out	$(objects)
