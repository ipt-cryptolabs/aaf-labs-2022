package Skovron_FI04_Ghilevsky_FI_03.test.ParserTest;

import Skovron_FI04_Ghilevsky_FI_03.main.Parser.Query.Select;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class SelectTest {
    @Test
    void regularSelectCase1Test(){
        Select select = new Select("SELECT FROM students");
        Assertions.assertEquals("students", select.getTableName());
    }

    @Test
    void regularSelectCase2Test(){
        Select select = new Select("SELECT FRO students");

        Exception exception = assertThrows(RuntimeException.class, select::getTableName);
        String expectedMessage = "Error: Invalid slq syntax (Select)";
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    void regularSelectCase3Test(){
        Select select = new Select("SELECT FROM ");

        Exception exception = assertThrows(RuntimeException.class, select::getTableName);
        String expectedMessage = "Error: Empty table name (Select)"; // or
        String actualMessage = exception.getMessage();

        assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    void isSelectAllTest(){
        Select select = new Select("SELECT FROM students");
        Assertions.assertTrue(select.isSelectAll());
    }

}
