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

        Row row = new Row("1", 3, 175, 72);

        Assertions.assertEquals("student", insert.getTableName());
        Assertions.assertEquals(row, insert.getRow());
    }

    @Test
    void regularInsertCase2Test(){
        Insert insert = new Insert("INSERT \"student id\" (11, 22, 333);");

        Row row = new Row("3", 11, 22, 333);

        Assertions.assertEquals("\"student id\"", insert.getTableName());
        Assertions.assertEquals(row, insert.getRow());
    }

    @Test
    void regularInsertCase3Test(){
        Insert insert = new Insert("InsERT student (11, 22, 333);");

        Row row = new Row("5", 11, 22, 333);

        Assertions.assertEquals("student", insert.getTableName());
        Assertions.assertEquals(row, insert.getRow());
    }

    @Test
    void regularInsertCase4Test(){
        Insert insert = new Insert("insert student (11, 22, 333);");

        Row row = new Row("7", 11, 22, 333);

        Assertions.assertEquals("student", insert.getTableName());
        Assertions.assertEquals(row, insert.getRow());
    }

    @Test
    void emptyInsertCase1Test(){
        Insert insert = new Insert("insert (3, 175, 72);");

        Exception exception = assertThrows(RuntimeException.class, insert::getTableName);
        String expectedMessage = "Error: Empty table name";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    void emptyInsertCase2Test(){
        Exception exception = assertThrows(RuntimeException.class,  () -> new Insert("insert student ();"));

        String expectedMessage = "Error: Invalid insert value (Insert)";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }
}