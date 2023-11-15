all: copyright gen

copyright:
	@cat LICENSE
	@sleep 2

gen:
	gcc index.c -lncurses -ltinfo