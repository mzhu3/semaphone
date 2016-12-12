yes:control.c
	gcc control.c -o ctrl
	gcc writing.c -o wrt
clear:
	rm ctrl
	rm wrt
	rm story.txt
