all: ihm.c
	@gcc -std=c99 -W -Wall -Wextra -o ihm ihm.c -lSDL -lSDL_net

test: prisenmainSDLjoy.c
	@gcc -std=c99 -W -Wall -Wextra -o $@ $^ -lSDL -lSDL_net

clean:
	@rm -rf ihm *.o *~