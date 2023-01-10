package Skovron_FI04_Ghilevsky_FI_03.test.CreateSelectTest;

import Skovron_FI04_Ghilevsky_FI_03.main.Controller.SelectTable.CreateSelectTable;
import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Row;
import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Table;
import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.Select;
import org.junit.jupiter.api.Test;

import java.util.*;

public class SelectGroupByTest {

    /**
     * демо логіка "select ... group_by age" для однієї групуючої колонки
     */
    @Test
    void logicGroupByTest(){
        ArrayList<Row> primeRow = new ArrayList<>();

        primeRow.add(new Row(1,2,3));
        primeRow.add(new Row(3,4,5));
        primeRow.add(new Row(2,3,6));
        primeRow.add(new Row(4,4,5));
        primeRow.add(new Row(1,4,5));
        primeRow.add(new Row(3,5,6));
        primeRow.add(new Row(1,5,3));
        primeRow.add(new Row(2,3,4));
        primeRow.add(new Row(3,4,5));
        primeRow.add(new Row(4,5,3));
        primeRow.add(new Row(5,5,6));

        // 2-1, 2-2, 3-3, 1-4, 1-5, 2-6

        Table table = new Table("name", "age", "COUNT(age)", "AVG(age)", "MAX(age)");
        ArrayList<List<Row>> groupRow = new ArrayList<>();

        Set<Integer> set1 = new TreeSet<>();
        for (Row row : primeRow){
            set1.add(row.getRow()[0]);
        }

        int unique_size1 = set1.size();

        for (int i = 0; i < unique_size1; i++){
            ArrayList<Row> list = new ArrayList<>();
            groupRow.add(list);
        }

        int i = 0;
        for(Integer integer : set1){
            for (Row row : primeRow){
                if(integer == row.getRow()[0]){
                    groupRow.get(i).add(row);
                }
            }
            i++;
        }

        for (List<Row> rowList : groupRow){
            int[] cells = new int[table.getRowsName().length];

            int count = rowList.size();
            int max = 0;
            int avg = 0;

            for (Row row : rowList){
                max = Math.max(row.getRow()[0], max);
                avg += row.getRow()[0];

                System.out.println(row);
            }

            cells[0] = rowList.get(0).getRow()[0];
            cells[1] = count;
            cells[2] = avg / count;
            cells[3] = max;

            table.rowInsert(new Row(cells));
            System.out.println();
        }

        table.selectAllAndPrint();
    }

    @Test
    void test2() {
        CreateSelectTable createSelectTable;
        createSelectTable = new CreateSelectTable(
                new Select("select from student"),
                new Table("tableName", "age", "grade", "mark", "weight", "height"));
        ArrayList<Row> primeRow = new ArrayList<>();
        //colName: age, grade, mark, weight, height
        primeRow.add(new Row(20, 3, 75, 90, 200));
        primeRow.add(new Row(20, 3, 77, 90, 180));

        primeRow.add(new Row(21, 2, 80, 95, 195));

        primeRow.add(new Row(21, 3, 80, 95, 195));

        //SELECT COUNT(age) AVG(mark) MAX(mark) AVG(height) AVG(weight) MAX(height) FROM student GROUP_BY age, grade
        String[] rowsName = {"age", "grade", "COUNT(age)", "AVG(mark)", "MAX(mark)", "AVG(height)", "AVG(weight)", "MAX(height)"};
        String[] groupNames = {"age", "grade"};

        String[] aggCol = {"age", "mark", "mark", "height", "weight", "height"};
        String[] aggFun = {"COUNT", "AVG", "MAX", "AVG", "AVG", "MAX"};

        createSelectTable.doGroupBY(primeRow, rowsName, groupNames, aggCol, aggFun).selectAllAndPrint();

    }
}
