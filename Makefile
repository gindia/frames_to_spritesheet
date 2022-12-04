EXE = ftss

$(EXE):
	@mkdir -p bin
	@cc -o ./bin/$(EXE) frames_to_sprite.c -lm

build: $(EXE)
	@echo "Done!"

clean:
	@rm *.o
	@rm bin/* -fr
