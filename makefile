

objects = main.o

main.out : $(objects)
	gcc	-Wall	-o	main.out	$(objects)

main.o : main.c
	gcc	-Wall 	-c 	main.c  # 这句由make 自动导出

clearn :
	rm main.out	$(objects)