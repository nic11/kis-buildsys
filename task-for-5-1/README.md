Перечисленные ниже команды позволят собрать и запустить проекты из
репозитория https://github.com/akhtyamovpavel/PatternsCollection

### Пошаговый рассказ
В качестве базовой ОС я взял Docker-образ ubuntu:focal.
Итак, через apt устанавливаем следующие пакеты:
- build-essential - для make, g++. Вообще это пакет с
  основными зависимостями, нужными любому разработчику
- cmake
- pkg-config
- doxygen
- Библиотеки
    - libboost-dev
    - libboost-system-dev
    - libssl-dev
    - gnutls-dev
    - libcurl4-openssl-dev
    - zlib1g-dev
    - libghc-gsasl-dev
- git - для сборки Decorator: там присутствуют внешние зависимости, которые ставятся
  из репозиториев с github
- sendmail - для Decorator: используется библиотекой vmime для отправки почты
- python3 - для примеров на питоне

Также для успешной сборки надо выставить переменную окружения
`VMIME_SENDMAIL_PATH=/usr/sbin/sendmail`. Это нужно, т.к. в cmakelists у Decorator
указана команда для сборки vmime. Можно было бы поправить cmakelists и прокинуть
туда путь до sendmail, который cmake смог кстати сам задетектить, но переменная
окружения позволяет обойтись без редактирования кода.

После описанного выше проекты успешно собираются и запускаются, кроме Decorator.
Он не может загрузить библиотеку:
`./Decorator: error while loading shared libraries: libinicpp.so: cannot open shared object file: No such file or directory`

Эту проблему также можно пофиксить без правки кода, запуская Decorator с выставленной
переменной окружения:
`LD_LIBRARY_PATH=/data/build/external/lib ./Decorator`

### TLDR
```sh
# Зависимости
apt update
apt install cmake build-essential python3 libboost-dev libssl-dev git libcurl4-openssl-dev libboost-system-dev gnutls-dev zlib1g-dev sendmail pkg-config libghc-gsasl-dev doxygen

# Сборка
export VMIME_SENDMAIL_PATH=/usr/sbin/sendmail
mkdir build
cd build
cmake ..
make -j8

# Запуск
cd /data/bin
./Whatever
LD_LIBRARY_PATH=/data/build/external/lib ./Decorator
```
