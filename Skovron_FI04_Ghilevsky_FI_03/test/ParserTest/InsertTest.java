package Skovron_FI04_Ghilevsky_FI_03.test.ParserTest;

import Skovron_FI04_Ghilevsky_FI_03.main.DataBase.Row;
import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.Insert;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class InsertTest {
    @Test
    void regularInsertCase1Test(){
        Insert insert = new Insert("INSERT student (3, 175, 72);");

        Assertions.assertEquals("student", insert.getTableName());
        Assertions.assertTrue(new Row(3, 175, 72).equals(insert.getRow()));
    }

    @Test
    void regularInsertCase2Test(){
        Insert insert = new Insert("INSERT \"student id\" (11, 222, 333);");

        Assertions.assertEquals("student id", insert.getTableName());
        Assertions.assertTrue(new Row(11, 222, 333).equals(insert.getRow()));
    }

    @Test
    void regularInsertCase3Test(){
        Insert insert = new Insert("InsERT student (3, 175, 72);");

        Assertions.assertEquals("student", insert.getTableName());
        Assertions.assertTrue(new Row(3, 175, 72).equals(insert.getRow()));
    }

    @Test
    void regularInsertCase4Test(){
        Insert insert = new Insert("insert student (3, 175, 72);");

        Assertions.assertEquals("student", insert.getTableName());
        Assertions.assertTrue(new Row(3, 175, 72).equals(insert.getRow()));
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
        Insert insert = new Insert("insert student ();");

        Exception exception = assertThrows(RuntimeException.class, insert::getRow);
        String expectedMessage = "Error: Empty row value";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }
}