# shell
Linux Text Shell project written in C.

PL:
Powłoka pobiera ze standardowego wejścia pojedynczy wiersz. Następnie dokonuje prostej analizy wiersza dzieląc go na słowa separowane spacjami. Pierwsze słowo jest nazwa programu który należy uruchomić (wykorzystując zmienną PATH), a pozostałe sa argumentami. UWAGA: procesy uruchamiać należy poprzez wywołania systemowe z rodziny exec (execl, execlp, execvp itd.) - inne rozwiązania (np. przekierowanie odpowiedzialności do systemowej powłoki) nie będą uznawane. Shell uruchamia program i standardowo czeka na zakończenie jego pracy, chyba ze ostatnim słowem jest znak & co powoduje uruchomienie programu w tle, jak w normalnym shellu bash. Shell kończy prace gdy otrzyma znak końca pliku. Dzięki temu możliwe jest przygotowanie prostych skryptów, które można uruchamiać z wiersza poleceń bash-a, jeżeli pierwsza linia skryptu ma postać #!/home/student/moj shell (gdzie po ! podaje się ścieżkę do programu shella) (12p). Dodatkowe opcje to:

możliwość przekierowania standardowego wyjścia polecenia przy pomocy » (6p)
możliwość tworzenia potoków o dowolnej długości przy pomocy znaku | (8p)
historia poleceń - shell przechowuje (w zewnętrznym pliku w katalogu domowym użytkownika - tak ze historia powinna ”przetrwać” zakończenie shella) dokładna treść 20 poleceń, a wysłanie sygnału SIGQUIT powoduje wyświetlenie historii na standardowym wyjściu.  (8p)
