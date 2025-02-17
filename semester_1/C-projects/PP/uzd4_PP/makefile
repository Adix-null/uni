SRC = main.c func.c
TEST_SRC = test.c func.c

PROD_EXE = main
TEST_EXE = test

all: $(PROD_EXE)

#pagrindinis
$(PROD_EXE): $(SRC)
	gcc -o $(PROD_EXE) $(SRC)

#testavimui
$(TEST_EXE): $(TEST_SRC)
	gcc -DTESTING=1 -o $(TEST_EXE) $(TEST_SRC)

clean:
	rm -f $(PROD_EXE) $(TEST_EXE)
