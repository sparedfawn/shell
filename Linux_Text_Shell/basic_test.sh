#!/home/krzysztof/Desktop/final_project/shellKK

echo "Testowanie tworzenia katalogu..."
mkdir katalog_testowy
ls -l | grep katalog_testowy
sleep 5s

echo "Testowanie wyswietlenia bierzacego katalogu..."
pwd
sleep 5s

echo "Testowanie przejscia miedzy katalogami..."
cd katalog_testowy
pwd
sleep 5s

echo "Powrot..."
cd ..
pwd
sleep 5s

echo "Usuniecie katalogu..."
rmdir katalog_testowy
ls -l | grep katalog_testowy
sleep 5s

echo "Wypisanie zawartosci katalogu (ls)..."
ls
sleep 5s

echo "Wypisanie zawartosci katalogu (ls -l)..."
sleep 1s
ls -l
sleep 5s

echo "Stworzenie pliku test.txt..."
touch test.txt
ls -l | grep test.txt
sleep 5s

echo "Wypisanie zawartosci pliku test.txt..."
echo to jest plik testowy >> test.txt
cat test.txt
sleep 5s

echo "Usuniecie pliku test.txt..."
rm -r test.txt
ls -l | grep test.txt
sleep 3s

echo "basic_test zakonczony!"