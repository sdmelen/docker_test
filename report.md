## Part 1. Готовый докер

- ### Возьмём официальный докер-образ с **nginx** и выкачаем его при помощи `docker pull`.
![Alt text](images/1.png)
- ### Проверим наличие докер-образа через `docker images`.
![Alt text](images/2.png)
- ### Запустим докер-образ через `docker run -d [image_id|repository]`.
![Alt text](images/3.png)
- ### Проверим, что образ запустился через `docker ps`.
![Alt text](images/4.png)
- ### Посмотрим информацию о контейнере через `docker inspect [container_id|container_name]`.
![Alt text](images/5.png)
- ### По выводу команды определим размер контейнера:
![Alt text](images/6.png)
- ### список замапленных портов:
![Alt text](images/7.png)
- ### ip контейнера:
![Alt text](images/8.png)
- ### Остановим докер образ через `docker stop [container_id|container_name]`.
![Alt text](images/9.png)
- ### Проверим, что образ остановился через `docker ps`.
![Alt text](images/10.png)
- ### Запустим докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду *run*.
![Alt text](images/11.png)
- ### Проверяем, что в браузере по адресу *localhost:80* доступна стартовая страница **nginx**.
![Alt text](images/12.png)
- ### Перезапустим докер контейнер через `docker restart [container_id|container_name]`. Проверим, что контейнер запустился.
![Alt text](images/13.png)

## Part 2. Операции с контейнером

- ### Прочитем конфигурационный файл *nginx.conf* внутри докер контейнера через команду *exec*.
![Alt text](images/14.png)
- ### Создаем на локальной машине файл *nginx.conf*.
![Alt text](images/15.png)
- ### Настраиваем в нем по пути */status* отдачу страницы статуса сервера **nginx**.
![Alt text](images/16.png)
- ### Скопируй созданный файл *nginx.conf* внутрь докер-образа через команду `docker cp`.
![Alt text](images/17.png)
- ### Перезапустим **nginx** внутри докер-образа через команду *exec*.
![Alt text](images/18.png)
- ### Проверим, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**.
![Alt text](images/19.png)
- ### Экспортируем контейнер в файл *container.tar* через команду *export*.
![Alt text](images/20.png)
- ### Останавливаем контейнер.
![Alt text](images/21.png)
- ### Удаляем образ через `docker rmi [image_id|repository]`, не удаляя перед этим контейнеры.
![Alt text](images/22.png)
- ### Удаляем остановленный контейнер.
![Alt text](images/23.png)
- ### Импортируем контейнер обратно через команду *import*.
![Alt text](images/24.png)
- ### Запускаем импортированный контейнер.
![Alt text](images/25.png)
- ### Проверяем, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**.
![Alt text](images/26.png)

## Part 3. Мини веб-сервер


- ### Пишем мини-сервер на **C** и **FastCgi**, который будет возвращать простейшую страничку с надписью `Hello World!`.
![Alt text](images/3.1.png)
- ### Пишем свой *nginx.conf*, который будет проксировать все запросы с 81 порта на *127.0.0.1:8080*.
![Alt text](images/3.2.png)
 - ### Устанавливаем fcgi
`brew install fcgi`
![Alt text](images/3.3.png)
 - ### Запускаем докер
`docker run -d -p 81:81 nginx`
![Alt text](images/3.4.png)
<!-- `[перезапустить контейнер]` -->
 - ### Копируем файлы 
`docker cp nginx.conf [container_id|container_name]:/etc/nginx`\
`docker cp hello.c [container_id|container_name]:/home `
![Alt text](images/3.5.png)
 - ### Запускаем интерактивную сессию bash внутри контейнера
`docker exec -it [container_id|container_name] bash`
 - ### Устанавливаем gcc, spawn-fcgi, libfcgi-dev
`apt-get update `\
`apt-get install -y gcc spawn-fcgi libfcgi-dev`
![Alt text](images/3.6.png)
 - ### Компилируем
`gcc -o hello hello.c -lfcgi`
- ### Запускаем написанный мини-сервер через *spawn-fcgi* на порту 8080.
`spawn-fcgi -p 8080 ./hello`
![Alt text](images/3.7.png)
- ### Проверяем, что в браузере по *localhost:81* отдается написанная страничка.
![Alt text](images/3.8.png)

## Part 4. Свой докер

- ### Пишем свой докер образ
![Alt text](images/4.0.png)
![Alt text](images/4.00.png)
- ### Собираем написанный докер образ через docker build, при этом указав имя и тег
![Alt text](images/4.1.png)
- ### Проверяем через docker images, что все собралось корректно
![Alt text](images/4.2.png)
- ### Запускаем собранный докер образ с маппингом 81 порта на 80 на локальной машине и маппингом папки ./nginx внутрь контейнера по адресу, где лежат конфигурационные файлы nginx'а
`docker run -it -p 80:81 -v "$(pwd)/nginx.conf:/etc/nginx/nginx.conf" -d hello:s21 bash`
![Alt text](images/4.3.png)
![Alt text](images/4.4.png)
- ### Проверяем, что по localhost:80 доступна страничка написанного мини сервера
![Alt text](images/4.5.png)
- ### Дописываем в ./nginx/nginx.conf проксирование странички /status, по которой надо отдавать статус сервера nginx
![Alt text](images/4.6.png)
![Alt text](images/4.5-6.png)
- ### Перезапускаем контейнер
`docker restart [container_id|container_name]`
- ### Проверяем, что теперь по localhost:80/status отдается страничка со статусом nginx
![Alt text](images/4.7.png)

## Part 5. **Dockle**

- ### Запускаем контейнера, остановка и удаление образа
`docker start [container_id|container_name]`\
`docker stop [container id/name]`\
`docker rmi -f hello:s21`
- ### Устанавливаем dockle
`brew install goodwithtech/r/dockle`
- ### Создание образа и экспортирование его в .tar
`docker build -t hello:s21 .`\
`docker save hello:s21 -o hello.tar`
- ### Сканируем образ из предыдущего задания через `dockle [image_id|repository]`.
`dockle --input hello.tar `
![Alt text](images/5.0.png)
- ### Исправляем образ так, чтобы при проверке через **dockle** не было ошибок и предупреждений.
![Alt text](images/5.1.png)
![Alt text](images/5.2.png)

## Part 6. Базовый **Docker Compose**

- ### Пишем файл *docker-compose.yml*, который:
  - ### 1) Поднимает докер-контейнер из [Части 5]
  - ### 2) Поднимает докер-контейнер с **nginx**, который будет проксировать все запросы с 8080 порта на 81 порт первого контейнера.
![Alt text](images/6.0.png)
- ### Замапим 8080 порт второго контейнера на 80 порт локальной машины.
![Alt text](images/6.5.png)
- ### Остановим все запущенные контейнеры.
`docker stop [container id/name]`
- ### Собираем и запускаем проект с помощью команд `docker-compose build` и `docker-compose up`.
`docker compose build `   
![Alt text](images/6.1.png)
`docker compose up `
![Alt text](images/6.2.png)
`docker compose down`
![Alt text](images/6.3.png)
- ### Проверяем, что в браузере по *localhost:80* отдается написанная страничка, как и ранее.
![Alt text](images/6.4.png)
