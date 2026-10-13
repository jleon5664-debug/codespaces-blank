#!/bin/bash
# Creates edge/in1.txt..in7.txt and edge/out1.txt..out7.txt: boundary cases the sample skips.
# Expected outputs follow the spec plus these assumptions: equal level and hp -> newcomer
# goes after; DEPOSIT_BACK matches case-sensitively; input without LOGOFF_PC prints nothing extra.
mkdir -p edge

# 1: withdraw more than stored
cat > edge/in1.txt <<'END'
DISPLAY_STORAGE
WITHDRAW_PARTY 2
DEPOSIT_PC Eevee Normal 20 55
WITHDRAW_PARTY 5
DISPLAY_STORAGE
LOGOFF_PC
END
cat > edge/out1.txt <<'END'
--- WILL'S PC STATUS ---
Storage Box Queue (0): EMPTY
Active Roster (0): EMPTY
------------------------
[EVENT] Withdrew 0 monster(s) from Will's PC to Active Roster.
[EVENT] Deposited to Will's PC: Eevee (Normal, Lv: 20, HP: 55)
[EVENT] Withdrew 1 monster(s) from Will's PC to Active Roster.
--- WILL'S PC STATUS ---
Storage Box Queue (0): EMPTY
Active Roster (1): Eevee [Lv: 20]
------------------------
[EVENT] Logged off Will's PC.
END

# 2: tie-breaks
cat > edge/in2.txt <<'END'
DEPOSIT_PC Golem Rock 62 60
DEPOSIT_PC Gengar Ghost 62 80
DEPOSIT_PC Haunter Ghost 62 80
DEPOSIT_PC Onix Rock 62 95
WITHDRAW_PARTY 4
DISPLAY_STORAGE
LOGOFF_PC
END
cat > edge/out2.txt <<'END'
[EVENT] Deposited to Will's PC: Golem (Rock, Lv: 62, HP: 60)
[EVENT] Deposited to Will's PC: Gengar (Ghost, Lv: 62, HP: 80)
[EVENT] Deposited to Will's PC: Haunter (Ghost, Lv: 62, HP: 80)
[EVENT] Deposited to Will's PC: Onix (Rock, Lv: 62, HP: 95)
[EVENT] Withdrew 4 monster(s) from Will's PC to Active Roster.
--- WILL'S PC STATUS ---
Storage Box Queue (0): EMPTY
Active Roster (4): Onix [Lv: 62] -> Gengar [Lv: 62] -> Haunter [Lv: 62] -> Golem [Lv: 62]
------------------------
[EVENT] Logged off Will's PC.
END

# 3: release boundaries
cat > edge/in3.txt <<'END'
DEPOSIT_PC Snorlax Normal 70 4
DEPOSIT_PC Gengar Ghost 62 80
DEPOSIT_PC Golem Rock 62 0
DEPOSIT_PC Pikachu Electric 45 0
WITHDRAW_PARTY 4
RELEASE_FAINTED 10
DISPLAY_STORAGE
RELEASE_FAINTED 80
RELEASE_FAINTED 81
DISPLAY_STORAGE
LOGOFF_PC
END
cat > edge/out3.txt <<'END'
[EVENT] Deposited to Will's PC: Snorlax (Normal, Lv: 70, HP: 4)
[EVENT] Deposited to Will's PC: Gengar (Ghost, Lv: 62, HP: 80)
[EVENT] Deposited to Will's PC: Golem (Rock, Lv: 62, HP: 0)
[EVENT] Deposited to Will's PC: Pikachu (Electric, Lv: 45, HP: 0)
[EVENT] Withdrew 4 monster(s) from Will's PC to Active Roster.
[EVENT] Released 3 fainted monster(s) with HP below 10.
--- WILL'S PC STATUS ---
Storage Box Queue (0): EMPTY
Active Roster (1): Gengar [Lv: 62]
------------------------
[EVENT] Released 0 fainted monster(s) with HP below 80.
[EVENT] Released 1 fainted monster(s) with HP below 81.
--- WILL'S PC STATUS ---
Storage Box Queue (0): EMPTY
Active Roster (0): EMPTY
------------------------
[EVENT] Logged off Will's PC.
END

