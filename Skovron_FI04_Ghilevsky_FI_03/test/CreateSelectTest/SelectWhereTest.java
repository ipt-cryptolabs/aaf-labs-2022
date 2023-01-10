package Skovron_FI04_Ghilevsky_FI_03.test.CreateSelectTest;

import Skovron_FI04_Ghilevsky_FI_03.main.Controller.SelectTable.CreateSelectTable;
import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Row;
import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Table;
import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.Select;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertThrows;

public class SelectWhereTest {
    @Test
    void findColNameTest(){
        Select select1 = new Select("select from student;"); //pass
        Table table = new Table("student", "age", "weight");
        table.rowInsert(new Row(1,2));
        table.rowInsert(new Row(2,3));
        table.rowInsert(new Row(3,4));

        CreateSelectTable createSelectTable = new CreateSelectTable(select1, table);

        assertThrows(IllegalArgumentException.class, () -> createSelectTable.findColName("student"));

        Assertions.assertEquals(0, createSelectTable.findColName("age"));
        Assertions.assertEquals(1, createSelectTable.findColName("weight"));

        assertThrows(IllegalArgumentException.class, () -> createSelectTable.findColName("height"));

    }

    @Test
    void manualCheckRowCompareCaseValueTest(){
        Select select1 = new Select("select from student;"); // pass
        Table table = new Table("student", "age", "weight");

        table.rowInsert(new Row(1,2));
        table.rowInsert(new Row(8,8));
        table.rowInsert(new Row(1,3));
        table.rowInsert(new Row(2,4));
        table.rowInsert(new Row(1,4));
        table.rowInsert(new Row(5,5));

        CreateSelectTable createSelectTable = new CreateSelectTable(select1, table);

        for (Row row : table.getRowArrayList())
            createSelectTable.rowCompare(row, "age", 1, createSelectTable.getOutTable());

        createSelectTable.getOutTable().selectAllAndPrint(); // 3 rows
    }

    @Test
    void manualCheckRowCompareCaseColumnTest(){
        Select select1 = new Select("select from student;"); // pass
        Table table = new Table("student", "age", "weight");

        table.rowInsert(new Row(1,2));
        table.rowInsert(new Row(8,8));
        table.rowInsert(new Row(1,3));
        table.rowInsert(new Row(2,4));
        table.rowInsert(new Row(1,4));
        table.rowInsert(new Row(5,5));

        CreateSelectTable createSelectTable = new CreateSelectTable(select1, table);

        for (Row row : table.getRowArrayList())
            createSelectTable.rowCompare(row, "age", "weight", createSelectTable.getOutTable());

        createSelectTable.getOutTable().selectAllAndPrint(); // 2 rows
    }
}
