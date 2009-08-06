default:
	@cd tools && gcc -O3 -fomit-frame-pointer build.c -o build
	@cd source && ../tools/build retro
	@mv source/retro .

clean:
	@rm -f source/*.o
	@rm -f tools/build
	@rm -f retro
