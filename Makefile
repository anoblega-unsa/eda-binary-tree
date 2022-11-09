all: a.out

run-dot:
	g++ avl.cpp && ./a.out && dot -Tpng tree.dot > tree.png

a.out:
	g++ avl.cpp -o a.out

test: a.out
	./a.out < inputs.txt

clean:
	rm a.out

