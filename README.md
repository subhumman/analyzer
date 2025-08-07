# File analyzer

Простой анализатор файлов с возможностью создания, переименования, изменения типа и удаления файлов. Все операции сохраняются в JSON файл для отслеживания истории.
(на данный момент функции анализа еще не добавлены, но в скором времени будут реализованы)
Такой же проект для порфтолио, как и остальные, но, просто ради интереса рекрутеров, я лично использую эту программу вместо того же touch. Да из принципа, но мне нравится.(Кстати тетрис точно такой же ```https:://github.com/subhumman/CDLLtet```

## Возможности

- **CREATE** - создание новых файлов
- **RENAME** - переименование файлов
- **CHTP** - изменение расширения файлов
- **REMOVE** - удаление файлов
- **HISTORY** - просмотр истории операций
- Автоматическое сохранение всех операций в JSON формате

## Сборка

### Требования
- CMake 3.14+
- C++17 совместимый компилятор
- Git (для загрузки зависимостей)

### Компиляция
```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

## Использование

Запускать через дефолт:
```bash
./analyzer
```
```powershell
.\analyzer.exe
```

### Список команд(не полный пока)

```
CREATE <filename>           - Создать новый файл
RENAME <old_name> <new_name> - Переименовать файл
CHTP <filename> <extension> - Изменить расширение файла
REMOVE <filename>           - Удалить файл
HISTORY                     - Показать историю операций
WRITE <filename> text("text" Тоже можно) - Записать
EXIT                        - Выйти из программы
```

### Пример

```
> CREATE test.txt
> File created successful

> CHTP test.txt md
> File successful type changed

> RENAME test.md document.md
> Renamed was successful!

> HISTORY
> Operations History:
>   [2024-01-15 10:30:00] CREATE - test.txt (success)
>   [2024-01-15 10:31:00] CHTP - test.txt -> test.md (success)
>   [2024-01-15 10:32:00] RENAME - test.md -> document.md (success)
```

## Структура

```
analyzer/
├── main.cpp                 # Главный файл программы
├── CMakeLists.txt          # Конфигурация сборки
├── scripts/
│   ├── lib/                # Заголовочки
│   │   ├── executor.hpp    # ЖЕСТОКИЙ ЭКЗЕКУТОР
│   │   ├── data_saver.hpp  # и так понятно
│   │   ├── lexer.hpp       # для парсинга команд
│   │   └── cli.hpp         # CLI интерфейс
│   └── src/                
│       ├── executor.cpp    
│       ├── data_saver.cpp  
│       ├── lexer.cpp       
│       └── cli.cpp         
└── cmake/
    └── CPM.cmake           # Менеджер зависимостей(если вы, возможно, не знаете что это такое - это оберта над FetchContent-ом(оффиц. штука внутри cmake для удобной установки зависимостей с гитхаба). Но, что важно, не всегда работает четко и приходится качать либы и линковать их(по крайней мере у меня так. Обычный find_package почему то не работает, но ведь всегда полезно прописать пути до .lib и include файлов, да?
```

## Зависимости

- **nlohmann/json** - для работы с JSON

## Сохранение данных

Все операции автоматически сохраняются в файл `operations.json` в формате:

```json
[
  {
    "timestamp": "2024-01-15 10:30:00",
    "operation": "CREATE",
    "filename": "test.txt",
    "status": "success"
  }
]
```





