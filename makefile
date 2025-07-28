all: battle_field_object.o battle_field_stage.o assignment_tests

battle_field_object.o : battle_field_object.cxx battle_field_object.hxx battle_field_stage.hxx space_battle.hxx exception_property_not_found.hxx
	g++ battle_field_object.cxx -c

battle_field_stage.o : battle_field_stage.cxx battle_field_stage.hxx space_battle.hxx
	g++ battle_field_stage.cxx -c

assignment_tests: ./tests/assignment_tests.o battle_field_object.o battle_field_stage.o
	g++ ./tests/assignment_tests.o battle_field_object.o battle_field_stage.o -lgtest -lgmock -oassignment_tests

INC_DEPS := translating_object_adapter.hxx \
            translating_object.hxx \
            object_translation.hxx \
			rotating_object_adapter.hxx \
			rotating_object.hxx \
			object_rotation.hxx \
            battle_field_stage.hxx \
            space_battle.hxx \
            battle_field_object.hxx \
            exception_property_not_found.hxx \
            exception_cant_read_property.hxx \
            exception_cant_write_property.hxx

./tests/assignment_tests.o: ./tests/assignment_tests.cxx $(INC_DEPS)
	g++ -I. ./tests/assignment_tests.cxx -c -o./tests/assignment_tests.o

clean:
	rm -rf *.o tests/*.o assignment_tests

