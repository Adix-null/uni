# -*- Makefile -*-

CC = g++
CFLAGS = -std=c++20

all: demo test

test: test.o Combatant.o MeleeAttack.o RangedAttack.o FireballAttack.o
	$(CC) $(CFLAGS) -o test $^

demo: Demo.o Combatant.o MeleeAttack.o RangedAttack.o FireballAttack.o
	$(CC) $(CFLAGS) -o Demo $^

demo.o: Demo.cpp CombatantAttack.h
	$(CC) $(CFLAGS) -c Demo.cpp -o $@

Combatant.o: Combatant.cpp CombatantAttack.h
	$(CC) $(CFLAGS) -c Combatant.cpp -o $@

MeleeAttack.o: MeleeAttack.cpp CombatantAttack.h
	$(CC) $(CFLAGS) -c MeleeAttack.cpp -o $@

RangedAttack.o: RangedAttack.cpp CombatantAttack.h RangedAttack.h
	$(CC) $(CFLAGS) -c RangedAttack.cpp -o $@

FireballAttack.o: FireballAttack.cpp CombatantAttack.h
	$(CC) $(CFLAGS) -c FireballAttack.cpp -o $@

clean:
	del /f /q *.o test.exe Demo.exe

.PHONY: all clean