# 4: deposit-back misses and duplicates
cat > edge/in4.txt <<'END'
DEPOSIT_PC Pidgey Normal 10 30
DEPOSIT_PC Pidgey Normal 25 40
DEPOSIT_PC Rattata Normal 5 20
WITHDRAW_PARTY 2
DEPOSIT_BACK Rattata
DEPOSIT_BACK Mewtwo
DEPOSIT_BACK pidgey
DEPOSIT_BACK Pidgey
DISPLAY_STORAGE
LOGOFF_PC
END
cat > edge/out4.txt <<'END'
[EVENT] Deposited to Will's PC: Pidgey (Normal, Lv: 10, HP: 30)
[EVENT] Deposited to Will's PC: Pidgey (Normal, Lv: 25, HP: 40)
[EVENT] Deposited to Will's PC: Rattata (Normal, Lv: 5, HP: 20)
[EVENT] Withdrew 2 monster(s) from Will's PC to Active Roster.
[ERROR] Rattata is not in the Active Roster.
[ERROR] Mewtwo is not in the Active Roster.
[ERROR] pidgey is not in the Active Roster.
[EVENT] Returned Pidgey from Active Roster back to Will's PC.
--- WILL'S PC STATUS ---
Storage Box Queue (2): Rattata [Lv: 5] -> Pidgey [Lv: 25]
Active Roster (1): Pidgey [Lv: 10]
------------------------
[EVENT] Logged off Will's PC.
END

# 5: round trip keeps FIFO
cat > edge/in5.txt <<'END'
DEPOSIT_PC Bulbasaur Grass 15 45
DEPOSIT_PC Squirtle Water 14 44
DEPOSIT_PC Charmander Fire 16 39
WITHDRAW_PARTY 1
DEPOSIT_BACK Bulbasaur
DISPLAY_STORAGE
WITHDRAW_PARTY 2
DISPLAY_STORAGE
LOGOFF_PC
END
cat > edge/out5.txt <<'END'
[EVENT] Deposited to Will's PC: Bulbasaur (Grass, Lv: 15, HP: 45)
[EVENT] Deposited to Will's PC: Squirtle (Water, Lv: 14, HP: 44)
[EVENT] Deposited to Will's PC: Charmander (Fire, Lv: 16, HP: 39)
[EVENT] Withdrew 1 monster(s) from Will's PC to Active Roster.
[EVENT] Returned Bulbasaur from Active Roster back to Will's PC.
--- WILL'S PC STATUS ---
Storage Box Queue (3): Squirtle [Lv: 14] -> Charmander [Lv: 16] -> Bulbasaur [Lv: 15]
Active Roster (0): EMPTY
------------------------
[EVENT] Withdrew 2 monster(s) from Will's PC to Active Roster.
--- WILL'S PC STATUS ---
Storage Box Queue (1): Bulbasaur [Lv: 15]
Active Roster (2): Charmander [Lv: 16] -> Squirtle [Lv: 14]
------------------------
[EVENT] Logged off Will's PC.
END

# 6: everything empty
cat > edge/in6.txt <<'END'
DISPLAY_STORAGE
RELEASE_FAINTED 50
DEPOSIT_BACK Missingno
WITHDRAW_PARTY 0
LOGOFF_PC
END
cat > edge/out6.txt <<'END'
--- WILL'S PC STATUS ---
Storage Box Queue (0): EMPTY
Active Roster (0): EMPTY
------------------------
[EVENT] Released 0 fainted monster(s) with HP below 50.
[ERROR] Missingno is not in the Active Roster.
[EVENT] Withdrew 0 monster(s) from Will's PC to Active Roster.
[EVENT] Logged off Will's PC.
END

# 7: no LOGOFF_PC
cat > edge/in7.txt <<'END'
DEPOSIT_PC Ditto Normal 30 48
WITHDRAW_PARTY 1
DISPLAY_STORAGE
END
cat > edge/out7.txt <<'END'
[EVENT] Deposited to Will's PC: Ditto (Normal, Lv: 30, HP: 48)
[EVENT] Withdrew 1 monster(s) from Will's PC to Active Roster.
--- WILL'S PC STATUS ---
Storage Box Queue (0): EMPTY
Active Roster (1): Ditto [Lv: 30]
------------------------
END

echo "Created edge/ with 7 tests. Run: ./run_tests.sh main.c edge"
