all: a.out

run-dot:
	g++ main.cpp && ./a.out && dot -Tpng tree.dot > tree.png

a.out:
	g++ main.cpp -o a.out

test: a.out
	./a.out < inputs.txt

clean:
	rm a.out

