##############################################################################################
# shiggy
##############################################################################################

all: shiggy.prg

shiggy.prg: data/shiggy main.c
	cd data && bin2c -o shiggy.h shiggy
	cl65 main.c -Oirs -o shiggy.prg
run: shiggy.prg
	x64sc -autostartprgmode 1 shiggy.prg

clean:
	$(RM) shiggy.prg
	$(RM) *.prg *.o *.s *.map *.lbl *.log *.lst *.d64
