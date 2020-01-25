build:
	g++ -o sorer -Wall -std=c++11 main.cpp
test:
	./sorer -f "data.sor" -from 0 -len 1000 -print_col_type 0
	./sorer -f "data.sor" -from 10 -len 1000 -print_col_type 0
	./sorer -f "data.sor" -from 0 -len 1000 -print_col_type 4
	./sorer -f "data.sor" -from 0 -len 20 -print_col_type 4
	#./sorer -f "data.sor" -from 0 -len 1000 -print_col_idx 9 0
	./sorer -f "data.sor" -from 0 -len 1000 -print_col_idx 5 2
	./sorer -f "data.sor" -from 0 -len 1000 -print_col_idx 4 2
	./sorer -f "data.sor" -from 0 -len 1000 -is_missing_idx 0 0
	./sorer -f "emptydata.sor" -from 0 -len 1000 -print_col_type 0
	./sorer -f "emptydata.sor" -from 0 -len 1000 -print_col_type 13
	./sorer -f "emptydata.sor" -from 0 -len 1000 -print_col_idx 0 0
	./sorer -f "emptydata.sor" -from 0 -len 1000 -print_col_idx 13 2
	./sorer -f "emptydata.sor" -from 0 -len 1000 -is_missing_idx 0 0
	./sorer -f "emptydata.sor" -from 0 -len 1000 -is_missing_idx 13 2