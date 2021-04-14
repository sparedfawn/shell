#!/home/krzysztof/Desktop/final_project/shellKK

echo "Proste przekierowanie wyniku polecenia (ls) do pliku testowego..."
ls >> test.txt
sleep 5s

echo "Wypisanie zawartosci pliku test.txt..."
cat test.txt
sleep 5s

echo "Przekierowanie wyniku polecenia (ls -l) do pliku testowego..."
ls -l >> test.txt
sleep 5s

echo "Wypisanie zawartosci pliku test.txt..."
cat test.txt
sleep 5s

echo "Zastosowanie pojedynczego pipe..."
ls | grep main
sleep 5s

echo "Wypisanie ostatnich 20 polecen z historii..."
cat ~/shell_history
sleep 5s

echo "Usuniecie pliku test.txt..."
rm -r test.txt
ls -l | grep test.txt
sleep 5s

echo "Uruchomienie programu firefox, aby kontynuowac testy prosze o zamkniecie firefoxa..."
firefox

echo "Uruchomienie firefoxa w tle..."
firefox &

echo "med_test zakonczony!"