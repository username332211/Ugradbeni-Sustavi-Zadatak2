# Ugradbeni Sustavi - Sleep Mode

## 1. Opis zadatka
Cilj zadatka je korištenje sleep mode-a za smanjenje potrošnje energije te njegovo testiranje pomoću Watchdog timer-a (WDT) i vanjskog prekida.

## 2. Korištene komponente
- 1 Arduino Mega mikrokontroler
- 1 tipkalo
- 1 LED dioda
- 1 otpornik

## 3. Funkcionalnost
Program funkcionira na sljedeći način: LED dioda prelazi iz stanja spavanja u stanje buđenja ovisno o dva glavna faktora, a to su Watchdog timer i vanjski prekid pomoću tipkala. Watchdog timer funkcionira na način da se nakon svakih 8 sekundi stanja spavanja LED dioda automatski budi zbog navedenog WDT-a, dok je isto tako moguće i LED diodu probuditi korištenjem tipkala. Čak i u slučaju korištenja tipkala, Watchdog timer je uvijek sinkroniziran sa zadnjim stanjem spavanja, što znači da neovisno o tome koji je prekid probudio LED diodu, razmak između sljedećeg prekida Watchdog timer-a uvijek iznosi 8 sekundi. Isto tako, vrijeme stanja buđenja LED diode je 5 sekundi.

## 4. Različiti Sleep Mode-ovi
Postoje različiti mogući sleep mode-ovi koji se mogu koristiti, a najistaknuitiji su sljedeći:
- IDLE mode - mikrokontroler ostaje uključen što znači da potrošnja energije nije minimalna, no većina komponenti se isključuje
- Power-down mode - mikrokontroler isključuje gotove sve komponente
- Standby mode - sličan kao power-down, no neke komponente ostaju aktivne, što označava veći potrošak energije nego kod prijašnje navedenog sleep mode-a

## 5. Zaključak
Zbog navadenih razloga iz opisa pod brojem 4, u ovom programu se koristi power-down mode za najmanju potrošnju energije.
