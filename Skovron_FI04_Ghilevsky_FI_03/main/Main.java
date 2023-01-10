package Skovron_FI04_Ghilevsky_FI_03.main;

import Skovron_FI04_Ghilevsky_FI_03.main.Controller.View;

public class Main {

    public static void main(String[] args) {
        View app = new View();

        app.run();

//        StringBuilder sb = new StringBuilder("abc;abc;");
//        System.out.println(sb.indexOf(";"));
//
//        if(sb.indexOf(";") > -1){
//            System.out.println(sb.delete(sb.indexOf(";"), sb.length()));
//        }

    }

    /*

        create student; (age, weight, height);

        create student (age, weight, height);
        /
        insert student (20, 100, 200);
        insert student (20, 100, 190);
        insert student (20, 90,  200);
        insert student (20, 200,  200);

        insert student (21, 100, 200);

        insert student (22, 100, 200);
        insert student (22, 200,  200);
        /
        select from student;
        select from student where age = 20;
        select from student where weight = height;

        select COUNT(age) from student group_by age;
        select COUNT(age), AVG(height), MAX(height) from student group_by age;
        select COUNT(age) from student where age = 20 group_by age;
        select COUNT(age) from student where weight = height group_by age;

        age  COUNT(weight)  AVG(height);
         22             2           178
         20             1           179

         select COUNT(id) from student where height = 170 group_by weight;
     */
}