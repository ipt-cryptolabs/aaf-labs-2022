package Skovron_FI04_Ghilevsky_FI_03.main;

import Skovron_FI04_Ghilevsky_FI_03.main.Controller.View;
import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Row;
import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Table;

import java.util.Random;

public class Main {
    public static void demo() {
        Table table = new Table("student_info", "age", "avg_mark", "height");

        Random random = new Random();
        for(int i = 0; i < 10; i ++){
            Row row = new Row(random.nextInt(30), random.nextInt(100), random.nextInt(200));
            table.rowInsert(row);
        }

        table.selectAllAndPrint();
    }


    public static void main(String[] args) {
        View app = new View();

        app.run();
        // demo();

    }

    /*

     create student (age, weight);
     insert student (1, 2);

     */

}