

a.out:main.c exp.tab.c ast.c ast.h compile.c
	gcc main.c exp.tab.c ast.c compile.c
exp.tab.c:exp.y
	bison exp.y

clean:
	rm exp.tab.c exp.tab.h a.out
	
	
