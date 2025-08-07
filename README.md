# File analyzer

Простой анализатор файлов с возможностью создания, переименования, изменения типа и удаления файлов. Все операции сохраняются в JSON файл для отслеживания истории.
(на данный момент функции анализа еще не добавлены, но в скором времени будут реализованы)
Такой же проект для порфтолио, как и остальные, но, просто ради интереса рекрутеров, я лично использую эту программу вместо того же touch. Да из принципа, но мне нравится.(Кстати тетрис точно такой же https:://github.com/subhumman/CDLLtet

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
mkdir build
cd build
cmake ..
cmake --build .
```

## Использование

Запустите программу:
```bash
./analyzer
```
```powershell
.\analyzer.exe
```

### Доступные команды

```
CREATE <filename>           - Создать новый файл
RENAME <old_name> <new_name> - Переименовать файл
CHTP <filename> <extension> - Изменить расширение файла
REMOVE <filename>           - Удалить файл
HISTORY                     - Показать историю операций
WRITE <filename> text("text" Тоже можно) - Записать
EXIT                        - Выйти из программы
```

### Примеры

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

## Структура проекта

```
analyzer/
├── main.cpp                 # Главный файл программы
├── CMakeLists.txt          # Конфигурация сборки
├── scripts/
│   ├── lib/                # Заголовочные файлы
│   │   ├── executor.hpp    # Класс для выполнения команд
│   │   ├── data_saver.hpp  # Класс для сохранения данных
│   │   ├── lexer.hpp       # Класс для парсинга команд
│   │   └── cli.hpp         # CLI интерфейс
│   └── src/                # Исходные файлы
│       ├── executor.cpp    # Реализация executor
│       ├── data_saver.cpp  # Реализация data_saver
│       ├── lexer.cpp       # Реализация lexer
│       └── cli.cpp         # Реализация CLI
└── cmake/
    └── CPM.cmake           # Менеджер зависимостей
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



