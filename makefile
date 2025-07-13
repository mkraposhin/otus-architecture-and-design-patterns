assignment_tests : assignment_tests.o
	g++ assignment_tests.o -lgtest -lgmock -oassignment_tests

assignment_tests.o : assignment_tests.cpp
	g++ -c assignment_tests.cpp

clean:
	rm -rf assignment_tests assignment_tests.o

##g++ assignment_tests.o /usr/lib/x86_64-linux-gnu/libgmock.a /usr/lib/x86_64-linux-gnu/libgtest.a -oassignment_tests