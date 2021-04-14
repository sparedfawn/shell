#!/home/krzysztof/Desktop/final_project/shellKK

echo "Zastosowanie wielokrotnego pipe..."
ls -l | grep main | tail -1
sleep 5s

echo "Inny przyklad wielokrotnego pipe..."
ls | grep shell | grep KK | head -3
sleep 5s

echo "Zastosowanie wielokrotnego pipe z przekierowaniem do pliku..."
cat basic_test.sh | grep echo | tail -2 >> test.txt
sleep 5s

echo "Wypisanie zawartosci testowego pliku..."
cat test.txt
sleep 5s

echo "Usuniecie pliku testowego..."
rm -r test.txt
ls -l | grep test.txt
sleep 3s

echo "hard_test zakonczony!"