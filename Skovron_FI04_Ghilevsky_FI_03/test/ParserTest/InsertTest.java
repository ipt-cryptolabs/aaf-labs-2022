package Skovron_FI04_Ghilevsky_FI_03.test.ParserTest;

import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Row;
import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.Insert;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;


/**
 * значення rowID може мінятись від + тестів
 */
public class InsertTest {
    @Test
    void regularInsertCase1Test(){
        Insert insert = new Insert("INSERT student (3, 175, 72);");

        Row row = new Row(3, 175, 72);

        Assertions.assertEquals("student", insert.getTableName());
        Assertions.assertEquals(row, insert.getRow());
    }

    @Test
    void regularInsertCase2Test(){
        Insert insert = new Insert("INSERT \"student id\" (11, 22, 333);");

        Assertions.assertEquals("\"student id\"", insert.getTableName());
        Assertions.assertEquals(new Row(11, 22, 333), insert.getRow());
    }

    @Test
    void regularInsertCase3Test(){
        Insert insert = new Insert("InsERT student (11, 22, 333);");

        Assertions.assertEquals("student", insert.getTableName());
        Assertions.assertEquals(new Row(11, 22, 333), insert.getRow());
    }

    @Test
    void regularInsertCase4Test(){
        Insert insert = new Insert("insert student (11, 22, 333);");

        Assertions.assertEquals("student", insert.getTableName());
        Assertions.assertEquals(new Row(11, 22, 333), insert.getRow());
    }

    @Test
    void NegativeAndWhiteSpaceValueTest(){
        String sql = "insert student ( 1,  2,  3);".trim(); // trim don't work, regex?
        System.out.println(sql);

        Insert insert1 = new Insert("insert student ( 1,  2,  3);");
        Insert insert2 = new Insert("insert student ( 1, -2,  3);");
        Insert insert3 = new Insert("insert student ( 1, -2, -3);");

        Insert insert4 = new Insert("insert student (-1,  2,  3);");
        Insert insert5 = new Insert("insert student (-1, -2,  3);");
        Insert insert6 = new Insert("insert student (-1, -2, -3);");

        Assertions.assertEquals("student", insert1.getTableName());

        Assertions.assertEquals(new Row(1,  2,  3), insert1.getRow());
        Assertions.assertEquals(new Row(1, -2,  3), insert2.getRow());
        Assertions.assertEquals(new Row(1, -2, -3), insert3.getRow());

        Assertions.assertEquals(new Row(-1,  2,  3), insert4.getRow());
        Assertions.assertEquals(new Row(-1, -2,  3), insert5.getRow());
        Assertions.assertEquals(new Row(-1, -2, -3), insert6.getRow());
    }

    @Test
    void emptyInsertCase1Test(){
        Exception exception = assertThrows(IllegalArgumentException.class, () -> new Insert("insert (3, 175, 72);"));
        String expectedMessage = "Error: Empty table name";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    void emptyInsertCase2Test(){
        Exception exception = assertThrows(IllegalArgumentException.class,  () -> new Insert("insert student ();"));

        String expectedMessage = "Error: Empty Column name (Insert)";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }
}