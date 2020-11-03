OBJS := main.o unit.o Hero.o
CC := g++-10
CFLAGS := -Wall -std=c++17



run_cpps: $(OBJS)
	$(CC) $(CFLAGS) -o a.out $(OBJS)

Hero.o: Hero.cpp Hero.h JSON.h
	$(CC) $(CFLAGS) -c Hero.cpp

unit.o: unit.cpp unit.h JSON.h
	$(CC) $(CFLAGS) -c unit.cpp

main.o: main.cpp Hero.h Monster.h JSON.h
	$(CC) $(CFLAGS) -c main.cpp

Install_Valgrind_and_Cppcheck:
	sudo apt-get install -y valgrind cppcheck

Warnings:
	cppcheck *.cpp --enable=warning --error-exitcode=1

Report_generation:
	cppcheck *.cpp --enable=performance --enable=style --output-file=report.txt

Check_mem_leak:
	valgrind --error-exitcode=1 --leak-check=full ./a.out units/unit_1.json units/unit_2.json

Run_tests:
	bash -c "./testing.sh"

Check_differences:
	diff output.txt exp_output.txt

Build:
	cmake unit_test/CMakeLists.txt && make -C unit_test/

Run_tests2:
	cd unit_test/ && ./runTests

Install_doxygen:
	sudo apt-get install doxygen

Install_graphviz:
	sudo apt-get install graphviz

Creating_documentation:
	doxygen doxconf
