make:
	g++ -Wall -std=c++11 main.cpp
test:
	./a.out -f "data.sor" -from 0 -len 1000 -print_col_type 0
	./a.out -f "data.sor" -from 10 -len 1000 -print_col_type 0
	./a.out -f "data.sor" -from 0 -len 1000 -print_col_type 4
	./a.out -f "data.sor" -from 0 -len 20 -print_col_type 4
	./a.out -f "data.sor" -from 0 -len 1000 -print_col_idx 9 0
	./a.out -f "data.sor" -from 0 -len 1000 -print_col_idx 5 2
	./a.out -f "data.sor" -from 0 -len 1000 -print_col_idx 4 2
	
	./a.out -f "emptydata.sor"