# Tagok

| Név | Github azonosito  | Javasolt relatív érdemjegy | Becsült óra | Indoklás  | 
| --- | ---- | --- | ------------------ | --------- |
| Kovács Kira | @kkira07 | 0 | 97 | Szépen csinálta a dolgát, mindig kivette a részét a feladatokból, a megoldásaira a reviewerek általában pozitiv visszajelzést adtak. |
| Varga Máté | @VMatthew | -1 | 69 | Néha be kellett segiteni a feladatokban, de alapvetően megcsinálta amit kértünk tőle. |
| Vörös Bence László | @vbence121 | 0 | 125 | Mindent megcsinált |


# Videók

 - [Gameplay](/videos/gameplay.mp4)
 - [CodeBaseDefense](/videos/codebasedefense.mp4)

# Befejezett feladatok

| Feladat | Merge ideje a határidóhöz (nap) | Change request körök | Reviewer | 
| ------- | ------------------------------- | -------------------- | -------- |
| Feladat 1 | +4 | 2 | @hegyhati | 
| Feladat 2 | +2 | 1 | @vizvezetek |
| jsonparser | +6 | 1 | @wajzy |
| levelup | +11 | 2 | @oliverosz |
| attackspeed | +5 | 1 | @vizvezetek |
| documentation | -4 | 0 | @teamlessname / @eriklorincz, @kalmar-adam |
| unittest | -5 | 1 | @teamlessname / @eriklorincz, @kalmar-adam |
| makefile | -1 | 0 | @hegyhati |
| refactor | -2 | 4 | @hegyhati |
| docker | -1 | 1 | @hegyhati |
| jsonpimp | Merge: 11.20 | 1 | @teamlessname / @eriklorincz, @kalmar-adam |
| map | Merge: 12.01 | 1 | @teamlessname / @eriklorincz, @kalmar-adam |
| game | Merge: 12.01 (Map-el együtt) | 1 | @teamlessname / @eriklorincz, @kalmar-adam |
| defense | Merge: 11.25 | 1 | @teamlessname / @eriklorincz, @kalmar-adam |
| damage | Merge: 11.25 (defens-el együtt) | 1 | @teamlessname / @eriklorincz, @kalmar-adam  |
| markedmap | Merge: 12.06 | 1 | @teamlessname / @eriklorincz, @kalmar-adam |
| preparedgame | Merge: 12.06 (MarkedMap-el együtt) | 1 | @teamlessname / @eriklorincz, @kalmar-adam |
| light radius | Merge: 12.06 | 1 | @teamlessname / @eriklorincz |
| rendering | nem készült el | - | - |

# Unit tesztek

| Osztály | Publikus metódusok száma | Unit tesztelt metódusok száma | Unit tesztek száma |
| --- | --- | --- | --- |
| `Unit` | 13 | 3 | 6 |
| `Hero` | 10 | 1 | 5 |
| `JSON` | 7 | 3 | 6 |

# Kód dokumentáció

| Teljesen dokumentált osztályok | Részben dokumentált osztályok | Nem dokumentált osztályok |
| --- | --- | --- | 
| `Unit` | ... | ... | 
| `Hero` | ... | ... |  
| `Monster` | ... | ... |
| `Game` | ... | ... |
| `Map` | ... | ... |
| `Json` | ... | ... |
| `MarkedMap` | ... | ... |
| `PreparedGame` | ... | ... |


# Mindenféle számok

 - Összes cpp kódsor : 1583
 - Egyéb kódsor (make,doxyfile,shellscript, ...) : 197 (+2580 sor doxconf)
 - cppcheck
   - warning : 0 (3 g++ -Wall által: Wdelete-non-virtual-dtor, Wreorder, Wsign-compare)
   - style : 16
   - performance : 7
   - unusedFunction : 0
   - missingInclude : 0
 
# Implicit megtanult dolgok
Olyanok, amik nem a tárgy anyaga, de muszáj/hasznos volt elsajátítani:
 - alapvető shell scripting
 - `std::variant`
 - ...

# Feedback (optional)
 
Melyik részt találtátok a leghasznosabbnak, miért. Használtátok-e az itt megszerzett dolgokat esetleg közben máskor. Volt-e olyan, amit hiányoltatok a tárgyból. Utólag visszagondolva is jó volt-e az online videósdi?
- Az itt megszerzett tudások többet használtunk a félév folyamán a 'projektmunka 2' nevü tárgyban, mint például git ismeretek, unit/google tesztek, doxygen, in-out tesztek, gh-pages, stb. Én úgy éreztem, hogy az online orák nem vettek el a tárgy tanulhatóságábol, emiatt nem volt nehezebb. 

# Üzenet a jövőbe (optional)

Így, hogy túlvagytok rajta, mi az, aminek örültetek volna, ha első héten elmondom, avagy: jövőre mit lenne jó, ha elmondanék majd?
