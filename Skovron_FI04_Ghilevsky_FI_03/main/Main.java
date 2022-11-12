package Skovron_FI04_Ghilevsky_FI_03.main;

import Skovron_FI04_Ghilevsky_FI_03.main.Controller.View;


public class Main {

    public static void main(String[] args) {
        View app = new View();

        app.run();
    }

    /*

        create student (age, weight, height);
        insert student (1, 2, 3);
        insert student (1, 4, 5);
        select from student;
        select from student where age = 1;
        select from student where weight = height;

        select COUNT(weight), AVG(height) from student group_by age;

        age  COUNT(weight)  AVG(height);
         22             2           178
         20             1           179

         select COUNT(id) from student where height = 170 group_by weight;
     */
}