=========================================================================================

																Anna Sarnavska
																    Zestaw6

=========================================================================================

Katalog *Zestaw6* zawiera programy, napisane na podstawie 2 zadan.

=========================================================================================

0) Makefile 	- Plik regul, ktory autoryzuje proces kompilacji,
		i linkowania  w przypadku, gdy potrzebujemy uzyc
		wiekszej ilosci modulow.
		Zawiera reguly kompilacji - opis zaleznosci pomiedzy
		plikami zrodlowymi. Makefile umozliwia uruchamianie
		kazdego programu katalogu za pomoca domyslnej reguly
		*all*. Takze ma mozliwosc usuwania plikow tymczasowych
		i niepotrzebnych.

Sklada sie:	_Makefile_ glowny plik regul.

Kompilacja:	make all
Czyszczenie:	make clean
_________________________________________________________________________________________

1) wykluczanie.c - Program pokazuje dzialanie watkow (rozwidlenie procesu w przestrzeni	
		adresowej i wykorzystanie dla poszczegolnych zadan) 
		za pomoca muteksow przy wykonaniu wzajemnego wykluczania.
		Najpierw zeby moc korzystac z biblioteki funkcji watkowych POSIX 
		uzywamy dyrektywy _REENTRANT, ktora oznacza kod jako kod wielokrotnego 
		uzytku.  (mozna wiele razy wchodzic). 
		Muteks okresla obiekty negocjujace dostep pomiedzy watkami. 
		(Tak zwana blokada). Chociaz watek ma inna konwencje niz semafory
		(wartosc 1 - zamknety, 0 - otwarty) i operacje wykonywane na muteksach sa 		niepodzielne - atomowe.
		Wykorzystamy to w celu unikniecia rownoczesnego 
		uzycia wspolnego zasobu (zmiennej globalnej) w czesciach kodu (sekcji 
		krytycznej).
		Na poczatku sesji krytycznej wypisuje sie zmienna (licznik), ktora poznej 		zwieksza sie o 1. 
		Zeby pokazac jak dziala program korzystamy sie z sekwencji sterujacych 
		konsoli. Po prawej stronie wypisuje sie konumikat z licznikiem, 
		kiedy watek jest w sekcji krytycznej. Po lewej, w tym samym wierszu, 
		komunikat pokazuje licznik w sekcji prywatnej. 
		W funkcji glownej main tworzymy watek za pomoca funkcji 
		pthread_create(). A poznej dla odpowiednich watkow wywolujemy funkcje 
		pthread_join() - odpowiednik wait'a dla procesow. 
		
	
Sklada sie:	_wykluczanie.c_ program glowny.
	
Kompilacja:	make all
Uruchomic:	./wykluczanie
_________________________________________________________________________________________


