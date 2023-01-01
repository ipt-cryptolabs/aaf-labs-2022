"""
                        ---> Варіант 7 <---

1. CREATE table_name (column_name [INDEXED] [, ...]); - створення таблиці.
 - CREATE students (name, group);
 - CREATE cats (id INDEXED, name INDEXED, favourite_food);

2. INSERT [INTO] table_name (“value” [, ...]); - додавання нового рядка з даними до таблиці.
 - INSERT INTO cats ("1", "Murzik", "Sausages");
 - INSERT cats ("2", "Pushok", "Fish");

3. SELECT FROM table_name [WHERE condition]; - формування вибірки із таблиці table_name:

    condition := column_name operator "value"
    | (condition) AND (condition)
    | (condition) OR (condition)
    | operator  := ( = | < ).

 - SELECT FROM cats;
 - SELECT FROM cats WHERE (name < "Murzik") OR (name = "Pushok");

                +----+--------+----------------+
                | id |  name  | favourite_food |
                +----+--------+----------------+
                |  1 | Murzik |    Sausages    |
                |  2 | Pushok |      Fish      |
                +----+--------+----------------+

4. SAVE - зберігає нашу базу до файлу.
 - SAVE;

5. EXIT - вихід з програми (За стандартом зберігає базу перед виходом).
 - EXIT;

"""
import parser

if __name__ == '__main__':
    try:
        # Друк документації цього файлу
        print(__doc__)
        # Нескінченний цикл
        while True:
            # Наша змінна для команди
            command = ""
            # Наш чекпоінт яким показуємо то початок команди чи ні
            start = True
            # Нескінченний цикл
            while True:
                # Якщо так, то це початок команди
                if start:
                    # Вводимо нашу команду
                    temp_input = input(">>> ")
                    # Міняємо значення, бо далі введення не є початком
                    start = False
                else:
                    # Доповнення команди
                    temp_input = input("...  ")

                # Додаємо до нашої команди те що вводили
                command += temp_input + " "

                # Логіка виходу при наяві ;
                if ";" in temp_input:
                    # Вихід із циклу
                    break

            # Тут обробка нашої команди
            parser.parsing(command)
    # Тут ми ловимо вихід з клавіатури (ctrl + c)
    except KeyboardInterrupt:
        # Вихід із застосунку
        exit("Goodbye ;)")
